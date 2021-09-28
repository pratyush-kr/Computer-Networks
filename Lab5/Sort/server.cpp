#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>

typedef struct Array Array;

struct Array
{
    int arr[255];
    int n;
};

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void bubbleSort(int *arr, int n) 
{ 
    int i, j; 
    for (i = 0; i < n-1; i++)     
      
    // Last i elements are already in place 
    for (j = 0; j < n-i-1; j++) 
        if (arr[j] > arr[j+1]) 
            swap(&arr[j], &arr[j+1]); 
}

int main(int argc, char *argv[])
{
    struct sockaddr_in saddr, caddr;
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
    int aid = accept(fd, (struct sockaddr*)&caddr, (socklen_t*)&len);
    if(aid < 0)
    {
        printf("Accept Failde\n");
        exit(-1);
    }
    printf("Accepted\n");
    Array x;
    recv(aid, &x, sizeof(x), 0);
    printf("Array Recieved\n");
    printf("\nPrinting Array\n");
    printf("Array: {%d", x.arr[0]);
    for(int i=1; i<x.n; i++)
        printf(", %d", x.arr[i]);
    printf("}\n");
    bubbleSort(&x.arr[0], x.n);
    printf("Sending\n");
    send(aid, &x, x.n, 0);
    return 0;
}
