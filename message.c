#include <message.h>


void send_msg(char* msg, int uid, client_t** clients)
{
	size_t i;
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(clients[i] != NULL && clients[i]->uid != uid)
		{
			write(clients[i]->clientfd, msg, strlen(msg));
		}
	}
}


void send_msg_all(char* msg, client_t** clients)
{
	size_t i;
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(clients[i]!=NULL)
		{
			write(clients[i]->clientfd, msg, strlen(msg));
		}
	}
}


void send_private_msg(char* msg, int uid, client_t** clients)
{
	size_t i;
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(clients[i]->uid == uid)
		{
			write(clients[i]->clientfd, msg, strlen(msg));
			break;
		}
	}
}

void send_group_msg_new_group(int uid, client_t** clients)
{
    /*struct sockaddr_in groupSock;
    struct in_addr localInterface;
    int g=0;

    char buff_out[BUFFER_SIZE];
    char finaldata1[50]="Hai";
     
    fgets(buff_out, BUFFER_SIZE-1,stdin);  
    groupSock.sin_family = AF_INET;
    groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");
    groupSock.sin_port = htons(5567); 
    localInterface.s_addr = inet_addr("192.168.56.101");
    setsockopt(8, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&localInterface, sizeof(localInterface));
    sendto(8, finaldata1, sizeof(finaldata1), 0, (struct sockaddr*)&groupSock, sizeof(groupSock));
    g++;*/
}
