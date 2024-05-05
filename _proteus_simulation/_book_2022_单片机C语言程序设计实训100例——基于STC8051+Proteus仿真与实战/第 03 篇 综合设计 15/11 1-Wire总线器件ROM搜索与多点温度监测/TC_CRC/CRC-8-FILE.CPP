#include <stdio.h>
unsigned char uCRC8;
void CRC8_1(unsigned char d)
{
  for( unsigned char i = 0; i < 8; i++ )
  {
    if ((uCRC8 ^ (d >> i)) & 0x01) { uCRC8 >>= 1 ; uCRC8 ^= 0x8C; }
    else uCRC8 >>= 1;
  }
}
//---------------------------------------------------------
void main()
{
  FILE *CRC8_File;  int i;
  CRC8_File  = fopen("c:\\CRC8.txt","w");
  for (i = 0x00; i <= 0xFF; i++)
  {
     uCRC8 = 0x00;
     CRC8_1(i);
     fprintf(CRC8_File,"0x%02X",uCRC8);
     if (i != 0xFF) fprintf(CRC8_File,",");
     if (i % 10 == 9) fprintf(CRC8_File,"\n");
  }
  fclose(CRC8_File);
}