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
    char str[255];
    char *line = NULL;
    int read;
    len = 0;
    FILE *fp = fopen("text.txt", "r");
    while((read = getline(&line, (size_t*)&len, fp))!= -1)
        strcpy(str, line);
    send(fd, &str, strlen(str), 0);
    fclose(fp);
    close(fd);
    return 0;
}