


void draw_map()
{
   //memcpy(to,from,length);
  int s=0;
  unsigned char *v,*c;
  v=screen;  //screen buffer
  c=prebuff; //buffer that tiles are put on, so i can copy only a certain amount
  for (s=0;s<192;++s)
  {
   memcpy(v,c,320);
   v=v+320;
   c=c+336;
  }


}
void keyupdate()
{
 keyhit=0;
 if (kbhit()){keyhit=getch();}
if (keyhit=='o'){options();}
if (keyhit=='c'){draw_tiles(worldlocx,worldlocy);}
if (keyhit=='g'){draw_tile(0,0,0);}
if (keyhit=='d'){draw_map();}
if (keyhit=='q' || keyhit=='Q'){quit=1;}
}

void options()
{
int nngo=0;
int nn=0;
char key=0;
long toff=0;
int maxopt=1;  //max options 0 would be only 1, 1 would be 2, 2 would be 3 options
while (nngo==0)
{
key=0;
if (kbhit()){key=getch();}
 gotoxy(1,1);
  draw_window("Options: 8/Up  5/Down  Space/Enter",3,7,312,186);
  print("Tiles");
  print("Exit");
  toff=(9<<8)+(9<<6)+5;dtbox(toff,75,8,5,32);
  toff=17+(nn*8);toff=(toff<<8)+(toff<<6)+5;dtbox(toff,75,8,4,32);
  memcpy(screen,text,64000);
  Clear(0,text);
  --winsa_tot;
  AUpdateAudio();
  if (key==32)
  {
   if (nn==0){edittiles();}
   if (nn==1){nngo=1;Clear(0,screen);}
  }
  if (key=='5'){++nn;if (nn>maxopt){nn=maxopt;}}
  if (key=='8'){--nn;if (nn<0){nn=0;}}
}
}

void dtbox(long arry,int w,int h,int color,int cl)
{
 int f=0,g=0,n=0;
 for (f=0;f<h;++f)
 {
  for (g=0;g<w;++g)
  {
   if (text[arry+g+n]==cl){text[arry+g+n]=color;}
  }
  n=n+320;
 }
}

void rect_fast(int left,int top, int right, int bottom, int color)
{
  unsigned int top_offset,bottom_offset,i,temp;

  if (top>bottom)
  {
	 temp=top;
	 top=bottom;
	 bottom=temp;
  }
  if (left>right)
  {
	 temp=left;
	 left=right;
	 right=temp;
  }

  top_offset=(top<<8)+(top<<6);
  bottom_offset=(bottom<<8)+(bottom<<6);

  for(i=left;i<=right;++i)
  {
	 double_buffer[top_offset+i]=color;
	 double_buffer[bottom_offset+i]=color;
  }
  for(i=top_offset;i<=bottom_offset;i=i+SCREEN_WIDTH)
  {
	 double_buffer[left+i]=color;
	 double_buffer[right+i]=color;
  }
}
