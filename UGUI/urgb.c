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
#include "UGUI/urgb.h"

uint16_t URGB_mXY(const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid)
{
	if((x >= cols) || (y >= rows)) return invalid;
	return(offset[y] + x);
}
void URGB_draw_pixel(uint32_t Frame[], const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid, const uint32_t color) 
{
	Frame[inURGB_mXY(offset, x, y, rows, cols, invalid)] = color;
}
uint32_t URGB_get_pixel(uint32_t Frame[], const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid) 
{
	Frame[invalid] = 0x00;
	return Frame[inURGB_mXY(offset, x, y, rows, cols, invalid)];
}
void URGB_CNV_draw_pixel(uint32_t Frame[], const uint8_t offset[], const uint8_t convert[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid, const uint32_t color) 
{
	uint8_t pos = convert[inURGB_mXY(offset, x, y, rows, cols, invalid)];
	Frame[inURGB_mXY(offset, URGB_COL(pos), URGB_ROW(pos), rows, cols, invalid)] = color;
}
uint32_t URGB_CNV_get_pixel(uint32_t Frame[], const uint8_t offset[], const uint8_t convert[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid) 
{
	uint8_t pos = convert[inURGB_mXY(offset, x, y, rows, cols, invalid)];
	Frame[invalid] = 0x00;
	return Frame[inURGB_mXY(offset, URGB_COL(pos), URGB_ROW(pos), rows, cols, invalid)];
}
void URGB_FillFrame(uint32_t Frame[], const uint8_t offset[], const uint16_t x, const uint16_t y, const uint16_t rows, const uint16_t cols, const uint16_t invalid, const uint16_t w, const uint16_t h, const uint32_t color)
{
	uint16_t row, col;
    for(row=0; row<h; row++) 
	{
        for(col=0; col<w; col++)
		{
			Frame[inURGB_mXY(offset, x+col, y+row, rows, cols, invalid)] = color;
		}
    }
}

// API2
#ifdef  USER_URGBP
__weak const struct URGB_Param_t URGB_Param = {
	0, // Frame Not NULL !!!
	{21*0, 21*1, 21*2, 21*3, 21*4, 21*5}, // offset
	{0, 0, 0, 0},  // convert
	6,   // rows
	21,  // cols
	(21*6+0), // invalid
};
uint16_t URGBP_mXY(const uint16_t x, const uint16_t y)
{
	if((x >= URGB_Param.cols) || (y >= URGB_Param.rows)) return URGB_Param.invalid;
	return(URGB_Param.offset[y] + x);
}
void URGBP_draw_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y, const uint32_t color)
{
	Frame[inURGBP_mXY(x, y)] = color;
}
uint32_t URGBP_get_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y)
{
	return Frame[inURGBP_mXY(x, y)];
}
void URGBP_CNV_draw_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y, const uint32_t color)
{
	uint8_t pos = URGB_Param.convert[inURGBP_mXY(x, y)];
	Frame[inURGBP_mXY(URGB_COL(pos), URGB_ROW(pos))] = color;
}
uint32_t URGBP_CNV_get_pixel(uint32_t Frame[], const uint16_t x, const uint16_t y)
{
	uint8_t pos = URGB_Param.convert[inURGBP_mXY(x, y)];
	return Frame[inURGBP_mXY(URGB_COL(pos), URGB_ROW(pos))];
}
void URGBP_FillFrame(uint32_t Frame[], const uint16_t x, const uint16_t y, const uint16_t w, const uint16_t h, const uint32_t color)
{
	uint16_t row, col;
    for(row=0; row<h; row++) 
	{
        for(col=0; col<w; col++)
		{
			Frame[inURGBP_mXY(x+col, y+row)] = color;
		}
    }
}
#endif
