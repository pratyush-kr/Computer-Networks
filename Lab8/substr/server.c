/*
mritunjaykumar2021@vitbhopal.ac.in
rk4167580@gmail.com
7992311430
*/
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int splitAndCompare(char *str, int n, char *s)
{
    int x=0, m;
    for(int i=0; i<n;)
    {
        char buff[255];
        int c = 0;
        for(int j=i; str[j]!=' ' || str[j]!='\0'; j++) m = j;
        m++;
        for(int j=i; j<m; j++)
            buff[c++] = str[j];
        buff[m] = '\0';
        printf("Current Buffer: %s\n", buff);
        i += m;
        if(strcmp(buff, s) == 0)
            return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int pno = atoi(argv[1]);
    struct sockaddr_in saddr, caddr;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(pno);
    saddr.sin_family = AF_INET;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        printf("Socket Creation Failed\n");
        exit(-1);
    }
    int len = sizeof(saddr);
    if(bind(fd, (struct sockaddr*)&saddr, len) < 0)
    {
        printf("Bind Failed\n");
        close(fd);
        exit(-1);
    }
    listen(fd, 2);
    char str1[255];
    char str2[255];
    int id = accept(fd, (struct sockaddr*)&caddr, &len);
    int n1 = recv(id, &str1, sizeof(str1), 0);
    str1[n1] = '\0';
    int n2 = recv(id, &str2, sizeof(str2), 0);
    str2[n2] = '\0';
    printf("str1 = %s\nstr2 = %s\n", str1, str2);
    printf("%d", splitAndCompare(str1, n1, str2));
    return 0;
}