/**
  * @file   lcdDriverPort.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/04/18
  * @brief  lkdGuiҺ����ʾ�������ӿڣ�����ֲ����亯���ľ������ݡ�
  */

#include "lkdGui.h"
#include "oled.h"
/**
  *@brief ��Gui������������ʾ��lcd��
  *@param  None
  *@retval None
  */
void GuiUpdateDisplayAll(void)
{
  /* ����û����� */
	OLED_Refresh();
}

/**
  *@brief ��Guiָ��������������ʾ��lcd��
  *@param  beginx,beginy,endx,endy ����
  *@retval None
  */
void GuiRangeUpdateDisplay(lkdCoord beginx, lkdCoord beginy,lkdCoord endx, lkdCoord endy)
{
	/* ����û����� */
	
}

/**
  *@brief �򻺳�������
  *@param  x,y ����
  *@param  color ��ɫ <Ŀǰֻ�к�:CBLACK ��:CWHITLE>
  *@retval None
  */
void GuiDrawPoint(lkdCoord x, lkdCoord y, lkdColour color)
{
  /* ����û����� */
	if(color)
	OLED_DrawPoint(x,y);
	else
		OLED_ClearPoint(x,y);
}

/**
  *@brief ��ȡ��ǰ��ʾ�ĵ�
  *@param  x,y ����
  *@param  color ��ɫ <Ŀǰֻ�к�:CBLACK ��:CWHITLE>
  *@retval None
  */
void  GuiReadPoint(lkdCoord x, lkdCoord y, lkdColour *pColor)
{
	/* ����û����� */
}

/**
  *@brief ����ʾ
  *@param  None
  *@retval None
  */
void CloseLcdDisplay(void)
{
  /* ����û����� */
}

/**
  *@brief ����ʾ
  *@param  None
  *@retval None
  */
void OpenLcdDisplay(void)
{
  /* ����û����� */
}