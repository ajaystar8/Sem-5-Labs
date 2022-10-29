#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

int n;

void *nonNegativeSum(void *param)
{
    int *arr = (int *)param;
    int sum = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] > 0)
            sum += arr[i];
    return (void *)sum;
}

int main()
{
    printf("Enter value of n: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    pthread_t thread;
    int sum;
    pthread_create(&thread, 0, &nonNegativeSum, (void *)arr);
    pthread_join(thread, (void **)&sum);
    printf("The sum of all non-negative nums is: %d\n", sum);

    return 0;
}