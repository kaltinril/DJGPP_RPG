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
  //end key list
  switch (key)
  {
   case 'a':case 'A':
   cout<<"Attach what?\n";
   attach();
   break;
   case 'e':case 'E':loopin=end_it;
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
 int n=0;
 long ary=(((ch_y-4)+6)*100)+((ch_x)+10);
 while (gogo==0)
 {
  if (kbhit()){key=getch();}
  display_at();
  if (key=='e' || key=='E'){gogo=1;}
  if (key=='w' || key=='W')
  {
   chan=item_tot;
   Clear(0,screen);
   for (n=0;n<item_tot;++n) //loop through items look for warp
   {
    cout<<item_place[n]<<"-"<<n<<"\n";
    if (item_place[n]==ary){cout<<"looks like you already have one\n";
    chan=n;
    cout<<chan<<"hhhh\n";
    if (n==item_tot){cout<<"sfsddsdsfdf"<<"\n";}
    n=item_tot;
    }    //end if
   }    //end for
      cout<<"d"<<chan<<"="<<item_tot<<"\n";
      if (chan==item_tot){++item_tot;}
   item_place[chan]=ary;
   item_name[chan]=1;
   item_temp[chan]=ary+1;
   item_tmp2[chan]=1;
   item_trig[chan]=5;
   key=getch();
  }  //end w

 }
}

void display_at()
{
 gotoxy(1,1);
 cout<<"list1\n";
 cout<<"warp\n";
}
