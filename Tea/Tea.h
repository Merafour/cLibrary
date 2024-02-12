/******************** (C) COPYRIGHT 2018 merafour ********************
* Author             : 冷月追风@merafour.blog.163.com
* Version            : V2.0.0
* Date               : 2024.02.09
* Description        : TEA encryption algorithm.
********************************************************************************
* merafour.blog.163.com
* merafour@163.com
* github.com/Merafour
*******************************************************************************/

#ifndef _TEA_H_
#define _TEA_H_
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

//extern void tea_encrypt(const uint32_t* v, const uint32_t* k, uint32_t* vout);
//extern void tea_decrypt(const uint32_t* v, const uint32_t* k, uint32_t* vout);
extern void tea_encrypt(uint32_t* v, const uint32_t* k, const uint8_t iteration);
extern void tea_decrypt(uint32_t* v, const uint32_t* k, const uint8_t iteration);
extern void _tea_encrypt(const uint32_t* v, const uint32_t* k, uint32_t* vout, const uint8_t iteration);
extern void _tea_decrypt(const uint32_t* v, const uint32_t* k, uint32_t* vout, const uint8_t iteration);

#ifdef __cplusplus
}
#endif
#endif // _TEA_H_
