void load_items()
{
 char blah[100];
 char byte_test;
 char test_string[14]="////++\\\\\\\\";

 long n=0,x=0,nn=1;
 short goo=0,ggo=0;

 ifstream fin;
 fin.open(item_fn);
 nn=0;
 while (n==0)
 {
  fin >> byte_test;
  if (byte_test==test_string[nn]){++nn;}
  ++x;
  if (nn==10){n=6;}
  if (x!=nn){x=0;nn=0;}
 }
 n=0;
 nn=0,x=0;
 int sn=0;
 while(goo==0)
 {
 items[n].add_tot=0;
  fin >> items[n].name;
  for (sn=0;sn<strlen(items[n].name);++sn)
  {
   if (items[n].name[sn]=='_'){items[n].name[sn]=32;}
  }
  fin >> items[n].des;
  for (sn=0;sn<strlen(items[n].des);++sn)
  {
   if (items[n].des[sn]=='_'){items[n].des[sn]=32;}
  }
  fin >> blah;
  ggo=0;
  while (ggo==0)
  {
   fin >> items[n].add[items[n].add_tot];
   fin >> items[n].type[items[n].add_tot];
   fin >> blah;
   if (blah[4]=='-'){ggo=1;}
   ++items[n].add_tot;
  }
  ++n;
  fin >> blah;
  if (strlen(blah)==10)
  {
   if (blah[4]=='-'){items_max=n;goo=1;}
  }
 }
 fin.close();
}



void load_chars(int pc)
{
 int ammt=0;
 char blah[100];
 char byte_test;
 char test_string[14]="////++\\\\\\\\";

 long n=0,x=0,nn=1;
 short goo=0,ggo=0;

 ifstream fin;
 fin.open("chars.lst");
 nn=0;
 while (n==0)
 {
  fin >> byte_test;
  if (byte_test==test_string[nn]){++nn;}
  ++x;
  if (nn==10){n=6;}
  if (x!=nn){x=0;nn=0;}
 }
 n=0;
 nn=0,x=0;
 int sn=0;
 while(goo==0)
 {
  fin >> players[mplayers].name;
  fin >> players[mplayers].type;
  fin >> players[mplayers].data[1];
  players[mplayers].data[0]=players[mplayers].data[1];
  fin >> players[mplayers].data[3];
  players[mplayers].data[2]=players[mplayers].data[3];
  fin >> players[mplayers].data[5];
  players[mplayers].data[4]=0;
  fin >> players[mplayers].data[6];  //strength
  fin >> players[mplayers].data[7];  //defence
  fin >> players[mplayers].data[8];  //speed
  fin >> players[mplayers].data[9];  //left or right
  fin >> players[mplayers].place;
  fin >> blah;
  if (strlen(blah)==10)
  {
   if (blah[4]=='='){++ammt;if (ammt==pc){goo=1;++mplayers;}}
   if (blah[4]=='-' && pc>ammt+1){goo=1;sprintf(players[mplayers].name,"Error c1");}
   if (blah[4]=='-' && pc<=ammt+1){goo=1;++mplayers;}
  }
 }
 fin.close();
}