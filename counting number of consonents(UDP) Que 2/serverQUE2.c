
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{ int ss,sb;
  ss=socket(AF_INET,SOCK_DGRAM,0);
  struct sockaddr_in servaddr;
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=ntohs(6011);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(ss,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
    
    struct sockaddr_in tempsendaddr;
    char buf[100];
    int len=sizeof(struct sockaddr);
    recvfrom(ss,buf,100,0,(struct sockaddr *)&tempsendaddr,&len);
    printf("Receive from Client: %s \n",buf);
    int c=0,i;
    for(i=0;buf[i]!='\0';i++)
    {if(tolower(buf[i])!='a' && tolower(buf[i])!='e' && tolower(buf[i])!='i' && tolower(buf[i])!='o' && tolower(buf[i])!='u' && tolower(buf[i])!=' ')
       {c++;
        }
     }
    printf("Number of consonants in the message : %d\n",c);
}
