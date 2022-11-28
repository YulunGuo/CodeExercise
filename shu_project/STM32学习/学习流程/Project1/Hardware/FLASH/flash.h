#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f10x_flash.h"

void FLASH_W(u32 add,u16 date);
u16 FLASH_R(u32 add);

#endif 