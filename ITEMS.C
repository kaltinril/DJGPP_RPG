void dtbox(long arry,int w,int h,int color,int cl)
{
 int f=0,g=0,n=0;
 for (f=0;f<h;++f)
 {
  for (g=0;g<w;++g)
  {
   if (text[arry+g+n]==cl){text[arry+g+n]=color;}
  }
  n=n+320;
 }
}

void cbox(long arry,long arry2,int w,int h)
{
 int f=0,g=0,n=0;
 for (f=0;f<h;++f)
 {
  for (g=0;g<w;++g)
  {
   text[arry+g+n]=temp[arry2+g+n];
  }
  n=n+320;
 }
}

void sprint(char *s)
{
 int n=curs_y;
 int nn=curs_x;
 int nm=strlen(s);
 print(s);
 curs_y=n;
 curs_x=nn+(9*nm);
}

void bsprint(char *s,int n,int change)
{
 curs_x=curs_x+((9*4)-((strlen(s)-change)*9));
 if (n==0){sprint(s);}
 if (n==1){print(s);}
}

void org_item()
{
 int is=0,ns=0,ni=0;
  for (is=0;is<bag_tot;++is)
  {
	if (bag_iamt[is]!=99)
		{
		 for (ns=is+1;ns<bag_tot;++ns)
		 {
		  if (bag_item[ns]==bag_item[is])
		  {
			bag_iamt[is]=bag_iamt[is]+bag_iamt[ns];
			if (bag_iamt[is]>99)
			{
			 bag_iamt[ns]=bag_iamt[is]-99;
			 bag_iamt[is]=99;
			}
			else
			{
                         for (ni=ns+1;ni<(bag_tot-1);++ni)
			 {
			  bag_item[ni]=bag_item[ni+1];
			  bag_iamt[ni]=bag_iamt[ni+1];
			 }
			 bag_item[bag_tot]=0;
			 bag_iamt[bag_tot]=0;
			 --bag_tot;
			}//end else
		  }//end if bag_item
		 }//end for ns
		}//end if bag_iamt
	  }//end for i
}//end function

void check_key(char key)
{
long ary=0;
 switch (key)
 {
  case 'q':case 'Q':
  //end program
  break;
  case LEFT:x_dir=-1;y_dir=0;
  next_an_tile=2;
  way=1;
  break;
  case DOWN:x_dir=0;y_dir=1;
  next_an_tile=0;
  way=0;
  break;
  case RIGHT:x_dir=1;y_dir=0;
  next_an_tile=2;
  way=0;
  break;
  case UP:x_dir=0;y_dir=-1;
  next_an_tile=1;
  way=0;
  break;
  case ' ':
  ary=(((ch_y-4)+ch_zy+y_dir)*100)+((ch_x+ch_zx)+x_dir);
  cout<<"\n"<<ary;
  getch();
  check_action(ary);
  break;
  default:
  break;
 }


}

int pcharm(int yy)
{
 //memcpy(text,screen,64000);
 //memcpy(double_buffer,text,64000);
 int ogo=0;
 char key=0;
 long toff=0;
 int n=0;
 while (ogo==0)
 {
  key=0;
     AUpdateAudio();
  if (kbhit()){key=getch();}
  if (key=='8'){--n;if (n<0){n=0;}}
  if (key=='5'){++n;if (n>mplayers-1){n=mplayers-1;}}
  if (key==' '){return(n);}
  toff=(24*320)+15;
  toff=toff+((50*320)*n);
  dm(yy);
  dtbox(toff,44,44,2,0);
  memcpy(screen,text,64000);
  Clear(0,text);
   winsa_tot=winsa_tot-3;
 }
 return (-1);
}

void mmenu()
{
 load_pcx(temp,320,200,"chars01.pcx",0,255,0);
 char tempchr[128];
 int tempsec=0,tempmin=0,temphour=0;
 long temptime=0,ttime=0,lasttime=0;
 int ogo=0;
 int var=0;
 char key;
 int f=0,n=0,nn=0;
 long toff=0,ttoff=0;
 int yy=9;
 while (ogo==0)
 {
 key=0;
    AUpdateAudio();
 if (kbhit()){key=getch();}
 if (key=='q' || key=='Q'){ogo=1;}
 if (key==' ')
 {
  if (yy==((8*5)+9)){ogo=1;}
  if (yy==(9+(8*1))){var=pcharm(yy);equipmen(var);}
  if (yy==(9+(8*3))){var=pcharm(yy);statmen(var);}
  if (yy==9){imenu();}
 }
 if (key=='v' || key=='V')
 {
  if (mplayers<3){n=(rand()%4)+1;
  load_chars(n);
  players[mplayers-1].data[19]=(rand()%51);
  players[mplayers-1].data[18]=50;}
 }
 if (key=='w'){tempmin=tempmin+59;}
 if (key=='8'){yy=yy-8;if (yy<10){yy=9;}}
 if (key=='5'){yy=yy+8;if (yy>(8*5)+9){yy=(8*5)+9;}}
 dm(yy);
 memcpy(screen,text,64000);
 Clear(0,text);
 winsa_tot=winsa_tot-3;
 }
}


void imenu()
{
 int ogo=0;
 char key=0;
 int yy1=9,xx1=5,yy2=35,xx2=3;
 int my=0,mx=0;
 long toff=0,ttoff=0;
 int nn=0;
 char tempchr[128];
 int f=0,srn=0;
 while (ogo==0)
 {
 key=0;
    AUpdateAudio();
 if (kbhit()){key=getch();} //get key
 //check keys
 if (key=='q' || key=='Q'){ogo=1;}
 if (key=='4')
 {
  if (nn==0){xx1=xx1-63;if (xx1<5){xx1=5;}}
 }
 if (key=='6')
 {
  if (nn==0){xx1=xx1+63;if (xx1>257){xx1=257;}}
 }
  if (key=='5'){yy2=yy2+8;++my;if (my>14){--my;yy2=yy2-8;++srn;}if (srn+15>bag_tot){--srn;if (srn<0){srn=0;}}}
 if (key=='8'){yy2=yy2-8;--my;if (my<0){++my;yy2=yy2+8;--srn;};if (srn<0){srn=0;};if (yy2<35){yy2=35;++my;}}
 if (key=='a' || key=='A'){nn=0;}
 if (key==' ')
 {
  if (xx1==257){ogo=1;}
  if (xx1==5){nn=1;}
  if (xx1==131){org_item();org_item();}
 }
 if (key=='v' && bag_tot<100){bag_item[bag_tot]=rand()%3;bag_iamt[bag_tot]=(rand()%99)+1;++bag_tot;}
 //end keys styff


 toff=(yy1<<8)+(yy1<<6)+xx1;
 ttoff=(yy2<<8)+(yy2<<6)+xx2;
 draw_window("Use    Drop   Sort          Exit",3,7,312,12);

 dtbox(toff,63,8,4,32);

 draw_window("      Items",3,25,180,171);

 if (bag_tot>0)
 {
  for (f=0;f<15;f=f+1)
  {
   sprintf(tempchr,"%s",items[bag_item[srn+f]].name);
   print(tempchr);
   sprintf(tempchr,":%d",bag_iamt[srn+f]);
   locate(17,((curs_y-wina[1].t)-10)/8,1);
   print(tempchr);
   if (f+srn+2>bag_tot){f=15;}
  }
 }

 else {sprintf(tempchr,"Bag Empty");print(tempchr);}
 if (nn!=0){dtbox(ttoff,180,8,4,32);}

 draw_window("Affects~~",189,25,126,171);
 print("A to Abort~~");
 draw_window("",3,184,312,12);
 if (nn==1 && (my+srn)<bag_tot){print(items[bag_item[my+srn]].des);}
 memcpy(screen,text,64000);
 Clear(0,text);
 winsa_tot=winsa_tot-4;
 }
}

void statmen(int s)
{
 long toff,ttoff;
 int goo=0;
 char key;
 char tempchr[20];
 long ang=0;
 while (goo==0)
 {
  key=0;
     AUpdateAudio();
  if (kbhit()){key=getch();}
  if (key=='q' || key=='Q' || key=='a' || key=='A'){goo=1;}
  draw_window("",3,7,312,183);
  draw_window("Status",3,7,57,12);
  toff=24*320+5;
  ttoff=players[s].place*44;
  if (players[s].data[0]==0){ttoff=6*44;}
  cbox(toff,ttoff,44,44);
  locate(7,0,0);
  sprintf(tempchr,players[s].name);
  print(tempchr);

  locate(17,0,0);toff=(curs_y<<8)+(curs_y<<6)+curs_x;print("EXP INFO");dtbox(toff,9*strlen("exp info"),8,22,32);
  locate(19,1,0);sprintf(tempchr,"Level:%d",players[s].data[5]);print(tempchr);
  locate(19,2,0);sprintf(tempchr,"Exp:  %d",players[s].data[4]);print(tempchr);
  locate(18,3,0);print("NEXT Lv.");
  locate(19,4,0);toff=(curs_y<<8)+(curs_y<<6)+curs_x;sprintf(tempchr,"Need: %d",players[s].data[18]);print(tempchr);
  dtbox(toff,9*strlen(tempchr),8,2,32);
  locate(19,5,0);toff=(curs_y<<8)+(curs_y<<6)+curs_x;sprintf(tempchr,"Have: %d",players[s].data[19]);print(tempchr);
  dtbox(toff,9*strlen(tempchr),8,4,32);
  //start of hp/mp area
  locate(5,2,0);print("HP:");
  locate(7,3,0);
  sprintf(tempchr,"%d/",players[s].data[0]);bsprint(tempchr,0,1);
  sprintf(tempchr,"%d",players[s].data[1]);bsprint(tempchr,1,0);
  locate(5,5,0);print("MP:");
  locate(7,6,0);
  sprintf(tempchr,"%d/",players[s].data[2]);bsprint(tempchr,0,1);
  sprintf(tempchr,"%d",players[s].data[3]);bsprint(tempchr,1,0);
  //end of hp/mp area    start of other main area
  locate(3,8,0);toff=(curs_y<<8)+(curs_y<<6)+curs_x;print("Main INFO");dtbox(toff,9*strlen("Main INFO"),8,22,32);
  locate(0,10,0);print("defence  10");
  print("Magic    10");
  print("Attack   10");
  //End main INFO area    start of magic info
  locate(20,8,0);toff=(curs_y<<8)+(curs_y<<6)+curs_x;print("Magic INFO");dtbox(toff,9*strlen("Magic INFO"),8,22,32);
  locate(18,10,0);print("Defence   3%");
  locate(18,11,0);print("Weak   Fire  10%");
  //end text
  memcpy(double_buffer,text,64000);
  ang=(float(players[s].data[19])/float(players[s].data[18]))*360;
  circlef(290,48,2,20,360);
  circlef(290,48,4,20,ang);
  memcpy(screen,double_buffer,64000);
  Clear(0,text);
  winsa_tot=winsa_tot-2;
 }
}

void equipmen(int s)
{
 long toff,ttoff;
 int goo=0;
 char key;
 char tempchr[20];
 while (goo==0)
 {
  key=0;
     AUpdateAudio();
  if (kbhit()){key=getch();}
  if (key=='q' || key=='Q' || key=='a' || key=='A'){goo=1;}
  draw_window("",3,7,312,183);
  draw_window("Equip",3,7,57,12);
  toff=24*320+15;
  ttoff=players[s].place*44;
  if (players[s].data[0]==0){ttoff=6*44;}
  cbox(toff,ttoff,44,44);
  locate(7,0,0);
  sprintf(tempchr,players[s].name);
  print(tempchr);
  memcpy(screen,text,64000);
  Clear(0,text);
  winsa_tot=winsa_tot-2;
 }
}

void dm(int yy)
{
 char tempchr[128];
 int tempsec=0,tempmin=0,temphour=0;
 long temptime=0,ttime=0,lasttime=0;
 int f=0,n=0,nn=0;
 long toff=0,ttoff=0;

 toff=(yy<<8)+(yy<<6)+240;
 draw_window("Items~Equip~Magic~Status~Save~Exit~~~To Exit~Space on Exit ~~Coding~by~Rack",240,7,75,132);
 dtbox(toff,75,8,4,32);
 //drawing window for time and gold
 draw_window("Time:",240,145,75,45);
 temptime=(clock()/CLOCKS_PER_SEC);
 ttime=temptime-lasttime;
 lasttime=temptime;
 tempsec=tempsec+ttime;
 while (tempsec>59)
 {
  ++tempmin;
  tempsec=tempsec-60;
 }
 while (tempmin>59){++temphour;tempmin=tempmin-60;}
 sprintf(tempchr,"%d:%d:%d",temphour,tempmin,tempsec);
 print(tempchr);
 print("~");
 print("Gold:");
 sprintf(tempchr," %d",gold);
 print(tempchr);
 //end of printing for time/gold window
 draw_window("       Characters",3,7,231,183);
 toff=24*320+15;
 for (n=0;n<mplayers;++n)
 {
  ttoff=players[n].place*44;
  if (players[n].data[0]==0){ttoff=6*44;}
  cbox(toff,ttoff,44,44);
  curs_x=80;
  curs_y=(toff-15)/320;
  toff=toff+(50*320);
  print(players[n].name);
  curs_x=80;
  sprint("Hp:");
  sprintf(tempchr,"%d/",players[n].data[0]);
  curs_x=curs_x+((9*4)-((strlen(tempchr)-1)*9));
  sprint(tempchr);
  sprintf(tempchr,"%d",players[n].data[1]);
  curs_x=curs_x+(9*4)-(strlen(tempchr)*9);
  print(tempchr);
  curs_x=80;
  sprint("Mp:");
  sprintf(tempchr,"%d/",players[n].data[2]);
  curs_x=curs_x+((9*4)-((strlen(tempchr)-1)*9));
  sprint(tempchr);
  sprintf(tempchr,"%d",players[n].data[3]);
  curs_x=curs_x+(9*4)-(strlen(tempchr)*9);
  print(tempchr);
  if (n==2){n=mplayers;}
 }


}
