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
    struct sockaddr_in saddr, caddr;
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
    printf("Server Listining\n");
    int len = sizeof(caddr);
    int aid = accept(fd, (struct sockaddr*)&caddr, &len);
    if(aid < 0)
    {
        printf("Accept Failde\n");
        exit(-1);
    }
    printf("Accepted\n");
    Numbers x;
    int n = recv(aid, &x, sizeof(x), 0);
    printf("Numbers recieved\n");
    printf("a = %d\nb = %d", x.a, x.b);
    int sum = x.a + x.b;
    send(aid, &sum, sizeof(&sum), 0);
    return 0;
}