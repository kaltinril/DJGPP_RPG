#include <dpmi.h>
#include <sys/nearptr.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>
#include <dos.h>
#include <go32.h>
#include <pc.h>
#include <io.h>
#include <iostream.h>
#include <fstream.h>


#define ON 1
#define OFF (0)

unsigned char *screen;
unsigned char *double_buffer=new unsigned char[64000];
unsigned char *temp=new unsigned char[64000];
#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define SCREEN_SIZE         SCREEN_WIDTH*SCREEN_HEIGHT

void near_ptr(char on_off)
  {
  if(on_off==ON)
    {
    if(__djgpp_nearptr_enable()==0)
      exit(1);
    screen=(unsigned char *)0xA0000+__djgpp_conventional_base;
    }
  else
    __djgpp_nearptr_disable();
  }

Clear(unsigned char color,unsigned char *ary)
{
 memset(ary,color,64000);
}
void set_mode(unsigned int mode)
  {
  __dpmi_regs regs;
  memset(&regs, 0, sizeof(regs));
  regs.x.ax=mode;
  __dpmi_int(0x10, &regs);
  }

#define sgn(x) ((x<0)?-1:((x>0)?1:0))  //macro to return the sign of a


void Line_f(int x1, int y1, int x2, int y2, int color)
{
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;

  screen[(py<<8)+(py<<6)+px]=color;

  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
	 for(i=0;i<dxabs;i++)
	 {
		y+=dyabs;
		if (y>=dxabs)
		{
		  y-=dxabs;
		  py+=sdy;
		}
		px+=sdx;
		screen[(py<<8)+(py<<6)+px]=color;
	 }
  }
  else /* the line is more vertical than horizontal */
  {
	 for(i=0;i<dyabs;i++)
	 {
		x+=dxabs;
		if (x>=dyabs)
		{
		  x-=dyabs;
		  px+=sdx;
		}
		py+=sdy;
		screen[(py<<8)+(py<<6)+px]=color;
	 }
  }
}


void Line_s(int x1, int y1, int x2, int y2, int color,unsigned char *pointer,
				int st_x,int st_y,int ed_x,int ed_y)
{
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;

  if (py<ed_y+1 && py>st_y-1 && px<ed_x+1 && px>st_x-1){pointer[(py<<8)+(py<<6)+px]=color;}

  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
	 for(i=0;i<dxabs;i++)
	 {
		y+=dyabs;
		if (y>=dxabs)
		{
		  y-=dxabs;
		  py+=sdy;
		}
		px+=sdx;
		if (py<ed_y+1 && py>st_y-1 && px<ed_x+1 && px>st_x-1){pointer[(py<<8)+(py<<6)+px]=color;}
	 }
  }
  else /* the line is more vertical than horizontal */
  {
	 for(i=0;i<dyabs;i++)
	 {
		x+=dxabs;
		if (x>=dyabs)
		{
		  x-=dyabs;
		  px+=sdx;
		}
		py+=sdy;
		if (py<ed_y+1 && py>st_y-1 && px<ed_x+1 && px>st_x-1){pointer[(py<<8)+(py<<6)+px]=color;}
	 }
  }
}



void circle_rad(int x,int y)
{
 int radii;
 long sa=(y<<8)+(y<<6)+x;
 int chx=0,chy=0,chyn=0,chxn=0,i=0;
 float rad=0,add=(3.1426/2)/90;
 for (radii=3;radii<50;++radii)
 {
 chx=0;
 chy=0;
 rad=0;
  while (chx>=chy)
  {
	chx=int(cos(rad)*radii);  //replace cos with a look up thing
	chy=int(sin(rad)*radii);  //replace sin with a look up thing
	chyn=(chy<<8)+(chy<<6);
	chxn=(chx<<8)+(chx<<6);
	screen[(sa+chyn)+chx]=double_buffer[(sa+chyn)+chx];    //Quad 1:Y and X normal
	 screen[(sa+chxn)+chy]=double_buffer[(sa+chxn)+chy];   //Quad 1:Y and X switched, Complimentary.
	screen[(sa-chyn)+chx]=double_buffer[(sa-chyn)+chx];    //Quad 2:Y and X normal
	 screen[(sa-chxn)+chy]=double_buffer[(sa-chxn)+chy];   //Quad 2:Y and X switched, Complimentary.
	screen[(sa-chyn)-chx]=double_buffer[(sa-chyn)-chx];    //Quad 3:Y and X normal
	 screen[(sa-chxn)-chy]=double_buffer[(sa-chxn)-chy];   //Quad 3:Y and X switched, Complimentary.
	screen[(sa+chyn)-chx]=double_buffer[(sa+chyn)-chx];    //Quad 4:Y and X normal
	 screen[(sa+chxn)-chy]=double_buffer[(sa+chxn)-chy];   //Quad 4:Y and X switched, Complimentary.
	rad=rad+add;
  }
 }
}

void circlen(int x,int y,int color,int r,int d)
{
 int radii;
 long sa=(y<<8)+(y<<6)+x;
 int chx=0,chy=0,chyn=0,chxn=0,i=0;
 float rad=0,add=(3.1426/2)/90;
 for (radii=2;radii<r;++radii)
 {
 chx=0;
 chy=0;
 rad=0;
  while (chx>=chy)
  {
	chx=int(cos(rad)*radii);  //replace cos with a look up thing
	chy=int(sin(rad)*radii);  //replace sin with a look up thing
	chyn=(chy<<8)+(chy<<6);
	chxn=(chx<<8)+(chx<<6);
	double_buffer[(sa+chyn)+chx]=color;    //Quad 1:Y and X normal
	 double_buffer[(sa+chxn)+chy]=color;   //Quad 1:Y and X switched, Complimentary.
        double_buffer[(sa-chyn)+chx]=color;    //Quad 2:Y and X normal
	 double_buffer[(sa-chxn)+chy]=color;   //Quad 2:Y and X switched, Complimentary.
        double_buffer[(sa-chyn)-chx]=color;    //Quad 3:Y and X normal
	 double_buffer[(sa-chxn)-chy]=color;   //Quad 3:Y and X switched, Complimentary.
        double_buffer[(sa+chyn)-chx]=color;    //Quad 4:Y and X normal
         double_buffer[(sa+chxn)-chy]=color;   //Quad 4:Y and X switched, Complimentary.
        rad=rad+add;
  }
 }
}

void circlef(int x,int y,int color,int r,int d)
{
 int radii;
 long sa=(y<<8)+(y<<6)+x;
 double_buffer[sa]=color;
 int chx=0,chy=0,chyn=0,chxn=0,i=0;
 float rad=0,add=(3.1426/2)/90;

 int dd=int((d*(3.1426/180)));
 long ang=0;
 for (radii=2;radii<r;++radii)
 {
 chx=0;
 chy=0;
 rad=0;
 ang=0;
  while (ang<d)
  {
	chx=int(cos(rad)*radii);  //replace cos with a look up thing
	chy=int(sin(rad)*radii);
        rad=(ang*3.1426/180);
        ++ang;
        //chy=chy*-1;
        //replace sin with a look up thing
	chyn=(chy<<8)+(chy<<6);
	double_buffer[(sa+chyn)+chx]=color;    //Quad 1:Y and X normal
	// double_buffer[(sa+chxn)+chy]=color;   //Quad 1:Y and X switched, Complimentary.
        //double_buffer[(sa-chyn)+chx]=color;    //Quad 2:Y and X normal
	// double_buffer[(sa-chxn)+chy]=color;   //Quad 2:Y and X switched, Complimentary.
        //double_buffer[(sa-chyn)-chx]=color;    //Quad 3:Y and X normal
	// double_buffer[(sa-chxn)-chy]=color;   //Quad 3:Y and X switched, Complimentary.
        //double_buffer[(sa+chyn)-chx]=color;    //Quad 4:Y and X normal
        // double_buffer[(sa+chxn)-chy]=color;   //Quad 4:Y and X switched, Complimentary.

  }
 }
}
