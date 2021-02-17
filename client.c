#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<string.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<sys/types.h> 
#include<arpa/inet.h> 
int main() 
{ 
int c_sock; 
char buf1[100]="\0",ques[100];char msg[100]; char name[100];char ack[100]; char succ[100]; char win[100];char ans[5][100]; c_sock = socket(AF_INET, SOCK_STREAM, 0); 
struct sockaddr_in client; 
memset(&client, 0, sizeof(client)); 
client.sin_family = AF_INET; 
client.sin_port = htons(9009); 
client.sin_addr.s_addr = inet_addr("35.246.29.33"); 
if(connect(c_sock, (struct sockaddr*)&client, 
sizeof(client))==-1) 
{ 
printf("connection error"); 
exit(1); 
} 
recv(c_sock,msg,sizeof(msg),0); 
 printf("%s",msg); 
gets(name); 
 send(c_sock,name,sizeof(name),0); 
printf("\nANSWER THE FOLLOWING MULTIPLE CHOICE 
QUESTIONS....SINGLE ANSWER IS ALLOWED[A|B|C|D]\n"); 
for(int i=0; i<5;i++) 
{ 
recv(c_sock, ques, sizeof(ques), 0); 
printf("\nQUESTION %d : %s",(i+1),ques); 
printf("\n>>>PLEASE ENTER YOUR ANSWER HERE : "); 
 gets(ans[i]); 
send(c_sock,ans[i], sizeof(ans[i]),0); 
recv(c_sock,ack, sizeof(ack),0); 
if((strcmp(ack,"success"))==0) 
continue; 
else if((strcmp(ack,"failure"))==0) 
{printf("\nWRONG ANSWER!! BETTER LUCK NEXT TIME\n"); 
exit(1);}
else if((strcmp(ack,"Timeisup"))==0) 
{printf("\nTIMEUP!! BETTER LUCK NEXT TIME\n"); exit(1);} } 
recv(c_sock,win,sizeof(win),0); 
printf("%s",win); 
close(c_sock); 
exit(0); 
return 0; 
} 

