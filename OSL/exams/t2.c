#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int n;

void *even(void *arr)
{
    int *nums = (int *)arr;
    int evenSum = 0;
    for (int i = 0; i < n; i += 2)
        evenSum += nums[i];
    return (void *)evenSum;
}

void *odd(void *arr)
{
    int *nums = (int *)arr;
    int oddSum = 0;
    for (int i = 1; i < n; i += 2)
        oddSum += nums[i];
    return (void *)oddSum;
}

int main()
{
    pthread_t threads[2];
    int oddSum, evenSum;
    printf("Enter n: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter numbers: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pthread_create(&threads[0], NULL, &even, (void *)arr);
    pthread_create(&threads[1], NULL, &odd, (void *)arr);

    pthread_join(threads[0], (void **)&evenSum);
    pthread_join(threads[1], (void **)&oddSum);

    printf("OddSum: %d\nEvenSum: %d\n ", oddSum, evenSum);

    return 0;
}