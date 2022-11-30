#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H
#include "sys.h"
// 步进电机

#define STEP_MOTOR_PORT GPIOB
#define STEP_MOTOR_A GPIO_Pin_3
#define STEP_MOTOR_B GPIO_Pin_4
#define STEP_MOTOR_C GPIO_Pin_8
#define STEP_MOTOR_D GPIO_Pin_9

void STEP_MOTOR_Init(void);
void STEP_MOTOR_OFF(void);
void STEP_MOTOR_4S(u8 speed);
void STEP_MOTOR_4R(u8 speed);
void STEP_MOTOR_4L(u8 speed);
void STEP_MOTOR_8R(u8 speed);
void STEP_MOTOR_8L(u8 speed);


#endif