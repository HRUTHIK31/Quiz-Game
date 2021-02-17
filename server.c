#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<time.h>
#include<sys/wait.h>
#include<pthread.h>
int main()
{
int s_sock, c_client, flag=0; int fd[2],min,total=0;
char buf1[100],buf2[100]="\0";char msg[100]="YOUR SWEET NAME
PLEASE >>>"; char name[100];
char names[10][100]; int times[10][6]; char que[5][500]; char
ans[5][100]; char answer[100];char ack[100];char win[100];char end[10];
strcpy(que[0],"WHO IS CEO OF GOOGLE ?\nA)TIM COOK\nB)SUNDHAR
PICHAI\nC)SATYA NADELLA\nD)JEFF BEZOS\n");
strcpy(que[1],"EVALUATE THE GIVEN EXPRESSION :2+2*2-2%2 =
?\nA)4\nB)5\nC)2\nD)3\n");
strcpy(que[2],"NAME THE LEAD MALE ACTOR OF
BAAHUBALI?\nA)SATHYARAJ\nB)NASSAR\nC)PRABHAS\nD)RANA\n");
strcpy(que[3],"WHICH COURSE DOES THIS PROJECT BELONGS
TO?\nA)OS\nB)VLSI\nC)DBMS\nD)COMPUTER NETWORKS\n");
strcpy(que[4],"WHAT IS THE NAME OF GIRLS HOSTEL OF
IIITDM?\nA)ASHOKA\nB)ASWATHA\nC)JASMINE\nD)LOTUS\n");
strcpy(ans[0],"B");
strcpy(ans[1],"B");
strcpy(ans[2],"C");
strcpy(ans[3],"D");
strcpy(ans[4],"C");
size_t t1,t2;

int childpid; int clientcount=0;int id;
socklen_t addr_size;
s_sock = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in server, other;
memset(&other, 0, sizeof(other));
memset(&server, 0, sizeof(server));
memset(times,0,sizeof(times[0][0])*6*10);
server.sin_family = AF_INET;
server.sin_port = htons(9009);
server.sin_addr.s_addr = INADDR_ANY;
if(bind(s_sock, (struct sockaddr*)&server, sizeof(server))==-1)
{
printf("Server is busy..\n");
exit(1);
}
listen(s_sock, 10);
addr_size = sizeof(other);
FILE *fp;
FILE *p;
while(1)
{
printf("PRESS ENTER ---> TO ALLOW CLIENT\nTYPE end --->
TO END THE GAME\n");
gets(end);
if((strcmp(end,"end"))==0)
break;
else
{
c_client = accept(s_sock, (struct sockaddr*)&other,

&addr_size);

id=clientcount;
clientcount++;
send(c_client,msg,sizeof(msg),0);
recv(c_client,name,sizeof(name),0);
strcpy(names[id],name);

printf("Connection %d accepted from : %s with port
%d\n\n",clientcount,inet_ntoa(other.sin_addr), ntohs(other.sin_port));

if(c_client==-1)
exit(1);

if((childpid=fork())==0)
{ int tym[5];
memset(tym,0,sizeof(tym));
close(s_sock);
int i;
for(i=0;i<5;i++)
{
send(c_client,que[i],100,0);
time(&t1);

recv(c_client,answer,sizeof(answer),0);
time(&t2);

if((t2-t1)>60)
{
strcpy(ack,"Timeisup");
send(c_client,ack,sizeof(ack),0);
printf("Disconnected from connection %d : %s

with port %d\n\n",clientcount,inet_ntoa(other.sin_addr),
ntohs(other.sin_port));
fp=fopen("times.txt","a");

fprintf(fp,"%d\t%s\t\t",(id+1),names[id]);
for(int i=0;i<5;i++)
{

fprintf(fp,"%d\t",tym[i]);
};

fprintf(fp,"-\n");
fclose(fp);
exit(1);
}
else
{
if((strcmp(ans[i],answer))==0)
{
int diff= t2-t1;
tym[i]=diff;
strcpy(ack,"success");
send(c_client,ack,sizeof(ack),0);
}
else
{
strcpy(ack,"failure");
send(c_client,ack,sizeof(ack),0);
fp=fopen("times.txt","a");

fprintf(fp,"%d\t%s\t\t",(id+1),names[id]);
for(int i=0;i<5;i++)
{

fprintf(fp,"%d\t",tym[i]);
};

fprintf(fp,"-\n");
printf("Disconnected from connection %d : %s with

port %d\n\n",clientcount,inet_ntoa(other.sin_addr),
ntohs(other.sin_port));
exit(1);
}
}
}
if(i==5)

{ flag++;
printf("Disconnected from connection %d : %s with port
%d\n\n",clientcount,inet_ntoa(other.sin_addr), ntohs(other.sin_port));

strcpy(win,"\nCONGRATULATIONS-YOU ANSWERED

CORRECTLY!!\nPLEASE WAIT FOR THE RESULTS!!\n");
send(c_client,win,sizeof(win),0);
fp=fopen("times.txt","a");
fprintf(fp,"%d\t%s\t\t",(id+1),names[id]);
for(int i=0;i<5;i++)
{

fprintf(fp,"%d\t",tym[i]);
total=total+tym[i];
};

fprintf(fp,"%d\n",total);

if(id==0)
{
p=fopen("total.txt","w");
fprintf(p,"%d\t\t%d\t\t%s",total,(id+1),names[id]);
}
else
{
p = fopen("total.txt", "r");
fscanf(p,"%d",&min);
fclose(p);
if(min>total)
{
p = fopen("total.txt", "w");
fprintf(p,"%d\t\t%d\t%s",total,(id+1),names[id]);
}
if(min==total)
{
p = fopen("total.txt", "a");
fprintf(p,"\n%d\t\t%d\t%s",total,(id+1),names[id]);
}
}
fclose(p);
fclose(fp);
exit(0);
}
}
}
}
char ch='\0';
printf("SCORE
BOARD\nID\tNAMES\t\tt1\tt2\tt3\tt4\tt5\tTotal-Time\n-------------------
---------------------------------------------------\n");
fp=fopen("times.txt","r");
ch=fgetc(fp);

while(ch!=EOF)
{ printf("%c",ch);
ch=fgetc(fp);
}
fclose(fp);
printf("\nWINNER DETAILS ARE :
\nTOTALTIME\tID\tCLIENT-NAME\n---------------------------------\n");
p=fopen("total.txt","r");
while((ch=fgetc(p))!=EOF)
printf("%c",ch);
printf("\n");
fclose(p);
close(s_sock);
return 0;
}
