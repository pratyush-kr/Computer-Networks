#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char *line = NULL;
    fp = fopen("text.txt", "r");
    int len = 0;
    int read;
    char str[255];
    if(fp == NULL)
        exit(-1);
    while((read = getline(&line, (size_t*)&len, fp))!= -1)
        strcpy(str, line);
    fclose(fp);
    printf("%s\n", str);
    printf("Yay\n");
    struct sockaddr_in saddr;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0)
    {
        printf("Socket Not Created\n");
        exit(-1);
    }
    len = sizeof(saddr);
    sendto(fd, (char*)&str[0], strlen(str), 0, (struct sockaddr*)&saddr, (socklen_t)len);
    return 0;
}