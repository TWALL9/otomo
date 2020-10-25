/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    GPIO_TypeDef * port;
    uint16_t pin;
} GPIO_reference_t;

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define ADC1_IN1_Pin GPIO_PIN_1
#define ADC1_IN1_GPIO_Port GPIOA
#define US1_OUT_Pin GPIO_PIN_6
#define US1_OUT_GPIO_Port GPIOA
#define US1_IN_Pin GPIO_PIN_7
#define US1_IN_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define FR_MOTOR_1_Pin GPIO_PIN_10
#define FR_MOTOR_1_GPIO_Port GPIOB
#define FR_MOTOR_2_Pin GPIO_PIN_11
#define FR_MOTOR_2_GPIO_Port GPIOB
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD
#define BL_MOTOR_1_Pin GPIO_PIN_6
#define BL_MOTOR_1_GPIO_Port GPIOC
#define BL_MOTOR_2_Pin GPIO_PIN_7
#define BL_MOTOR_2_GPIO_Port GPIOC
#define BR_MOTOR_1_Pin GPIO_PIN_8
#define BR_MOTOR_1_GPIO_Port GPIOC
#define BR_MOTOR_2_Pin GPIO_PIN_9
#define BR_MOTOR_2_GPIO_Port GPIOC
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define BL_MOTOR_ENC_Pin GPIO_PIN_4
#define BL_MOTOR_ENC_GPIO_Port GPIOD
#define BL_MOTOR_ENC_EXTI_IRQn EXTI4_IRQn
#define BR_MOTOR_ENC_Pin GPIO_PIN_5
#define BR_MOTOR_ENC_GPIO_Port GPIOD
#define BR_MOTOR_ENC_EXTI_IRQn EXTI9_5_IRQn
#define FL_MOTOR_1_Pin GPIO_PIN_7
#define FL_MOTOR_1_GPIO_Port GPIOB
#define FL_MOTOR_2_Pin GPIO_PIN_8
#define FL_MOTOR_2_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/