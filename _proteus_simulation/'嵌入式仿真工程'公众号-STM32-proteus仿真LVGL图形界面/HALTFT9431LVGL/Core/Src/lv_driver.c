#include "main.h"
#include "ILI9341.h"
#include "lv_driver.h"
//#include <stdio.h>

// void ILI9341_flush(struct _disp_drv_t * drv, const lv_area_t * area,  lv_color_t * color_map)
void lv_driver_flush(lv_disp_drv_t * drv, const lv_area_t * area,  lv_color_t * color_map)
{
    TFT_Flush_Data(area->x1, area->y1, area->x2, area->y2, (uint16_t*)color_map);
    
    lv_disp_flush_ready(drv);
}

