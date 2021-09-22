#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

void populate(struct sockaddr_in *saddr, int pno)
{
    saddr->sin_family = AF_INET;
    saddr->sin_port = pno;
    saddr->sin_addr.s_addr = INADDR_ANY;
}

int main(int argc, char *argv[])
{
    for(int i=0; i<argc; i++)
        printf("Pno: %s\n", argv[i]);
    int n;
    printf("Servers: ");
    scanf(" %d", &n);
    struct sockaddr_in saddr[3];
    int len = sizeof(saddr[0]);
    int fd[3] = {0};
    for(int i=0; i<n; i++)
        populate(&saddr[i], atoi(argv[1+i]));
    for(int i=0; i<n; i++)
        connect(fd[i], (struct sockaddr*)&saddr, len);
    int i=0;
    while(i < 3)
    {
        printf("Client: ");
        char buffer[255];
        scanf(" %[^\n]%*c", buffer);
        send(fd[i], buffer, strlen(buffer), 0);
        int n = recv(fd[i], buffer, sizeof(buffer), 0);
        buffer[n] = '\0';
        printf("Server %d: %s\n", i+1, buffer);
        i++;
    }
    for(int i=0; i<n; i++)
        close(fd[i]);
    return 0;
}