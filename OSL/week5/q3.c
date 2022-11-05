#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

void *primeNosArray(void *param)
{
    int *arr = (int *)param;
    int n1 = arr[0];
    int n2 = arr[1];
    for (int i = n1; i <= n2; i++)
    {
        int flag = 1;
        for (int j = 2; j < i; j++)
        {
            if (!(i % j))
            {
                flag = 0;
                break;
            }
        }
        if (flag)
            printf("%d ", i);
    }
    return NULL;
}

int main()
{
    int arr[2];

    printf("Enter n1: ");
    scanf("%d", &arr[0]);

    printf("Enter n2: ");
    scanf("%d", &arr[1]);
    
    pthread_t thread;
    pthread_create(&thread, 0, &primeNosArray, (void *)arr);
    pthread_join(thread, 0);

    return 0;
}