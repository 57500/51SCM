#ifndef __XPT2046_H__
#define __XPT2046_H__


#define XPT2046_XP       0x9c
#define XPT2046_YP       0xdc
#define XPT2046_VBAT     0xac
#define XPT2046_AUX      0xec







unsigned int XPT2046_ReadAD(unsigned char Command);

#endif