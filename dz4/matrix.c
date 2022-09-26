#include <stdio.h>
#include <stdlib.h>

// allocates memory for the matrix
double **mkMat(int M, int N);

//releases the memory reserved for the matrix
void freeMat(double **A, int M);

//outputs a matrix
void outMat(double **A, int M, int N);

//makes a copy of the matrix
double **cpMat(double **A, int M, int N);

//transposes the matrix
double **transM(double **A, int M, int N)
{
    double **at = mkMat(N, M);
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            at[i][j] = A[j][i];
        }
    }
    return at;
}

//finds the inverse matrix
double **invertM(double **A, int M)
{
    double **ainv = mkMat(M, M), **cA = cpMat(A, M, M);
    for (int i = 0; i < M; ++i){
        for (int j = 0; j < M; ++j){
            if (i == j){
                ainv[i][j] = 1.0;
            } else{
                ainv[i][j] = 0.0;
            }
        }
    }
    int k;
    for (int i = 0; i < M; ++i){
        k = 0;
        if (cA[i][i] == 0){
            while ((i + k < M) && (cA[i][i+k] == 0)){
                k++;
            }
            if ((i + k) == M){
                k = -1;
                break;
            }
            double *buff = A[i];
            cA[i] = cA[i+k];
            cA[i+k] = buff;
            buff = ainv[i];
            ainv[i] = ainv[i+k];
            ainv[i+k] = buff;
            --i;
            continue;
        }
        for (int j = i + 1; j < M; ++j){
            for (k = M-1; k >= i; --k){
                ainv[i][k] /=  cA[i][i];
                cA[i][k] /= cA[i][i];
             }
           if (cA[j][i] == 0){
                continue;
            }
            for(k = M-1; k >= i; --k){
                cA[j][k] -= cA[i][k] * cA[j][i];
                ainv[j][k] -= ainv[i][k] * cA[j][i];
            }
        }
    }
    ainv[M-1][M-1] /= cA[M-1][M-1];
    cA[M-1][M-1] = 1;
    if (k == -1){
       return -1;
    }
    for (int i = M - 1; i > 0; --i){
        for (int j = i - 1; j >= 0; --j){
            ainv[j][i] -= ainv[i][i] * cA[j][i];
        }
    }
    freeMat(cA, M);
    return ainv;
}

double **mkMat(int M, int N)
{
    double **Mat = (double**) malloc(sizeof (double*) * M);
    for (int i = 0; i < M; ++i) {
        Mat[i] = (double*) malloc(sizeof(double) * N);
    }
    return Mat;
}

//reads the matrix from the keyboard
void scanMat(double **A, int M, int N)
{
    for (int i = 0; i < M; ++i){
        for (int j = 0; j < N; ++j){
            scanf("%lf", &A[i][j]);
        } 
    }
}

double **cpMat(double **A, int M, int N)
{
    double **cpA = mkMat(M, N);
    for (int i = 0; i < M; ++i){
        for (int j = 0; j < N; ++j){
            cpA[i][j] = A[i][j];
        }
    }
    return cpA;
}

//fils the matrix with random numbers
void randMat(double **A, int M, int N)
{
    int ran = 99999;
    for (int i = 0; i < M; ++i){
        for (int j = 0; j < N; ++j){
            A[i][i] = (rand() % ran - (ran / 2)) / 1000;
        }
    }
}

void outMat(double **A, int M, int N)
{
    printf("\n");
    for (int i = 0; i < M; ++i){
        for (int j = 0; j < N; ++j){
            printf("%5.2lf ", A[i][j]);
        }
        printf("\n");
    }
}

void freeMat(double **A, int M)
{
    for (int i = 0; i < M; ++i){
        free(A[i]);
    }
    free(A);
}

int main(void)
{
    int M, N;
    printf("enter matrix dementions\n");
    scanf("%d%d", &M, &N);
    printf("\n");
    double **A = mkMat(M, N);
//    scanMat(A, M, N);
    randMat(A, M, N);
    outMat(A, M, N);
    printf("\n");
//    double **at = transM(A, M, N);
    double **at = invertM(A, M);
    if (at == -1){
        printf("matrix is degenerate\n");
        return 0;
    }
    outMat(at, M, N);
    freeMat(A, M);
    freeMat(at, M);
    return 0;
}
