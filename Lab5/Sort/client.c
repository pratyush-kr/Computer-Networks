#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

typedef struct Array Array;

struct Array
{
    int arr[255];
    int n;
};

int main(int argc, char *argv[])
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    int pno = atoi(argv[1]);
    saddr.sin_port = htons(pno);
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
    Array x;
    int n;
    printf("Size: ");
    scanf(" %d", &n);
    x.n = n;
    printf("Array: ");
    for(int i=0; i<n; i++)
        scanf(" %d", &x.arr[i]);

    printf("\nPrinting Array\n");
    printf("Array: {%d", x.arr[0]);
    for(int i=1; i<n; i++)
        printf(", %d", x.arr[i]);
    printf("}\n");

    send(fd, &x, sizeof(x), 0);
    recv(fd, &x, sizeof(x), 0);
    printf("\nPrinting Array\n");
    printf("Sorted Array: {%d", x.arr[0]);
    for(int i=1; i<n; i++)
        printf(", %d", x.arr[i]);
    printf("}\n");
    return 0;
}
