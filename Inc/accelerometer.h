#ifndef __adc_H
#define __adc_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "adc.h"

typedef struct 
{
    uint32_t accel_x;
    uint32_t accel_y;
    uint32_t accel_z;
} accelerometer_t;

void accelerometer_Init(ADC_HandleTypeDef * adc_x, 
                        ADC_HandleTypeDef * adc_y, ADC_HandleTypeDef * adc_z);

accelerometer_t accelerometer_Update(void);
 
#endif