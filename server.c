#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <client_t.h>
#include <session.h>

int main(int argc, char *argv[])
{
	int port; 								
	int sockfd; 							
	int clisockfd; 
	int reuse=1;						
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	pthread_t thread; 					
	client_t* client; 					
	size_t uid = 0; 						 
	client_t* clients[MAX_CLIENTS] = {NULL};
	session_args_t session_args; 			
	socklen_t clilen = sizeof(client_addr);
	

	if (argc < 2)
	{
        fprintf(stderr,"ERROR, no port provided.\n");
        return 1;
    }
	

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket.");
		return 1;
	}
	memset((char *) &server_addr, 0, sizeof(server_addr));
    port = atoi(argv[1]);
	server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
	
setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int));

	if (bind(sockfd, (struct sockaddr *) &server_addr,
        sizeof(server_addr)) < 0)
		{
			perror("ERROR on binding.");
			return 1;
		}
		
		
	if (listen(sockfd,5) < 0)
	{
		perror("ERROR on listening.");
		return 1;
	}
	
	puts("[SYSTEM_MSG]: Server has been started.");
	
	
	session_args.clients = clients;
	
	
	while(1)
	{
		clisockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clilen);
		if (clisockfd < 0)
		{
			perror("ERROR on accept");
			continue;
		}
		
		
		if ((get_client_count()) == MAX_CLIENTS){
			printf("[SYSTEM_MSG]: Can't accept %s (MAX_CLIENTS is reached).", inet_ntoa(client_addr.sin_addr));
		       perror("[SYSTEM_MSG]: Can't accept  (MAX_CLIENTS is reached).");
                 	close(clisockfd);
			continue;
		}
		else
		{
			uid++;
	}
		
		
		client = (client_t*)malloc(sizeof(client_t));
		client->addr = client_addr;
		client->clientfd = clisockfd;
		client->uid = uid;
		client->authorized = 0;
		sprintf(client->name, "guest%lu", uid);
		
		
		add_user(client, clients);
		
		
		session_args.client = client;
		
		
		if(pthread_create(&thread, NULL, &session, (void*) &session_args))
		{
			close(clisockfd);
			delete_user(client->uid, clients);
			free(client);
		}
	}
	return 0; 
}
