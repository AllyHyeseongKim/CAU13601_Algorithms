#include <stdio.h>


int fibonacci(int n) {
    int f[n + 2];

    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i < n + 1; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    return f[n];
}

int main() {
    printf("-------------------------------------------------------\n");
    printf("      FIBONACCI NUMBER USING DYNAMIC PROGRAMMING\n");
    printf("-------------------------------------------------------\n");
    printf(" 5-th fibonacci number: %d \n", fibonacci(5));
    printf("10-th fibonacci number: %d \n", fibonacci(10));
    printf("-------------------------------------------------------\n");
    printf(" MATRIX-CHAIN MULTIPLICATION USING DYNAMIC PROGRAMMING\n");
    printf("-------------------------------------------------------\n");
    return 0;
}
