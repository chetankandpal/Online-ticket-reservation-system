#include<netinet/in.h>
#include <unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/types.h>
#include<stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include <signal.h>
#include<time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void bookad(int sd)
{
 char buf1[18];
 read(sd,buf1,16);
 buf1[16]='\0';
 printf("%s\n",buf1);

 char buf2[29];
 read(sd,buf2,28);
 buf2[28]='\0';
 printf("%s\n",buf2);
 

 int n;
 char buf_acc[20];
 printf("Account name   Password \n");
 while(n=read(sd,buf_acc,20)!=0)
 {
   if(buf_acc[0]=='-' && buf_acc[1]=='1')break;

  for(int i=0;i<10;i++)
   if(buf_acc[i] =='`')continue;
   else printf("%c",buf_acc[i]);
   printf("             ");
  for(int i=0;i<10;i++)
    if(buf_acc[i+10]=='`')continue;
    else printf("%c",buf_acc[i+10]); 

    memset(buf_acc,0,20);
 }


 char buf_acm[49];
 read(sd,buf_acm,49);
 buf_acm[48]='\0';
 printf("%s\n",buf_acm);

 char namecustoad[10];
memset(namecustoad,'`',10);
scanf("%s",namecustoad);

for(int i=0;i<10;i++)if(namecustoad[i]=='\0')namecustoad[i]='`';
write(sd,namecustoad,10);

system("clear");

char buf3[109];
read(sd,buf3,109);
buf3[108]='\0';
printf("%s\n",buf3);
getchar();
char ch;
scanf("%c",&ch);
write(sd,&ch,1);

if(ch=='1')
{
printf("Ticket No. Train No.   Class            Booking Time\n");
 
 int n;
 char buf4[100];
 printf("       ");
 while(read(sd,buf4,100))
  {
    if(buf4[0] !='\0')
   printf("%s       ",buf4);
    
    memset(buf4,0,sizeof(buf4));
  }
}
else if(ch=='2')
{

 char ticket[100]; 
 char train_no[100]; 
 printf("Give the ticket details to view --- Ticket no. and train no.\n");
 scanf("%s",ticket);
 getchar();
 scanf("%s",train_no);

 write(sd,ticket,100);
 write(sd,train_no,100);
 


 printf("Ticket No. Train No.   Class            Booking Time\n");
 
 int n;
 char buf5[100];
 printf("       ");

 while(read(sd,buf5,100))
 {
   printf("%s       ",buf5);
   memset(buf5,0,sizeof(buf5));
 }
  
}
else if(ch=='3')
{
char buf4[64];
read(sd,buf4,64);
printf("%s\n",buf4);
getchar();
char ch;
scanf("%c",&ch);
write(sd,&ch,1);

//Give train class
char buf5[87];
read(sd,buf5,87);
printf("%s\n",buf5);
getchar();
scanf("%c",&ch);
write(sd,&ch,1);




//Result of booking
char buf6[25]; 
read(sd,buf6,25);
printf("%s\n",buf6);


char ticket_no[100];

read(sd,ticket_no,100);
printf("%s\n",ticket_no);
getchar();
char buf7[8];
read(sd,buf7,8);
printf("T%s\n",buf7);

}
else if(ch=='4')
{
 char ticket[100]; 
 char train_no[100]; 
 printf("Give the ticket details to update --- Ticket no. and train no.\n");
 scanf("%s",ticket);
 getchar();
 scanf("%s",train_no);

 write(sd,ticket,100);
 write(sd,train_no,100);
 
 char buf4[56];
 read(sd,buf4,56);
 printf("%s\n",buf4);

 char c[2];
 scanf("%s",c);
 write(sd,c,1);


 printf("Update done\n");
}
else if(ch=='5')
{
 char ticket[100]; 
 char train_no[100]; 
 printf("Give the ticket details to cancel --- Ticket no. and train no.\n");
 scanf("%s",ticket);
 scanf("%s",train_no);

 write(sd,ticket,100);
 write(sd,train_no,100);
 
 printf("Booking canceled \n");
}


}

void bookag(int sd)
{
//Choice for agent

char buf1[23];
read(sd,buf1,23);
printf("%s\n",buf1);

//Name of customer
char namecustoag[10];
memset(namecustoag,'`',10);
scanf("%s",namecustoag);

for(int i=0;i<10;i++)if(namecustoag[i]=='\0')namecustoag[i]='`';
write(sd,namecustoag,10);

char buf2[64];
read(sd,buf2,64);
printf("%s\n",buf2);
getchar();
char op;
scanf("%c",&op);
write(sd,&op,1);

if(op=='1')
{

//Give train choice
char buf3[64];
read(sd,buf3,64);
printf("%s\n",buf3);
getchar();
char ch;
scanf("%c",&ch);
write(sd,&ch,1);

//Give train class
char buf4[87];
read(sd,buf4,87);
printf("%s\n",buf4);
getchar();
scanf("%c",&ch);
write(sd,&ch,1);




//Result of booking
char buf5[25]; 
read(sd,buf5,25);
printf("%s\n",buf5);


char ticket_no[100];

read(sd,ticket_no,100);
printf("%s\n",ticket_no);
getchar();
char buf6[8];
read(sd,buf6,8);
printf("T%s\n",buf6);

}
else if(op=='2')
{
 printf("Ticket No. Train No.   Class            Booking Time\n");
 
 int n;
 char buf7[100];
 printf("       ");
 while(read(sd,buf7,100))
  {
    if(buf7[0] !='\0')
   printf("%s       ",buf7);
    
    memset(buf7,0,sizeof(buf7));
  }


}


}

void cancel(int sd)
{
 char ticket[100]; 
 char train_no[100]; 
 printf("Give the ticket details to cancel --- Ticket no. and train no.\n");
 scanf("%s",ticket);
 scanf("%s",train_no);

 write(sd,ticket,100);
 write(sd,train_no,100);
 
 printf("Booking canceled \n");
}

void update(int sd)
{
  
 char ticket[100]; 
 char train_no[100]; 
 printf("Give the ticket details to update --- Ticket no. and train no.\n");
 scanf("%s",ticket);
 getchar();
 scanf("%s",train_no);

 write(sd,ticket,100);
 write(sd,train_no,100);
 
 char buf1[56];
 read(sd,buf1,56);
 printf("%s\n",buf1);

 char ch[2];
 scanf("%s",ch);
 write(sd,ch,1);


 printf("Update done\n");


}


void view(int sd)
{

 printf("Ticket No. Train No.   Class            Booking Time\n");
 
 int n;
 char buf3[100];
 printf("       ");
 while((n=read(sd,buf3,100))!=0)
  {
    if(buf3[0] !='\0')
   printf("%s       ",buf3);
    
    memset(buf3,0,sizeof(buf3));
  }

  
}

void book(int sd)
{
char ch;
//Give train choice
char buf1[65];
read(sd,buf1,64);
printf("%s\n",buf1);
scanf("%s",&ch);
write(sd,&ch,1);

//Give train class
char buf2[88];
read(sd,buf2,87);
printf("%s\n",buf2);
scanf("%s",&ch);
write(sd,&ch,1);




//Result of booking
char buf3[25]; 
read(sd,buf3,25);
printf("%s\n",buf3);


char ticket_no[101];
read(sd,ticket_no,100);
printf("%s\n",ticket_no);
char buf4[8];
read(sd,buf4,8);
printf("T%s\n",buf4);

}


void main()
{


  
struct sockaddr_in serv;

int sd=socket(AF_UNIX,SOCK_STREAM,0);

serv.sin_family=AF_UNIX;
serv.sin_port=htons(7521);
serv.sin_addr.s_addr=INADDR_ANY;

connect(sd,(void*)&serv,sizeof(serv));

system("clear");

char buf1[153];
char temp;
int n;
read(sd,buf1,153);
buf1[152]='\0';
printf("%s\n",buf1);

//choice for account
char ch;
char c;
scanf("%s",&ch);
write(sd,&ch,1);

if(ch=='1')
{
//semaphore op 

char buf2[53];
read(sd,buf2,53);
printf("%s\n",buf2);

memset(buf2,0,sizeof(buf2));


//choice Yes or No
char s[3];

scanf("%s",s);

write(sd,s,3);

system("clear");

//Login
if(s[0]=='Y')
{

char buf3[57];
read(sd,buf3,57);
printf("%s\n",buf3);
}
else if(s[0]=='N')
{
  char buf3a[51];
  read(sd,buf3a,51);
  printf("%s\n",buf3a);
}

char name[10];
char pass[10];
memset(name,'`',10);
memset(pass,'`',10);
//Enter name
scanf("%s",name);
for(int i=0;i<10;i++)if(name[i]=='\0')name[i]='`';
write(sd,name,10);

char buf4[27];
read(sd,buf4,27);
printf("%s",buf4);

//Enter password
scanf("%s",pass);
for(int i=0;i<10;i++)if(pass[i]=='\0')pass[i]='`';
write(sd,pass,10);

getchar();
char buf5[33];
read(sd,buf5,33);
buf5[32]='\0';

if(buf5[3]=='N')
{
  printf("%s\n",buf5);
close(sd);
shutdown(sd,0);
shutdown(sd,1);
shutdown(sd,2);

exit(0);
}

printf("%s\n",buf5);
system("clear");

char buf6[169]; 
read(sd,buf6,169);
printf("%s",buf6);
scanf("%s",&c);
write(sd,&c,1);

//Booking
if(c=='1')book(sd);
else if(c=='2')view(sd);
else if(c=='3')update(sd);
else if(c=='4')cancel(sd);


}
else if(ch=='2')
{
 
char buf2[53];
read(sd,buf2,53);
printf("%s\n",buf2);

memset(buf2,0,sizeof(buf2));


//choice Yes or No
char s[3];

scanf("%s",s);

write(sd,s,3);

system("clear");

//Login
if(s[0]=='Y')
{
char buf3[57];
read(sd,buf3,57);
printf("%s\n",buf3);
}
else if(s[0]=='N')
{
  char buf3a[51];
  read(sd,buf3a,51);
  printf("%s\n",buf3a);
}

char name[10];
char pass[10];
memset(name,'`',10);
memset(pass,'`',10);
//Enter name
scanf("%s",name);
for(int i=0;i<10;i++)if(name[i]=='\0')name[i]='`';
write(sd,name,10);

char buf4[27];
read(sd,buf4,27);
printf("%s",buf4);

//Enter password
scanf("%s",pass);
for(int i=0;i<10;i++)if(pass[i]=='\0')pass[i]='`';
write(sd,pass,10);


char buf5[33];
read(sd,buf5,33);


buf5[32]='\0';

if(buf5[3]=='N')
{
  printf("%s\n",buf5);
close(sd);
shutdown(sd,0);
shutdown(sd,1);
shutdown(sd,2);

exit(0);
}
printf("%s\n",buf5);
system("clear");

bookag(sd);


}
else if(ch=='3')
{
char buf3[57];
read(sd,buf3,57);
buf3[56]='\0';
printf("%s\n",buf3);


char name[10];
char pass[10];
//Enter name
scanf("%s",name);
write(sd,name,10);

char buf4[27];
read(sd,buf4,27);
buf4[26]='\0';
printf("%s\n",buf4);

//Enter password
scanf("%s",pass);
write(sd,pass,10);


char buf5[33];
read(sd,buf5,33);


buf5[32]='\0';

if(buf5[3]=='N')
{
  printf("%s\n",buf5);
close(sd);
shutdown(sd,0);
shutdown(sd,1);
shutdown(sd,2);

exit(0);
}

printf("%s\n",buf5);
getchar();
system("clear");
 bookad(sd);

}
close(sd);
shutdown(sd,0);
shutdown(sd,1);
shutdown(sd,2);
}

