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
 while(goo==0)
 {
 items[n].add_tot=0;
  fin >> items[n].name;
  fin >> items[n].des;
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