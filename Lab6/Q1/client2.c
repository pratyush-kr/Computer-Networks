#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8081);
    int len = sizeof(saddr);
    connect(fd, (struct sockaddr*)&saddr, len);
    printf("Client: ");
    int num = 0;
    scanf(" %d", &num);
    send(fd, &num, sizeof(num), 0);
    recv(fd, &num, sizeof(num), 0);
    printf("sum: %d\n", num);
    close(fd);
    return 0;
}