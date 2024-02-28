#include <stdio.h>
#include <conio.h>
unsigned int uCRC16;
void CRC_16(unsigned char d)
{
  for( unsigned char i = 0; i < 8; i++ )
  {
    if ((uCRC16 ^ (d >> i)) & 0x01)
    {
      uCRC16 >>= 1 ; uCRC16 ^= 0xA001;
    }
    else uCRC16 >>= 1;
  }
}
void main()
{  
  FILE *CRC16_File;  int i;
  CRC16_File = fopen("c:\\CRC16.txt","w");
  for (i = 0x00; i <= 0xFF; i++)
  {
	 uCRC16 = 0x0000;  CRC_16(i);
     fprintf(CRC16_File,"0x%04X",uCRC16);
     if (i != 0xFF) fprintf(CRC16_File,",");
     if (i % 10 == 9) fprintf(CRC16_File,"\n");
  }
  fclose(CRC16_File);
}
