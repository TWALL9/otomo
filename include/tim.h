/**
  ******************************************************************************
  * File Name          : TIM.h
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim14;

void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_TIM14_Init(void);
                        
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

TIM_HandleTypeDef * HAL_TIM_GetHandleTypeDef_TIM3(void);
uint32_t PWM_SetDutyCycle(TIM_HandleTypeDef *timerHandle, uint32_t channel, uint8_t dutyCycle);

void TIM_IncrementMsTick(void);
uint32_t TIM_GetMilliseconds(void);

uint32_t TIM_GetMicroseconds(void);
void TIM_MicrosecondDelay(uint16_t delay);

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/