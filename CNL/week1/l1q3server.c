#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORTNO 10201

int server_fd, addrlen, new_socket, valread;
struct sockaddr_in address;
char buffer[1024] = {0};


void CreateServerSocket(){
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    addrlen = sizeof(address);
}

void PerformServerTask(){
    bind(server_fd, (struct sockaddr *)&address, addrlen);

    printf("Server Waiting...\n");

    listen(server_fd, 5);

    memset(buffer, 0, sizeof(buffer));

    // client socket address is stored in the same address structure
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    char *ip_add = inet_ntoa(address.sin_addr);
    int port = address.sin_port;
    printf("Client ip:%s Client port:%d \n", ip_add, port);

    if (new_socket)
        printf("Connection accpeted.\n");

    valread = read(new_socket, buffer, 1024);

    printf("Message received from client.\n");
    for (int i = 0; buffer[i] != '\0'; i++)
        buffer[i] -= 32;

    send(new_socket, buffer, sizeof(buffer), 0);

    printf("Message sent back. \n");

    memset(buffer, 0, sizeof(buffer));
}

int main()
{
    CreateServerSocket();
    PerformServerTask();
    close(new_socket);
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}