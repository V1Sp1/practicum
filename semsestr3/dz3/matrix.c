#include <stdio.h>
#include <stdlib.h>

#define M 3
#define N 2
#define K 2
void vecMultiply(unsigned m, unsigned n, unsigned k, int a[][n], int b[][k], int c[][k])
{
    for (unsigned i = 0; i < m; ++i){
        for (unsigned j = 0; j < k; ++j){
            c[i][j] = 0;
            for (unsigned l = 0; l < n; ++l){
                c[i][j] += a[i][l] * b[l][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    printf("enter the first matrix\n");
    int m = atoi(argv[1]), n = atoi(argv[2]), k = atoi(argv[3]);
    int a[m][n], b[n][k], c[m][k];
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            scanf("%d", &a[i][j]);
        }
    }
    printf("enter the second matrix\n");
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < k; ++j){
            scanf("%d", & b[i][j]);
        }
    }
    printf("result of multiply\n");
    vecMultiply( M, N, K, a, b, c);
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < k; ++j){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
