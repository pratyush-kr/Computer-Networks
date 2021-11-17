#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>


int main(int argv, char *argc[])
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int len = sizeof(saddr);
    if(bind(fd, (struct sockaddr*)&saddr, len) < 0)
    {
        printf("Bind Failed\n");
    }
    char str[255];
    FILE *fp;
    char *line = NULL;
    fp = fopen("newFile.txt", "w");
    int n = recvfrom(fd, (char*)&str[0], sizeof(str), 0, (struct sockaddr*)&caddr, (socklen_t*)&len);
    str[n] = '\n';
    fprintf(fp, "%s", str);
    fclose(fp);
    return 0;
}