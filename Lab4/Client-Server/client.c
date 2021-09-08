#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>

int main()
{
    struct sockaddr_in saddr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0)
    {
        printf("Socket Not Created\n");
        exit(-1);
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    char buff[25];
    while(1)
    {
        printf("Client: ");
        scanf(" %[^\n]%*c", buff);
        int len = sizeof(saddr); 
        sendto(fd, buff, strlen(buff), 0, (const struct sockaddr*)&saddr, len);
        if(!strcmp(buff, "exit"))
            break;
        int n = recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr*)&saddr, &len);
        buff[n] = '\0';
        printf("Server: %s\n", buff);
    }
    return 0;
}