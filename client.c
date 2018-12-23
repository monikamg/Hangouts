#define h_addr h_addr_list[0] /* for backward compatibility */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<sys/time.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <malloc.h>
#include <pthread.h>
#include<fcntl.h>
/*#include<linux/proc_fs.h>*/
//#include<dos.h>
#define BUFFER_SIZE 150
void delay(unsigned int);
typedef struct {
	int serverfd;				
} server_t;

void* session(void*);

int main(int argc, char *argv[])
{
	int sockfd, port;
    struct sockaddr_in serv_addr;
    struct hostent *server;
     int count =0;
	char buff[150];
	pthread_t thread; 
	server_t* serverfd;
        fd_set fdset;
        struct timeval timeout={300,0};
		
	port = 5567;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket.");
		return 1;
	}
//fcntl(sockfd,F_SETFL,O_NONBLOCK);
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	//bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);
        serv_addr.sin_addr.s_addr=INADDR_ANY;
       
	if(connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("ERROR connecting");
               	return 1;
	}
         
                 
        FD_ZERO(&fdset);
        FD_SET(sockfd,&fdset);
        int r;
        //setsockopt(sockfd,IPPROTO_TCP,TCP_SYNCNT,&reuse,sizeof(reuse));
	serverfd = malloc(sizeof(server_t));
	serverfd->serverfd = sockfd;
	if(pthread_create(&thread, NULL, &session, (void*) serverfd))
	{
		close(sockfd);
	}
	bzero(buff, BUFFER_SIZE);
        setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
	while(read(sockfd,buff,sizeof(buff))>0)
	{
               
                                
		printf("%s", buff);
		bzero(buff, BUFFER_SIZE);
              
	}
	close(sockfd);
	return 0;
}


void* session(void *args)
{
 //ssize_t buff	
char buff[100];
	server_t* tmp;
	int sockfd;
	tmp = (server_t*) args;
	sockfd = tmp->serverfd;
	bzero(buff, BUFFER_SIZE);
	while(strcmp(buff,"\\quit"))
	{
		x:fgets(buff, sizeof(buff), stdin);
               //printf("Size of Buff\t:%ld",strlen(buff));
                if(strlen(buff)>50){printf("[SERVER _MSG]:Too long! Please Send Mesaage Again!\n");goto x; }
		write(sockfd, buff,100);
		bzero(buff, BUFFER_SIZE);
	}
	pthread_detach(pthread_self());
	return NULL;
}

