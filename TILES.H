struct Tile
{
 int action;  //what will happen when stepped on
 int walk;    //if you can walk onto the tile
 int animeyn; //animation yes or no, on or off, 0 or 1,
 int anime1;  //which tile to change to
 int anime2;  //how long to wait to animate, example 2, 91clicks/2 is 45clks
 long anime3; //stores the click you were on so you can wait for anime2 clks
 int trans;   //if it is a cut out, a full tile, or water like tile so it
              //adds the colors together and gets a cool look
};
int worldlocx=0;
int worldlocy=0;
  unsigned char *tile=new unsigned char[64000];
  unsigned char *prebuff=new unsigned char[69888];  //336*208//21 * 13
unsigned char world[3][16384]; //128*128
Tile tiles[240];
//world[layer][tilenumber];
//layer0 background/ground dirt water floor tiles
//layer1 chairs tables items trees candle's things on walls
//layer2 character layer player, other moving creatures...
//layer3 outside forest look in overworld, clouds, walls in 3d, pillars

//draw_tile(tile_num)
draw_tile(int,int,int);
//draw_tiles()
draw_tiles(int,int);
//edittiles(); change the walk trans anime etc values
void changetiles(int);
void edittiles();
