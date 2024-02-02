#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#define PORT 4771
int main(int argc,char *argv[])
{
        char buffer[100];

        time_t tm;
        time(&tm);

        int sockfd,a,connfd,len,i=0;
        struct sockaddr_in servaddr,cliaddr;
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        if(sockfd==-1)
        {
                printf("Error creating socket\n");
                exit(0);
        }
        printf("Server Socket Created Successfully.\n");
        bzero((struct sockaddr *)&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(PORT);
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
        {
                printf("Error in BIND function");
                exit(0);
        }
        printf("Server Socket Binded.\n");
        if((a=listen(sockfd,5))==-1)
        {
                printf("Error in LISTEN function");
                exit(0);
        }
        printf("Server Socket Listened...\n");
        len=sizeof(cliaddr);
        if((connfd=accept(sockfd,(struct sockaddr *)&cliaddr,&len))<0)
        {
                printf("Error in ACCEPT");
                exit(0);
        }
        do
        {	
                strcpy(buffer," ");
                read(connfd,buffer,100);
                
                time_t tm;
        	time(&tm);
                strcat(buffer,ctime(&tm));
                
                printf("From client :%s",buffer);
                if(strcmp(buffer,"bye\n")==0)
                {
                        printf("from Client: %s",buffer);
                        goto stop;
                }
                printf("Server(Echoing) :");
                //fgets(buffer,sizeof(buffer),stdin);
                //strcat(buffer,ctime(&tm));
                write(connfd,buffer,100);
        }while(strcmp(buffer,"bye\n") != 0);
        stop:
        exit(0);
        close(connfd);
        return 0;
}
