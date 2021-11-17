#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int x=0;
    int pid = fork();
    if(pid == 0)
    {
        pid = fork();
        pid = fork();
        printf("Child %d\n", pid);
    }
    else
        printf("Parent %d\n", pid);
    return 0;
}