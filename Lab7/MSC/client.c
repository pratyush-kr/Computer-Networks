#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main()
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1024);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int len = sizeof(saddr);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    connect(fd, (struct sockaddr*)&saddr, len);
    printf("Client: ");
    char buffer[255];
    scanf(" %c[^\n]", buffer);
    send(fd, buffer, strlen(buffer), 0);
    int n = recv(fd, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';
    printf("Server: %s\n", buffer);
    close(fd);
    return 0;
}