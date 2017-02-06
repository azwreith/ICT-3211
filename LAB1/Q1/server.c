#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#define MAXSIZE 150

main() {
	int sockfd,newsockfd,retval, i, flag;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;

	char buff[MAXSIZE];
	int a=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd==-1) {
		printf("\nSocket creation error");
		exit(0);
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1) {
		printf("Binding error");
		close(sockfd);
	}

	retval=listen(sockfd,1);
	if(retval==-1) {
		close(sockfd);
	}

	actuallen=sizeof(clientaddr);
	newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);

	if(newsockfd==-1) {
		close(sockfd);
	}
	while(1) {
		recedbytes=recv(newsockfd,buff,sizeof(buff),0);

		if(recedbytes==-1) {
			close(sockfd);
			close(newsockfd);
		}
		printf("The client sent the string: ");
		puts(buff);
		
		if(strcmp(buff, "stop") == 0) {
			close(newsockfd);
			exit(0);
		}
		
		printf("Reversed string: ");
		for(i=strlen(buff)-1; i>=0; i--) {
			printf("%c", buff[i]);
		}
		printf("\n");
		
		flag = 1;
		for(i=0; i<strlen(buff)/2; i++) {
			if(buff[i] != buff[strlen(buff)-i-1]) {
				flag = 0;
			}
		}
	
		if(flag) {
			strcpy(buff, "Palindrome");
		}
		else {
			strcpy(buff, "Not a Palindrome");
		}
	
		sentbytes=send(newsockfd,buff,sizeof(buff),0);

		if(sentbytes==-1) {
			close(sockfd);
			close(newsockfd);
		}
	
	}

	close(sockfd);
	close(newsockfd);
}

