#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>

#define PORT 8080

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == 0)
    {
        perror("Socket failed");
        exit(-1);
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    int binder = bind(fd, (struct sockaddr*)&address, sizeof(address));
    if(binder < 0)
    {
        perror("Bind failed");
        exit(-1);
    }
    int listener = listen(fd, 3);
    if(listener < 0)
    {
        perror("Listen failed");
        exit(-1);
    }
    return 0;
}