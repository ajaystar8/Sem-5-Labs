#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORTNO 10201

int server_fd, new_socket, addrlen, valread;
struct sockaddr_in address;
char buffer[1024] = {0};
char *msg;

void CreateServerSocket()
{
    // create a welcome socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    addrlen = sizeof(address);
}

void PerformServerTask()
{
    // bind the welcome socket to the local protocol address
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // make welcome socket wait for a client request;
    listen(server_fd, 5);

    while (1)
    {
        // when client wants to establish connection
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        if (fork() == 0)
        {
            // time function
            struct tm *newtime;
            time_t ltime;
            time(&ltime);
            newtime = localtime(&ltime);
            msg = asctime(newtime);
            // till here --> code snippet from ibm docs

            // send the time obtained, to the client
            send(new_socket, msg, strlen(msg), 0);

            printf("Current Date and Time sent.\n");
        }
        else
            close(new_socket);
    }
}

int main()
{
    CreateServerSocket();

    printf("Server Waiting...\n");

    PerformServerTask();

    // closing the new socket created
    close(new_socket);

    // closing the welcoming socket
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}