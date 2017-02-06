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

	char buff[MAXSIZE][20];
	FILE *fp;
  char fileBuff[150];
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
		recedbytes=recv(newsockfd, &buff,sizeof(buff),0);

		if(recedbytes==-1) {
			close(sockfd);
			close(newsockfd);
		}

		if((fp = fopen("student.txt", "a+")) == NULL) {
			printf("Error opening file");
			exit(1);
		}
   	//fgets(fileBuff, sizeof fileBuff,fp);
   	
   	if(strcmp(buff[0], "1") == 0) {
   		fprintf(fp, "%s", buff[1]);
   		fprintf(fp, "%s", "\n");
   		fclose(fp);
   	}
   	else if(strcmp(buff[0], "2") == 0) {
   		i = 1;
   		while(fgets(fileBuff, sizeof fileBuff,fp) != NULL) {
   			strcpy(buff[i++], fileBuff);
   		}
   		buff[0][0] = (char)i;
   	}
   	else if(strcmp(buff[0], "3") == 0) {
   		remove("student.txt");
   	}
   	else {
   		printf("Invalid");
   	}
   	
		sentbytes=send(newsockfd, &buff,sizeof(buff),0);

		if(sentbytes==-1) {
			close(sockfd);
			close(newsockfd);
		}
	
	}
	close(sockfd);
	close(newsockfd);
}

