//------------------------ Dogs102x6.h ----------------------------
//  ���ƣ�EADOGSͷ�ļ�
//-----------------------------------------------------------------
#ifndef HAL_DOGS102X6_H
#define HAL_DOGS102X6_H
#define i8  signed char
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
//��Ļ��С�����壨�ڵ���׵ף�
#define DOGS102x6_X_SIZE		102		//��Ļ��ȣ����أ�
#define DOGS102x6_Y_SIZE		64		//��Ļ�߶ȣ����أ�
#define DOGS102x6_DRAW_NORMAL	0x00	//������������ʾ������
#define DOGS102x6_DRAW_INVERT	0x01	//�ڰ���������ʾ������
extern u8 dogs102x6Memory[];			//ֱ�ӷ���֡����
extern void Dogs102x6_init();
extern void Dogs102x6_disable(void);
extern void Dogs102x6_writeCommand(u8* sCmd, u8 i);
extern void Dogs102x6_writeData(u8* sData, u8 i);
extern void Dogs102x6_setAddress(u8 pa, u8 ca);
extern void Dogs102x6_setInverseDisplay(void);
extern void Dogs102x6_clearInverseDisplay(void);
extern void Dogs102x6_scrollLine(u8 lines);
extern void Dogs102x6_setAllPixelsOn(void);
extern void Dogs102x6_clearAllPixelsOn(void);
extern void Dogs102x6_clearScreen(void);
extern void Dogs102x6_charDraw(u8 row, u8 col, u16 f, u8 style);
extern void Dogs102x6_charDrawXY(u8 x, u8 y, u16 f, u8 style);
extern void Dogs102x6_stringDraw(u8 row, u8 col, char *word, u8 style);
extern void Dogs102x6_stringDrawXY(u8 x, u8 y, char *word, u8 style);
extern void Dogs102x6_clearRow(u8 row);
extern void Dogs102x6_pixelDraw(u8 x, u8 y, u8 style);
extern void Dogs102x6_horizontalLineDraw(u8 x1, u8 x2, u8 y, u8 style);
extern void Dogs102x6_verticalLineDraw(u8 y1, u8 y2, u8 x, u8 style);
extern void Dogs102x6_lineDraw(u8 x1, u8 y1, u8 x2, u8 y2, u8 style);
extern void Dogs102x6_circleDraw(u8 x, u8 y, u8 radius, u8 style);
extern void Dogs102x6_imageDraw(const u8 IMAGE[], u8 row, u8 col);
extern void Dogs102x6_clearImage(u8 height, u8 width, u8 row, u8 col);
#endif