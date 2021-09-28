#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

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
    listen(fd, 3);
    int i=0;
    int num;
    int sum = 0;
    int id[3];
    while(i < 3)
    {
        id[i] = accept(fd, (struct sockaddr*)&caddr, &len);
        recv(id[i], &num, sizeof(num), 0);
        printf("Client %d: %d\n", i+1, num);
        sum += num;
        i++;
    }
    printf("Sum: %d\n", sum);
    for(int i=0; i<3; i++)
        send(id[i], &sum, sizeof(sum), 0);
    close(fd);
    return 0;
}