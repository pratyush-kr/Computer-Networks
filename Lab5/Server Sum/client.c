#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

typedef struct Numbers Numbers;

struct Numbers
{
    int a;
    int b;
};

int main()
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(5000);
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
    Numbers x;
    printf("a: ");
    scanf(" %d", &x.a);
    printf("b: ");
    scanf(" %d", &x.b);
    int sum;
    send(fd, &x, sizeof(x), 0);
    int n = recv(fd, &sum, sizeof(sum), 0);
    printf("sum = %d\n", sum);
    return 0;
}