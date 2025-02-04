/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
---Author-Explanation
*
* 1.00.00 020519 JJL    First release of uC/GUI to uC/OS-II interface
*
*
* Known problems or limitations with current version
*
*    None.
*
*
* Open issues
*
*    None
*********************************************************************************************************
*/
//#include <ucos_ii.h>
#include "GUI_Private.H"
#include "stdio.H"
#include "GUI_X.H"
#include "GUI.H"


/*
*********************************************************************************************************
*                                         GLOBAL VARIABLES
*********************************************************************************************************
*/

static  int        KeyPressed;
static  char       KeyIsInited;


/*
*********************************************************************************************************
*                                        TIMING FUNCTIONS
*
* Notes: Some timing dependent routines of uC/GUI require a GetTime and delay funtion.
*        Default time unit (tick), normally is 1 ms.
*********************************************************************************************************
*/

int  GUI_X_GetTime (void)
{
	return 0;
}


void  GUI_X_Delay (int period)
{

}


/*
*********************************************************************************************************
*                                          GUI_X_ExecIdle()
*********************************************************************************************************
*/
void GUI_X_ExecIdle (void)
{

}


/*
*********************************************************************************************************
*                                    MULTITASKING INTERFACE FUNCTIONS
*
* Note(1): 1) The following routines are required only if uC/GUI is used in a true multi task environment,
*             which means you have more than one thread using the uC/GUI API.  In this case the #define
*             GUI_OS 1   needs to be in GUIConf.h
*********************************************************************************************************
*/

void  GUI_X_InitOS (void)
{

}


void  GUI_X_Lock (void)
{
}



void  GUI_X_Unlock (void)
{

}


U32  GUI_X_GetTaskId (void)
{
	return 0;
}

/*
*********************************************************************************************************
*                                        GUI_X_WaitEvent()
*                                        GUI_X_SignalEvent()
*********************************************************************************************************
*/


void GUI_X_WaitEvent (void)
{

}

void GUI_X_Log(const char *s)
{


}
void GUI_X_Warn(const char *s)
{


}
void GUI_X_ErrorOut(const char *s)
{


}

void GUI_TOUCH_X_ActivateX()
{

}
void GUI_TOUCH_X_ActivateY()
{

}

int GUI_TOUCH_X_MeasureX()
{
	return 0;
}
int GUI_TOUCH_X_MeasureY()
{
	return 0;
}



void GUI_X_SignalEvent (void)
{

}

/*
*********************************************************************************************************
*                                      KEYBOARD INTERFACE FUNCTIONS
*
* Purpose: The keyboard routines are required only by some widgets.
*          If widgets are not used, they may be eliminated.
*
* Note(s): If uC/OS-II is used, characters typed into the log window will be placed	in the keyboard buffer.
*          This is a neat feature which allows you to operate your target system without having to use or
*          even to have a keyboard connected to it. (useful for demos !)
*********************************************************************************************************
*/

static  void  CheckInit (void)
{

}


void GUI_X_Init (void)
{

}


int  GUI_X_GetKey (void)
{
 
	return 0;
}


int  GUI_X_WaitKey (void)
{
	return 0;
}


void  GUI_X_StoreKey (int k)
{

}

