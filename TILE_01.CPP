#include <time.h>
#include <errno.h>
#include "graf3.h"
#include "audio.h"
#include "sound.h"
#include "items.h"
#include "loader.h" //open_map() save_map() make_map()
#include "pcx.h"
#include "pcx.c"
#include "vars.h"  //all the global vars i need to access a lot
#include "stats.h"  //ch_x  ch_y  ch_n  damage  enemyes  n_damage
						  //damage_type
#include "item01.h"
#include "text.h"
#include "tiles_01.h"  //tile[64000]  trans[240]  tile_h  tile_w  start_x
							  //start_y  tile_n  count_n  screen_1[9600]
							  //array_count[2][240]  tile_type[2][240]
#include "loader.c"   //were the acual functions are stored form loader.h
#include "item01.c"
#include "text.c"
#include "items.c"

#if defined(_MSC_VER) || defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__DJGPP__)
#else
#define kbhit() 0
#endif
#include "sound.c"
/**************functions***************************************************
 *         draw_tile(tile_num,x,y,flip value);                            *
 *    draw_tiles(screen_1[n],add,x/y);   if x/y=0 then x if not then y    *
 *    check_tile(direction,screen[n]);      direction 4 5 6 or 8          *
 **************************************************************************/

void blitz(int,int);  //int_1 distance to offset//int_2 0=x or 1=y
char get_keys();     //key=get_keys();  same as key=getch();
void check_d_key(char);  //send the key to check_d_key(key);
void check_cycle(int);   //check the cycle variable check_cycle(cycle);
main()
{

 unsigned long i=0;
 float t1;
 for (i=0;i<100;++i)
 {
  bag_item[i]=0;
  bag_iamt[i]=0;
 }

 for (i=0;i<256;++i)
 {
  trans[i]=0;
  walkn[i]=0;
  actrg[i]=0;
 }
 for (i=0;i<240;++i){array_count[0][i]=0;array_count[1][i]=0;array_count[2][i]=0;
 array_count[3][i]=0;array_count[4][i]=0;}
 for (i=0; i<500; ++i)
 {
  item_tmp2[i]=0;
 }
 map_now[0]=1;
 map_now[1]=1;
 near_ptr(ON);
 set_mode(0x13);
 open_map();
 load_pcx(abc,320,200,"abc.pcx",0,255,0);
 load_pcx(tile,320,200,pcx_name,0,255,0);
 memcpy(screen,tile,64000);
 load_items();
 load_chars(1);
 players[mplayers-1].data[18]=50;
 players[mplayers-1].data[19]=rand()%51;
 load_chars(4);
 players[mplayers-1].data[18]=100;
 players[mplayers-1].data[19]=rand()%101;
 getch();
 int go=1;
 int movesl=0;
  char key;
  int n=0;
  int um=0;
  int ns=0;
  int nns=0;
  int chg=0,xy=0;
  nosound();
  Clear(0,double_buffer);
  Clear(0,text);
  gotoxy(1,1);
  draw_window("Press any key to continue...",3,7,312,102);
  print("Q.....quit");
  print("1,2,3 or 0....toggle layers");
  print("8..go up");
  print("5..go down");
  print("4..go left");
  print("6..go right");
  print("f..reset FPS");
  print("n..set everything to normal");
  print("minus...have less steps");
  print("plus...to have more steps");
  memcpy(screen,text,64000);
  getch();
vol=64;
  Clear(0,text);
  --winsa_tot;
 start=clock();
 timein=clock();
 Clear(0,screen);  //clears the screen
 open_mod("test.xm");
 play_mod(64);

 while (gon==1)
 {
 key=0;  //reset the key buffer
 if (kbhit()){key=get_keys();}   //check for a key
 check_d_key(key);     //send key to check function to check for action
 AUpdateAudio();
 check_mod(1);
 movesl=0;       //tell the program not to animate moving
 y_dir=0;        //clear the y direction variable
 x_dir=0;        //Clear the x direction variable
 check_key(key);     //checks the key, and sets the y_dir/x_dir as needed
 um=0;               //clear the variable for use
 if (key!=LEFT || key!=RIGHT || key!=UP || key!=DOWN){um=c_new_spot();}
                                   //check the spot in front of you
 if (um==3){movesl=1;}  //if there is no wall in front of you let animate
 if(nostop==1){movesl=1;}     //if walls are turned off let animate
  if (key!=LEFT && key!=RIGHT && key!=UP && key!=DOWN){movesl=0;}
            //if you did not hit a direct don't animate
 if (way>1){way=0;}     //used to put the character in a certain direction

 if (ch_x+x_dir<0){movesl=2;}
 if (ch_y+y_dir<4){movesl=2;}
 if (ch_x+x_dir>90){movesl=2;}
 if (ch_y+y_dir>88){movesl=2;}
 if (y_dir!=0 && ch_zy!=6){movesl=2;}
 if (x_dir!=0 && ch_zx!=10){movesl=2;}
 if (um!=3 && nostop==0){movesl=0;}
 if (movesl==2)
 {
 cx_off=0;
 cy_off=0;
 for (n=0;n<16;n=n+addn)
 {
  if (kbhit()){key=getch();}
  xy=0;
  if (y_dir!=0)
  {
   xy=1;
   cy_off=cy_off+(y_dir*addn);

   if (ch_zy==0 && y_dir<0){cy_off=0;n=16;}
   if (ch_zy==11 && y_dir>0){cy_off=0;n=16;}
  }
  if (x_dir!=0)
  {
   cx_off=cx_off+(x_dir*addn);
    if (ch_zx==0 && x_dir<0){cx_off=0;n=16;}
    if (ch_zx==19 && x_dir>0){cx_off=0;n=16;}
  }
  AUpdateAudio();
  blitz(chg,xy); //animate in here
  Clear(0,double_buffer);
  ++amt;
  ++cycle;
  check_cycle(cycle);
 }
    ch_zx=ch_zx+x_dir;
   if (ch_zx<0){ch_zx=0;}
   if (ch_zx>19){ch_zx=19;}
    ch_zy=ch_zy+y_dir;
  if (ch_zy<0){ch_zy=0;}
  if (ch_zy>11){ch_zy=11;}
  cx_off=0;cy_off=0;
 }
 if (movesl==1) //checks to see if they hit a wall when they hit a key
 {
  if (x_dir!=0){cy_off=-1;}
  for(n=0;n<16;n=n+addn)  //move smoothly from one tile to next
  {
   if (kbhit()){key=getch();} //gets the keys in so it doesn't beep
  chg=(x_dir*-n);     //sets it up like your automaticly going to go x
  xy=0;          //0 is for x and 1 will make it change y instead
  if (y_dir!=0)
  {
   xy=1;chg=(y_dir*-n);
   if (n==8 || n==16){++way;}
   if (way>1){way=0;}
  }
  if (x_dir!=0)
  {
   if (n==8 || n==16)
   {
    ++next_an_tile;
    if (next_an_tile<2 || next_an_tile>3){next_an_tile=2;}
    --cy_off;
    if (cy_off<-1){cy_off=0;}
   }
  }
   AUpdateAudio();
  blitz(chg,xy); //animate in here
  Clear(0,double_buffer);
  ++amt;
  ++cycle;
  check_cycle(cycle);
  }
  cy_off=0;
  chg=0;
  //put restictions here
  ch_x=ch_x+x_dir;
  ch_y=ch_y+y_dir;//moves the player or at least his pict
 if (ch_x<0){ch_x=0;}
 if (ch_y<0){ch_y=0;}

 } //end if there is no wall
 if (movesl==0)
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
 }//end main loop


 t1=clock();
 set_mode(0x03);
 cout<<"\n";
 cout<<"It took<<"<<((t1-start)/CLOCKS_PER_SEC)<<">> seconds.\n";
 cout<<"Fps: <"<<amt/((t1-start)/CLOCKS_PER_SEC)<<">\n";
 cout<<"Rack\nhttp://members.xoom.com/rack/\nrackattack@hotmail.com";
close_all();
}

void blitz(int x,int y)
{
  if (draw_0==1){draw_tiles(screen_1[0],x,y);}
  if (draw_1==1){draw_tiles(screen_1[1],x,y);}
  if (draw_2==1){draw_tiles(screen_1[2],x,y);}
  draw_tile(ch_n+next_an_tile,(ch_zx*16)+cx_off,4+(ch_zy*16)+cy_off,way,0,0);
  if (draw_3==1){draw_tiles(screen_1[3],x,y);}
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
  if (key=='1'){++draw_0;if(draw_0>1){draw_0=0;}}
  if (key=='2'){++draw_1;if(draw_1>1){draw_1=0;}}
  if (key=='3'){++draw_2;if(draw_2>1){draw_2=0;}}
  if (key=='0'){++draw_3;if(draw_3>1){draw_3=0;}}
  if (key=='+')
  {
  ++addn;
  if (addn==3){addn=4;}
  if (addn>4 && addn<8){addn=8;}
  if (addn>8 && addn<16){addn=16;}
  if (addn>16){addn=16;}
  }
  if (key=='-')
  {
  --addn;
  if (addn==3){addn=2;}
  if (addn>4 && addn<8){addn=4;}
  if (addn>8 && addn<16){addn=8;}
  if (addn<1){addn=1;}
  }
  if (key=='n' || key=='N'){draw_0=0;draw_1=0;draw_2=0;draw_3=0;addn=2;}
  if (key=='f'){amt=0; start=clock();}
  if (key=='q' || key=='Q'){gon=0;}
  if (key=='w' || key=='W'){++nostop;if (nostop>1){nostop=0;}}
  if (key=='s' || key=='S'){gotoxy(1,1);cout<<"Save as...";get_file();save_map();make_map();}
  if (key=='o' || key=='O'){gotoxy(1,1);cout<<"open...";get_file();open_map();load_pcx(tile,320,200,pcx_name,0,255,0);}


 if (key=='i' || key=='I')
  {
   mmenu();
	/*cout<<"\n";
	long n=0;
	cout<<"Amount"<<int(bag_iamt[n])<<"Item"<<int(bag_item[n])<<"placement"<<n<<"\n";
	for (n=bag_tot-4;n<bag_tot;++n)
	{
	 cout<<"Amount"<<int(bag_iamt[n])<<"Item"<<int(bag_item[n])<<"placement"<<n<<"\n";
	}
	getch();*/
  }
}

void check_cycle(int c)
{
 int n=0;
  if (c>100){cycle=0;}
  if (cycle%10==0)
  {
   for (n=0;n<240;++n)
   if (array_count[0][n]>=array_count[1][n] && array_count[3][n]==1)
   {
    if (array_count[4][n]<array_count[2][n]){++array_count[1][n];++array_count[4][n];}
    if (array_count[2][n]<0){++array_count[1][n];}
   }

   n=0;
  } //end if c%5
}
