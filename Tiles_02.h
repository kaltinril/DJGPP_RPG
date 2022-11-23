//unsigned char *tile=new unsigned char[SCREEN_SIZE];
unsigned char *tile=new unsigned char[64000];
unsigned char *tile_temp=new unsigned char[69888];
//unsigned char *screen_1=(unsigned char *) malloc(9600);
unsigned char *trans=new unsigned char[240];
unsigned char *walkn=new unsigned char[240];
unsigned char *actrg=new unsigned char[240];
int tile_w=16;
int tile_h=16;
long start_x=0;
int start_y=0;
int tile_n=0;
int count_n=0;
//struct screens_1
//{
// unsigned char *tile;
//};
unsigned char screen_1[4][9600];
//screens_1 screen_1[4];
//screen_1[0].tile=(unsigned char *)malloc(240)
int array_count[2][240];
/***************************************************************************
 *  Draw_tile                                                              *
 *       draws a tile from the tile buffer to the double buffer            *
 *       And makes sure it will fit on the screen, if any edge of the      *
 *       Tile if off the screen the function cuts that part off, and draws *
 *          Only what you can see                                          *
 **************************************************************************/

void draw_tile(int tilev,int x,int y)
{
 start_x=tilev<<4;
 start_y=0;
 while (start_x>319)
 {
  if (start_x>319){start_x=start_x-320;start_y=start_y+16;}
 }
 if (trans[tilev]==0)
 {
 unsigned char *v;//tile_temp buffer
 unsigned char *c;//tile buffer
 v=tile_temp+(y<<8)+(y<<6)+(y<<4)+x;
 c=tile+(start_y<<8)+(start_y<<6)+start_x;
  for (y=0;y<16;++y)
  {
   memcpy(v,c,16);
   v=v+336;
   c=c+320;
  }
  return;
  }
  if (trans[tilev]==1)
  {
  long d=(y<<8)+(y<<6)+(y<<4)+x;
  long u=(start_y<<8)+(start_y<<6)+start_x;
  for (y=0;y<16;++y)
  {
   for (x=0;x<16;++x)
   {
    if (tile[u]!=0){tile_temp[d]=tile[u];}
    ++u;
    ++d;
   }
   u=u+304;
   d=d+320;
  }
  return;
 }
 return;
}

/***************************************************************************
 *  Draw_tiles                                                             *
 *       draws the array of tiles to the screen                            *
 **************************************************************************/
void draw_tiles(unsigned char *array)
 {
  long ns=((ch_y-4)*100)+ch_x;
  long n=0,nn=0;
  int x=0,y=0;
 for (nn=0;nn<13;++nn)
 {
 x=0;
  for (n=0;n<21;++n)
  {
   //while(array[ns+n]==20 && n<20){++n;x=x+16;}
   	if (array_count[1][array[ns+n]]>array_count[0][array[ns+n]]){array_count[1][array[ns+n]]=0;}
	if (array[ns+n]+array_count[1][array[ns+n]]-20)
	{draw_tile(array[ns+n]+array_count[1][array[ns+n]],x,y);}
   x=x+16;
  }
  y=y+16;
  ns=ns+100;
 }
nn=0;
 for (n=0;n<(192*320);n=n+320)
 {
 memcpy(double_buffer+n+1280,tile_temp+nn,320);
 nn=nn+336;
 }
}

/***************************************************************************
 *  c_new_spot                                                             *
 *       Checks to see if the tile that you are about to move on is a      *
 *       Walkable tile, make sure it isn't a wall.                         *
 *       If num returns 4 then there is no wall, if num returns any other  *
 *         Number it has found 1 or more walls on that spot in one of the  *
 *         Four frames.                                                    *
 **************************************************************************/
int c_new_spot()
{
 int ch_ny=(ch_y-4)+ch_zy,ch_nx=(ch_x)+ch_zx,ary=0;
 ch_ny=ch_ny+y_dir;
 ch_nx=ch_nx+x_dir;
 ch_ny=(ch_ny*100);
 ary=ch_ny+ch_nx;
 int num=0,i=0;
  for (i=0;i<3;++i)
  {
   if (walkn[screen_1[i][ary]]==0)
   ++num;
  }
return(num);
}

/***************************************************************************
 *  check_action                                                           *
 *       Checks the tile that you are on or a tile of your specification   *
 *       To see if the tile has a certain actrg value which can mean       *
 *       That there is an item at that spot, or a warp, or a door etc..    *
 **************************************************************************/

void check_action(long ary_2)
{
 int ch_ny=(ch_y-4)+ch_zy,ch_nx=(ch_x)+ch_zx,ary=0,frm=0,n=0;
 ch_ny=(ch_ny*100);
 ary=ch_ny+ch_nx;
 if (ary_2!=0){ary=ary_2;}
 for (frm=0;frm<4;++frm)
 {
  if (actrg[screen_1[frm][ary]]==4)
  {
	for (n=0;n<item_tot;++n)
	{
	 if(ary==item_place[n])
	 {
          //getch();
	  //do item thing here...
	  //save the item_name variable to the Main items variable
	  //save how many of them you have.
	  //delete the item, or somehow turn it off, so it won't get gotten again.

          //make is so that they have to want to orginize it, if not
          //then is just stays messed up.
	  org_item();   //called from items.h to orginize the items
	  if (bag_tot<100)
	  {

	  //make it so it looks through the bag, and adds a number if you
	  //alrady have the item, instead of taking up another space
		bag_item[bag_tot]=item_name[n];
		bag_iamt[bag_tot]=item_temp[n];
		++bag_tot;
		//org_item();   //called from items.h to orginize the items
	  }
	  else {cout<<"Bag full.";getch();}
	 }

	}
  }
  if (actrg[screen_1[frm][ary]]==5)
  {
	for (n=0;n<item_tot;++n)
	{
	 if(ary==item_place[n])
	 {
         int adn=0;
	  if (item_name[n]!=map_now[0]){++adn;}
           if (item_tmp2[n]!=map_now[1]){++adn;}
           if (adn>0)
           {
            short tot_mapl=0,tot_maps=0;
            int grip=open("mainlist.lst",O_RDONLY|O_BINARY);
            char crapdata[12];
            short ij=0;
            for (ij=0; ij<int(item_name[n]); ++ij)
            {
             read(grip,crapdata,12);
            }
            close(grip);
            strncpy(RfName,(char *)crapdata,12);
            RfName[12]='\0';
            //crapdata[12]="\n";
            //grip=open(crapdata,O_RDONLY|O_BINARY);
            grip=open(RfName,O_RDONLY|O_BINARY);
             for (ij=0; ij<item_tmp2[n]; ++ij)
             {
              read(grip,crapdata,12);
             }
             strncpy(RfName,(char *)crapdata,12);
             RfName[12]='\0';
             close(grip);
             open_map();
             cout<<"\n";
             cout<<RfName<<"filename ";
             getch();
            //check map name in maplist.lst
		//open mapname
		//loadmap values, and change to that map.
           cout<<"\n";
           cout<<map_now[0]<<"mapnow"<<map_now[1];
           map_now[0]=item_name[n];
           map_now[1]=item_tmp2[n];
           cout<<"\n";
                      cout<<map_now[0]<<"mapnew"<<map_now[1];
                      getch();
           }
	  ch_x=item_temp[n]%100;
	  ch_y=((item_temp[n]-ch_x)/100)-2;
	  ch_x=ch_x-10;
	  n=item_tot;
	 }
	}
  }
  if (actrg[screen_1[frm][ary]]==10)
  {
   //display text box, and read in text to be displayed.

  }
 }

}
