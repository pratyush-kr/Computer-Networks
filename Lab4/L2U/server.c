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
    struct sockaddr_in saddr, caddr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    printf("Waiting:\n");
    if(bind(fd, (const struct sockaddr*)&saddr, sizeof(saddr)) < 0)
    {
        printf("bind failed\n");
    }
    char buffer[25];
    int len = sizeof(caddr);
    while(1)
    {
        int n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&caddr, &len);
        buffer[n] = '\0';
        printf("Client: %s", buffer);
        int i=0;
        while(buffer[i] != '\0')
            buffer[i++] = toupper(buffer[i]);
        sendto(fd, buffer, strlen(buffer), 0, (const struct sockaddr*)&caddr, len);
    }
    close(fd);
    return 0;
}