#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORTNO 10201
 
int main()
{
    int server_fd, new_socket, addrlen, valread;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // create a welcome socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    addrlen = sizeof(address);

    // bind the welcome socket to the local protocol address
    bind(server_fd, (struct sockaddr *)&address, addrlen);

    // make welcome socket wait for a client request;
    printf("Server Waiting....\n");
    listen(server_fd, 5);

    // when client wants to establish connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent.\n");

    // closing the new socket created
    close(new_socket);

    // closing the welcoming socket
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}