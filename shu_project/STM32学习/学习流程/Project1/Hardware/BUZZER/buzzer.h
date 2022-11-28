#ifndef __BUZZER_H
#define __BUZZER_H

#include "sys.h"

#define BUZZERPORT GPIOB
#define BUZZER GPIO_Pin_5

void BUZZER_Init(void);
void BUZZER_BEEP1(void); //œÏ“ª…˘
void BUZZER_BEEP2(void);
void MIDI_PLAY(void); //≤•∑≈MIDI“Ù¿÷
	
#endif