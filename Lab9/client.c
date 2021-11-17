#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_family = AF_INET;
    int pno = atoi(argv[1]);
    saddr.sin_port = htons(pno);
    int len = sizeof(saddr);
    connect(fd, (struct sockaddr*)&saddr, len);
    while(1)
    {
        printf("Client: ");
        char buffer[255];
        scanf(" %s", buffer);
        send(fd, buffer, strlen(buffer), 0);
        buffer[recv(fd, buffer, sizeof(buffer), 0)] = '\0';
        printf("Server: %s\n", buffer);
    }
    close(fd);
    return 0;
}