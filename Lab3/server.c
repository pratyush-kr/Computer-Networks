#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>

int main()
{
    struct sockaddr_in saddr, caddr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    printf("Waiting:\n");
    if(bind(fd, (const struct sockaddr*)&saddr, sizeof(saddr)) < 0)
    {
        printf("bind failed\n");
    }
    char buffer[25];
    int len = sizeof(caddr);
    int n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&caddr, &len);
    buffer[n] = '\0';
    printf("%s\n", buffer);
    char buff[] = "msg rec";
    sendto(fd, buff, strlen(buff), 0, (const struct sockaddr*)&caddr, len);
    close(fd);
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    /*
    // struct sockaddr_in {
    //            sa_family_t    sin_family; /* address family: AF_INET */
    //            in_port_t      sin_port;   /* port in network byte order */
    //            struct in_addr sin_addr;   /* internet address */
    //        };

    //        /* Internet address. */
    //        struct in_addr {
    //            uint32_t       s_addr;     /* address in network byte order */
    //        };
    //  ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    //    ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
    //    ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
    // ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

    // */
    return 0;
}