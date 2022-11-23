//loader.h
//open_map, opens a map file.

BOOL open_map()
  {
  char temp_char[13];
  unsigned char checkin[5];
  int n=0;
  //open map file
  int grip=open(RfName,O_RDONLY|O_BINARY);
  if(grip<0)
    return BAD;

  read(grip,checkin,4);

  if(strncmp((char *)checkin,"RACK",4))
    {
    close(grip);
    return (-1);
    }

  read(grip,checkin,4);

  if(strncmp((char *)checkin,"MYMP",4))
    {
    close(grip);
    return (-1);
    }
  read(grip,map_ver,1);
  if (map_ver>this_ver){Clear(0,screen);gotoxy(1,1);cout<<"Map is a newer version then this program can read.\nPlease download a newer version from\n http://members.xoom.com/rack/\n";return(-1);}
  read(grip,screen_1[0],9600);
  read(grip,screen_1[1],9600);
  read(grip,screen_1[2],9600);
  read(grip,screen_1[3],9600);
  read(grip,pcx_name,12);
  close(grip);

  strncpy(temp_char,(char *)pcx_name,9);
  temp_char[9]='\0';
  strncat(temp_char, "mor", 3);

  //open .mor file
  grip=open(temp_char,O_RDONLY|O_BINARY);
  read(grip,&tile_num,1);
  read(grip,walkn,240);
  read(grip,trans,240);
  read(grip,actrg,240);
  if (map_ver>0){read(grip,array_count[0],240);}
  if (map_ver==1)
  {
   for (n=0;n<240;++n)
   {
    if (array_count[0][n]!=0){array_count[2][n]=-1;array_count[3][n]=1;}
   }
  }
  if (map_ver>1){read(grip,array_count[2],240);read(grip,array_count[3],240);}
  read(grip,checkin,4);
  if(!strncmp((char *)checkin,"ITEM",4))
    {
    int i=0;
    read(grip,&item_tot,sizeof(short));
    for (i=0; i<item_tot; i++)
      {
      read(grip,&item_place[i],sizeof(short));
      read(grip,&item_name[i],sizeof(char));
      read(grip,&item_temp[i],sizeof(short));
      read(grip,&item_tmp2[i],sizeof(short));
      }
    }
  close(grip);
  }

BOOL save_map()
  {
  char temp_char[13];
  unsigned char checkin[5];

  //save map file
  int grip=open(RfName,O_RDWR|O_BINARY);
  if(grip<0)
    return BAD;

  write(grip,"RACK",4);
  write(grip,"MYMP",4);
  write(grip,this_ver,1);
  write(grip,screen_1[0],9600);
  write(grip,screen_1[1],9600);
  write(grip,screen_1[2],9600);
  write(grip,screen_1[3],9600);
  write(grip,pcx_name,12);
  close(grip);

  strncpy(temp_char,(char *)pcx_name,9);
  temp_char[9]='\0';
  strncat(temp_char, "mor", 3);

  //save .mor file
  grip=open(temp_char,O_RDWR|O_BINARY);
  write(grip,&tile_num,1);
  write(grip,walkn,240);
  write(grip,trans,240);
  write(grip,actrg,240);
  write(grip,array_count[0],240);
  write(grip,array_count[2],240);
  write(grip,array_count[3],240);
  write(grip,"ITEM",4);
  write(grip,&item_tot,sizeof(short));
  int i=0;
  for (i=0; i<item_tot; i++)
  {
   write(grip,&item_place[i],sizeof(short));
   write(grip,&item_name[i],sizeof(char));
   write(grip,&item_temp[i],sizeof(short));
   write(grip,&item_tmp2[i],sizeof(short));
  }
 close(grip);
}
BOOL make_map()
  {
  char temp_char[13];
  unsigned char checkin[5];

  //save map file
  int grip=open(RfName,O_CREAT | O_BINARY, S_IWRITE | S_IREAD );
  if(grip<0)
    return BAD;

  write(grip,"RACK",4);
  write(grip,"MYMP",4);
  write(grip,this_ver,1);
  write(grip,screen_1[0],9600);
  write(grip,screen_1[1],9600);
  write(grip,screen_1[2],9600);
  write(grip,screen_1[3],9600);
  write(grip,pcx_name,12);
  close(grip);

  strncpy(temp_char,(char *)pcx_name,9);
  temp_char[9]='\0';
  strncat(temp_char, "mor", 3);

  //save .mor file
  grip=open(temp_char,O_CREAT | O_BINARY, S_IWRITE | S_IREAD );
  write(grip,&tile_num,1);
  write(grip,walkn,240);
  write(grip,trans,240);
  write(grip,actrg,240);
  write(grip,array_count[0],240);
  write(grip,array_count[2],240);
  write(grip,array_count[3],240);
  write(grip,"ITEM",4);
  write(grip,&item_tot,sizeof(short));
  int i=0;
  for (i=0; i<item_tot; i++)
  {
   write(grip,&item_place[i],sizeof(short));
   write(grip,&item_name[i],sizeof(char));
   write(grip,&item_temp[i],sizeof(short));
   write(grip,&item_tmp2[i],sizeof(short));
  }
 close(grip);
}


void get_file()
{
	gotoxy(1,4);
	cout<<"Path:";
	cin>>path;
	cout<<"\nFilename:";
	cin>>filename;
	strncpy(RfName, path, strlen(path));
	RfName[strlen(path)]='\0';
	strncat(RfName, filename, strlen(filename));
}


