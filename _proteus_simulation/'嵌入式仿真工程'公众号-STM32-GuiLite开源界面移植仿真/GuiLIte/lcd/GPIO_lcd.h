#ifndef      __GPIO_LCD_H
#define	     __GPIO_LCD_H


#include "stm32f4xx.h" 
//#include "fonts.h"
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define     GPIO_DATA_USE_ONEPORT  0
#define     GPIO_DATA_USE_ANYPORT  1

typedef enum
{ 
  GPIO_Set_Mode_IN = 1,
  GPIO_Set_Mode_OUT 
}GPIOMODESET_t;
typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;
/******************************* GPIO 显示屏8080通讯引脚定义 ***************************/
/******控制信号线******/
//片选
#define      GPIO_LCD_CS_CLK                RCC_AHB1Periph_GPIOB
#define      GPIO_LCD_CS_PORT               GPIOB
#define      GPIO_LCD_CS_PIN                GPIO_Pin_0

//DC引脚
#define      GPIO_LCD_DC_CLK                RCC_AHB1Periph_GPIOB   
#define      GPIO_LCD_DC_PORT               GPIOB
#define      GPIO_LCD_DC_PIN                GPIO_Pin_1
//写使能
#define      GPIO_LCD_WR_CLK                RCC_AHB1Periph_GPIOB   
#define      GPIO_LCD_WR_PORT               GPIOB
#define      GPIO_LCD_WR_PIN                GPIO_Pin_2

//读使能
#define      GPIO_LCD_RD_CLK                RCC_AHB1Periph_GPIOB   
#define      GPIO_LCD_RD_PORT               GPIOB
#define      GPIO_LCD_RD_PIN                GPIO_Pin_3

//复位引脚直接使用NRST，开发板复位的时候会使液晶复位


//背光引脚
#define      GPIO_LCD_RS_CLK                RCC_AHB1Periph_GPIOB    
#define      GPIO_LCD_RS_PORT               GPIOB
#define      GPIO_LCD_RS_PIN                GPIO_Pin_5

/********信号线控制相关的宏***************/
#define	GPIO_LCD_CS_SET  	GPIO_SetBits(GPIO_LCD_CS_PORT,GPIO_LCD_CS_PIN)//;GPIO_LCD_CS_PORT->BSRR=GPIO_LCD_CS_PIN;    //片选端口  		
#define	GPIO_LCD_DC_SET		GPIO_SetBits(GPIO_LCD_DC_PORT,GPIO_LCD_DC_PIN)//GPIO_LCD_DC_PORT->BSRR=GPIO_LCD_DC_PIN;    //数据/命令 	  
#define	GPIO_LCD_WR_SET		GPIO_SetBits(GPIO_LCD_WR_PORT,GPIO_LCD_WR_PIN)//GPIO_LCD_WR_PORT->BSRR=GPIO_LCD_WR_PIN;    //写数据			
#define	GPIO_LCD_RD_SET		GPIO_SetBits(GPIO_LCD_RD_PORT,GPIO_LCD_RD_PIN)//GPIO_LCD_RD_PORT->BSRR=GPIO_LCD_RD_PIN;    //读数据			
								    
#define	GPIO_LCD_CS_CLR  	GPIO_ResetBits(GPIO_LCD_CS_PORT,GPIO_LCD_CS_PIN)//GPIO_LCD_CS_PORT->BRR=GPIO_LCD_CS_PIN;     //片选端口  		
#define	GPIO_LCD_DC_CLR		GPIO_ResetBits(GPIO_LCD_DC_PORT,GPIO_LCD_DC_PIN)//GPIO_LCD_DC_PORT->BRR=GPIO_LCD_DC_PIN;    //数据/命令		     
#define	GPIO_LCD_WR_CLR		GPIO_ResetBits(GPIO_LCD_WR_PORT,GPIO_LCD_WR_PIN)//GPIO_LCD_WR_PORT->BRR=GPIO_LCD_WR_PIN;     //写数据			
#define	GPIO_LCD_RD_CLR		GPIO_ResetBits(GPIO_LCD_RD_PORT,GPIO_LCD_RD_PIN)//GPIO_LCD_RD_PORT->BRR=GPIO_LCD_RD_PIN;     //读数据	

//使用同一个IO端口作为数据口
#if GPIO_DATA_USE_ONEPORT == 1

///********数据信号线***************/
#define      GPIO_DATA_CLK                RCC_APB2Periph_GPIOG   
#define      GPIO_DATA_PORT               GPIOG
#define      GPIO_DATA_PIN                GPIO_Pin_All
	
//数据线输入输出
#define DATAOUT(x) 		GPIO_DATA_PORT->ODR=x; //数据输出
#define DATAIN()     	GPIO_DATA_PORT->IDR;   //数据输入	


//使用任意IO端口作为数据口
#elif 		GPIO_DATA_USE_ANYPORT == 1




/******数据线******/
//D0
#define      GPIO_LCD_D0_CLK                RCC_AHB1Periph_GPIOA  
#define      GPIO_LCD_D0_PORT               GPIOA
#define      GPIO_LCD_D0_PIN                GPIO_Pin_0

//D1
#define      GPIO_LCD_D1_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D1_PORT               GPIOA
#define      GPIO_LCD_D1_PIN                GPIO_Pin_1

//D2
#define      GPIO_LCD_D2_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D2_PORT               GPIOA
#define      GPIO_LCD_D2_PIN                GPIO_Pin_2

//D3
#define      GPIO_LCD_D3_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D3_PORT               GPIOA
#define      GPIO_LCD_D3_PIN                GPIO_Pin_3

//D4
#define      GPIO_LCD_D4_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D4_PORT               GPIOA
#define      GPIO_LCD_D4_PIN                GPIO_Pin_4

//D5
#define      GPIO_LCD_D5_CLK                RCC_AHB1Periph_GPIOA  
#define      GPIO_LCD_D5_PORT               GPIOA
#define      GPIO_LCD_D5_PIN                GPIO_Pin_5

//D6
#define      GPIO_LCD_D6_CLK                RCC_AHB1Periph_GPIOA  
#define      GPIO_LCD_D6_PORT               GPIOA
#define      GPIO_LCD_D6_PIN                GPIO_Pin_6

//D7
#define      GPIO_LCD_D7_CLK                RCC_AHB1Periph_GPIOA  
#define      GPIO_LCD_D7_PORT               GPIOA
#define      GPIO_LCD_D7_PIN                GPIO_Pin_7

//D8
#define      GPIO_LCD_D8_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D8_PORT               GPIOA
#define      GPIO_LCD_D8_PIN                GPIO_Pin_8

//D9
#define      GPIO_LCD_D9_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D9_PORT               GPIOA
#define      GPIO_LCD_D9_PIN                GPIO_Pin_9

//D10
#define      GPIO_LCD_D10_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D10_PORT               GPIOA
#define      GPIO_LCD_D10_PIN                GPIO_Pin_10

//D11
#define      GPIO_LCD_D11_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D11_PORT               GPIOA
#define      GPIO_LCD_D11_PIN                GPIO_Pin_11

//D12
#define      GPIO_LCD_D12_CLK                RCC_AHB1Periph_GPIOA  
#define      GPIO_LCD_D12_PORT               GPIOA
#define      GPIO_LCD_D12_PIN                GPIO_Pin_12

//D13
#define      GPIO_LCD_D13_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D13_PORT               GPIOA
#define      GPIO_LCD_D13_PIN                GPIO_Pin_13

//D14
#define      GPIO_LCD_D14_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D14_PORT               GPIOA
#define      GPIO_LCD_D14_PIN                GPIO_Pin_14

//D15
#define      GPIO_LCD_D15_CLK                RCC_AHB1Periph_GPIOA   
#define      GPIO_LCD_D15_PORT               GPIOA
#define      GPIO_LCD_D15_PIN                GPIO_Pin_15

/********信号线控制相关的宏***************/
//#define	GPIO_LCD_CS_SET  	GPIO_CS_PORT->BSRR=GPIO_CS_PIN    //片选端口  		
//#define	GPIO_LCD_DC_SET		GPIO_DC_PORT->BSRR=GPIO_DC_PIN    //数据/命令 	  
//#define	GPIO_LCD_WR_SET		GPIO_WR_PORT->BSRR=GPIO_WR_PIN    //写数据			
//#define	GPIO_LCD_RD_SET		GPIO_RD_PORT->BSRR=GPIO_RD_PIN    //读数据			
//								    
//#define	GPIO_LCD_CS_CLR  	GPIO_CS_PORT->BRR=GPIO_CS_PIN     //片选端口  		
//#define	GPIO_LCD_DC_CLR		GPIO_DC_PORT->BRR=GPIO_DC_PIN     //数据/命令		     
//#define	GPIO_LCD_WR_CLR		GPIO_WR_PORT->BRR=GPIO_WR_PIN     //写数据			
//#define	GPIO_LCD_RD_CLR		GPIO_RD_PORT->BRR=GPIO_RD_PIN     //读数据	


/********数据线控制相关的宏***************/
/*#define GPIO_LCD_D0_WRITE    GPIO_LCD_D0_PORT->ODR    //D0端口
#define GPIO_LCD_D0_READ     GPIO_LCD_D0_PORT->IDR     //D0端口

#define GPIO_LCD_D1_WRITE    GPIO_LCD_D1_PORT->ODR    //D1端口
#define GPIO_LCD_D1_READ     GPIO_LCD_D1_PORT->IDR     //D1端口

#define GPIO_LCD_D2_WRITE    GPIO_LCD_D2_PORT->ODR    //D2端口
#define GPIO_LCD_D2_READ     GPIO_LCD_D2_PORT->IDR     //D2端口

#define GPIO_LCD_D3_WRITE    GPIO_LCD_D3_PORT->ODR    //D3端口
#define GPIO_LCD_D3_READ     GPIO_LCD_D3_PORT->IDR     //D3端口

#define GPIO_LCD_D4_WRITE    GPIO_LCD_D4_PORT->ODR    //D4端口
#define GPIO_LCD_D4_READ     GPIO_LCD_D4_PORT->IDR    //D4端口

#define GPIO_LCD_D5_WRITE    GPIO_LCD_D5_PORT->ODR    //D5端口
#define GPIO_LCD_D5_READ     GPIO_LCD_D5_PORT->IDR     //D5端口

#define GPIO_LCD_D6_WRITE    GPIO_LCD_D6_PORT->ODR    //D6端口
#define GPIO_LCD_D6_READ     GPIO_LCD_D6_PORT->IDR     //D6端口

#define GPIO_LCD_D7_WRITE    GPIO_LCD_D7_PORT->ODR    //D7端口
#define GPIO_LCD_D7_READ     GPIO_LCD_D7_PORT->IDR     //D7端口

#define GPIO_LCD_D8_WRITE    GPIO_LCD_D8_PORT->ODR    //D8端口
#define GPIO_LCD_D8_READ     GPIO_LCD_D8_PORT->IDR     //D8端口

#define GPIO_LCD_D9_WRITE    GPIO_LCD_D9_PORT->ODR    //D9端口
#define GPIO_LCD_D9_READ     GPIO_LCD_D9_PORT->IDR     //D9端口

#define GPIO_LCD_D10_WRITE    GPIO_D10_PORT->ODR    //D10端口
#define GPIO_LCD_D10_READ     GPIO_LCD_D10_PORT->IDR     //D10端口

#define GPIO_LCD_D11_WRITE    GPIO_LCD_D11_PORT->ODR    //D11端口
#define GPIO_LCD_D11_READ     GPIO_LCD_D11_PORT->IDR     //D11端口

#define GPIO_LCD_D12_WRITE    GPIO_LCD_D12_PORT->ODR    //D12端口
#define GPIO_LCD_D12_READ     GPIO_LCD_D12_PORT->IDR     //D12端口

#define GPIO_LCD_D13_WRITE    GPIO_LCD_D13_PORT->ODR    //D13端口
#define GPIO_LCD_D13_READ     GPIO_LCD_D13_PORT->IDR     //D13端口

#define GPIO_LCD_D14_WRITE    GPIO_LCD_D14_PORT->ODR    //D14端口
#define GPIO_LCD_D14_READ     GPIO_LCD_D14_PORT->IDR     //D14端口

#define GPIO_LCD_D15_WRITE    GPIO_LCD_D15_PORT->ODR    //D15端口
#define GPIO_LCD_D15_READ     GPIO_LCD_D15_PORT->IDR     //D15端口



#define D0_W  PDout(0)
#define D0_R  PDin(0)

#define D1_W  PDout(1)
#define D1_R  PDin(1)

#define D2_W  PDout(2)
#define D2_R  PDin(2)

#define D3_W  PDout(3)
#define D3_R  PDin(3)

#define D4_W  PDout(4)
#define D4_R  PDin(4)

#define D5_W  PDout(5)
#define D5_R  PDin(5)

#define D6_W  PDout(6)
#define D6_R  PDin(6)

#define D7_W  PDout(7)
#define D7_R  PDin(7)

#define D8_W  PDout(8)
#define D8_R  PDin(8)

#define D9_W  PDout(9)
#define D9_R  PDin(9)

#define D10_W  PDout(10)
#define D10_R  PDin(10)

#define D11_W  PDout(11)
#define D11_R  PDin(11)

#define D12_W  PDout(12)
#define D12_R  PDin(12)


#define D13_W  PDout(13)
#define D13_R  PDin(13)

#define D14_W  PDout(14)
#define D14_R  PDin(14)

#define D15_W  PDout(15)
#define D15_R  PDin(15)*/

#endif

/*************************************** 调试预用 ******************************************/
#define      DEBUG_DELAY()       //GPIO_Delay(0xFFFF)         

/***************************** ILI934 显示区域的起始坐标和总行列数 ***************************/
#define      GPIO_DispWindow_X_Star		    0     //起始点的X坐标
#define      GPIO_DispWindow_Y_Star		    0     //起始点的Y坐标

#define 			GPIO_LESS_PIXEL	  							320 //240			//液晶屏较短方向的像素宽度
#define 			GPIO_MORE_PIXEL	 								240 //320			//液晶屏较长方向的像素宽度

//根据液晶扫描方向而变化的XY像素宽度
//调用GPIO_GramScan函数设置方向时会自动更改
extern uint16_t LCD_X_LENGTH,LCD_Y_LENGTH; 

//液晶屏扫描模式
//参数可选值为0-7
extern uint8_t LCD_SCAN_MODE;

/******************************* 定义 ILI934 显示屏常用颜色 ********************************/


#define      WHITE		 		                 0xFFFF	   //白色
#define      BLACK                         0x0000	   //黑色 
#define      GREY                          0xF7DE	   //灰色 
#define      BLUE                          0x001F	   //蓝色 
#define      BLUE2                         0x051F	   //浅蓝色 
#define      RED                           0xF800	   //红色 
#define      MAGENTA                       0xF81F	   //红紫色，洋红色 
#define      GREEN                         0x07E0	   //绿色 
#define      CYAN                          0x7FFF	   //蓝绿色，青色 
#define      YELLOW                        0xFFE0	   //黄色 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF
#define      BACKGROUND		                BLUE2   //默认背景颜色
/*#define ILI9341_BLACK   0x0000
#define ILI9341_BLUE    0x001F
#define ILI9341_RED     0xF800
#define ILI9341_GREEN   0x07E0
#define ILI9341_CYAN    0x07FF
#define ILI9341_MAGENTA 0xF81F
#define ILI9341_YELLOW  0xFFE0
#define ILI9341_WHITE   0xFFFF*/

/******************************* 定义 ILI934 常用命令 ********************************/
#define      CMD_SetCoordinateX		 		    0x2A	     //设置X坐标
#define      CMD_SetCoordinateY		 		    0x2B	     //设置Y坐标
#define      CMD_SetPixel		 		          0x2C	     //填充像素




/********************************** 声明 ILI934 函数 ***************************************/
void                     GPIO_LCD_Init                    ( void );
void                     GPIO_Rst                     ( void );
void                     GPIO_BackLed_Control         ( FunctionalState enumState );
void                     GPIO_GramScan                ( uint8_t ucOtion );
void                     GPIO_OpenWindow              ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight );
void                     GPIO_Clear                   ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight );
void                     GPIO_SetPointPixel           ( uint16_t usX, uint16_t usY,uint16_t color );
uint16_t                 GPIO_GetPointPixel           ( uint16_t usX , uint16_t usY );
void                     GPIO_DrawLine                ( uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2,uint16_t color );
void                     GPIO_DrawRectangle           ( uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight,uint16_t ucFilled );
void                     GPIO_DrawCircle              ( uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled );
void                     GPIO_DispChar_EN             ( uint16_t usX, uint16_t usY, const char cChar );
void                     GPIO_DispStringLine_EN       ( uint16_t line, char * pStr );
void                     GPIO_DispString_EN      		 ( uint16_t usX, uint16_t usY, char * pStr );
void 										 GPIO_DispString_EN_YDir 		 ( uint16_t usX,uint16_t usY ,  char * pStr );

void                     GPIO_DispChar_CH             ( uint16_t usX, uint16_t usY, uint16_t usChar );
void                     GPIO_DispString_CH           ( uint16_t usX, uint16_t usY,  char * pStr );
void                     GPIO_DispString_EN_CH        ( uint16_t usX, uint16_t usY,  char * pStr );
void 										 GPIO_DispStringLine_EN_CH 	 ( uint16_t line, char * pStr );
void 										 GPIO_DispString_EN_CH_YDir   ( uint16_t usX,uint16_t usY , char * pStr );
 void          GPIO_FillColor           ( uint32_t ulAmout_Point, uint16_t usColor );
 uint16_t               GPIO_Read_PixelData      ( void );


void 											LCD_SetFont											(sFONT *fonts);
sFONT 										*LCD_GetFont										(void);
void 											LCD_ClearLine										(uint16_t Line);
void 											LCD_SetBackColor								(uint16_t Color);
void 											LCD_SetTextColor								(uint16_t Color)	;
void 											LCD_SetColors										(uint16_t TextColor, uint16_t BackColor);
void 											LCD_GetColors										(uint16_t *TextColor, uint16_t *BackColor);
uint16_t 								  GPIO_Read_ID									(void);
void GPIO_FillScreen(uint16_t color);
unsigned short DATAIN(void);
void DATAOUT(unsigned short x);
void drawline(uint16_t a,uint16_t b,uint16_t c,uint16_t d);

void GPIO_DisplayStringEx(uint16_t x, 							//字符显示位置x
														 uint16_t y, 							//字符显示位置y
														 uint16_t Font_width,			//要显示的字体宽度，英文字符在此基础上/2。注意为偶数
														 uint16_t Font_Height,		//要显示的字体高度，注意为偶数
														 uint8_t *ptr,						//显示的字符内容
														 uint16_t DrawModel);  		//是否反色显示

void GPIO_DisplayStringEx_YDir(uint16_t x, 					//字符显示位置x
																	uint16_t y, 					//字符显示位置y
																	uint16_t Font_width,	//要显示的字体宽度，英文字符在此基础上/2。注意为偶数
																	uint16_t Font_Height,	//要显示的字体高度，注意为偶数
																	uint8_t *ptr,					//显示的字符内容
																	uint16_t DrawModel);  //是否反色显示
#endif /* __BSP_GPIO_GPIO_H */


