#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 150

main() {
	int sockfd,retval, i, loc;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr;
	int buff[MAXSIZE];
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1) {
		printf("\nSocket Creation Error");
	}
	//printf("%i",sockfd);
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1) {
		printf("Connection error\n");
		exit(0);
	}
	
	while(1) {
		printf("Enter the 10 numbers and the key: ");
		
		for(i=0; i<11; i++) {
			scanf("%d", &buff[i]);
		}
		
		sentbytes=send(sockfd,buff,sizeof(buff),0);
		

		if(sentbytes==-1) {
			printf("!!");
			close(sockfd);
		}
	
		recedbytes=recv(sockfd,&loc,sizeof(loc),0);
		if(loc >= 0) {
			printf("Found at index: %d", loc);
		}
		else {
			printf("Not found!");
		}
		printf("\n");
	}
	
	close(sockfd);
}
