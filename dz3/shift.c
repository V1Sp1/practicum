/*
                Task:
Write a function? that shifts an array
by a number entered by the user.
*/
#include <stdio.h>

#define len sizeof(a) / sizeof(*a)

void shiftArray(int arr[], int N, int M)
{
    M %= N;
    if (M == 0){
        return;
    } else if (M < 0){
        M += N;
    }
    int i = 0, r = 0, pred = arr[0], suc = arr[0];
    for (int changes = 0; changes < N; ++changes){
        i = (i + M) % N;
        if (i == r){
            arr[i] = pred;
            r++;
            i++;
            pred = arr[i];
        }
        suc = arr[i];
        arr[i] = pred;
        pred = suc;
    }
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, M;
    scanf("%d", &M);
    shiftArray( a, len, M);
    for (int i = 0; i < len; ++i){
        printf ("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
