#include "graf3.h"
//#include <string.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <io.h>
#include <dir.h>
//#define S_IREAD 0x0100  /* owner may read */
//#define S_IWRITE 0x0080 /* owner may write */
fopen(int,char *, int);
showdir();
char screen_1[4][9600];
char tile_name[12];
main()
{
/////temp////////////////////////
 unsigned long i=0;
strncpy(tile_name, "main0001.pcx", 10);
 for (i=0;i<9600;++i)
 {
  screen_1[0][i]=9;
 }
 for (i=0;i<9600;++i)
 {
  screen_1[1][i]=10*((rand()%2)+1);
 }
 for (i=0;i<9600;++i)
 {
  screen_1[2][i]=5;
  if (rand()%2==1){screen_1[2][i]=20;}
 }
  for (i=0;i<9600;++i)
 {
  screen_1[3][i]=11;
  if (rand()%2==1){screen_1[3][i]=20;}
 }

/////temp////////////////////////
char filename[12];
char path[27];
char RfName[40];
int go=1;
char key=0;
int a=0;
while (go==1)
{
 gotoxy(1,1);
 cout<<"Q:  Quit\n"<<"1:  Open a file\n"<<"2:  Save file"<<"3:  New File";
 key=0;
 if (kbhit()){key=getch();}
 cout<<key<<"Key"<<int(key);
 delay(200);
 if (key=='q' || key=='Q'){go=90;}
 if (key=='1')
 				{
				 showdir();
				 gotoxy(1,4);
				 cout<<"Path:";
				 cin>>path;
				 cout<<"\nFilename:";
				 cin>>filename;
				 strncpy(RfName, path, strlen(path));
				 RfName[strlen(path)]='\0';
				 strncat(RfName, filename, strlen(filename));
				 cout<<RfName;
				 a=fopen(1,RfName,strlen(RfName));
				 if (a==1){gotoxy(10,10);cout<<"Invalid Path or File Already Exists";}
				 if (a==4){gotoxy(10,10);cout<<"File Not Found";}
				 for (a=0;a<320;++a)
				 {
				 cout<<int(screen_1[0][a]);
				 }
				 getch();
				}
 if (key=='3')
				{
				 showdir();
				 gotoxy(1,4);
				 cout<<"Path:";
				 cin>>path;
				 cout<<"\nFilename:";
				 cin>>filename;
				 strncpy(RfName, path, strlen(path));
				 RfName[strlen(path)]='\0';
				 strncat(RfName, filename, strlen(filename));
				 cout<<RfName;
				 a=fopen(0,RfName,strlen(RfName));
				 if (a==1){gotoxy(10,10);cout<<"Invalid Path or File Already Exists";}
				 if (a==4){gotoxy(10,10);cout<<"File Not Found";}
				}
 if (key=='2')
				{
				 showdir();
				 gotoxy(1,4);
				 cout<<"Path:";
				 cin>>path;
				 cout<<"\nFilename:";
				 cin>>filename;
				 strncpy(RfName, path, strlen(path));
				 RfName[strlen(path)]='\0';
				 strncat(RfName, filename, strlen(filename));
				 cout<<RfName;
				 a=fopen(2,RfName,strlen(RfName));
				 if (a==1){gotoxy(10,10);cout<<"Invalid Path or File Already Exists";}
				 if (a==4){gotoxy(10,10);cout<<"File Not Found";}
				}

}
}

showdir()
{
 cout<<"oops";

}

fopen(int how,char *filename,int length)
{
	int handle;
	//char msg[] = "Hello world";
	if (how==0){handle = open(filename, O_CREAT | O_TEXT , S_IWRITE | S_IREAD );}
	if (how==1){handle = open(filename, O_RDONLY | O_TEXT);}
	if (how==2){handle = open(filename, O_WRONLY | O_TEXT);}
	//if (how==3){handle = open(filename, O_RDWR | O_TEXT);}
	if (how==0 || how==2)
	{
	 write(handle, screen_1[0], 9600);
	 write(handle, screen_1[1], 9600);
	 write(handle, screen_1[2], 9600);
	 write(handle, screen_1[3], 9600);
	 write(handle, tile_name, strlen(tile_name));
	}
	if (how==1)
	{
	 read(handle, screen_1[0], 9600);
	 read(handle, screen_1[1], 9600);
	 read(handle, screen_1[2], 9600);
	 read(handle, screen_1[3], 9600);
	 read(handle, tile_name, 12);
	}
	close(handle);
	return (0);
}
