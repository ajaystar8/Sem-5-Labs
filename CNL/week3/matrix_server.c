#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORTNO 5001

int main()
{
    int sd;
    int arr[100];
    struct sockaddr_in sadd, cadd;

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = inet_addr("127.0.0.1");
    sadd.sin_port = htons(PORTNO);

    int result = bind(sd, (struct suckaddr *)&sadd, sizeof(sadd));
    int len = sizeof(sadd);

    int m = recvfrom(sd, arr, sizeof(arr), 0, (struct sockaddr *)&sadd, &len);
    printf("the server send is\n");

    // int size = arr[];
    int row = arr[0], col = arr[1];
    int size = (row * col) + 2;
    int z = 0;
    for (int i = 2; i < size; i++)
    {
        if (z == col)
        {
            printf("\n");
            z = 0;
        }
        printf("%d ", arr[i]);
        z++;
    }

    return 0;
}