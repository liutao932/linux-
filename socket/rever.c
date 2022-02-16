#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define IPSIZE 30
#include"proto.h"

int main()
{
	struct msg_st rbuf;
	struct sockaddr_in laddr,raddr;
	int sd = socket(AF_INET,SOCK_DGRAM,0);
	socklen_t raddr_len;
	char ipstr[IPSIZE];
	if(sd <0)
	{
		perror("socket()");
		exit(1);
	}
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(RCVPORT));
	inet_pton(AF_INET,"0.0.0.0",&laddr.sin_addr);
	
	if(bind(sd,(void*)&laddr,sizeof(laddr))< 0)
	{
		perror("bind()");
		exit(1);
	}
	raddr_len = sizeof(raddr);
	while(1)
	{

		recvfrom(sd,&rbuf,sizeof(rbuf),0,(void *)&raddr,&raddr_len);
		inet_ntop(AF_INET,&raddr.sin_addr,ipstr,IPSIZE);
		printf("-----MESSAGE FROM %s:%d--\n", ipstr,ntohs(raddr.sin_port));
		printf("NAME  = %s\n",rbuf.name);
		printf("MATH  = %d\n",ntohl(rbuf.math));
		printf("CHINESE  = %d\n",ntohl(rbuf.chinese));
	}

	exit(0);
	//close();
}
