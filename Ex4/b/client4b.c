#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<string.h>
#include<time.h>

int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[100];
    char recvline[100];
    
    struct sockaddr_in servaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&servaddr,sizeof servaddr);
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22000);
    
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
    while(1)
    {
        bzero( sendline, 100);
        bzero( recvline, 100);
        fgets(sendline,100,stdin); /*stdin = 0 , for standard input */
        
        time_t t;   // not a primitive datatype
        time(&t);
        char msg[100];
        strcat(msg,ctime(&t));
        strcat(msg,sendline);
        
        write(sockfd,msg,strlen(msg)+1);
        read(sockfd,recvline,100);
        printf("%s",recvline);
        break;
    }
}
