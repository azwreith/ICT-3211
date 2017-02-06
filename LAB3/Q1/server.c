#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<ctype.h>
#define MAXSIZE 150

main() {
	int sockfd,newsockfd,retval, i;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;

	char buff[MAXSIZE];
	int buff2[MAXSIZE];
	FILE *fp;
   	char fileBuff[255];
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
		printf("The client sent the file name: ");
		puts(buff);
		
		if((fp = fopen(buff, "r")) == NULL) {
			printf("Error opening file");
			exit(1);
		}

   	
   	buff2[0] = 0;
   	buff2[1] = 0;
   	buff2[2] = 0;
   	buff2[3] = 0;
   	while(fgets(fileBuff, sizeof fileBuff,fp) != NULL) {
		 	for(i = 0; i < strlen(fileBuff) - 1; i++) {
		 		if(isalpha(fileBuff[i])) {
		 			buff2[0]++;
		 		}
		 		else if(isdigit(fileBuff[i])) {
		 			buff2[1]++;
		 		}
		 		else if(fileBuff[i] == ' ') {
		 			buff2[3]++;
		 		}
		 		else {
		 			buff2[2]++;
		 		}
		 	}
   	}
		sentbytes=send(newsockfd,buff2,sizeof(buff2),0);

		if(sentbytes==-1) {
			close(sockfd);
			close(newsockfd);
		}
	
	}
	close(sockfd);
	close(newsockfd);
}

