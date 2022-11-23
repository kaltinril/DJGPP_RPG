void change_tile()
{

 int ch_ny=(ch_y-4)+ch_zy,ch_nx=(ch_x)+ch_zx,ary=0;
 ch_ny=(ch_ny*100);
 ary=ch_ny+ch_nx;
 int nd=0;
 switch (action){
  case 0: //copy   c
	temptile=screen_1[layer][ary];
	gotoxy(1,1);
  break;
  case 1: //cut    x
	temptile=screen_1[layer][ary];
	screen_1[layer][ary]=20;
  break;
  case 2: //paste  v
	screen_1[layer][ary]=temptile;
  break;
  case 3: //delete z
	screen_1[layer][ary]=20;
  break;
  case 4: //remove layer
    for (nd=0;nd<9600;++nd)
    {
    screen_1[layer][nd]=20;
    }
  break;

  default:

  break;
 }

}

int pick_tile()
{
 int x1=0,y1=0,xn=0,yn=0;
 int gol=1;
 char key=0;
 int arry=0;
 while (gol==1)
 {
 key=0;
  memcpy(double_buffer,tile,64000);
  if (kbhit()){key=getch();}
  if (key=='q' || key=='Q'){gol=0;}
  if (key==LEFT){--x1;}
  if (key==RIGHT){++x1;}
  if (key==UP){--y1;}
  if (key==DOWN){++y1;}
  if (x1<0){x1=0;}
  if (y1<0){y1=0;}
  if (x1>19){x1=19;}
  if (y1>11){y1=11;}
    if (key==' '){return((y1*20)+x1);}
  xn=x1*16;
  yn=y1*16;
  arry=(y1*20)+x1;
  rect_fast(xn,yn,xn+15,yn+15,4);
  memcpy(screen,double_buffer,64000);
  gotoxy(1,22);
  cout<<"Tile:"<<arry<<"\n"
      <<"Trans:"<<int(trans[arry])
      <<" |Walkn:"<<int(walkn[arry])
      <<" |ACTrg"<<int(actrg[arry])<<"|ANIMI:"<<int(array_count[0][arry])<<"\n";
  if (key=='a' || key=='a')
  {
   Clear(0,screen);
   memcpy(screen,tile,64000);
   gotoxy(1,1);
   cout<<"0=off/1=on\n";
   gotoxy(1,2);
   cout<<"Transparency 0/1\n";
   trans[arry]=(int(getch())-48);
   gotoxy(1,3);
   cout<<"Walkability 0/1\n";
   walkn[arry]=(int(getch())-48);
   gotoxy(1,4);
   cout<<"Animation Value\n";
   array_count[0][arry]=(int(getch())-48);
   gotoxy(1,5);
   cout<<"Action Trigger Value.. 5=warp 0=normal\n";
   actrg[arry]=(int(getch())-48);
  }
 }
 return (20);
}




long pick_map_place(long arry)
{
int x=0,y=0;
 while (arry>9)
 {
  arry=arry-10;
  ++x;
 }
 y=arry;
  set_fname(x,y);
  int gss=1;
  char key=0;
  int movesl=0,um=0,chg=0;
  int n=0,xy=0;
  tempary=ary;
  while (gss==1)
 {
 key=0;  //reset the key buffer
 if (kbhit()){key=get_keys();}   //check for a key
 if (key=='q' || key=='Q'){gss=34;}
 gss=checkin_key(key);     //send key to check function to check for action
 movesl=1;y_dir=0;x_dir=0;um=0;
 check_key(key);
 if (key!=LEFT && key!=RIGHT && key!=UP && key!=DOWN){movesl=0;}
            //if you did not hit a direct don't animate
 if (way>1){way=0;}     //used to put the character in a certain direction
 if (ch_x+x_dir<0){movesl=0;}
 if (ch_y+y_dir<4){movesl=0;}
 if (movesl==1) //checks to see if they hit a wall when they hit a key
 {
  chg=(x_dir*-16);     //sets it up like your automaticly going to go x
  xy=0;          //0 is for x and 1 will make it change y instead
  if (y_dir!=0)
  {xy=1;chg=(y_dir*-16);}
  blitz(chg,xy); //animate in here
  Clear(0,double_buffer);
  ++amt;
  ++cycle;
  check_cycle(cycle);
  cy_off=0;
  //put restictions here
  ch_x=ch_x+x_dir;
  ch_y=ch_y+y_dir;//moves the player or at least his pict
 if (ch_x<0){ch_x=0;}
 if (ch_y<0){ch_y=0;}

 } //end if there is no wall
 else
 {
  blitz(0,0);
  Clear(0,double_buffer);
 } //end else if thre is no wall, so thre is a wall, don't animate or move
  n=0;
  ++amt;
  ++cycle;
  check_cycle(cycle);
  if (key!=NULL)
  {
	check_action(0);
  } //end if key!=null

 }
 return(tempary);
}





int checkin_key(char key)
{
  if (key=='1'){++draw_0;if(draw_0>1){draw_0=0;}}
  if (key=='2'){++draw_1;if(draw_1>1){draw_1=0;}}
  if (key=='3'){++draw_2;if(draw_2>1){draw_2=0;}}
  if (key=='0'){++draw_3;if(draw_3>1){draw_3=0;}}
  if (key=='q' || key=='Q'){return(-1);}
  nostop=1;
  if (key=='s' || key=='S'){gotoxy(1,1);cout<<"Save as...";get_file();save_map();make_map();}
  if (key=='o' || key=='O'){gotoxy(1,1);cout<<"open...";get_file();open_map();load_pcx(tile,320,200,pcx_name,0,255,0);}
  int ch_ny=(ch_y-4)+ch_zy,ch_nx=(ch_x)+ch_zx;
  ch_ny=(ch_ny*100);
  ary=ch_ny+ch_nx;
  if (key==' '){tempary=ary;return(-1);}
  gotoxy(1,1);

  return(1);
  }



  long pick_map()
  {
  long mapary=11;
  long nn=0;
  char testeof[1];
  long map_cnt=0;
  long b_read_t=0;
  int grip=open("mainlist.lst",O_RDONLY|O_BINARY);
  int fl=filelength(grip);
  Clear(0,screen);
  unsigned char **maps_lists=new unsigned char*[fl/12];
  for (nn=0;nn<fl/12;++nn)
  {
   maps_lists[nn]=new unsigned char[13];
  }
  nn=0;
  cout<<fl<<"Filelength"<<nn<<"\n";
  getch();
  while (nn==0)
  {
   ++map_cnt;
   read(grip,maps_lists[map_cnt-1],12);
   maps_lists[map_cnt-1][12]='\0';
   b_read_t=b_read_t+12;
   if (b_read_t>=fl){nn=1;}

  }
  cout<<"byetread"<<b_read_t<<"\n";
  for (nn=0;nn<fl/12;++nn)
  {
   cout<<"Map:"<<nn+1<<" MAPNAME:"<<maps_lists[nn]<<"\n";
  }
  cout<<map_cnt<<"map count\n";
  getch();
   close(grip);


   int going=1;
   char key=0;
   int start_a=0,n=0;
   int curs_a=0;
   char tstr[128];
   wina[winsa_tot].l=3;
   wina[winsa_tot].t=7;
   wina[winsa_tot].w=300;
   wina[winsa_tot].h=180;
   sprintf(wina[winsa_tot].s,"Map:%d...MapName:%s",n+1,maps_lists[0]);
   Clear(0,screen);
   Clear(0,text);
   draw_window(wina[winsa_tot].s,wina[winsa_tot].l,wina[winsa_tot].t,wina[winsa_tot].w,wina[winsa_tot].h);
   while(going==1)
   {
   key=0;
    if (kbhit()){key=getch();}
    if (key=='e' || key=='E'){going=34;}
    if (key==' ')
    {
     return((((curs_a+1)+start_a)*10)+1);
    }
    if (key=='8')
    {
     --curs_a;
     if (curs_a<0){curs_a=0;}
     if (start_a>0 && curs_a==0)
     {
      --start_a;
      if (start_a<0)
      {
      start_a=0;
      }
     }//moveup
    }
    if (key=='5')
    {
     ++curs_a;
     if (curs_a>12){curs_a=12;}
     if ((start_a+13)<map_cnt && curs_a==12)
     {
      ++start_a;
      if ((start_a+13)>map_cnt)
      {
      start_a=start_a-1;
      }
     }
    }//movedown
    if (key=='8' || key=='5'){Clear(0,double_buffer);Clear(0,text);    draw_window("",wina[winsa_tot].l,wina[winsa_tot].t,wina[winsa_tot].w,wina[winsa_tot].h);}
    locate(0,0,0);
    for (n=start_a;n<start_a+13;++n)
    {
        sprintf(tstr,"Map:%d...MapName:%s",n+1,maps_lists[n]);
        print(tstr);
    }

    locate(33,curs_a,winsa_tot);
    print(":.:");
    //cout<<"<\n";
    if ((start_a+13)<map_cnt){locate(36,12,winsa_tot);print(",");}
    if (start_a>0){locate(36,0,winsa_tot);print(",");}
    memcpy(double_buffer,text,64000);
    memcpy(screen,double_buffer,64000); 
   }
   return(mapary);
  }
