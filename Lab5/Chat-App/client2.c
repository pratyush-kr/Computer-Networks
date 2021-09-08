#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    struct sockaddr_in saddr;
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
    if(connect(fd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0)
    {
        printf("Connection Failed\n");
        exit(-1);
    }
    printf("Connected to server\n");
    char cbuffer[255];
    char sbuffer[255];
    while(1)
    {
        printf("Client: ");
        scanf(" %[^\n]%*c", cbuffer);
        send(fd, cbuffer, strlen(cbuffer), 0);
        if(!strcmp(cbuffer, "exit"))
            break;
        int n = recv(fd, sbuffer, sizeof(sbuffer), 0);
        sbuffer[n] = '\0';
        printf("Server: %s\n", sbuffer);
    }
    close(fd);
    return 0;
}