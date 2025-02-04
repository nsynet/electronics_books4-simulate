#ifndef      __GPIO_LCD_H
#define	     __GPIO_LCD_H


#include "stm32f4xx.h" 
//#include "fonts.h"
//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
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
/******************************* GPIO ��ʾ��8080ͨѶ���Ŷ��� ***************************/
/******�����ź���******/
//Ƭѡ
#define      GPIO_LCD_CS_CLK                RCC_AHB1Periph_GPIOB
#define      GPIO_LCD_CS_PORT               GPIOB
#define      GPIO_LCD_CS_PIN                GPIO_Pin_0

//DC����
#define      GPIO_LCD_DC_CLK                RCC_AHB1Periph_GPIOB   
#define      GPIO_LCD_DC_PORT               GPIOB
#define      GPIO_LCD_DC_PIN                GPIO_Pin_1
//дʹ��
#define      GPIO_LCD_WR_CLK                RCC_AHB1Periph_GPIOB   
#define      GPIO_LCD_WR_PORT               GPIOB
#define      GPIO_LCD_WR_PIN                GPIO_Pin_2

//��ʹ��
#define      GPIO_LCD_RD_CLK                RCC_AHB1Periph_GPIOB   
#define      GPIO_LCD_RD_PORT               GPIOB
#define      GPIO_LCD_RD_PIN                GPIO_Pin_3

//��λ����ֱ��ʹ��NRST�������帴λ��ʱ���ʹҺ����λ


//��������
#define      GPIO_LCD_RS_CLK                RCC_AHB1Periph_GPIOB    
#define      GPIO_LCD_RS_PORT               GPIOB
#define      GPIO_LCD_RS_PIN                GPIO_Pin_5

/********�ź��߿�����صĺ�***************/
#define	GPIO_LCD_CS_SET  	GPIO_SetBits(GPIO_LCD_CS_PORT,GPIO_LCD_CS_PIN)//;GPIO_LCD_CS_PORT->BSRR=GPIO_LCD_CS_PIN;    //Ƭѡ�˿�  		
#define	GPIO_LCD_DC_SET		GPIO_SetBits(GPIO_LCD_DC_PORT,GPIO_LCD_DC_PIN)//GPIO_LCD_DC_PORT->BSRR=GPIO_LCD_DC_PIN;    //����/���� 	  
#define	GPIO_LCD_WR_SET		GPIO_SetBits(GPIO_LCD_WR_PORT,GPIO_LCD_WR_PIN)//GPIO_LCD_WR_PORT->BSRR=GPIO_LCD_WR_PIN;    //д����			
#define	GPIO_LCD_RD_SET		GPIO_SetBits(GPIO_LCD_RD_PORT,GPIO_LCD_RD_PIN)//GPIO_LCD_RD_PORT->BSRR=GPIO_LCD_RD_PIN;    //������			
								    
#define	GPIO_LCD_CS_CLR  	GPIO_ResetBits(GPIO_LCD_CS_PORT,GPIO_LCD_CS_PIN)//GPIO_LCD_CS_PORT->BRR=GPIO_LCD_CS_PIN;     //Ƭѡ�˿�  		
#define	GPIO_LCD_DC_CLR		GPIO_ResetBits(GPIO_LCD_DC_PORT,GPIO_LCD_DC_PIN)//GPIO_LCD_DC_PORT->BRR=GPIO_LCD_DC_PIN;    //����/����		     
#define	GPIO_LCD_WR_CLR		GPIO_ResetBits(GPIO_LCD_WR_PORT,GPIO_LCD_WR_PIN)//GPIO_LCD_WR_PORT->BRR=GPIO_LCD_WR_PIN;     //д����			
#define	GPIO_LCD_RD_CLR		GPIO_ResetBits(GPIO_LCD_RD_PORT,GPIO_LCD_RD_PIN)//GPIO_LCD_RD_PORT->BRR=GPIO_LCD_RD_PIN;     //������	

//ʹ��ͬһ��IO�˿���Ϊ���ݿ�
#if GPIO_DATA_USE_ONEPORT == 1

///********�����ź���***************/
#define      GPIO_DATA_CLK                RCC_APB2Periph_GPIOG   
#define      GPIO_DATA_PORT               GPIOG
#define      GPIO_DATA_PIN                GPIO_Pin_All
	
//�������������
#define DATAOUT(x) 		GPIO_DATA_PORT->ODR=x; //�������
#define DATAIN()     	GPIO_DATA_PORT->IDR;   //��������	


//ʹ������IO�˿���Ϊ���ݿ�
#elif 		GPIO_DATA_USE_ANYPORT == 1




/******������******/
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

/********�ź��߿�����صĺ�***************/
//#define	GPIO_LCD_CS_SET  	GPIO_CS_PORT->BSRR=GPIO_CS_PIN    //Ƭѡ�˿�  		
//#define	GPIO_LCD_DC_SET		GPIO_DC_PORT->BSRR=GPIO_DC_PIN    //����/���� 	  
//#define	GPIO_LCD_WR_SET		GPIO_WR_PORT->BSRR=GPIO_WR_PIN    //д����			
//#define	GPIO_LCD_RD_SET		GPIO_RD_PORT->BSRR=GPIO_RD_PIN    //������			
//								    
//#define	GPIO_LCD_CS_CLR  	GPIO_CS_PORT->BRR=GPIO_CS_PIN     //Ƭѡ�˿�  		
//#define	GPIO_LCD_DC_CLR		GPIO_DC_PORT->BRR=GPIO_DC_PIN     //����/����		     
//#define	GPIO_LCD_WR_CLR		GPIO_WR_PORT->BRR=GPIO_WR_PIN     //д����			
//#define	GPIO_LCD_RD_CLR		GPIO_RD_PORT->BRR=GPIO_RD_PIN     //������	


/********�����߿�����صĺ�***************/
/*#define GPIO_LCD_D0_WRITE    GPIO_LCD_D0_PORT->ODR    //D0�˿�
#define GPIO_LCD_D0_READ     GPIO_LCD_D0_PORT->IDR     //D0�˿�

#define GPIO_LCD_D1_WRITE    GPIO_LCD_D1_PORT->ODR    //D1�˿�
#define GPIO_LCD_D1_READ     GPIO_LCD_D1_PORT->IDR     //D1�˿�

#define GPIO_LCD_D2_WRITE    GPIO_LCD_D2_PORT->ODR    //D2�˿�
#define GPIO_LCD_D2_READ     GPIO_LCD_D2_PORT->IDR     //D2�˿�

#define GPIO_LCD_D3_WRITE    GPIO_LCD_D3_PORT->ODR    //D3�˿�
#define GPIO_LCD_D3_READ     GPIO_LCD_D3_PORT->IDR     //D3�˿�

#define GPIO_LCD_D4_WRITE    GPIO_LCD_D4_PORT->ODR    //D4�˿�
#define GPIO_LCD_D4_READ     GPIO_LCD_D4_PORT->IDR    //D4�˿�

#define GPIO_LCD_D5_WRITE    GPIO_LCD_D5_PORT->ODR    //D5�˿�
#define GPIO_LCD_D5_READ     GPIO_LCD_D5_PORT->IDR     //D5�˿�

#define GPIO_LCD_D6_WRITE    GPIO_LCD_D6_PORT->ODR    //D6�˿�
#define GPIO_LCD_D6_READ     GPIO_LCD_D6_PORT->IDR     //D6�˿�

#define GPIO_LCD_D7_WRITE    GPIO_LCD_D7_PORT->ODR    //D7�˿�
#define GPIO_LCD_D7_READ     GPIO_LCD_D7_PORT->IDR     //D7�˿�

#define GPIO_LCD_D8_WRITE    GPIO_LCD_D8_PORT->ODR    //D8�˿�
#define GPIO_LCD_D8_READ     GPIO_LCD_D8_PORT->IDR     //D8�˿�

#define GPIO_LCD_D9_WRITE    GPIO_LCD_D9_PORT->ODR    //D9�˿�
#define GPIO_LCD_D9_READ     GPIO_LCD_D9_PORT->IDR     //D9�˿�

#define GPIO_LCD_D10_WRITE    GPIO_D10_PORT->ODR    //D10�˿�
#define GPIO_LCD_D10_READ     GPIO_LCD_D10_PORT->IDR     //D10�˿�

#define GPIO_LCD_D11_WRITE    GPIO_LCD_D11_PORT->ODR    //D11�˿�
#define GPIO_LCD_D11_READ     GPIO_LCD_D11_PORT->IDR     //D11�˿�

#define GPIO_LCD_D12_WRITE    GPIO_LCD_D12_PORT->ODR    //D12�˿�
#define GPIO_LCD_D12_READ     GPIO_LCD_D12_PORT->IDR     //D12�˿�

#define GPIO_LCD_D13_WRITE    GPIO_LCD_D13_PORT->ODR    //D13�˿�
#define GPIO_LCD_D13_READ     GPIO_LCD_D13_PORT->IDR     //D13�˿�

#define GPIO_LCD_D14_WRITE    GPIO_LCD_D14_PORT->ODR    //D14�˿�
#define GPIO_LCD_D14_READ     GPIO_LCD_D14_PORT->IDR     //D14�˿�

#define GPIO_LCD_D15_WRITE    GPIO_LCD_D15_PORT->ODR    //D15�˿�
#define GPIO_LCD_D15_READ     GPIO_LCD_D15_PORT->IDR     //D15�˿�



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

/*************************************** ����Ԥ�� ******************************************/
#define      DEBUG_DELAY()       //GPIO_Delay(0xFFFF)         

/***************************** ILI934 ��ʾ�������ʼ������������� ***************************/
#define      GPIO_DispWindow_X_Star		    0     //��ʼ���X����
#define      GPIO_DispWindow_Y_Star		    0     //��ʼ���Y����

#define 			GPIO_LESS_PIXEL	  							320 //240			//Һ�����϶̷�������ؿ��
#define 			GPIO_MORE_PIXEL	 								240 //320			//Һ�����ϳ���������ؿ��

//����Һ��ɨ�跽����仯��XY���ؿ��
//����GPIO_GramScan�������÷���ʱ���Զ�����
extern uint16_t LCD_X_LENGTH,LCD_Y_LENGTH; 

//Һ����ɨ��ģʽ
//������ѡֵΪ0-7
extern uint8_t LCD_SCAN_MODE;

/******************************* ���� ILI934 ��ʾ��������ɫ ********************************/


#define      WHITE		 		                 0xFFFF	   //��ɫ
#define      BLACK                         0x0000	   //��ɫ 
#define      GREY                          0xF7DE	   //��ɫ 
#define      BLUE                          0x001F	   //��ɫ 
#define      BLUE2                         0x051F	   //ǳ��ɫ 
#define      RED                           0xF800	   //��ɫ 
#define      MAGENTA                       0xF81F	   //����ɫ�����ɫ 
#define      GREEN                         0x07E0	   //��ɫ 
#define      CYAN                          0x7FFF	   //����ɫ����ɫ 
#define      YELLOW                        0xFFE0	   //��ɫ 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF
#define      BACKGROUND		                BLUE2   //Ĭ�ϱ�����ɫ
/*#define ILI9341_BLACK   0x0000
#define ILI9341_BLUE    0x001F
#define ILI9341_RED     0xF800
#define ILI9341_GREEN   0x07E0
#define ILI9341_CYAN    0x07FF
#define ILI9341_MAGENTA 0xF81F
#define ILI9341_YELLOW  0xFFE0
#define ILI9341_WHITE   0xFFFF*/

/******************************* ���� ILI934 �������� ********************************/
#define      CMD_SetCoordinateX		 		    0x2A	     //����X����
#define      CMD_SetCoordinateY		 		    0x2B	     //����Y����
#define      CMD_SetPixel		 		          0x2C	     //�������




/********************************** ���� ILI934 ���� ***************************************/
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

void GPIO_DisplayStringEx(uint16_t x, 							//�ַ���ʾλ��x
														 uint16_t y, 							//�ַ���ʾλ��y
														 uint16_t Font_width,			//Ҫ��ʾ�������ȣ�Ӣ���ַ��ڴ˻�����/2��ע��Ϊż��
														 uint16_t Font_Height,		//Ҫ��ʾ������߶ȣ�ע��Ϊż��
														 uint8_t *ptr,						//��ʾ���ַ�����
														 uint16_t DrawModel);  		//�Ƿ�ɫ��ʾ

void GPIO_DisplayStringEx_YDir(uint16_t x, 					//�ַ���ʾλ��x
																	uint16_t y, 					//�ַ���ʾλ��y
																	uint16_t Font_width,	//Ҫ��ʾ�������ȣ�Ӣ���ַ��ڴ˻�����/2��ע��Ϊż��
																	uint16_t Font_Height,	//Ҫ��ʾ������߶ȣ�ע��Ϊż��
																	uint8_t *ptr,					//��ʾ���ַ�����
																	uint16_t DrawModel);  //�Ƿ�ɫ��ʾ
#endif /* __BSP_GPIO_GPIO_H */


