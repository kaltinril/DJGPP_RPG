void org_item();
void check_key(char);
void check_action(long);
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
  case LEFT:x_dir=-1;y_dir=0;break;

  case DOWN:x_dir=0;y_dir=1;break;

  case RIGHT:x_dir=1;y_dir=0;break;

  case UP:x_dir=0;y_dir=-1;break;

  default:
  break;
 }


}
