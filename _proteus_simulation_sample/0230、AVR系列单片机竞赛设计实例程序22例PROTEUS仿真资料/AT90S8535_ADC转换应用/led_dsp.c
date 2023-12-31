#define _led_dsp_c
#include <io8535v.h>
#include <macros.h>
#include <led_dsp.h>
#include <adc.h>
void change_data (int dsp_data)
{
	uchar temp_n;
	if(dsp_data<=(AREF_VOL*100))
		{
			temp_n = dsp_data/1000;
			disp_buffer[0]=led_tabel[temp_n];
			dsp_data %=1000;
			temp_n = dsp_data/100;
			disp_buffer[1]=(led_tabel[temp_n])|0x80;//加上小数点
			dsp_data %=100;
			temp_n = dsp_data/10;
			disp_buffer[2]=led_tabel[temp_n];
			dsp_data %=10;
			disp_buffer[3]=led_tabel[dsp_data];
		}
	//scan_led(disp_buffer);
	return;
}

void scan_led(uchar *disp_p)
{
	uchar i,scan_n;
	scan_n=0xfe;
	for (i=0; i<4; i++)
	{
		data_port = *(disp_p+i);
		scan_port = scan_n;
		scan_n=(scan_n<<1)+1;
		delay(50);
		scan_port = 0xff;
	}
	return;
	
}

void delay(uchar delay_t)
{
	uchar c;
	while(delay_t--)
	{
		c=10;
		while(c--);
	}
}