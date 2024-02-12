/************************ (C) COPYLEFT 2018 Merafour *************************
* File Name          : URGB.h
* Author             : Merafour
* Last Modified Date : 2024.2.12
* Description        : RGB.
********************************************************************************
* https://merafour.blog.163.com
* merafour@163.com
* https://github.com/merafour
******************************************************************************/
#ifndef _URGB_H_
#define _URGB_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef URGB_ROWS
#define URGB_ROWS       6
#endif
#ifndef URGB_COLS
#define URGB_COLS       21
#endif
//#ifndef URGB_TYPE
////#define URGB_TYPE       uint16_t
//#define URGB_TYPE       uint8_t
//#endif

struct URGB_Param_t {
	uint32_t* const Frame;  // Frame Not NULL !!!
	const uint8_t offset[URGB_ROWS];
	const uint8_t convert[URGB_ROWS*URGB_COLS+2];
	const uint8_t rows;
	const uint8_t cols;
	const uint8_t invalid;
};
#define  URGB_ROW(pos)      ((pos>>5)&0x07)
#define  URGB_COL(pos)      (pos&0x1F)
#define  URGB_POS(row,col)  (((row&0x07)<<5) | (col&0x1F))

// API 1
static inline uint16_t inURGB_mXY(const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid)
{
	if((x >= cols) || (y >= rows)) return invalid;
	return(offset[y] + x);
}

static inline void inURGB_draw_pixel(uint32_t Frame[], const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid, const uint32_t color) 
{
	Frame[inURGB_mXY(offset, x, y, rows, cols, invalid)] = color;
}

static inline uint32_t inURGB_get_pixel(uint32_t Frame[], const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid) 
{
	Frame[invalid] = 0x00;
	return Frame[inURGB_mXY(offset, x, y, rows, cols, invalid)];
}
extern uint16_t URGB_mXY(const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid);
extern void URGB_draw_pixel(uint32_t Frame[], const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid, const uint32_t color);
extern uint32_t URGB_get_pixel(uint32_t Frame[], const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid);
extern void URGB_CNV_draw_pixel(uint32_t Frame[], const uint8_t offset[], const uint8_t convert[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid, const uint32_t color);
extern uint32_t URGB_CNV_get_pixel(uint32_t Frame[], const uint8_t offset[], const uint8_t convert[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid);
extern void URGB_FillFrame(uint32_t Frame[], const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid, const uint16_t w, const uint16_t h, const uint32_t color);

// API2
#ifdef  USER_URGBP
extern const struct URGB_Param_t URGB_Param;
static inline uint16_t inURGBP_mXY(const uint16_t x, const uint16_t y)
{
	if((x >= URGB_Param.cols) || (y >= URGB_Param.rows)) return URGB_Param.invalid;
	return(URGB_Param.offset[y] + x);
}

static inline void inURGBP_draw_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint32_t color) 
{
	Frame[inURGBP_mXY(x, y)] = color;
}

static inline uint32_t inURGBP_get_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y) 
{
	return Frame[inURGBP_mXY(x, y)];
}
extern uint16_t URGBP_mXY(const uint16_t x, const uint16_t y);
extern void URGBP_draw_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y, const uint32_t color);
extern uint32_t URGBP_get_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y);
extern void URGBP_CNV_draw_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y, const uint32_t color);
extern uint32_t URGBP_CNV_get_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y);
extern void URGBP_FillFrame(uint32_t Frame[], const uint16_t x, const uint16_t y, const uint16_t w, const uint16_t h, const uint32_t color);

#endif

#ifdef __cplusplus
}
#endif
#endif  // _URGB_H_
