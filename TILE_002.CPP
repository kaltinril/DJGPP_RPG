#include <time.h>
#include <errno.h>
#include "graf3.h"
#include "vars.h"
#include "audio.h"
#include "sound.h"
#include "pcx.h"
#include "pcx.c"
#include "tiles.h"
#include "text.h"
#include "text.c"
#include "func.h"
#include "func.c"
#include "tile.c"

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


main()
{
 near_ptr(ON);
 set_mode(0x13);
 load_pcx(abc,320,200,"abc.pcx",0,255,0);
 load_pcx(tile,320,200,"tile_001.pcx",0,255,0);
 memcpy(screen,tile,64000);
 nosound();
 vol=64;
 open_mod("test.xm");
 play_mod(64);
 quit=0;
 long nn=0;
 while(quit==0)
 {
  //draw_tiles();
  keyupdate();
  AUpdateAudio();
 }
 close_all();
}