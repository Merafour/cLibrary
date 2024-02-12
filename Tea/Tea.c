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

#include "Tea/tea.h"
//static const uint8_t Iteration = 32;
#define _delta_mask  0xbdc3931aU
static const uint32_t _delta = 0x9e3779b9^_delta_mask;
void tea_encrypt(uint32_t* v, const uint32_t* k, const uint8_t iteration)
{
    uint32_t v0 = v[0], v1 = v[1], sum = 0, i; /*setup*/
    //uint32_t delta = 0x9e3779b9; /*akeyscheduleconstant*/
    uint32_t delta = _delta^_delta_mask; /*akeyscheduleconstant*/
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3]; /*cachekey*/
    for(i=0;i<iteration/*Iteration*/;i++) {
        /*basiccyclestart*/
        sum += delta;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    } /*endcycle*/
    v[0] = v0;
    v[1] = v1;
}

void tea_decrypt(uint32_t* v, const uint32_t* k, const uint8_t iteration)
{
    uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i; /*setup*/
    //uint32_t delta = 0x9e3779b9; /*akeyscheduleconstant*/
    uint32_t delta = _delta^_delta_mask; /*akeyscheduleconstant*/
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3]; /*cachekey*/
    for(i = 0; i < iteration/*Iteration*/; i++) {
        /*basiccyclestart*/
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        sum -= delta;
    } /*endcycle*/
    v[0] = v0;
    v[1] = v1;
}

void _tea_encrypt(const uint32_t* v, const uint32_t* k, uint32_t* vout, const uint8_t iteration)
{
    uint32_t v0 = v[0], v1 = v[1], sum = 0, i; /*setup*/
    uint32_t delta = 0x9e3779b9; /*akeyscheduleconstant*/
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3]; /*cachekey*/
    for(i = 0; i < iteration/*Iteration*/; i++) {
        /*basiccyclestart*/
        sum += delta;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    } /*endcycle*/
    vout[0] = v0;
    vout[1] = v1;
}

void _tea_decrypt(const uint32_t* v, const uint32_t* k, uint32_t* vout, const uint8_t iteration)
{
    uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i; /*setup*/
    uint32_t delta = 0x9e3779b9; /*akeyscheduleconstant*/
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3]; /*cachekey*/
    for(i = 0; i < iteration/*Iteration*/; i++) {
        /*basiccyclestart*/
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        sum -= delta;
    } /*endcycle*/
    vout[0] = v0;
    vout[1] = v1;
}

