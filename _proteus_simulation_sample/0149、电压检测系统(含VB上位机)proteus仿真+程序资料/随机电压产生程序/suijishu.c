#include<reg52.h>
#include<stdlib.h>
void main(void)
{ 
  int tempnum,i;
  while(1)
{
  tempnum=rand();
  if (0<=tempnum<=255)
  P1=tempnum;
  for(i=0;i<30000;i++);
}
 
}

