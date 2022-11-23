void dis_char(int charv) //get the value of the character to be read
{
 charv=charv<<3; //times the charv by 8 becaues every letter is 8 accross
 int chars_y=0,chars_x=charv;  //the x and y varaibles for the abc pcx file
 long color_get=0,color_put=0;  //the 2 array values to point to the start
                                //of the places in the buffers
 while (charv>311){chars_y=chars_y+8;charv=charv-312;}  //to get the y
                                     //value for the abc pcx file position
 chars_x=charv; //sets the x value to the correct position
 color_get=(chars_y<<8)+(chars_y<<6)+chars_x;   //sets the array value to the
 color_put=(curs_y<<8)+(curs_y<<6)+curs_x;     //correct values to point to
                                   //the start of the place in the buffer
 int y,x,color;
 for (y=0;y<8;++y)
 {
  for (x=0;x<8;++x)
  {
   color=abc[color_get+x];
   if (color>0)
   {
    double_buffer[color_put+x]=color;//put the color from the abc to the text buffer
   }
  }
  color_get=color_get+320; //move down to next y start
  color_put=color_put+320; //same here
 }
 curs_x=curs_x+9;
 if (curs_x>t_max-1){curs_x=curs_x-t_max;curs_y=curs_y+8;}
}


void print(char *charlist)
{
 int length=strlen(charlist);//get the length of the string to be printed
 int i=0,check=0;
 int value=0,bv=0;
 int st_a=0,new_a=c_xst,end_a=c_xst;
  while(length>st_a)
 {
 new_a=c_xst;
 if ((st_a+(end_a))>length)
 {
  new_a=length-st_a;
 }
 if ((st_a+(end_a))<length)
 {
  if (charlist[st_a+end_a-1]!=32 && charlist[st_a+end_a-1]!=int('~'))
   {
    if (charlist[st_a+end_a]!=32 && charlist[st_a+end_a]!=int('~'))
     {
      for (i=0;i<end_a;++i)
      {
       if (charlist[(st_a+(end_a-1))-i]==32)
       {
        new_a=(end_a-1)-i;
        i=end_a;
       }
      }
     }
    }
  }
  for (i=0;i<new_a;++i)
  {
  value=int(charlist[st_a+i]); //find the value of the letter to be printed
                          //correct value to fit my pcx file settings.

  bv=value;
/*  if (value>63 && value<91 && value==bv){value=value-65;}
  if (value>96 && value<124 && value==bv){value=value-71;}
  if (value>47 && value<58 && value==bv){value=value+4;}
  if (value==32 && value==bv){value=62;}
  if (value==46 && value==bv){value=63;}
  if (value==44 && value==bv){value=64;}
  if (value>38 && value<43 && value==bv){value=value+26;}
  if (value==58 && value==bv){value=69;}
  if (value==59 && value==bv){value=70;}
  if (value==33 && value==bv){value=71;}
  if (value=='/' && value==bv){value=65;}
  if (value=='!' && value==bv){value=66;}
  if (value=='%' &&value==bv){value=67;}
*/                        //end correcting value.
  check=curs_y;
  if (bv==int('~')){curs_y=curs_y+8;curs_x=curs_s_x;st_a=st_a-(new_a-i)+1;i=new_a;}else{dis_char(value);}
 if ((st_a+i+2)>length){i=new_a;}
 }
 if (check==curs_y){curs_y=curs_y+8;}
 curs_x=curs_s_x;
 st_a=st_a+new_a;
 while(charlist[st_a]==32){st_a=st_a+1;}
 }
}


int create_window(char *texts,int left, int top, int width, int length,int order)
{

 sprintf(wina[winsa_tot].s[0],texts);
 wina[winsa_tot].l=left;
 wina[winsa_tot].t=top;
 wina[winsa_tot].w=width;
 wina[winsa_tot].h=length;
 wina[winsa_tot].ss=1;
 wina[winsa_tot].order=order;
 ++winsa_tot;
 return(winsa_tot-1);
}

void draww(int left,int top,int width,int length)
{
  int n=0;
 long toff=((top-3)<<8)+((top-3)<<6)+(left-3);
 long tnoff=((top)<<8)+((top)<<6)+(left);
 memcpy(double_buffer+toff,abc+3197,3);
 memcpy(double_buffer+toff+320,abc+3517,3);
 memcpy(double_buffer+toff+640,abc+3837,3);
 for (n=3;n<length+3;n=n+3)
 {
 memcpy(double_buffer+toff+n*320,abc+317,3);
 memcpy(double_buffer+toff+(n*320)+320,abc+637,3);
 memcpy(double_buffer+toff+(n*320)+640,abc+957,3);
 }
 memcpy(double_buffer+toff+(n*320),abc+4157,3);
 memcpy(double_buffer+toff+(n*320)+320,abc+4477,3);
 memcpy(double_buffer+toff+(n*320)+640,abc+4797,3);
 int f=n*320;
 for (n=3;n<width+3;n=n+3)
 {
 memcpy(double_buffer+toff+n+f,abc+5117,3);
 memcpy(double_buffer+toff+n+f+320,abc+5437,3);
 memcpy(double_buffer+toff+n+f+640,abc+5757,3);
 }
 for (n=3;n<width+3;n=n+3)
 {
 memcpy(double_buffer+toff+n,abc+5117,3);
 memcpy(double_buffer+toff+n+320,abc+5437,3);
 memcpy(double_buffer+toff+n+640,abc+5757,3);
 }
 f=n;
 for (n=3;n<length+3;n=n+3)
 {
 memcpy(double_buffer+toff+(n*320)+f,abc+317,3);
 memcpy(double_buffer+toff+(n*320)+f+320,abc+637,3);
 memcpy(double_buffer+toff+(n*320)+f+640,abc+957,3);
 }
 memcpy(double_buffer+toff+(n*320)+f,abc+2237,3);
 memcpy(double_buffer+toff+(n*320)+f+320,abc+2557,3);
 memcpy(double_buffer+toff+(n*320)+f+640,abc+2877,3);
 memcpy(double_buffer+toff+f,abc+1277,3);
 memcpy(double_buffer+toff+f+320,abc+1597,3);
 memcpy(double_buffer+toff+f+640,abc+1917,3);
 n=0;
 for (f=0;f<length;++f)
 {
 memset(double_buffer+tnoff+n,32,width);
 n=n+320;
 }
}
void draw_window(int wind)
{
int left=0,top=0,width=0,length=0;
 left=wina[wind].l;
 top=wina[wind].t;
 width=wina[wind].w;
 length=wina[wind].h;
 int n=0;
 /*
 long toff=((top-3)<<8)+((top-3)<<6)+(left-3);
 long tnoff=((top)<<8)+((top)<<6)+(left);
 int f=0;

 for (f=0;f<length;++f)
 {
 memset(text+tnoff+n,32,width);
 n=n+320;
 }//draws the blue background            */
 draww(left,top,width,length);

 //the next 4 lines set up the test start end postions
 c_xst=width/9;
 curs_x=left+2;
 curs_s_x=curs_x;
 curs_y=top+2;
 //prints all of the lines into the window
 n=0;
 while (n<wina[wind].ss)
 {
  print(wina[wind].s[n]);
  ++n;
 }

}



void add_print(char *string,int wind)
{
 //put the string into the next line in the window
 sprintf(wina[wind].s[wina[wind].ss],string);
 ++wina[wind].ss; //set it up so for the next add_print
}

void locate(int a,int b,int c)
{
 curs_x=wina[c].l+(a*9)+2;
 curs_y=wina[c].t+(b<<3)+2;
 c_xst=wina[c].w;
}


void clearLwin()
{
 int n=0,m=0;
int length=0;
 for (n=0;n<wina[winsa_tot-1].ss;++n)
 {
  for (m=0;m<strlen(wina[winsa_tot-1].s[n]);++m)
  wina[winsa_tot-1].s[n][m]=0;
 }
 wina[winsa_tot-1].ss=0;
 wina[winsa_tot-1].l=0;
 wina[winsa_tot-1].t=0;
 wina[winsa_tot-1].w=0;
 wina[winsa_tot-1].h=0;
 --winsa_tot;
}

void drawallwins()
{
 int n=0,m=0;
Clear(0,double_buffer);
for (n=0;n<5;++n)
{
 for (m=0;m<winsa_tot;++m)
 {
  if (wina[m].order==(5-n))
   {draw_window(m);}
 }
}
}