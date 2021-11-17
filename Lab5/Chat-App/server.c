#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1026);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        printf("Building socket failed\n");
        exit(-1);
    }
    printf("Socket Creation Sucessfull\n");
    if(bind(fd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0)
    {
        printf("Binding failed\n");
        exit(-1);
    }
    printf("Bind Sucessfull\n");
    if(listen(fd, 5) != 0)
    {
        printf("Listen Failed\n");
        exit(-1);
    }
    printf("Server Listening\n");
    int len = sizeof(caddr);
    char cbuffer[255];
    char sbuffer[255];
    int aid[2];
    printf("Accepted\n");
    while(1)
    {
        aid[0] = accept(fd, (struct sockaddr*)&caddr, &len);
        aid[1] = accept(fd, (struct sockaddr*)&caddr, &len);
        int n = recv(aid, cbuffer, sizeof(cbuffer), 0);
        cbuffer[n] = '\0';
        printf("Clinet: %s\n", cbuffer);
        if(aid < 0)
        {
            printf("Accept Failde\n");
            exit(-1);
        }
        printf("Accepted\n");
        printf("Server: ");
        scanf(" %[^\n]%*c", sbuffer);
        send(aid, sbuffer, strlen(sbuffer), 0);
    }
    close(aid);
    close(fd);
    return 0;
}