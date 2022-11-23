void change_tile()
{

 int ch_ny=(ch_y-4)+6,ch_nx=(ch_x)+10,ary=0;
 ch_ny=(ch_ny*100);
 ary=ch_ny+ch_nx;

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
  if (key==' '){return((y1*20)+x1);}
  if (x1<0){x1=0;}
  if (y1<0){y1=0;}
  if (x1>19){x1=19;}
  if (y1>11){y1=11;}
  xn=x1*16;
  yn=y1*16;
  arry=(y1*20)+x1;
  rect_fast(xn,yn,xn+15,yn+15,4);
  memcpy(screen,double_buffer,64000);
  gotoxy(1,22);
  cout<<"Tile:"<<arry<<"\n"
      <<"Trans:"<<int(trans[arry])
      <<" |Walkn:"<<int(walkn[arry])
      <<" |ANIMI:"<<int(array_count[1][arry])<<"|ANIMI:"<<int(array_count[0][arry])<<"\n";
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
  }
 }
 return (20);
}
