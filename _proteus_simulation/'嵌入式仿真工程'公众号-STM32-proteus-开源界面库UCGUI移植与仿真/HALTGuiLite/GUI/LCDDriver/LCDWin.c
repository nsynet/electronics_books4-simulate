/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDWin.C
Purpose     : Driver for Simulator under Windows
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.00a   031007 JE     a) LCD_L0_Init changed, filling not needed at
                         this point
2.00a   030613 JE     a) Parameter of SETPIXEL checked in debug version
                      b) _DrawBitLine2bpp and _DrawBitLine4bpp reworked
2.00    010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
1.30c   000529 JE     a) Interface changed
1.30b   000428 RS     a) DIB class eliminated
                      b) Internal cleanups, support for high color
1.30a   000417 RS     a) Major cleanup in DIB class
1.30    000309 RS     a) Interface change for emWIn V1.30
                         (LCD_L0_SetLUTEntry, LCD_GetDevCap)
1.10a   000121 RS     a) RECTHEIGHT, RECTWIDTH modified in order to
                         fix bug which would at some time prevent
												 displaying the first line of the display.
1.10.00 000110 RS     a) Modifications in order to make it easy to
                         implement driver in any windows program
1.04.02 991118 RS     a) additional assertion added
                         LCD_MAX_LOG_COLORS
1.04.01 991018 RS     a) Support for LCD_FIXEDPALETTE added
                         with Anitaliasing enabled
1.04.00 991013 JE/RS  a) Support for LCD_FIXEDPALETTE added
                      b) Driver now accepts the same LCDConf.h as
											   the embedded system
											c) Bugfix for ..
1.02.02 990831 RS     a) Small optimization added for 16-color bitmaps
1.02.01 990726 RS     a) Transparency support for 16-color bitmpas
                         added
1.02.00 990212 RS     a) New interface version 1.02 supported
1.00    990118 RS     First release
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
---------------------------END-OF-HEADER------------------------------
*/

//#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

//#include <windows.h>
#include "LCD.h"
#include "ili9341.h"
#include "LCD_Private.h"              /* include LCDConf.h */
#include "LCDSIM.h"
#include "GUI_Private.h"
#include <stddef.h>           /* needed for definition of NULL */
//#include "memory.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#if LCD_BITSPERPIXEL <= 8
  #define PIXELINDEX U8
#else
  #define PIXELINDEX WORD
#endif

#ifdef WIN32
  #ifndef ASSERT
    #define ASSERT(Val) \
    if (!(Val)) \
      MessageBox(NULL,"...in file "__FILE__,"Assertion failed...",MB_OK);
  #endif
#endif

#ifdef LCD_ASSERT
  #undef LCD_ASSERT
#endif
#define LCD_ASSERT(v) ASSERT(v)

#ifndef LCD_DISPLAY_INDEX
  #define LCD_DISPLAY_INDEX 0
#endif

/*********************************************************************
*
*       Macros for internal use
*/
#ifdef _DEBUG
static int _CheckBound(unsigned int c) {
  unsigned int NumColors = LCD_BITSPERPIXEL > 8 ? (LCD_BITSPERPIXEL > 16) ? 0xffffffff : 0xffff : (1 << LCD_BITSPERPIXEL) - 1;
  if (c > NumColors) {
    GUI_DEBUG_ERROROUT("LCDWin::SETPIXEL: parameters out of bounds");
    return 1;
  }
  return 0;
}

  #define SETPIXEL(x, y, c) \
    if (!_CheckBound(c)) { \
			ILI9341_DrawPixel(x, y, c);   \
    }
#else
	#define SETPIXEL(x, y, c) ILI9341_DrawPixel(x, y, c)
#endif
#define XORPIXEL(x, y)    _XorPixel(x,y)

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _XorPixel
*/
static void _XorPixel(int x, int y) {
  unsigned int Index = LCD_L0_GetPixelIndex(x,y);
	ILI9341_DrawPixel(x, y, LCD_NUM_COLORS-1-Index);
}

/*********************************************************************
*
*       _DrawBitLine1BPP
*/
static void _DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0, Index1;
  #if (GUI_USE_MEMDEV_1BPP_FOR_SCREEN == 1)
    const LCD_PIXELINDEX aTrans[2] = {0, 1};
    if (!pTrans) {
      pTrans = aTrans;
    }
  #endif
  Index0 = *(pTrans + 0);
  Index1 = *(pTrans + 1);
  x+=Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
			ILI9341_DrawPixel(x++,y, (*p & (0x80>>Diff)) ? Index1 : Index0);
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
  		if (*p & (0x80>>Diff))
			  ILI9341_DrawPixel(x,y, Index1);
      x++;
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    do {
  		if (*p & (0x80>>Diff)) {
        int Pixel = GetPixel(x,y, LCD_DISPLAY_INDEX);
				ILI9341_DrawPixel(x,y, LCD_NUM_COLORS-1-Pixel);
      }
      x++;
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
	}
}

/*********************************************************************
*
*       _DrawBitLine2BPP
*/
#if (LCD_MAX_LOG_COLORS > 2)
static void _DrawBitLine2BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          SETPIXEL(x++, y, PixelIndex);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          SETPIXEL(x++, y, Index);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            SETPIXEL(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            SETPIXEL(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       _DrawBitLine4BPP
*/
#if (LCD_MAX_LOG_COLORS > 4)
static void _DrawBitLine4BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          SETPIXEL(x++, y, PixelIndex);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          SETPIXEL(x++, y, Index);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            SETPIXEL(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            SETPIXEL(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       _DrawBitLine8BPP
*/
#if (LCD_MAX_LOG_COLORS > 16)
static void _DrawBitLine8BPP(int x, int y, U8 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
    if (pTrans) {
      for (;xsize > 0; xsize--,x++,p++) {
        pixel = *p;
        SETPIXEL(x, y, *(pTrans+pixel));
      }
    } else {
      for (;xsize > 0; xsize--,x++,p++) {
        SETPIXEL(x, y, *p);
      }
    }
  } else {   /* Handle transparent bitmap */
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SETPIXEL(x+0, y, *(pTrans+pixel));
        }
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SETPIXEL(x+0, y, pixel);
        }
      }
    }
  }
}
#endif

/*********************************************************************
*
*       _DrawBitLine16BPP
*/
#if (LCD_BITSPERPIXEL > 8)
static void _DrawBitLine16BPP(int x, int y, U16 const * p, int xsize) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    for (;xsize > 0; xsize--,x++,p++) {
      SETPIXEL(x, y, *p);
    }
  } else {   /* Handle transparent bitmap */
    for (; xsize > 0; xsize--, x++, p++) {
      pixel = *p;
      if (pixel) {
        SETPIXEL(x + 0, y, pixel);
      }
    }
  }
}
#endif

/*********************************************************************
*
*       _DrawBitLine24BPP
*/
#if (LCD_BITSPERPIXEL > 16)
static void _DrawBitLine24BPP(int x, int y, U32 const * p, int xsize) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    for (;xsize > 0; xsize--, x++, p++) {
      SETPIXEL(x, y, *p);
    }
  } else {   /* Handle transparent bitmap */
    for (; xsize > 0; xsize--, x++, p++) {
      pixel = *p;
      if (pixel) {
        SETPIXEL(x+0, y, pixel);
      }
    }
  }
}
#endif

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/

/*********************************************************************
*
*       LCD_L0_DrawPixel
*
*  Purpose:  Writes 1 pixel into the display.
*/
void LCD_L0_DrawPixel(int x, int y) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    XORPIXEL(x, y);
  } else {
    SETPIXEL(x, y, LCD_COLORINDEX);
  }
}

/*********************************************************************
*
*       LCD_L0_DrawHLine  绘制水平线函数
*/
void LCD_L0_DrawHLine(int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (;x0 <= x1; x0++) {
      XORPIXEL(x0, y);
    }
  } else {
    for (;x0 <= x1; x0++) {
      SETPIXEL(x0, y, LCD_COLORINDEX);
    }
  }
}

/*********************************************************************
*
*       LCD_L0_DrawVLine    绘制垂直线函数
*/
void LCD_L0_DrawVLine(int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (y0 <= y1) {
      XORPIXEL(x, y0);
      y0++;
    }
  } else {
    while (y0 <= y1) {
      SETPIXEL(x, y0, LCD_COLORINDEX);
      y0++;
    }
  }
}

/*********************************************************************
*
*       LCD_L0_FillRect 填充矩阵函数
*/
void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0,y0, x1);
  }
}

/*********************************************************************
*
*       LCD_L0_DrawBitmap 画位图函数
*/
void LCD_L0_DrawBitmap(int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8* pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  /*
     Use DrawBitLineXBPP
  */
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
    #if (LCD_MAX_LOG_COLORS > 2)
      case 2:
        _DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        _DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        _DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 8)
      case 16:
        _DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 16)
      case 24:
        _DrawBitLine24BPP(x0, i + y0, (const U32 *)pData, xsize);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
}

/*********************************************************************
*
*       LCD_L0_SetOrg
*
*  Purpose:
*    Sets the original position of the virtual display.
*    Has no function at this point with the PC-driver.
*/
void LCD_L0_SetOrg(int x, int y) {
  LCDSIM_SetOrg(x, y, LCD_DISPLAY_INDEX);
}

/*********************************************************************
*
*       Support for verification
*
*  Purpose:
*    The following routines are implemented, but have no functionility
*    at this point. The reason is that these functions are supposed
*    to supervise the hardware, which for obvious reasons can not be
*    done in a simulation.
*/
#if LCD_VERIFY
int  LCD_GetErrStat(void) {
  return 0;
}
void LCD_ClrErrStat(void) {
}
int  LCD_GetErrCnt (void) {
  return 0;
}
#endif  

/*********************************************************************
*
*       LCD_On
*       LCD_Off  关闭LCD 
*
*  (Not supported in Simulation)
*/
void LCD_Off          (void) {}
void LCD_On           (void) {}

/*********************************************************************
*
*       LCD_L0_SetLUTEntry 修改 LCD 控制器的 LUT 的中的单个条目 
*/
void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR color) {
  LCDSIM_SetLUTEntry(Pos, color, LCD_DISPLAY_INDEX);
}

void LCDSIM_SetLUTEntry(U8 Pos, LCD_COLOR color, int LayerIndex){
	
}
void  LCDSIM_SetOrg(int x, int y, int LayerIndex){
	
}
int  LCDSIM_GetPixelIndex(int x, int y, int LayerIndex){
	return 0;
}
void   LCDSIM_SetPixelIndex(int x, int y, int Index, int LayerIndex){
	
}


/*********************************************************************
*
*       LCD_L0_Init  LCD初始化 
*/
int  LCD_L0_Init(void) {
	return 0;
}

int  LCD_L0_CheckInit(void) {
  return 0;
} 

/*********************************************************************
*
*       LCD_L0_ReInit
*
*  Purpose:
*    This routine is supplied for compatibility and interchangability of
*    "C"-sources with embedded versions of the driver. It has no real
*    effect in the PC-version as there is simply no need to re-initialize
*    the LCD since it is just simulated anyhow.
*/
void LCD_L0_ReInit       (void) {}

/*********************************************************************
*
*       LCD_L0_GetPixelIndex 取得某点像素颜色值,并返回 
*/
unsigned LCD_L0_GetPixelIndex(int x, int y)  {
  return GetPixel(x,y, LCD_DISPLAY_INDEX);
}

/*********************************************************************
*
*       LCD_L0_XorPixel  反转像素函数 
*
*  Purpose:
*    Inverts 1 pixel of the display.
*/
void LCD_L0_XorPixel(int x, int y) {
  XORPIXEL(x, y);
}

/*********************************************************************
*
*       LCD_L0_SetPixelIndex 设定指定点颜色值
*
*  Purpose:
*    Writes 1 pixel into the display.
*/
void LCD_L0_SetPixelIndex(int x, int y, int ColorIndex) {
  SETPIXEL(x, y, ColorIndex);
}

/*********************************************************************
*
*       LCD_L0_GetDevFunc
*/
void * LCD_L0_GetDevFunc(int Index) {
  GUI_USE_PARA(Index);
  return NULL;
}

//#else
  void LCDWin_c(void);
  void LCDWin_c(void) { } /* avoid empty object files */
//#endif /* defined(WIN32) && defined(LCD_USE_WINSIM) */

