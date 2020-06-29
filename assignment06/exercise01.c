#include <stdio.h>
#include <stdlib.h>

#define UP 0
#define LEFT 1
#define CROSS 2

int LCS_print(int **b, char *X, int i, int j)
{
    if (i == 0 || j == 0)
    {
        return 0;
    }
    if (b[i][j] == CROSS)
    {
        LCS_print(b, X, i - 1, j - 1);
        printf("%c ", X[i - 1]);
    }
    else if (b[i][j] == UP)
    {
        LCS_print(b, X, i - 1, j);
    }
    else
    {
        LCS_print(b, X, i, j - 1);
    }
    return 1;
}

void LCS_length(char *X, char *Y, int m, int n)
{
    int c[m + 1][n + 1];

    int **b = malloc(sizeof(int *) * (m + 1));
    for (int i = 0; i < m + 1; i++)
    {
        b[i] = malloc(sizeof(int) * (n + 1));
    }
    for (int i = 0; i < m + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            b[i][j] = 0;
        }
    }

    for (int i = 1; i < m + 1; i++)
    {
        c[i][0] = 0;
    }
    for (int j = 0; j < n + 1; j++)
    {
        c[0][j] = 0;
    }
    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = CROSS;
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                b[i][j] = UP;
            }
            else
            {
                c[i][j] = c[i][j - 1];
                b[i][j] = LEFT;
            }
        }
    }

    printf("LCS: ");
    LCS_print(b, X, m, n);
    printf("\n");

    free(b);
}

int main(void)
{
    char X[7] = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
    char Y[6] = {'B', 'D', 'C', 'A', 'B', 'A'};

    int m = sizeof(X) / sizeof(X[0]);
    int n = sizeof(Y) / sizeof(Y[0]);

    LCS_length(X, Y, m, n);

    return 0;
}