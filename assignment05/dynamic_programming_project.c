#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int fibonacci(int n) {
    int f[n + 2];

    f[0] = 0;
    f[1] = 1;

    if (n <= 1) {
        return 1;
    }
    for (int i = 2; i < n + 1; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    return f[n];
}


#define NUM_MATRICES 3

int count = 0;

void print_optimal_parens(int **s, int i, int j, int *order) {

    if (i == j) {
        printf("M%d ", i);
        order[count] = i;
        count++;
    } else {
        printf("( ");
        order[count] = -1;
        count++;
        print_optimal_parens(s, i, s[i][j], order);
        print_optimal_parens(s, s[i][j] + 1, j, order);
        printf(")");
        order[count] = 0;
        count++;
    }
}
void matrix_chain_order(int *dimension, int *order) {

    int m[NUM_MATRICES + 1][NUM_MATRICES + 1] = {0};
    int **s;
    s = (int **) malloc(sizeof(int *) * NUM_MATRICES + 1);
    for (int i = 0; i < NUM_MATRICES + 1; i++) {
        s[i] = (int *) malloc(sizeof(int) * NUM_MATRICES + 1);
    }

    for (int i = 1; i < NUM_MATRICES + 1; i++) {
        m[i][i] = 0;
    }
    for (int l = 2; l < NUM_MATRICES + 1; l++) {
        for (int i = 1; i < NUM_MATRICES - l + 2; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + dimension[i - 1] * dimension[k] * dimension[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Matrix M: \n");
    printf(" ---------------------------\n");
    printf("| M |   1   |   2   |   3   |\n");
    printf("|---|-------|-------|-------|\n");
    for (int i = 1; i < NUM_MATRICES + 1; i ++) {
        printf("| %d |", i);
        for (int j = 1; j < NUM_MATRICES + 1; j ++) {
            printf("  %3d  |",m[i][j]);
        }
        printf("\n");
    }
    printf(" ---------------------------\n");
    printf("Minimum Multiplication: %d\n\n", m[1][NUM_MATRICES]);

    printf("Matrix S: \n");
    printf(" ---------------------\n");
    printf("| M |  1  |  2  |  3  |\n");
    printf("|---|-----|-----|-----|\n");
    for (int i = 1; i < NUM_MATRICES + 1; i ++) {
        printf("| %d |", i);
        for (int j = 1; j < NUM_MATRICES + 1; j ++) {
            printf("  %d  |",s[i][j]);
        }
        printf("\n");
    }
    printf(" ---------------------\n");

    printf("Optimal Matrix Chain Multiplication Order: ");
    print_optimal_parens(s, 1, 3, order);
    printf("\n\n");
}
void matrix_mult(int **matrix1, int **matrix2, int **result, int dimension0, int dimension1, int dimension2) {

    for (int i = 0; i < dimension0; i++) {
        for (int j = 0; j < dimension2; j++) {
            result[i][j] = 0;
        }
    }
    for (int i = 0; i < dimension0; i++) {
        for (int j = 0; j < dimension2; j++) {
            for (int k = 0; k < dimension1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}
void matrix_chain_mult(int *dimension, int **mult_result) {

    // Calculate the optimal order of the multiplication
    int order[NUM_MATRICES * 2 + 1] = {0};
    matrix_chain_order(dimension, order);

    // Generate three input matrices containing randomly positive integers (1 ~ 9)
    srand(time(NULL));

    printf("Input Matrix %dX%d:\n", dimension[0], dimension[1]);
    int **matrix_0;
    matrix_0 = (int **) malloc(sizeof(int *) * dimension[0]);
    for (int i = 0; i < dimension[0]; i++) {
        matrix_0[i] = (int *) malloc(sizeof(int) * dimension[1]);
    }
    for (int i = 0; i < dimension[0]; i++) {
        for (int j = 0; j < dimension[1]; j++) {
            matrix_0[i][j] = rand() % 9 + 1;
            printf("%2d ", matrix_0[i][j]);
        }
        printf("\n");
    }
    printf("Input Matrix %dX%d:\n", dimension[1], dimension[2]);
    int **matrix_1;
    matrix_1 = (int **) malloc(sizeof(int *) * dimension[1]);
    for (int i = 0; i < dimension[1]; i++) {
        matrix_1[i] = (int *) malloc(sizeof(int) * dimension[2]);
    }
    for (int i = 0; i < dimension[1]; i++) {
        for (int j = 0; j < dimension[2]; j++) {
            matrix_1[i][j] = rand() % 9 + 1;
            printf("%2d ", matrix_1[i][j]);
        }
        printf("\n");
    }
    printf("Input Matrix %dX%d:\n", dimension[2], dimension[3]);
    int **matrix_2;
    matrix_2 = (int **) malloc(sizeof(int *) * dimension[2]);
    for (int i = 0; i < dimension[2]; i++) {
        matrix_2[i] = (int *) malloc(sizeof(int) * dimension[3]);
    }
    for (int i = 0; i < dimension[2]; i++) {
        for (int j = 0; j < dimension[3]; j++) {
            matrix_2[i][j] = rand() % 9 + 1;
            printf("%2d ", matrix_2[i][j]);
        }
        printf("\n");
    }

    // Matrix Chain Multiplication
    if (order[2] == -1) {
        int **mult_sub_result;
        mult_sub_result = (int **) malloc(sizeof(int *) * dimension[1]);
        for (int i = 0; i < dimension[1]; i++) {
            mult_sub_result[i] = (int *) malloc(sizeof(int) * dimension[3]);
        }
        matrix_mult(matrix_1, matrix_2, mult_sub_result, dimension[1], dimension[2], dimension[3]);
        matrix_mult(matrix_0, mult_sub_result, mult_result, dimension[0], dimension[1], dimension[3]);
    } else {
        int **mult_sub_result;
        mult_sub_result = (int **) malloc(sizeof(int *) * dimension[0]);
        for (int i = 0; i < dimension[0]; i++) {
            mult_sub_result[i] = (int *) malloc(sizeof(int) * dimension[2]);
        }
        matrix_mult(matrix_0, matrix_1, mult_sub_result, dimension[0], dimension[1], dimension[2]);
        matrix_mult(mult_sub_result, matrix_2, mult_result, dimension[0], dimension[2], dimension[3]);
    }
}

int main() {

    // Exercise 01: Algorithm of Fibonacci numbers using dynamic programming
    printf("-------------------------------------------------------\n");
    printf("      FIBONACCI NUMBER USING DYNAMIC PROGRAMMING\n");
    printf("-------------------------------------------------------\n");
    printf(" 5-th fibonacci number: %d \n", fibonacci(5));
    printf("10-th fibonacci number: %d \n", fibonacci(10));


    // Exercise 02: Matrix-chain multiplication algorithm using dynamic programming
    printf("-------------------------------------------------------\n");
    printf(" MATRIX-CHAIN MULTIPLICATION USING DYNAMIC PROGRAMMING\n");
    printf("-------------------------------------------------------\n");

    int dimension[NUM_MATRICES + 1] = {5, 3, 7, 10};
    int **mult_result;
    mult_result = (int **) malloc(sizeof(int *) * dimension[0]);
    for (int i = 0; i < dimension[0]; i++) {
        mult_result[i] = (int *) malloc(sizeof(int) * dimension[3]);
    }

    matrix_chain_mult(dimension, mult_result);
    printf("Matrix Chain Multiplication Result, Matrix %dX%d:\n", dimension[0], dimension[3]);
    for (int i = 0; i < dimension[0]; i++) {
        for (int j = 0; j < dimension[3]; j++) {
            printf("%4d ", mult_result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
