#include <stdio.h>
void main()
{
  FILE *fp;
  fp = fopen("24c04.bin","wb");
  fwrite("111111\x0",1,7,fp);
  fclose(fp);
}