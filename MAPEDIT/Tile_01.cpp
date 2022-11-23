#include <time.h>
#include <errno.h>
#include "menu.h"
#include "graf3.h"
#include "loader.h"
#include "pcx.h"
#include "pcx.c"
#include "vars.h"
#include "varsed.h"
#include "stats.h"  //ch_x  ch_y  ch_n  damage  enemyes  n_damage
						  //damage_type
#include "items.h"
#include "tiles_01.h"  //tile[64000]  trans[240]  tile_h  tile_w  start_x
							  //start_y  tile_n  count_n  screen_1[9600]
							  //array_count[2][240]  tile_type[2][240]
#include "loader.c"
#include "menu.c"
#include "editor.h"
/**************functions***************************************************
 *         draw_tile(tile_num,x,y,flip value);                            *
 *    draw_tiles(screen_1[n],add,x/y);   if x/y=0 then x if not then y    *
 *    check_tile(direction,screen[n]);      direction 4 5 6 or 8          *
 **************************************************************************/
//pcx_struct pcxbuf;    //Buffer for PCX data
//Pcx pcxloader;        //PCX loader object
main()
{

 unsigned long i=0;
 float start,t1;
 for (i=0;i<100;++i)
 {
  bag_item[i]=0;
  bag_iamt[i]=0;
 }
 for (i=0;i<9600;++i)
 {
  screen_1[0][i]=9;
  //if (screen_1[i]==1){screen_1[i]=3;}
 }
 for (i=0;i<9600;++i)
 {
  screen_1[1][i]=10*((rand()%2)+1);
	 if (rand()%2==1 && screen_1[1][i]==10){screen_1[1][i]=11;}
  //if (screen_1[i]==1){screen_1[i]=3;}
 }
 screen_1[1][710]=14;
 for (i=0;i<9600;++i)
 {
  screen_1[2][i]=5;
  if (rand()%2==1){screen_1[2][i]=20;}
  //if (screen_1[i]==1){screen_1[i]=3;}
 }
 screen_1[2][710]=20;
  for (i=0;i<9600;++i)
 {
  screen_1[3][i]=13;
  if (rand()%2==1){screen_1[3][i]=20;}
  //if (screen_1[i]==1){screen_1[i]=3;}
 }
 screen_1[3][710]=20;
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
  item_trig[i]=0;
 }

 map_now[0]=1;
 map_now[1]=1;
 near_ptr(ON);
 set_mode(0x13);
 open_map();
 load_pcx(tile,320,200,pcx_name,0,255,0);
 memcpy(screen,tile,64000);
 getch();
 int go=1;
 int movesl=0;
 long amt=0;
 char key=0;
 int nostop=0;
  int n=0;
  int ns=0;
  int nns=0;
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
 int way=0;
 int addn=2;
 int next_an_tile=0;
 int draw_0=1,draw_1=1,draw_2=1,draw_3=1;
 int cycle=0;
 Clear(0,screen);  //clears the screen
 int ch_ny=(ch_y-4)+6,ch_nx=(ch_x)+10,ary=0;
 while (go==1)
 {
 key=0;
 movesl=0;

  //b_swap();         //function for swaping 2 buffers in asm
						  //b_swap is about .2 fps faster
						  //same as memcpy(screen,double_buffer,64000);
  //memset(double_buffer,0,64000);  //slower clear screen.
  //Clear(0,double_buffer); //gain about 4-7 fps without clearing

  if (kbhit()){key=getch();}
  if (key=='1'){++draw_0;if(draw_0>1){draw_0=0;}}
  if (key=='2'){++draw_1;if(draw_1>1){draw_1=0;}}
  if (key=='3'){++draw_2;if(draw_2>1){draw_2=0;}}
  if (key=='0'){++draw_3;if(draw_3>1){draw_3=0;}}
  if (key=='+'){++addn;++addn;if (addn>16){addn=16;}}
  if (key=='-'){--addn;--addn;if (addn<1){addn=1;}}
  if (key=='n' || key=='N'){draw_0=1;draw_1=1;draw_2=1;draw_3=1;addn=2;}
  if (key=='f'){amt=0; start=clock();}
  if (key=='q' || key=='Q'){go=0;}
  nostop=1;
  if (key=='s' || key=='S'){gotoxy(1,1);cout<<"Save as...";get_file();save_map();make_map();}
  if (key=='o' || key=='O'){gotoxy(1,1);cout<<"open...";get_file();open_map();load_pcx(tile,320,200,pcx_name,0,255,0);}
  if (key=='z' || key=='Z'){action=3;}
  if (key=='x' || key=='X'){action=1;}
  if (key=='c' || key=='C'){action=0;}
  if (key=='v' || key=='V'){action=2;}
  if (key=='d' || key=='D'){action=4;}
  if (key=='a' || key=='A'){action=5;}
  if (key=='g' || key=='G'){temptile=pick_tile();}
  if (key=='l' || key=='L'){++layer;if (layer>3){layer=0;}}
  if (key==' '){change_tile();}
  if (key=='m' || key=='M'){menu_sys();}
  ch_ny=(ch_y-4)+6,ch_nx=(ch_x)+10;
  ch_ny=(ch_ny*100);
  ary=ch_ny+ch_nx;
  gotoxy(1,1);
  cout<<"\n";
  cout<<"layer:"<<int(layer)<<" ary:"<<ary;
  cout<<"\n";
  cout<<"TileValue:"<<int(screen_1[layer][ary]);
  cout<<"\n";
  if (key=='i' || key=='I')
  {
	cout<<"\n";
	n=0;
	cout<<"Amount"<<int(bag_iamt[n])<<"Item"<<int(bag_item[n])<<"placement"<<n<<"\n";
	for (n=bag_tot-4;n<bag_tot;++n)
	{
	 cout<<"Amount"<<int(bag_iamt[n])<<"Item"<<int(bag_item[n])<<"placement"<<n<<"\n";
	}
	getch();
  }
  if (key=='8')
  {
	next_an_tile=1;
	++way;
	ch_y=ch_y-1;
	n=ch_y;
	if (nostop==0)
	{
	check_tile(8,screen_1[0]);
	if (n==ch_y){check_tile(8,screen_1[1]);}
	if (n==ch_y){check_tile(8,screen_1[2]);}
	}
	if (n==ch_y){movesl=1;}   //checks to see if they did not hit a wall
	if (ch_y<4){ch_y=4;movesl=0;}
  }
  if (key=='5')
  {
  next_an_tile=0;
	++way;
	ch_y=ch_y+1;
	n=ch_y;

	if (nostop==0)
	{
	check_tile(5,screen_1[0]);
	if (n==ch_y){check_tile(5,screen_1[1]);}
	if (n==ch_y){check_tile(5,screen_1[2]);}
	}
	if (n==ch_y){movesl=1;}   //checks to see if they did not hit a wall
	if (ch_y>84){ch_y=84;movesl=0;}
  }
  if (key=='4')
  {
	++next_an_tile;
	if (next_an_tile<2 || next_an_tile>3){next_an_tile=2;}
	way=1;
	ch_x=ch_x-1;
	n=ch_x;
	if (nostop==0)
	{
	check_tile(4,screen_1[0]);
	if (n==ch_x){check_tile(4,screen_1[1]);}
	if (n==ch_x){check_tile(4,screen_1[2]);}
	}
	if (n==ch_x){movesl=1;}   //checks to see if they did not hit a wall
	if (ch_x<0){ch_x=0;movesl=0;}
  }

  if (key=='6')
  {             //for the moving right part
  ++next_an_tile;
  if (next_an_tile<2 || next_an_tile>3){next_an_tile=2;}
  way=0;
	ch_x=ch_x+1;
	n=ch_x;
	if (nostop==0)        //checks to make sure they have walls on
	{
	check_tile(6,screen_1[0]); //checks the tile the person has moved to,
	if (n==ch_x){check_tile(6,screen_1[1]);}  //to see if they need to be
	if (n==ch_x){check_tile(6,screen_1[2]);}  //moved back a space.
	}
	if (n==ch_x){movesl=1;}   //checks to see if they did not hit a wall
	if (ch_x>80){ch_x=80;movesl=0;}
  }     //End moving right..............................

check_key(key);
		  if (way>1){way=0;}


 if (movesl==1) //checks to see if they hit a wall when they hit a key
 {
	if (key=='4'){ch_x=ch_x+1;nns=0;}
	else       //moves the place back a spot, so that it can animate it
	{          //moving
		if (key=='6'){ch_x=ch_x-1;nns=0;}
		 else          //same just differnt direction
		 {
		  if (key=='8'){ch_y=ch_y+1;nns=1;}
		  else         //same as above comment
			if (key=='5'){ch_y=ch_y-1;nns=1;}
		 }             //same
	}
		for(n=0;n<16;n=n+addn)
		{                //this is the loop that moves the tiles up down left
							  //or right slowly, so it looks like the guy moves not
							  //the screen or tiles
		  if (kbhit()){getch();}   //gets key, so that it doesn't beep.
		  if (key=='4'){ns=n;++next_an_tile;}   //this makes the character
		  if (key=='6'){ns=-n;++next_an_tile;}  //animate while walking
		  if (key=='5'){ns=-n;++way;next_an_tile=0;} //same
		  if (key=='8'){ns=n;++way;next_an_tile=1;}  //same
		  if (key=='4' || key=='6'){if (next_an_tile<2 || next_an_tile>3){next_an_tile=2;}}
		  if (way>1){way=0;}   //this and the above, make sure it is animated
									  //corectly
		  Clear(0,double_buffer);   //clear double_buffer
  if (draw_0==1){draw_tiles(screen_1[0],ns,nns);}   //the following are the differnt
  if (draw_1==1){draw_tiles(screen_1[1],ns,nns);}   //layers being drawn, and checked
  if (draw_2==1){draw_tiles(screen_1[2],ns,nns);}   //for non drawn tiles etc
    rect_fast(160,100,175,115,31+way);
  //draw_tile(ch_n+next_an_tile,160,100,way,0,0);
  if (draw_3==1){draw_tiles(screen_1[3],ns,nns);}
		  memcpy(screen+1280,double_buffer+1280,61440); //hmm i wonder
		  ++amt;
          ++cycle;
  if (cycle>50){cycle=0;}
  if (cycle%5==0)
  {
	 for (i=0;i<240;++i)
	 {
	  if (array_count[0][i]>=array_count[1][i]){++array_count[1][i];}
	 }
	i=0;
  }
		}
	if (key=='4'){ch_x=ch_x-1;}
	else                       //moves place back, so that when it exits
	{                          //this area of moving, it will show the tiles
	  if (key=='6'){ch_x=ch_x+1;}   //at the correct spot..
		else
		{
		 if (key=='8'){ch_y=ch_y-1;}
		 else
		if (key=='5'){ch_y=ch_y+1;}
		}
	}
 }
 else
 {
  if (draw_0==1){draw_tiles(screen_1[0],0,0);}
  if (draw_1==1){draw_tiles(screen_1[1],0,0);}
  if (draw_2==1){draw_tiles(screen_1[2],0,0);}
      rect_fast(160,100,175,115,31+way);
  //draw_tile(ch_n+next_an_tile,160,100,way,0,0);
  if (draw_3==1){draw_tiles(screen_1[3],0,0);}
  memcpy(screen+1280,double_buffer+1280,61440);  //copies LESS
		  Clear(0,double_buffer);
 }
  n=0;
  ++amt;
  ++cycle;
  if (cycle>50){cycle=0;}
  if (cycle%5==0)
  {
	 for (n=0;n<240;++n)
	 {
	  if (array_count[0][n]>=array_count[1][n]){++array_count[1][n];}
	 }
	n=0;
  }
  if (key!=NULL)
  {
	check_action(0);
  }
 }
 t1=clock();
 set_mode(0x03);
 cout<<"\n";
 cout<<"It took<<"<<((t1-start)/CLOCKS_PER_SEC)<<">> seconds.\n";
 cout<<"Fps: <"<<amt/((t1-start)/CLOCKS_PER_SEC)<<">\n";
 cout<<"Rack\nhttp://members.xoom.com/rack/\nrackattack@hotmail.com";
}