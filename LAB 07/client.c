
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>        /* netbd.h is needed for struct hostent =) */
#include <fcntl.h>

#define MAXDATASIZE 100   /* Max number of bytes of data */
#define STDIN 0

int main(int argc, char *argv[])
{
  int fd, numbytes, nval;	  /* files descriptors */
  char buf[MAXDATASIZE];  /* buf will store received text */
  
  struct hostent *he;         /* structure that will get information about remote host */
  struct sockaddr_in server;  /* server's address information */

  if (argc !=3) {	      /* this is used because our program will need 2 arguments (IP,port) */
    printf("Usage: %s <IP Address> <port>\n",argv[0]);
    exit(-1);
  }
  
  if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  /* calls socket() */
    printf("socket() error\n");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2])); /* htons() is needed again */
  //server.sin_addr = *((struct in_addr *)he->h_addr);  /*he->h_addr passes "*he"'s info to "h_addr" */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  bzero(&(server.sin_zero),8);

  if(connect(fd, (struct sockaddr *)&server,sizeof(struct sockaddr))==-1){ /* calls connect() */
    printf("connect() error\n");
    exit(-1);
  }

static char buf1[1000];
//defining sets to hold the fd for using them with select function. Master is necessary because these sets will change once they are sent to the select function
fd_set rset,master,wset;
	struct timeval timeout;
/*initialising fd sets that are storing status of fd*/	
	FD_ZERO(&rset);
	FD_ZERO(&master);
	//FD_ZERO(&wset);
//adding fd to master set
	FD_SET(fd,&master);
	FD_SET(STDIN,&master);

do
{
	rset=master;
	//wset=master;

//time tells select to monitor for that much amount of time.
	timeout.tv_sec=100;
	timeout.tv_usec=0;

	//select system call takes two sets to check if fd is ready for readio or writeio
	nval=select(fd+1,&rset,NULL,NULL,&timeout);//using select to verify if it is possible to 
	//nval=select(fd+1,&rset,&wset,NULL,NULL);//using select to verify if it is possible to 
	
	//if some data waiting to be read. then read it
	if(FD_ISSET(fd,&rset))
  	{
  	      numbytes=recv(fd,buf,MAXDATASIZE,0);
  	      buf[numbytes]='\0';
  	      printf("Server Message: %s\n",buf); 
	}
	//printf("My Message to server:");
	//if socket is ready to be written then scan data from user and send it
	if(FD_ISSET(STDIN,&rset))
	{
  		fgets(buf1,1000,stdin);
  		send(fd,buf1,strlen(buf1),0);
  	}

}while(strncmp(buf,"exit",4)!=0);
      
    //   close(fd);   /* close fd =) */
     
}
