#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int pno = atoi(argv[1]);
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(pno);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int len = sizeof(saddr);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(connect(fd, (struct sockaddr*)&saddr, len) < 0)
    {
        printf("Connection Failed\n");
    }
    char str1[255] = "somewhere over the rainbow";
    char str2[255] = "over";
    send(fd, &str1, strlen(str1), 0);
    sleep(1);
    send(fd, &str2, strlen(str2), 0);
    close(fd);
    return 0;
}