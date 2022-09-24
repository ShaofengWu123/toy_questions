#include <arpa/inet.h>
#include <sys/socket.h>
#include <error.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define TEST2

int main(){
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *res;
    int status;

    memset(&hints,0,sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    #ifdef TEST1
    /* using getaddrinfo to populate the addrinfo struct */
    getaddrinfo("www.github.com","80",&hints,&res);
    
    // int socket(int domain, int type, int protocol);
    sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);

    // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    // note: struct sockaddr and struct sockaddr_in have different definitions but they represent the same content. These two structs are both of 16 bytes.
    status = connect(sockfd,res->ai_addr,res->ai_addrlen);
    
    #endif

    #ifdef TEST2
    /* manully populate the arguments */
    struct sockaddr_in destaddr;
    destaddr.sin_family = AF_INET;
    destaddr.sin_port = htons(80);

    destaddr.sin_addr.s_addr = inet_addr("140.82.112.3");// github
    // destaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    
    // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    status = connect(sockfd,&destaddr,sizeof(destaddr));

    #endif
    if(status){
        fprintf(stderr, "connect error: %s\n", strerror(status));
    }
    printf("connect() returns with [%d]\n",status);
    close(sockfd);
    return 0;
    
}