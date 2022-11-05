#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

int n;

void *sumEven(void *param)
{
    int *arr = (int *)param;
    int evenSum = 0;
    for (int i = 0; i < n; i++)
        if (!(arr[i] % 2))
            evenSum += arr[i];
    // printf("%d\n", evenSum);
    return (void *)evenSum;
}

void *sumOdd(void *param)
{
    int *arr = (int *)param;
    int oddSum = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] % 2)
            oddSum += arr[i];
    return (void *)oddSum;
}

int main()
{
    printf("Enter value of n: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int eSum, oSum;

    pthread_t thread[2];

    pthread_create(&thread[0], 0, &sumEven, (void *)arr);
    pthread_create(&thread[1], 0, &sumOdd, (void *)arr);

    pthread_join(thread[1], (void **)&oSum);
    pthread_join(thread[0], (void **)&eSum);

    printf("Even Sum: %d\n", eSum);
    printf("Odd Sum: %d\n", oSum);

    return 0;
}