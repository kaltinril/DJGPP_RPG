#include <time.h>
#include <errno.h>
#include "menu.h"
#include "fnctions.h"
#include "text.h"
#include "editor.h"
#include "graf3.h"
#include "loader.h" //open_map() save_map() make_map()
#include "pcx.h"
#include "pcx.c"
#include "stats.h"  //ch_x  ch_y  ch_n  damage  enemyes  n_damage
						  //damage_type
#include "vars.h"  //all the global vars i need to access a lot
#include "varsed.h"
#include "items.h"
#include "tiles_01.h"  //tile[64000]  trans[240]  tile_h  tile_w  start_x
							  //start_y  tile_n  count_n  screen_1[9600]
							  //array_count[2][240]  tile_type[2][240]
#include "loader.c"   //were the acual functions are stored form loader.h
#include "menu.c"
#include "editor.c"
#include "fnctions.c"
#include "text.c"
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
 for (i=0;i<240;++i){array_count[0][i]=0;array_count[1][i]=0;}

 for (i=0; i<500; ++i)
 {
  item_tmp2[i]=0;
 }
 map_now[0]=1;
 map_now[1]=1;
 near_ptr(ON);
 set_mode(0x13);
 open_map();
 load_pcx(tile,320,200,pcx_name,0,255,0);
 load_pcx(abc,320,200,"abc.pcx",0,255,0);
 memset(text,0,64000);
 memcpy(screen,tile,64000);
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
  gotoxy(1,1);
  cout<<"Press any key to continue...\n";
  cout<<"Press Q to quit\n";
  cout<<"Press 1,2,3 or 0 to toggle layers\n";
  cout<<"Press 8 to go up\n";
  cout<<"Press 5 to go down\n";
  cout<<"Press 4 to go left\n";
  cout<<"Press 6 to go right\n";
  cout<<"Press f to reset FPS\n";
  cout<<"Press n to set everything to normal\n";
  cout<<"Press - to have less steps\n";
  cout<<"Press + to have more steps\n";

  getch();
 start=clock();
 Clear(0,screen);  //clears the screen
 action_ab=0; //turns off warps/items
 while (gon==1)
 {
 key=0;  //reset the key buffer
 if (kbhit()){key=get_keys();}   //check for a key
 check_d_key(key);     //send key to check function to check for action
 movesl=0;       //tell the program not to animate moving
 y_dir=0;        //clear the y direction variable
 x_dir=0;        //Clear the x direction variable
 check_key(key);     //checks the key, and sets the y_dir/x_dir as needed
 um=0;               //clear the variable for use
 if (key!=LEFT || key!=RIGHT || key!=UP || key!=DOWN){um=c_new_spot();}
                                   //check the spot in front of you
 if (um==4){movesl=1;}  //if there is no wall in front of you let animate
 if(nostop==1){movesl=1;}     //if walls are turned off let animate
  if (key!=LEFT && key!=RIGHT && key!=UP && key!=DOWN){movesl=0;}
            //if you did not hit a direct don't animate
 if (way>1){way=0;}     //used to put the character in a certain direction
 if (key=='h'){cout<<"sdfs"<<ch_x<<"||"<<ch_y<<"\n";getch();}
 if (ch_x+x_dir<0){movesl=2;}
 if (ch_y+y_dir<4){movesl=2;}
 if (ch_x+x_dir>90){movesl=2;}
 if (ch_y+y_dir>88){movesl=2;}
 if (y_dir!=0 && ch_zy!=6){movesl=2;}
 if (x_dir!=0 && ch_zx!=10){movesl=2;}
 if (movesl==2)
 {
 xy=0;
  if (y_dir!=0)
  {
  xy=1;
  ch_zy=ch_zy+y_dir;
  if (ch_zy<0){ch_zy=0;}
  if (ch_zy>11){ch_zy=11;}
  }
  if (x_dir!=0)
  {
   ch_zx=ch_zx+x_dir;
   if (ch_zx<0){ch_zx=0;}
   if (ch_zx>19){ch_zx=19;}
  }
  blitz(chg,xy); //animate in here
  Clear(0,double_buffer);
  ++amt;
  ++cycle;
  check_cycle(cycle);
 }

 if (movesl==1) //checks to see if they hit a wall when they hit a key
 {
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
 }//end main loop


 t1=clock();
 set_mode(0x03);
 cout<<"\n";
 cout<<"It took<<"<<((t1-start)/CLOCKS_PER_SEC)<<">> seconds.\n";
 cout<<"Fps: <"<<amt/((t1-start)/CLOCKS_PER_SEC)<<">\n";
 cout<<"Rack\nhttp://members.xoom.com/rack/\nrackattack@hotmail.com";
}








