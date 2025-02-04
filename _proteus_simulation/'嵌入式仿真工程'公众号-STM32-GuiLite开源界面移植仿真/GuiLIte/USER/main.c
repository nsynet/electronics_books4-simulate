#include "led.h"
#include "GPIO_lcd.h"
#include "hanzi.h"
#define NULL 0
#define GL_RGB_32_to_16(rgb) (((((unsigned int)(rgb)) & 0xFF) >> 3) | ((((unsigned int)(rgb)) & 0xFC00) >> 5) | ((((unsigned int)(rgb)) & 0xF80000) >> 8))
//Encapsulate your LCD driver:
void gfx_draw_pixel(int x, int y, unsigned int rgb)
{
	GPIO_SetPointPixel(x, y, GL_RGB_32_to_16(rgb));
}
//UI entry
struct DISPLAY_DRIVER
{
	void (*draw_pixel)(int x, int y, unsigned int rgb);
	void (*fill_rect)(int x0, int y0, int x1, int y1, unsigned int rgb);
} Gui_driver;
extern void startHelloParticle(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver);
void delay_1ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //自己定义
      while(i--) ;    
   }
}
void ILI9341_Show_Chinese( uint16_t x, uint16_t y, uint8_t* font, uint8_t size, uint32_t fColor, uint32_t bColor)
{
    uint8_t temp;
	uint16_t y0=y; 
  uint8_t t,t1;  
	uint8_t csize=(size/8+((size%8)?1:0))*(size);	// 得到字体一个字符对应点阵集所占的字节数	
	for(t=0; t<csize; t++)
	{   												   
		temp = font[t];			                                          
		for(t1=0; t1<8; t1++)
		{
			if(temp&0x80)   GPIO_SetPointPixel(x, y, fColor);	
            else            GPIO_SetPointPixel(x, y, bColor);            
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}      
}

int main(void)
{ 
 
	unsigned short i;
	LED_Init();		        //
	GPIO_LCD_Init ();  
	Gui_driver.draw_pixel = gfx_draw_pixel;
	Gui_driver.fill_rect = NULL;
	startHelloParticle(NULL, 320, 240, 2, &Gui_driver);
	while(1)
	{
		delay_1ms(1000);
	}
}






