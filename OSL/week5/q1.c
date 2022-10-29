#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

int n;

void *fibo(void *param)
{
    int *arr = (int *)param;
    arr[0] = 0;
    arr[1] = 1;
    for (int i = 2; i < n; i++)
        arr[i] = arr[i - 1] + arr[i - 2];
    return NULL;
}

int main()
{
    pthread_t thread;
    printf("Enter n: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    pthread_create(&thread, 0, fibo, (void *)arr);
    pthread_join(thread, 0);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}