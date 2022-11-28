#include "flash.h"

void FLASH_W(u32 add,u16 date){
	FLASH_Unlock(); //解锁
	FLASH_ClearFlag(FLASH_FLAG_BANK1_BSY | FLASH_FLAG_EOP | FLASH_FLAG_WRPRTERR | FLASH_FLAG_PGERR); //清除去标志位
	FLASH_ErasePage(add); //擦除页数据
	FLASH_ProgramHalfWord(add,date); //写入
	FLASH_ClearFlag(FLASH_FLAG_BANK1_BSY | FLASH_FLAG_EOP | FLASH_FLAG_WRPRTERR | FLASH_FLAG_PGERR); //清除去标志位
	FLASH_Lock();
}


u16 FLASH_R(u32 add){
	u16 date;
	date = *(u16*)(add);
	return date;
}