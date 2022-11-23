#include <time.h>
#include <errno.h>
#include "graf3.h"
#include "vars.h"
#include "audio.h"
#include "sound.h"
#include "pcx.h"
#include "pcx.c"
#include "text.h"
#include "text.c"

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
 load_pcx(abc,320,200,"abc2.pcx",0,255,0);
 Clear(0,text);
 Clear(0,double_buffer);
 short thiswin=0;
 //window=create_window("this is text",left,top,width,height,order);
 //returns the window look up value
 thiswin=create_window("ello ello ello",3,3,99,99,5);
 add_print("Is this ok.",thiswin);
 thiswin=create_window("For the Cool people!",50,50,198,99,3);
 add_print("Rack",thiswin);
 add_print("Garrett~Joe",thiswin);
 thiswin=create_window("+-!@#$%%^?<>~[]\:;'*=",25,25,150,70,4);
 drawallwins();
 memcpy(screen,double_buffer,64000);
 getch();
wina[0].order=1;
 drawallwins();
 memcpy(screen,double_buffer,64000);
 getch();
wina[0].order=5;
 drawallwins();
 memcpy(screen,double_buffer,64000);
 getch();
 while (winsa_tot>0){clearLwin();}
 drawallwins();
 memcpy(screen,double_buffer,64000);
 getch();
char key=0;
int nostop=1;

while (nostop==1)
{
 key=0;
 if (kbhit()){key=getch();cout<<int(key)<<"||"<<key;}
 if (key=='q' || key=='Q'){nostop=0;}
}

}
