int damage=0,n_damage=0,damage_type=0,enemys[3];
int ch_n=0,ch_x=0,ch_y=4,y_dir=1,x_dir=0,cx_off=0,cy_off=0;
int ch_zx=10,ch_zy=6;
int gold=129;
int mplayers=0;
int pkind[15];
struct player
{
  char name[20];
  int type;
  long place;
  //thinking about making an array for all of these ints.
  //and access it with #defines that say hp=0; hpt=1; etc.

  long data[100];
  //0  hp
  //1  hp  total
  //2  mp
  //3  mp  total
  //4  exp
  //5  expl
  //6  intitial strength
  //7  intitial defence
  //8  intitial speed
  //9  left or right handed
  //10  left
  //11  right
  //12  head
  //13  body
  //14  special
  //15  attack
  //16  defence
  //17  magic
  //18  expneeded
  //19  exphave
};
player players[15];

