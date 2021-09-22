#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1024);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int len = sizeof(saddr);
    if(bind(fd, (const struct sockaddr*)&saddr, len) < 0)
    {
        printf("Bind Failed\n");
        close(fd);
        exit(-1);
    }
    listen(fd, 3);
    int id = accept(fd, (struct sockaddr*)&caddr, &len);
    char buffer[255];
    int n = recv(id, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';
    printf("Client: %s\n", buffer);
    printf("Server: ");
    scanf("%c[^\n]", buffer);
    send(id, buffer, strlen(buffer), 0);
    return 0;
}