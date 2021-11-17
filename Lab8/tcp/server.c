#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

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
    char str[255];
    int id = accept(fd, (struct sockaddr*)&caddr, &len);
    int n = recv(id, &str, sizeof(str), 0);
    printf("%s\n", str);
    close(fd);
    FILE *f;
    f = fopen("NewFile.txt", "w");
    fprintf(f, "%s", str);
    fclose(f);
    return 0;
}