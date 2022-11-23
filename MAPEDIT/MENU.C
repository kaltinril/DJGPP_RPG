void menu_sys()
{
 char key=0;
 int loopin=0;
 int end_it=1;
 int r_t=15;
 while (loopin==0)
 {
  key=0;
  if (kbhit()){key=getch();}
  if (key!=0){Clear(0,screen);}
  gotoxy(1,1);
  cout<<"|Key|\n";
  gotoxy(r_t,1);
  cout<<"|Action|\n";
  cout<<"----------------------------------------\n";
  //key list
  gotoxy(1,3); //e
  cout<<"e E\n";
  gotoxy(r_t,3);
  cout<<"Exit\n";
  gotoxy(1,4);//a
  cout<<"a A\n";
  gotoxy(r_t,4);
  cout<<"Attach -s to tile\n";
  gotoxy(1,5);
  cout<<"i I\n";
  gotoxy(r_t,5);
  cout<<"Items attributes\n";
  //end key list
  switch (key)
  {
   case 'a':case 'A':
   cout<<"Attach what?\n";
   attach();
   break;
   case 'e':case 'E':loopin=end_it;
   break;
   case 'i':case 'I':
   cout<<"ok item total is?\n";
   item_tot=int(getch())-48;
   break;
   default:
   break;
  }
 }
 Clear(0,screen);
}

void attach()
{
 int gogo=0;
 char key=0;
 int chan=0;
 int nary=0,aary=0;
 int n=0;
 long ary=(((ch_y-4)+ch_zy)*100)+((ch_x)+ch_zx);
 while (gogo==0)
 {
  if (kbhit()){key=getch();}
  display_at();
  if (key=='e' || key=='E'){gogo=1;}
  if (key=='w' || key=='W')
  {
  char temp_map[13];
   strncpy(temp_map,(char *)map_name,12);
   temp_map[12]='\0';
   tempx=ch_x;
   tempy=ch_y;
   aary=pick_map();
   nary=pick_map_place(aary);
   if (map_now[0]+map_now[1]>1){set_fname(map_now[0],map_now[1]);}
   if (map_now[0]+map_now[1]<2)
   {
    strncpy(RfName,(char *)temp_map,12);
    RfName[12]='\0';
    open_map();
   }
   chan=item_tot;
   Clear(0,screen);
   cout<<"itemtot"<<item_tot<<"\n";
   getch();
   for (n=0;n<item_tot;++n) //loop through items look for warp
   {
    cout<<item_place[n]<<"-"<<n<<"\n";
    if (item_place[n]==ary)
    {
    chan=n;
    n=item_tot;
    }    //end if
   }    //end for
      if (chan==item_tot){++item_tot;}
   int x=0,y=0;
   while (aary>9)
   {
    aary=aary-10;
    ++x;
   }
   y=aary;
   cout<<"x"<<x<<"y"<<y<<"\n";
   getch();
   item_place[chan]=ary;   //were to warp from
   item_name[chan]=x;      //which list to find the map in
   item_temp[chan]=nary;  //were to warp to
   item_tmp2[chan]=y;      //which map in the list to warp to
   item_trig[chan]=5;      //action tigger value
   key=getch();
   ch_x=tempx;
   ch_y=tempy;
  }  //end w

 }
}

void display_at()
{
 gotoxy(1,1);
 cout<<"list1\n";
 cout<<"warp\n";
}
