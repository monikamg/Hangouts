#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 512 


typedef struct {
	struct sockaddr_in addr;	
	int clientfd;				
	int uid;					
	char name[24];				
	int authorized;				
} client_t;
