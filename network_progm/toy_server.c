#include <arpa/inet.h>
#include <sys/socket.h>
#include <error.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// /* Structure describing an Internet (IP) socket address. */
// #if  __UAPI_DEF_SOCKADDR_IN
// #define __SOCK_SIZE__	16		/* sizeof(struct sockaddr)	*/
// struct sockaddr_in {
//   __kernel_sa_family_t	sin_family;	/* Address family		*/
//   __be16		sin_port;	/* Port number			*/
//   struct in_addr	sin_addr;	/* Internet address		*/

//   /* Pad to size of `struct sockaddr'. */
//   unsigned char		__pad[__SOCK_SIZE__ - sizeof(short int) -
// 			sizeof(unsigned short int) - sizeof(struct in_addr)];
// };
// #define sin_zero	__pad		/* for BSD UNIX comp. -FvK	*/
// #endif

#define INET_ADDRSTRLEN 16
#define BUFFSIZE 512

int main(int argc, char** argv){
    int sockfd;
    int newsockfd;
    struct sockaddr_in srcaddr;
    struct sockaddr_in clientaddr_info;
    socklen_t clientaddr_len;
    char clientaddr[INET_ADDRSTRLEN];


    /* manully populate the arguments */
    
    srcaddr.sin_family = AF_INET;
    srcaddr.sin_port = htons(atoi(argv[1]));
    // srcaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    srcaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    /* int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); */
    bind(sockfd, &srcaddr, sizeof(srcaddr));

    printf("Server listening on port %s\n",argv[1]);
    /* int listen(int sockfd, int backlog); */
    listen(sockfd,5);

    /* int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen); */
    newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr_info, &clientaddr_len);
    
    if(newsockfd == -1){
        printf("Connection failed\n");
    }
    else{
        inet_ntop(AF_INET, &clientaddr_info.sin_addr.s_addr, clientaddr, INET_ADDRSTRLEN);
        printf("------------\nConnection established\n[Client information]\nIP address:%s\n",clientaddr);
        printf("Port:%d\n------------\n",ntohs(clientaddr_info.sin_port));
        // printf("IP:%s\n",inet_ntoa(clientaddr_info.sin_addr));
        //char buf[BUFFSIZE];
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
                recvsize = recv(newsockfd,buf,BUFFSIZE,0);
                /*ssize_t recv(int sockfd, void *buf, size_t len, int flags);*/
                if(recvsize <= 0){
                    fprintf(stderr, "Recv error: %s\n", strerror(recvsize));
                }
                else{
                    printf("Client: %s",buf);
                }
                if(strcmp(buf,"END TALK\n") == 0){
                    break;
                }
            }
            printf("Client from IP: %s Port: %d leaves\n",clientaddr,ntohs(clientaddr_info.sin_port));
            close(newsockfd);
            
        }
        else{
            // parent for sending
            size_t sendsize;
            fflush(stdin);
            while(1){
                
                getline(&buf, &sendsize, stdin);
                //fgets(buf, BUFFSIZE, stdin);
                //printf("message get: %s", buf);

                /*ssize_t send(int sockfd, const void *buf, size_t len, int flags);*/
                sendsize = send(newsockfd, buf, strlen(buf)+1, 0);
                //printf("message sent\n");
                if(sendsize<strlen(buf)+1){
                    printf("Message sent size: %ld",sendsize);
                } 
            }
        }
        // /*ssize_t recv(int sockfd, void *buf, size_t len, int flags);*/
        // char buf[BUFFSIZE];
        // int recvsize = recv(newsockfd,buf,BUFFSIZE,0);
        // if(recvsize <= 0){
        //     fprintf(stderr, "Recv error: %s\n", strerror(recvsize));
        // }
        // else{
        //     printf("Client: %s",buf);
        // }

        // sprintf(buf,"Hello from Server\n");
        // /*ssize_t send(int sockfd, const void *buf, size_t len, int flags);*/
        // int sendsize = send(newsockfd, buf, strlen(buf)+1, 0);
        // if(sendsize<strlen(buf)+1){
        //     printf("Message sent size: %d",sendsize);
        // }
    }
    close(sockfd);
    return 0;
    
}