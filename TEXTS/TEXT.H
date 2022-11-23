  short curs_y,curs_x,curs_s_x;
short t_max=312;
short c_xst=35,c_yst=20;
  unsigned char *abc=new unsigned char[64000];
  unsigned char *text=new unsigned char[64000];
struct wins
{
 char s[10][128]; //String
 short ss;    //total amount of strings
 short l;     //Left
 short t;     //Top
 short w;     //Width
 short h;     //Height
 short order;
};
wins wina[5];
short winsa_tot=0;
 void dis_char(int);
 void print(char *);
 void add_print(char *,int);
 void draw_window(int);
 int create_window(char *,int,int,int,int,int);
 void locate(int,int,int);
void clearLwin();
void drawallwins();