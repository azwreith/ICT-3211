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
	int sockfd,retval, i;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr;
	char buff[MAXSIZE][20];
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
		printf("1. Insert\n2. View\n3. Delete\nEnter operation: ");
		scanf("%s",buff[0]);
		if(strcmp(buff[0], "1") == 0) {
			printf("Enter Record: ");
			scanf("%s", buff[1]);
		}
		sentbytes=send(sockfd, &buff,sizeof(buff),0);	

		if(sentbytes==-1) {
			printf("!!");
			close(sockfd);
		}

		recedbytes=recv(sockfd, &buff,sizeof(buff),0);
		if(strcmp(buff[0], "2") == 0) {
			for(i=1; i<(int)buff[0][0]; i++) {
				printf("%s",buff[i]);
			}
		}
	}
	
	close(sockfd);
}
