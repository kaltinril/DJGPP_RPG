/**********************************************************************
 *  Consts/keys                                                       *
 *                                                                    *
 *********************************************************************/
const char LEFT='4';
const char DOWN='5';
const char RIGHT='6';
const char UP='8';

/**********************************************************************
 *   main vars                                                        *
 *        bag                                                         *
 *                                                                    *
 *                                                                    *
 *********************************************************************/
 unsigned char bag_tot=0;
 int *bag_item=new int[100];
 unsigned char *bag_iamt=new unsigned char[100];
/**********************************************************************
 *   Used in tile.h/main                                              *
 *                                                                    *
 *                                                                    *
 *                                                                    *
 *********************************************************************/
int map_now[2];

 long t_start=-1,t_end=-1;
/**********************************************************************
 *     Loader.h                                                       *
 *        Vars from loader.h                                          *
 *                                                                    *
 *                                                                    *
 *********************************************************************/
//#define S_IREAD 0x0100  /* owner may read */
//#define S_IWRITE 0x0080 /* owner may write */

int fnopen();
int open_it();
int fnmake();
int open_mor(char *);
typedef unsigned long DWORD;
typedef unsigned int BWORD;
typedef unsigned char BYTE;  //8 bits

//char tile_stats[240];  //walkablitity is 0 transparency is 1
								  //and action is 2
	BYTE tile_num[1];  //how many total tiles the pcx file has
	char pcx_name[13]="Tile_001.pcx";  //the pcx filename

char filename[13];  //the filename of the map file
char path[26];      //the path to the file
char RfName[41]="mainfile.mmp";    //space for the path+filename

short item_tot=0;
//eventually replace it so that it will malloc only the total item amount
short *item_place=new short[500];   //were item is, or were warp is

short *item_temp=new short[500];    //used for warping, were to warp to

short *item_tmp2=new short[500];
short *item_trig=new short[500];
BYTE *item_name=new BYTE[500];  //value for the item, not the acual
													//name, also the value for the map
													//to warp to