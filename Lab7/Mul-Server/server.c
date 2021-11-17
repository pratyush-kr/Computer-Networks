#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int pno = atoi(argv[1]);
    printf("Pno: %d\n", pno);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(pno);
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
    while(1)
    {
        int n = recv(id, buffer, sizeof(buffer), 0);
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);
        printf("Server: ");
        scanf("%[^\n]%*c", buffer);
        send(id, buffer, strlen(buffer), 0);
    }
    close(fd);
    return 0;
}