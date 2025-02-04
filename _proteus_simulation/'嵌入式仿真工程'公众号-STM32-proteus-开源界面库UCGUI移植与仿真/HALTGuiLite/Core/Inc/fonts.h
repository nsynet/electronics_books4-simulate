/*
 * fonts.h
 *
 *  Created on: 29 mars 2023
 *      Author: PC-MAGHREBI
 */

#ifndef FONTS_H_
#define FONTS_H_
#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

typedef struct {
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;


extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;
#ifdef __cplusplus
}
#endif

#endif /* FONTS_H_ */
