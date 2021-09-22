#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<string.h>

void populate(struct sockaddr_in *saddr, int pno)
{
    saddr->sin_family = AF_INET;
    saddr->sin_port = htons(pno);
    saddr->sin_addr.s_addr = INADDR_ANY;
}

int main(int argc, char *argv[])
{
    for(int i=1; i<argc; i++)
        printf("Pno: %s\n", argv[i]);
    int n;
    printf("Servers: ");
    scanf(" %d", &n);
    struct sockaddr_in saddr[n];
    int fd[n];
    for(int i=0; i<n; i++)
        populate(&saddr[i], atoi(argv[1+i]));
    int len = sizeof(saddr[0]);
    for(int i=0; i<n; i++)
        fd[i] = socket(AF_INET, SOCK_STREAM, 0);
    int i=0;
    char buffer[255];
    while(i < n)
    {
        connect(fd[i], (struct sockaddr*)&saddr[i], len);
        printf("Client: ");
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