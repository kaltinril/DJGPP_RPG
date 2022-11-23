/////////////// pcx.c ////////////////
//////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
char load_pcx(unsigned char *buffer, long x_size, long y_size, char *filename, unsigned char set_pal_start, unsigned char set_pal_end, unsigned char map_pal_offset)
  {
  FILE *fp;
  int num_bytes,index;
  long count;
  unsigned char data;
  struct
    {
    unsigned char red, blue, green;
    } palette[256];

  if((fp = fopen(filename,"rb"))==NULL)
    return -1;
  // load the header
  for(index=0; index<128; index++)
    getc(fp);
  // load the data and decompress into buffer
  count=0;
  while(count <= x_size*y_size)
    {
    data = getc(fp);
    if(data>=192 && data<=255)
      {
      num_bytes = data-192;
      data  = getc(fp);
      while(num_bytes-->0)
        buffer[count++] = data+(map_pal_offset-set_pal_start);
      } // end if rle
    else  // actual data, just copy it into buffer at next location
      buffer[count++] = data+(map_pal_offset-set_pal_start);
    } // end while
  fseek(fp,-768L,SEEK_END);
  for (index=0; index<256; index++)
    {
    palette[index].red   = (getc(fp) >> 2);
    palette[index].green = (getc(fp) >> 2);
    palette[index].blue  = (getc(fp) >> 2);
    } // end for index
  for(index=0; index<(set_pal_end-set_pal_start); index++)
    {
    outportb(0x3c8, index+map_pal_offset);
    outportb(0x3c9, palette[index+set_pal_start].red);
    outportb(0x3c9, palette[index+set_pal_start].green);
    outportb(0x3c9, palette[index+set_pal_start].blue);
    }
  fclose(fp);
  return 0;
  }
//////////////////////////////////////////////////////////////////////////

