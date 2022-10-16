#include <arpa/inet.h>
#include <sys/socket.h>
#include <error.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define BUFFSIZE 512

int main(int argc,char** argv){
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *res;
    int status;

    memset(&hints,0,sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;


    // /* using getaddrinfo to populate the addrinfo struct */
    // getaddrinfo("www.github.com","80",&hints,&res);

    // // int socket(int domain, int type, int protocol);
    // sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);

    // // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    // // note: struct sockaddr and struct sockaddr_in have different definitions but they represent the same content. These two structs are both of 16 bytes.
    // status = connect(sockfd,res->ai_addr,res->ai_addrlen);

    /* manully populate the arguments */
    struct sockaddr_in destaddr;
    destaddr.sin_family = AF_INET;
    destaddr.sin_port = htons(atoi(argv[2]));

    // destaddr.sin_addr.s_addr = inet_addr("140.82.112.3");// github
    destaddr.sin_addr.s_addr = inet_addr(argv[1]);
    // int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET,SOCK_STREAM,0);


    printf("Connecting to server %s:%s\n",argv[1],argv[2]);
    // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    status = connect(sockfd,&destaddr,sizeof(destaddr));

    if(status){
        fprintf(stderr, "Connect error: %s\n", strerror(status));
    }
    else{
        printf("Connect() returns with %d\n",status);
        char * buf;
        buf = (char *)malloc(BUFFSIZE);
        int pid = fork();
        if(pid < 0){
            printf("Fork failed\n");
            return -1;
        }
        else if(pid==0){
            //child for receiving
            int recvsize;
            while(1){
                /*ssize_t recv(int sockfd, void *buf, size_t len, int flags);*/
                recvsize = recv(sockfd,buf,BUFFSIZE,0);
                if(recvsize <= 0){
                    fprintf(stderr, "Recv error: %s\n", strerror(recvsize));
                }
                else{
                    printf("Host: %s",buf);
                }
            }
        }
        
        else{
            // parent for sending
            size_t sendsize;
            fflush(stdin);
            while(1){
                // fscanf(stdin,"%[^\n]",buf);
                // fgets(buf, BUFFSIZE, stdin);
                getline(&buf, &sendsize, stdin);
                /*ssize_t send(int sockfd, const void *buf, size_t len, int flags);*/
                sendsize = send(sockfd, buf, strlen(buf)+1, 0);

                // client ends
                if(strcmp(buf,"END TALK\n") == 0){
                    break;
                }
                if(sendsize<strlen(buf)+1){
                    printf("Message sent size: %ld",sendsize);
                }
            }
            kill(pid, SIGKILL);
        }


        // char buf[BUFFSIZE];
        // sprintf(buf,"Hello from Client\n");
        // /*ssize_t send(int sockfd, const void *buf, size_t len, int flags);*/
        // int sendsize = send(sockfd, buf, strlen(buf)+1, 0);
        // if(sendsize<strlen(buf)+1){
        //     printf("Message sent size: %d",sendsize);
        // }
        // /*ssize_t recv(int sockfd, void *buf, size_t len, int flags);*/
        // int recvsize = recv(sockfd,buf,BUFFSIZE,0);
        // if(recvsize <= 0){
        //     fprintf(stderr, "Recv error: %s\n", strerror(recvsize));
        // }
        // else{
        //     printf("Host: %s",buf);
        // }


    }
    close(sockfd);
    return 0;

}