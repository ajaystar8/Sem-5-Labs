#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

int n;

void *fibo(void *arr)
{
    int *nums = (int *)arr;
    nums[0] = 0;
    nums[1] = 1;
    for (int i = 2; i < n; i++)
        nums[i] = nums[i - 1] + nums[i - 2];
    return (void *)arr;
}

int main()
{
    pthread_t thread;
    printf("Enter n: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    pthread_create(&thread, NULL, &fibo, (void *)arr);
    pthread_join(thread, (void **)&arr);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}