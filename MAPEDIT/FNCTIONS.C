void blitz(int x,int y)
{
  long s=0;
  int hg=0;
  if (draw_0==1){draw_tiles(screen_1[0],x,y);}
  if (draw_1==1){draw_tiles(screen_1[1],x,y);}
  if (draw_2==1){draw_tiles(screen_1[2],x,y);}
  draw_tile(ch_n+next_an_tile,(ch_zx*16)+cx_off,4+(ch_zy*16)+cy_off,way,0,0);
  rect_fast(160,100,175,115,31+way);
  if (draw_3==1){draw_tiles(screen_1[3],x,y);}
  int n=0;
  memcpy(temp,double_buffer,64000);
  Clear(0,double_buffer);
  s=2;
  int sch=2;
  long soff=((200/sch)*320);
  if (fullscreen==1){soff=0;}
  for (n=0;n<200;++n)
  {
   hg=0;
   if (n>=s){s=s+sch;hg=1;}
   if (fullscreen==1){hg=0;}
   if (hg==0){memcpy(soff+double_buffer,temp+1280+(n*320),320);soff=soff+320;}

  }
  for (n=4;n<69;++n)
  {
   memcpy(double_buffer+(n*320),text+(n*320),123);
  }
  while(inp(0x3DA) & 0x08 );
  while(!(inp(0x3DA) & 0x08 ));
  memcpy(screen+1280,double_buffer+1280,61440);  //copies LESS
}

char get_keys()
{
 char key=getch();
 return(key);
}

void check_d_key(char key)
{
  if (key=='z' || key=='Z'){++fullscreen;if (fullscreen==2){fullscreen=0;}}
  if (key=='1'){++draw_0;if(draw_0>1){draw_0=0;}}
  if (key=='2'){++draw_1;if(draw_1>1){draw_1=0;}}
  if (key=='3'){++draw_2;if(draw_2>1){draw_2=0;}}
  if (key=='0'){++draw_3;if(draw_3>1){draw_3=0;}}
  if (key=='+'){++addn;++addn;if (addn>16){addn=16;}}
  if (key=='-'){--addn;--addn;if (addn<1){addn=1;}}
  if (key=='n' || key=='N'){draw_0=1;draw_1=1;draw_2=1;draw_3=1;addn=2;}
  if (key=='f'){amt=0; start=clock();}
  if (key=='q' || key=='Q'){gon=0;}
  if (key=='b' || key=='B'){++action_ab;if (action_ab==1){action_ab=13;}if (action_ab==14){action_ab=0;}}
  nostop=1;
  if (key=='s' || key=='S'){gotoxy(1,1);cout<<"Save as...";get_file();save_map();make_map();}
  if (key=='o' || key=='O'){gotoxy(1,1);cout<<"open...";get_file();open_map();map_now[0]=-1;map_now[1]=-1;}
  if (key=='z' || key=='Z'){action=3;}
  if (key=='x' || key=='X'){action=1;}
  if (key=='c' || key=='C'){action=0;}
  if (key=='v' || key=='V'){action=2;}
  if (key=='d' || key=='D'){action=4;}
  if (key=='a' || key=='A'){action=5;}
  if (key=='g' || key=='G'){temptile=pick_tile();cout<<"temptile"<<int(temptile)<<"\n";getch();}
  if (key=='l' || key=='L'){++layer;if (layer>3){layer=0;}}
  if (key==' '){change_tile();}
  if (key=='m' || key=='M'){menu_sys();}
  int ch_ny=(ch_y-4)+ch_zy,ch_nx=(ch_x)+ch_zx;
  ch_ny=(ch_ny*100);
  ary=ch_ny+ch_nx;
  gotoxy(1,1);
  char lstrg[128];
  sprintf(lstrg,"Layer:%d",int(layer));
  draw_window(lstrg,3,7,117,57);
  sprintf(lstrg,"Ary:%d",ary);
  print(lstrg);
  sprintf(lstrg,"TileValue:%d",int(screen_1[layer][ary]));
  print(lstrg);
  sprintf(lstrg,"item 0 warp 1 ");
  print(lstrg);
  print("Q.....Quit");
}

void check_cycle(int c)
{
 int n=0;
  if (c>100){cycle=0;}
  if (cycle%5==0)
  {
   for (n=0;n<240;++n)
   if (array_count[0][n]>=array_count[1][n]){++array_count[1][n];}
   n=0;
  } //end if c%5
}