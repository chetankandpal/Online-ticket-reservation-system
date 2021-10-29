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
#include<errno.h>
#define NUM_THREADS 50


struct cData{

char ticket[100];
char train_no[100];
char class[100];
char date[100];

}cus;

void bookad(int nsd)
{

char ch;
int num;
time_t curtime;
struct tm* loc_time;
curtime=time(NULL);
loc_time=localtime(&curtime);
char name[10];

struct flock fl;

fl.l_type=F_RDLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

 char* message="\n\n\n\tADMIN ACCOUNT";
 write(nsd,message,strlen(message));


 message="List of the accounts present";
 write(nsd,message,strlen(message));

 int fd_account=open("loginc.txt",O_RDONLY);

 fcntl(fd_account,F_SETLKW,&fl);
 int n;
 char buf_acc[20];
 while((n=read(fd_account,buf_acc,20)) !=0)
 {
   if(n==-1)break;
   write(nsd,buf_acc,20);
   //printf("%s \n",buf_acc);
  memset(buf_acc,0,sizeof(buf_acc));
 }
  fl.l_type=F_UNLCK;
  close(fd_account);
  message="-1                 ";
  write(nsd,message,strlen(message));

 message="\n\n\n\tName of the account for applying operations ";
 write(nsd,message,strlen(message));
  read(nsd,name,10);

 message="\n\n\n\n\tAvailable operations are \n\n\n\t01.View all\n\n\n\t02.View\n\n\n\t03.Book ticket\n\n\n\t04.Modify\n\n\n\t05.Cancel booking";
 write(nsd,message,strlen(message));
 read(nsd,&ch,1);


  char file_cust[11];
  file_cust[0]='c';
  file_cust[1]='u';
  file_cust[2]='s';
  file_cust[3]=name[0];
  file_cust[4]=name[1];
  file_cust[5]=name[2];
  file_cust[6]=name[4];

  for(int i=7;i<10;i++)file_cust[i]='0';
  file_cust[10]='\0';

 if(ch=='1')
 {

 fl.l_type=F_RDLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

   int fdv=open(file_cust,O_RDONLY) ;
   lseek(fdv,0,SEEK_SET);
   fcntl(fdv,F_SETLKW,&fl);

  int n;
  char buf1[100];

 while((n=read(fdv,buf1,100) )!=0)
  {
    if(n==-1)break;
    //printf("%s \n",buf1);
    write(nsd,buf1,100);
    memset(buf1,0,sizeof(buf1));
  }


  fl.l_type=F_UNLCK;
  close(fdv);

 }
 else if(ch=='2')
 {
 fl.l_type=F_RDLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

 //printf("%s ",file_cust);
 int fdv1=open(file_cust,O_RDONLY) ;
 if(fdv1<0)perror("open");
 //printf("%d \n",fdu);
 lseek(fdv1,0,SEEK_SET);
char ticket[100];
char train_no[100];

read(nsd,ticket,100);
read(nsd,train_no,100);

 int k1=1,k2=0;

 int n;
 fcntl(fdv1,F_SETLKW,&fl);
 char buf[400];
 int flag=0;
 while((n=read(fdv1,buf,400))!=0)
  {

  //printf("%d \n",n);
   if(n==-1)perror("read");
    k1=1;k2=0;
  //Ticket check
  int i=0;
 while(buf[i] !='\0' && i<400)
  {
    if(ticket[i] !=buf[i]){k1=0;break;}
    i++;
  }
   //Train_no check
     if(buf[100]==train_no[0])k2=1;

  if(flag==0 && k1==1 && k2==1)
  {
    flag=1;
    lseek(fdv1,-400,SEEK_CUR);
    int cou=0;
    while(cou<400)
    {
      read(fdv1,buf,100);
      write(nsd,buf,100);
      cou +=100;
    }

  }

  memset(buf,0,sizeof(buf));

  }
//  printf("%d \n",n);
  fl.l_type=F_UNLCK;
  close(fdv1);
 }
 else if(ch=='3')
 {
char train_no[2];
message="\n\n\n\t01.TRAIN A\n\n\n\t02.TRAIN B\n\n\n\t03.TRAIN C\n\n\n\tSelect train(1-3)";
write(nsd,message,strlen(message));
read(nsd,train_no,1);


 fl.l_type=F_WRLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

if(train_no[0]=='1')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,1);

 int fd_t1=open("train1.txt",O_RDWR,0777);
 fcntl(fd_t1,F_SETLKW,&fl);
 char value[4];

 read(fd_t1,value,4);
 lseek(fd_t1,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t1,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);


 // Writing to the file
  char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"A");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));

  write(nsd,decchar,100);
  message="Train A";
  write(nsd,message,strlen(message));

  close(fd_t1);
  close(fd_cus);

}
else if(train_no[0]=='2')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,2);

int fd_t2=open("train2.txt",O_RDWR,0777);
fcntl(fd_t2,F_SETLKW,&fl);
 char value[4];

 read(fd_t2,value,4);
 lseek(fd_t2,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t2,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);

  char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"B");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));


  write(nsd,decchar,sizeof(decchar));
  message="Train B";
  write(nsd,message,strlen(message));
  close(fd_t2);
  close(fd_cus);
}

else if(train_no[0]=='3')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,1);

int fd_t3=open("train3.txt",O_RDWR,0777);
fcntl(fd_t3,F_SETLKW,&fl);
 char value[4];

 read(fd_t3,value,4);
 lseek(fd_t3,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t3,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);

   char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"C");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));


  write(nsd,decchar,sizeof(decchar));
  message="Train C";
  write(nsd,message,strlen(message));
  close(fd_t3);
  close(fd_cus);
 }
 }
 else if(ch=='4')
 {
fl.l_type=F_WRLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

 //printf("%s ",file_cust);
 int fdu=open(file_cust,O_RDWR) ;
 if(fdu<0)perror("open");
 //printf("%d \n",fdu);
 lseek(fdu,0,SEEK_SET);
char ticket[100];
char train_no[100];

read(nsd,ticket,100);
read(nsd,train_no,100);

 int k1=1,k2=0;

 int n;
 fcntl(fdu,F_SETLKW,&fl);
 char buf[400];
 int flag=0;
 while((n=read(fdu,buf,400))!=0)
  {

  //printf("%d \n",n);
   if(n==-1)perror("read");
    k1=1;k2=0;
  //Ticket check
  int i=0;
 while(buf[i] !='\0' && i<400)
  {
    if(ticket[i] !=buf[i]){k1=0;break;}
    i++;
  }
   //Train_no check
     if(buf[100]==train_no[0])k2=1;

  if(flag==0 && k1==1 && k2==1)
  {
    flag=1;
    char d;
    message="Enter class you want to change -1AC ,2AC, SL\n Give (1-3)";
    write(nsd,message,strlen(message));
    read(nsd,&d,1);
   if(d=='1')
   {
   lseek(fdu,-200,SEEK_CUR);
    char cl1[100]="1AC";
    write(fdu,cl1,sizeof(cl1));
   }
   else if(d=='2')
   {
    lseek(fdu,-200,SEEK_CUR);
    char cl2[100]="2AC";
    write(fdu,cl2,sizeof(cl2));
   }
   else if(d=='3')
   {
    lseek(fdu,-200,SEEK_CUR);
    char cl3[100]="SL ";
    write(fdu,cl3,sizeof(cl3));
   }
   lseek(fdu,100,SEEK_CUR);

  }

  memset(buf,0,sizeof(buf));

  }
//  printf("%d \n",n);
  fl.l_type=F_UNLCK;
  close(fdu);
 }
 else if(ch=='5')
 {

fl.l_type=F_WRLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

 //printf("%s ",file_cust);
 int fdd=open(file_cust,O_RDWR) ;
 if(fdd<0)perror("open");
 //printf("%d \n",fdu);
 lseek(fdd,0,SEEK_SET);
char ticket[100];
char train_no[100];

read(nsd,ticket,100);
read(nsd,train_no,100);

 int k1=1,k2=0;
 int n;
 fcntl(fdd,F_SETLKW,&fl);
 char buf[400];
 int flag=0;
 while((n=read(fdd,buf,400))!=0)
  {

  //printf("%d \n",n);
   if(n==-1)perror("read");
    k1=1;k2=0;
  //Ticket check
  int i=0;
 while(buf[i] !='\0' && i<400)
  {
    if(ticket[i] !=buf[i]){k1=0;break;}
    i++;
  }
   //Train_no check
     if(buf[100]==train_no[0])k2=1;

  if(flag==0 && k1==1 && k2==1)
  {
    flag=1;
    lseek(fdd,-400,SEEK_CUR);
    char temp_buf[400];
    memset(temp_buf,'\0',sizeof(temp_buf));
    write(fdd,temp_buf,sizeof(temp_buf));


 int fd_t;
 if(train_no[0]=='A')
 {
  fd_t= open("train1.txt",O_RDWR,0777);
 }
 else if(train_no[0]=='B')
 {
   fd_t= open("train2.txt",O_RDWR,0777);
 }
 else if(train_no[0]=='C')
 {
   fd_t= open("train3.txt",O_RDWR,0777);
 }

 fcntl(fd_t,F_SETLKW,&fl);
 char value[4];

 read(fd_t,value,4);
 lseek(fd_t,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec--;
 sprintf(value,"%d",dec);
 write(fd_t,&value,4);
 fl.l_type=F_UNLCK;
  }

  }
 }

}


void bookag(int nsd)
{
char ch;
int num;
time_t curtime;
struct tm* loc_time;
curtime=time(NULL);
loc_time=localtime(&curtime);

  char name[10];

  char* message="\n\n\n\tName of the client";
  write(nsd,message,strlen(message));

  read(nsd,name,10);


   message="\n\n\n\tAvailable options are \n\n\n\t01.Book Ticket\n\n\n\t02.View Tickets";

  write(nsd,message,strlen(message));
  read(nsd,&ch,1);



  char file_cust[11];
  file_cust[0]='c';
  file_cust[1]='u';
  file_cust[2]='s';
  file_cust[3]=name[0];
  file_cust[4]=name[1];
  file_cust[5]=name[2];
  file_cust[6]=name[4];

  for(int i=7;i<10;i++)file_cust[i]='0';
  file_cust[10]='\0';

  struct flock fl;


  if(ch=='1')
{
char train_no[2];
message="\n\n\n\t01.TRAIN A\n\n\n\t02.TRAIN B\n\n\n\t03.TRAIN C\n\n\n\tSelect train(1-3)";
write(nsd,message,strlen(message));
read(nsd,train_no,1);


 fl.l_type=F_WRLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

if(train_no[0]=='1')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,1);

 int fd_t1=open("train1.txt",O_RDWR,0777);
 fcntl(fd_t1,F_SETLKW,&fl);
 char value[4];

 read(fd_t1,value,4);
 lseek(fd_t1,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t1,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);


 // Writing to the file
  char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"A");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));

  write(nsd,decchar,100);
  message="Train A";
  write(nsd,message,strlen(message));

  close(fd_t1);
  close(fd_cus);

}
else if(train_no[0]=='2')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,2);

int fd_t2=open("train2.txt",O_RDWR,0777);
fcntl(fd_t2,F_SETLKW,&fl);
 char value[4];

 read(fd_t2,value,4);
 lseek(fd_t2,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t2,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);

  char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"B");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));


  write(nsd,decchar,sizeof(decchar));
  message="Train B";
  write(nsd,message,strlen(message));
  close(fd_t2);
  close(fd_cus);
}
else if(train_no[0]=='3')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,1);

int fd_t3=open("train3.txt",O_RDWR,0777);
fcntl(fd_t3,F_SETLKW,&fl);
 char value[4];

 read(fd_t3,value,4);
 lseek(fd_t3,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t3,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);

   char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"C");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));


  write(nsd,decchar,sizeof(decchar));
  message="Train C";
  write(nsd,message,strlen(message));
  close(fd_t3);
  close(fd_cus);
}

}
  else if(ch=='2')
  {
 fl.l_type=F_RDLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

   int fdv=open(file_cust,O_RDONLY) ;
   lseek(fdv,0,SEEK_SET);
   fcntl(fdv,F_SETLKW,&fl);

  int n;
  char buf1[100];

 while((n=read(fdv,buf1,100) )!=0)
  {
    if(n==-1)break;
    //printf("%s \n",buf1);
    write(nsd,buf1,100);
    memset(buf1,0,sizeof(buf1));
  }

  fl.l_type=F_UNLCK;
  close(fdv);

  }

memset(file_cust,'0',sizeof(file_cust));
}



void book(int nsd,char* name)
{
char ch;
int num;
time_t curtime;
struct tm* loc_time;
curtime=time(NULL);
loc_time=localtime(&curtime);

char* message="\n\n\n\tWELCOME TO RAILWAY PORTAL\n\n\n\tAvailable facalities are\n\n\n\t01.Book Ticket\n\n\n\t02.View Previous Bookings\n\n\n\t03.Update Booking\n\n\n\t04.Cancel Booking\n\n\n\tSelect from (1-4)\n";

write(nsd,message,strlen(message));

read(nsd,&ch,1);

 char file_cust[11];
  file_cust[0]='c';
  file_cust[1]='u';
  file_cust[2]='s';
  file_cust[3]=name[0];
  file_cust[4]=name[1];
  file_cust[5]=name[2];
  file_cust[6]=name[4];

  for(int i=7;i<10;i++)file_cust[i]='0';
  file_cust[10]='\0';

struct flock fl;

if(ch=='1')
{
char train_no;
message="\n\n\n\t01.TRAIN A\n\n\n\t02.TRAIN B\n\n\n\t03.TRAIN C\n\n\n\tSelect train(1-3)";
write(nsd,message,strlen(message));
read(nsd,&train_no,1);


 fl.l_type=F_WRLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

if(train_no=='1')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,1);

 int fd_t1=open("train1.txt",O_RDWR,0777);
 fcntl(fd_t1,F_SETLKW,&fl);
 char value[4];

 read(fd_t1,value,4);
 lseek(fd_t1,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t1,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);


 // Writing to the file
  char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"A");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));

  write(nsd,decchar,100);
  message="Train A";
  write(nsd,message,strlen(message));

  close(fd_t1);
  close(fd_cus);
}
else if(train_no=='2')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,2);

int fd_t2=open("train2.txt",O_RDWR,0777);
fcntl(fd_t2,F_SETLKW,&fl);
 char value[4];

 read(fd_t2,value,4);
 lseek(fd_t2,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t2,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);

  char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"B");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));


  write(nsd,decchar,sizeof(decchar));
  message="Train B";
  write(nsd,message,strlen(message));
  close(fd_t2);
  close(fd_cus);
}
else if(train_no=='3')
{
 char cls[2];
 message="\n\n\n\tSelect the class\n\n\n\t01.First AC\n\n\n\t02.Second AC\n\n\n\t03.Sleeper\n\n\n\tSelect from (1-3)";
 write(nsd,message,strlen(message));
 read(nsd,&cls,1);

int fd_t3=open("train3.txt",O_RDWR,0777);
fcntl(fd_t3,F_SETLKW,&fl);
 char value[4];

 read(fd_t3,value,4);
 lseek(fd_t3,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec++;
 sprintf(value,"%d",dec);
 write(fd_t3,&value,4);
 fl.l_type=F_UNLCK;


  int  fd_cus=open(file_cust,O_CREAT|O_RDWR|O_APPEND,0777);
  lseek(fd_cus,0,SEEK_SET);
  fcntl(fd_cus,F_SETLKW,&fl);

   char decchar[100];
  sprintf(decchar,"%d",dec);
  strcpy(cus.ticket,decchar);
  strcpy(cus.train_no,"C");
  strcpy(cus.date,asctime(loc_time));

  if(cls[0]=='1')strcpy(cus.class,"1AC");
  else if(cls[0]=='2')strcpy(cus.class,"2AC");
  else if(cls[0]=='3')strcpy(cus.class,"SL ");

  write(fd_cus,&cus,sizeof(cus));
  fl.l_type=F_UNLCK;

  message="Ticket booked\nTicket no\n";
  write(nsd,message,strlen(message));


  write(nsd,decchar,sizeof(decchar));
  message="Train C";
  write(nsd,message,strlen(message));
  close(fd_t3);
  close(fd_cus);
}

}
else if(ch=='2')
{

 fl.l_type=F_RDLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

   int fdv=open(file_cust,O_RDONLY) ;
   lseek(fdv,0,SEEK_SET);
   fcntl(fdv,F_SETLKW,&fl);

  int n;
  char buf1[100];

 while((n=read(fdv,buf1,100) )!=0 )
  {
    if(n==-1)break;
    //printf("%d \n",n);
    write(nsd,buf1,100);
    memset(buf1,0,sizeof(buf1));
  }


  fl.l_type=F_UNLCK;
  close(fdv);

}
else if(ch=='3')
{

 fl.l_type=F_WRLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

 //printf("%s ",file_cust);
 int fdu=open(file_cust,O_RDWR) ;
 if(fdu<0)perror("open");
 //printf("%d \n",fdu);
 lseek(fdu,0,SEEK_SET);
char ticket[100];
char train_no[100];

read(nsd,ticket,100);
read(nsd,train_no,100);

 int k1=1,k2=0;

 int n;
 fcntl(fdu,F_SETLKW,&fl);
 char buf[400];
 int flag=0;
 while((n=read(fdu,buf,400))!=0)
  {

  //printf("%d \n",n);
   if(n==-1)perror("read");
    k1=1;k2=0;
  //Ticket check
  int i=0;
 while(buf[i] !='\0' && i<400)
  {
    if(ticket[i] !=buf[i]){k1=0;break;}
    i++;
  }
   //Train_no check
     if(buf[100]==train_no[0])k2=1;

  if(flag==0 && k1==1 && k2==1)
  {
    flag=1;
    char d;
    message="Enter class you want to change -1AC ,2AC, SL\n Give (1-3)";
    write(nsd,message,strlen(message));
    read(nsd,&d,1);
   if(d=='1')
   {
   lseek(fdu,-200,SEEK_CUR);
    char cl1[100]="1AC";
    write(fdu,cl1,sizeof(cl1));
   }
   else if(d=='2')
   {
    lseek(fdu,-200,SEEK_CUR);
    char cl2[100]="2AC";
    write(fdu,cl2,sizeof(cl2));
   }
   else if(d=='3')
   {
    lseek(fdu,-200,SEEK_CUR);
    char cl3[100]="SL ";
    write(fdu,cl3,sizeof(cl3));
   }
   lseek(fdu,100,SEEK_CUR);

  }

  memset(buf,0,sizeof(buf));

  }
//  printf("%d \n",n);
  fl.l_type=F_UNLCK;
  close(fdu);

}
else if(ch=='4')
{
 fl.l_type=F_WRLCK;
 fl.l_whence=SEEK_SET;
 fl.l_start=0;
 fl.l_len=0;
 fl.l_pid=getpid();

 //printf("%s ",file_cust);
 int fdd=open(file_cust,O_RDWR) ;
 if(fdd<0)perror("open");
 //printf("%d \n",fdu);
 lseek(fdd,0,SEEK_SET);
char ticket[100];
char train_no[100];

read(nsd,ticket,100);
read(nsd,train_no,100);

 int k1=1,k2=0;
 int n;
 fcntl(fdd,F_SETLKW,&fl);
 char buf[400];
 int flag=0;
 while((n=read(fdd,buf,400))!=0)
  {

  //printf("%d \n",n);
   if(n==-1)perror("read");
    k1=1;k2=0;
  //Ticket check
  int i=0;
 while(buf[i] !='\0' && i<400)
  {
    if(ticket[i] !=buf[i]){k1=0;break;}
    i++;
  }
   //Train_no check
     if(buf[100]==train_no[0])k2=1;

  if(flag==0 && k1==1 && k2==1)
  {
    flag=1;
    lseek(fdd,-400,SEEK_CUR);
    char temp_buf[400];
    memset(temp_buf,'\0',sizeof(temp_buf));
    write(fdd,temp_buf,sizeof(temp_buf));


 int fd_t;
 if(train_no[0]=='A')
 {
  fd_t= open("train1.txt",O_RDWR,0777);
 }
 else if(train_no[0]=='B')
 {
   fd_t= open("train2.txt",O_RDWR,0777);
 }
 else if(train_no[0]=='C')
 {
   fd_t= open("train3.txt",O_RDWR,0777);
 }

 fcntl(fd_t,F_SETLKW,&fl);
 char value[4];

 read(fd_t,value,4);
 lseek(fd_t,0,SEEK_SET);
 int dec;
 sscanf(value,"%d",&dec);
  dec--;
 sprintf(value,"%d",dec);
 write(fd_t,&value,4);
 fl.l_type=F_UNLCK;
  }

  }

}

memset(file_cust,'0',sizeof(file_cust));
}


int custlogin(int nsd,char* name)
{


char* message="\n\n\tDo you have existing account ?\n\n\t Give Yes or No ";


	 write(nsd,message,strlen(message));


         char buf[3];
        read(nsd,buf,3);



         char name_customer[10];
         char pass_customer[10];

	 if(buf[0]=='Y')
	 {
	 message="\n\n\tPlease login into your account\n\n\t Enter your name : \n";

	 write(nsd,message,strlen(message));


	 read(nsd,name_customer,10);

	 message="\n\n\tEnter your password : \n";


	 write(nsd,message,strlen(message));
	 read(nsd,pass_customer,10);





	 char line[20];

	 int fd_customer=open("loginc.txt",O_RDONLY);
         int n,f=0;

	 while((n=read(fd_customer,line,21)) !=0)
	 {

	    int k1=0;
            for(int i=0;i<10;i++)
	    {
            if(name_customer[i]==line[i]){k1++;}
            else break;
            }

	    int k2=0;
            for(int i=0;i<10;i++)
	    {

             if(pass_customer[i]==line[i+10]){k2++;}
	     else break;
	    }


	    if(k1==10 && k2==10)
	    {
		 for(int i=0;i<10;i++)name[i]=name_customer[i];
		 message="\n\n\tLogin Successful            \n";
	     write(nsd,message,strlen(message));
	     f=1;break;


	    }

	 memset(line,'0',20);
	 }

	 if(f==0)
	 {
		 message="\n\n\tNo such account found!      \n";
		 write(nsd,message,strlen(message));

          return 0;
	 }
	 lseek(fd_customer,0,SEEK_SET);
     close(fd_customer);
     }
    else if(buf[0]=='N')
	 {
	 message="\n\n\tPlease create your account\n\n\t Enter your name :";

         memset(name_customer,'`',10);
	 memset(pass_customer,'`',10);
       	 write(nsd,message,strlen(message));
         read(nsd,name_customer,10);

	 message="\n\n\tEnter your password : \n";


  	 write(nsd,message,strlen(message));
         read(nsd,pass_customer,10);

	 int fd_customer=open("loginc.txt",O_CREAT|O_WRONLY|O_APPEND,0777);
	 write(fd_customer,name_customer,10);
	 write(fd_customer,pass_customer,10);

     for(int i=0;i<10;i++)name[i]=name_customer[i];
	 message="\n\n\tAccount created successfully\n";

	 write(nsd,message,strlen(message));
    close(fd_customer);
	 }

  return 1;
}



int agentlogin(int nsd)
{
char* message="\n\n\tDo you have existing account ?\n\n\t Give Yes or No ";


	 write(nsd,message,strlen(message));


         char buf[3];
        read(nsd,buf,3);



         char name_agent[10];
         char pass_agent[10];

	 if(buf[0]=='Y')
	 {
	 message="\n\n\tPlease login into your account\n\n\t Enter your name : \n";

	 write(nsd,message,strlen(message));


	 read(nsd,name_agent,10);

	 message="\n\n\tEnter your password : \n";


	 write(nsd,message,strlen(message));
	 read(nsd,pass_agent,10);





	 char line[20];

	 int fd_agent=open("loginag.txt",O_RDONLY);
         int n,f=0;

	 while((n=read(fd_agent,line,21)) !=0)
	 {

	    int k1=0;
            for(int i=0;i<10;i++)
	    {
            if(name_agent[i]==line[i]){k1++;}
            else break;
            }

	    int k2=0;
            for(int i=0;i<10;i++)
	    {

             if(pass_agent[i]==line[i+10]){k2++;}
	     else break;
	    }


	    if(k1==10 && k2==10)
	    { message="\n\n\tLogin Successful            \n";
	     write(nsd,message,strlen(message));
	     f=1;break;


	    }

	 memset(line,'0',20);
	 }

	 if(f==0)
	 {
		 message="\n\n\tNo such account found!      \n";
		 write(nsd,message,strlen(message));

      return 0;
	 }
	 lseek(fd_agent,0,SEEK_SET);

         }
         else if(buf[0]=='N')
	 {
	 message="\n\n\tPlease create your account\n\n\t Enter your name :";

         memset(name_agent,'`',10);
	 memset(pass_agent,'`',10);
       	 write(nsd,message,strlen(message));
         read(nsd,name_agent,10);

	 message="\n\n\tEnter your password : \n";


  	 write(nsd,message,strlen(message));
         read(nsd,pass_agent,10);

	 int fd_customer=open("loginag.txt",O_CREAT|O_WRONLY|O_APPEND,0777);
	 write(fd_customer,name_agent,10);
	 write(fd_customer,pass_agent,10);


	 message="\n\n\tAccount created successfully\n";

	 write(nsd,message,strlen(message));
	 }

return 1;
}


int adminlogin(int nsd)
{

   char name_admin[10];
	 char pass_admin[10];


	 char* message="\n\n\tPlease login into your account\n\n\t Enter your name : \n";

	 write(nsd,message,strlen(message));


	 read(nsd,name_admin,10);

	 message="\n\n\tEnter your password : \n";
	 write(nsd,message,strlen(message));
	 read(nsd,pass_admin,10);

          int k1,k2;

         if(name_admin[0]=='a'&& name_admin[1]=='d'&& name_admin[2]=='m'&& name_admin[3]=='i'&& name_admin[4]=='n')k1=1;

		 if(pass_admin[0]=='1'&& pass_admin[1]=='2'&& pass_admin[2]=='3'&& pass_admin[3]=='a'&& pass_admin[4]=='d'&& pass_admin[5]=='m')k2=1;

      //printf("%d %d \n",k1,k2);
	    if(k1==1 && k2==1)
	    { message="\n\n\tLogin Successful\n            ";
	     write(nsd,message,strlen(message));
	    }
       else
    	 {
		 message="\n\n\tNo such account found! \n     ";
		 write(nsd,message,strlen(message));
         return 0;
	     }


return 1;

}

void* thread_start(void *sock)
{
int nsd=*(int*)sock;

char ch;


char* message="\n\n\n\n\t ONLINE TICKET RESERVATION SYSTEM \n\n\n\tMAIN MENU\n\n\n\t01.Normal Account\n\n\n\t02.Agent Account\n\n\n\t03.Administrative Account\n\n\n\t Select your account (1-3)";

write(nsd,message,strlen(message));
int n=read(nsd,&ch,1);

    int r;


   if(ch=='1') //normal account
   {
	     char name[10];
    r= custlogin(nsd,name);

	if(r==1) book(nsd,name);

   }
   else if(ch =='2') //Agent account
   {
    r=agentlogin(nsd);

	if(r==1)bookag(nsd);
   }
   else if(ch=='3') //Administrator account
   {
    r=adminlogin(nsd);
   if(r==1)bookad(nsd);
   }


close(nsd);

pthread_exit(NULL);
}




void main()
{

struct sockaddr_in serv,cli;

int nsd,sd;
sd=socket(AF_UNIX,SOCK_STREAM,0);

serv.sin_family=AF_UNIX;
serv.sin_addr.s_addr=INADDR_ANY;
serv.sin_port=htons(7521);

bind(sd,(void*)&serv,sizeof(serv));
listen(sd,50);



int sz=sizeof(cli);
pthread_t mythread[NUM_THREADS];
int k=0;
while(1)
{
nsd=accept(sd,(void*)&cli,&sz);

if(nsd<0)exit(1);

int r=pthread_create(&mythread[k++],NULL,thread_start,(void*)&nsd);

if(r !=0)
{
printf("Could not create thread\n");
}

if(k>=50)
{
  k=0;
  while(k<50)
  {
    pthread_join(mythread[k++],NULL);
  }
  k++;
}

}

close(sd);
}
