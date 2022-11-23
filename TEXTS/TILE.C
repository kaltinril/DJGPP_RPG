draw_tile(int tilen,int x,int y)
{
int yy=0,xx=0; //create variables used to get the tile places
x=x*16;
y=y*16;
xx=tilen*16;
while(xx>319) //convert the tilenumber to an x an y on the tile place
{
 xx=xx-320;
 yy=yy+16;
}
//draw the tile into the prebuffer without transparency
  int lx=0,ly=0;
  for (ly=0;ly<16;++ly)
  {
   for (lx=0;lx<16;++lx)
   {
    prebuff[((y+ly)*336)+x+lx]=tile[((yy+ly)*320)+xx+lx];
   }
  }
if (tiles[tilen].trans==1)
{
//draw the tile into the prebuffer with transparency

}

};

draw_tiles(int wx,int wy)
{
int y=0,x=0,n=0;
int ny=0;//ny new y
 for (n=0;n<3;++n)
 {
 for (y=0;y<13;++y)
 {
 ny=wy+y;
 ny=ny*20;
  for (x=0;x<21;++x)
  {
   draw_tile(world[n][ny+x],x,y);
  }
 }
 }
};


//edittiles area to edit the tiles attributes
void edittiles()
{
 int nngo=0;
 char key=0;
 int yy=0,xx=0;
 while (nngo==0)
 {
   AUpdateAudio();
  key=0;
  if (kbhit()){key=getch();}
  memcpy(double_buffer,tile,64000);
  if (key==32){changetiles((yy<<8)+(yy<<6)+xx);}
  if (key=='q' || key=='Q'){nngo=1;}
  if (key=='4'){--xx;if (xx<0){xx=0;}}
  if (key=='6'){++xx;if (xx>19){xx=19;}}
  if (key=='8'){--yy;if (yy<0){yy=0;}}
  if (key=='5'){++yy;if (yy>11){yy=11;}}
  rect_fast(xx*16,yy*16,(xx*16)+15,(yy*16)+15,4);
  memcpy(screen,double_buffer,64000);
 }

}

void changetiles(int datile)
{
  int ngn=0;
  int nn=0;
  long toff=0;
  char key=0;
  int maxatt=3; //max attributes on the tiles
  while (ngn==0)
  {
  key=0;
  if (kbhit()){key=getch();}
  if (key=='5'){++nn;if (nn>maxatt){nn=maxatt;}}
  if (key=='8'){--nn;if (nn<0){nn=0;}}
  gotoxy(1,1);
  draw_window("Tile Attributes",3,7,150,12);
  toff=(9<<8)+(9<<6)+5;dtbox(toff,135,8,5,32);
  draw_window("",5,27,144,69);
  print("Walkability");
  print("Action");
  print("Transparency");
  print("Animate");
  toff=29+(nn*8);toff=(toff<<8)+(toff<<6)+7;dtbox(toff,135,8,4,32);
  memcpy(screen,text,64000);
  Clear(0,text);
  winsa_tot=winsa_tot-2;

  AUpdateAudio();
  }
}
