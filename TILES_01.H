//unsigned char *tile=new unsigned char[SCREEN_SIZE];
unsigned char *tile=new unsigned char[64000];
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
int array_count[5][240];
/***************************************************************************
 *  Draw_tile                                                              *
 *       draws a tile from the tile buffer to the double buffer            *
 *       And makes sure it will fit on the screen, if any edge of the      *
 *       Tile if off the screen the function cuts that part off, and draws *
 *          Only what you can see                                          *
 **************************************************************************/

void draw_tile(int a,int sx,int sy,int flip,int st_x,int st_y)
{
 int y=0,x=0,sl_x=16,sl_y=16;
 if (st_x>0){st_x=16-st_x;}
 if (st_y>0){st_y=16-st_y;}
 unsigned char *v;
 unsigned char *c;
 start_y=0;
 start_x=a<<4;  //change to tile_w if  you want flexible tiles
 long end_line=0;
 while (start_x>319)
 {
  if (start_x>319){start_x=start_x-320;start_y=start_y+tile_h;}
 }
 sl_y=16-st_y;
 if ((sx+16)>319 || (sy+16)>195){end_line=1;flip=0;}
 if (trans[a]==0 && end_line==0)
 {
  v=double_buffer+(sy<<8)+(sy<<6)+sx;
  c=tile+((start_y+st_y)<<8)+((start_y+st_y)<<6)+start_x;
  //if (st_x>0 || st_x<0){memcpy(screen,double_buffer,64000);cout<<st_x;getch();}

  for (y=0;y<sl_y;++y)
  {
	memcpy(v,c+(st_x),16-st_x);
	v=v+320;
	c=c+320;
  }
  return;
 }
 if (trans[a]==1 || end_line==1)
 {
  long n_y=0,n_y2=0;
  int color=0;
  if (st_x>0){sl_x=16-st_x;}
  n_y=(((y+start_y+st_y)<<8)+((y+start_y+st_y)<<6)+start_x)+st_x;
  n_y2=((y+sy)<<8)+((y+sy)<<6)+sx;
  if (flip==0)
  {
	for (y=0;y<sl_y;++y)
	{
	 if (start_y<184)
	  {
		for (x=0;x<sl_x;++x)
		{
		 if ((sx+x)<320 && (sy+y)<196)
		{
		 color=tile[n_y+x];
		 if (color){double_buffer[n_y2+x]=color;}
		}
		else
		 x=tile_w;
		 if ((sy+y)>195){y=tile_h;}
		}
	  n_y=n_y+320;
	  n_y2=n_y2+320;
	 }
	}
    return;
  }
  if (flip==1)
  {

	for (y=0;y<tile_h;++y)
	{
	 if (start_y<184)
	  {
		for (x=tile_w;x>0;--x)
		{
		 color=tile[n_y+x-1];
		 if (color){double_buffer[n_y2+16-x]=color;}
		}
	  n_y=n_y+320;
	  n_y2=n_y2+320;
	 }
	}
return;
  }
	if (flip==2)
	{
	 n_y=n_y+5120;
	for (y=0;y<tile_h;++y)
	{
	 if (start_y<184)
	  {
		for (x=0;x<tile_w;++x)
		{
		 color=tile[n_y+x];
		 if (color){double_buffer[n_y2+x]=color;}
		}
	  n_y=n_y-320;
	  n_y2=n_y2+320;
	 }
	}
return;
  }
	if (flip==3)
	{
	 n_y=n_y+5120;
	for (y=0;y<tile_h;++y)
	{
	 if (start_y<184)
	  {
		for (x=tile_w;x>0;--x)
		{
		 color=tile[n_y+x-1];
		 if (color){double_buffer[n_y2+16-x]=color;}
		}
	  n_y=n_y-320;
	  n_y2=n_y2+320;
	 }
	}
return;
  }
 }
}
/***************************************************************************
 *  Draw_tiles                                                             *
 *       draws the array of tiles to the screen                            *
 **************************************************************************/
void draw_tiles(unsigned char *array, int change, int sxoryd)
{   //this area takes the array for the 240 different places on the screen
	 //and sends the tile number to the tile function.
int c_x=0,c_y=0,s_x=0,s_y=0,blah=0,bleh=0,ngg;
if (sxoryd==0){c_x=change;}
else
 {
  c_y=change;
 }
 int x=c_x,y=4+c_y,n=0,nn=0;
long ns=ch_y-4;
ns=(ns<<6)+(ns<<5)+(ns<<2)+ch_x;
 for (nn=0;nn<13;++nn)
 {
	if (bleh==1 && nn>0){--nn;}
 if (y<4){s_y=y+12;y=4;}
 if (c_y>0 && y-4==c_y && nn==0 && bleh==0)
	  {
			 s_y=y-4;y=4;nn=-1;ns=ns-100;
	  }
  for (n=0;n<21;++n)
  {
	if (blah==1 && n>0){--n;}
	if (x<0){s_x=16+x;x=0;}
	if (c_x>0 && x==c_x && n==0 && blah==0){s_x=x;x=0;n=-1;}
     ngg=array[ns+n];
   if (array_count[1][ngg]>array_count[0][ngg] && array_count[3][ngg]==1)
   {
    if (array_count[4][ngg]<array_count[2][ngg]){array_count[1][ngg]=0;++array_count[4][ngg];}
    if (array_count[2][ngg]<0){array_count[1][ngg]=0;}
   }
	if (array[ns+n]+array_count[1][array[ns+n]]-20)
	{draw_tile(array[ns+n]+array_count[1][array[ns+n]],x,y,0,s_x,s_y);}
	if (s_x==0){x=x+16;}
	else
	{
		 x=x+s_x;
	}
	s_x=0;
	blah=0;
	if (x>319){x=c_x;n=21;if(s_y==0){y=y+16;}else{y=y+s_y;}}
	if (n<0){n=0;blah=1;}
  }
  bleh=0;
  if (nn<0){nn=0;bleh=1;}
  ns=ns+100;
  s_y=0;
  if (y>195){nn=13;}

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
 if (actrg[screen_1[frm][ary]]==7 && array_count[3][screen_1[frm][ary]]==0)
 {
  array_count[3][screen_1[frm][ary]]=1;
  for (n=0;n<item_tot;++n)
  {
   if(ary==item_place[n])
   {
    org_item();
    if (bag_tot<100)
    {
     bag_item[bag_tot]=item_name[n];
     bag_iamt[bag_tot]=item_temp[n];
     ++bag_tot;
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
