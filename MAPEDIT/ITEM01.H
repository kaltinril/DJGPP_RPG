struct item
{
 char name[20];
 char des[100];
 short add[100];
 short type[100];
 short add_tot;
};
long items_max=0;
char item_fn[13]="items001.lst";
item items[1024];
void load_items();