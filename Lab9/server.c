#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr, caddr;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_family = AF_INET;
    int pno = atoi(argv[1]);
    saddr.sin_port = htons(pno);
    int len = sizeof(saddr);
    if(bind(fd, (const struct sockaddr*)&saddr, len) < 0)
    {
        printf("Bind Failed\n");
        close(fd);
        exit(-1);
    }
    listen(fd, 10);
    char buffer[255];
    int pid;
    int clients = 0;
    while(1)
    {
        int id = accept(fd, (struct sockaddr*)&saddr, &len);
        clients++;
        printf("Client Count: %d\n", clients);
        pid = fork();
        if(pid == 0)
        {
            buffer[recv(id, buffer, sizeof(buffer), 0)] = '\0';
            printf("Client: %s\n", buffer);
            printf("Child: ");
            scanf(" %s", buffer);
            send(id, buffer, strlen(buffer), 0);
        }
        else if(pid > 0)
        {
            printf("I am Parent\n");
            close(id);
        }
    }
    return 0;
}