#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 150

main() {
  pid_t pid = fork();
	
	if(pid == 0) {
		int sockfd,retval;
	  int recedbytes,sentbytes;
	  struct sockaddr_in serveraddr;
	  char buff[MAXSIZE];
	  
	  sleep(5);
	  
	  sockfd=socket(AF_INET,SOCK_STREAM,0);
	  if(sockfd==-1) {
		  printf("\nSocket Creation Error");
	  }
	  serveraddr.sin_family=AF_INET;
	  serveraddr.sin_port=htons(3389);
	  serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	  retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	  if(retval==-1) {
		  printf("Connection error");
	  }
	  while(1) {
	    scanf("%s",buff);
	    sentbytes=send(sockfd,buff,sizeof(buff),0);

	    if(sentbytes==-1) {
		    printf("!!");
		    close(sockfd);
	    }
	  }
	  close(sockfd);
	}
	
	
	else {
		int sockfd,newsockfd,retval;
		socklen_t actuallen;
		int recedbytes,sentbytes;
		struct sockaddr_in serveraddr,clientaddr;

		char buff[MAXSIZE];
		int a=0;
		sockfd=socket(AF_INET,SOCK_STREAM,0);

		if(sockfd==-1) {
			printf("\nSocket creation error");
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
		  printf("=> %s", buff);
		  printf("\n");
	  }

		close(sockfd);
		close(newsockfd);
	}

}

