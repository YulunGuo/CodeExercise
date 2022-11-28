#include "flash.h"

void FLASH_W(u32 add,u16 date){
	FLASH_Unlock(); //����
	FLASH_ClearFlag(FLASH_FLAG_BANK1_BSY | FLASH_FLAG_EOP | FLASH_FLAG_WRPRTERR | FLASH_FLAG_PGERR); //���ȥ��־λ
	FLASH_ErasePage(add); //����ҳ����
	FLASH_ProgramHalfWord(add,date); //д��
	FLASH_ClearFlag(FLASH_FLAG_BANK1_BSY | FLASH_FLAG_EOP | FLASH_FLAG_WRPRTERR | FLASH_FLAG_PGERR); //���ȥ��־λ
	FLASH_Lock();
}


u16 FLASH_R(u32 add){
	u16 date;
	date = *(u16*)(add);
	return date;
}