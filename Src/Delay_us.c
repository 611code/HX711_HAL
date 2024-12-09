//
// Created by 18681 on 24-10-6.
//
#include "Delay_us.h"
#define DLY_TIM_Handle (&htim4)
void Delay_us(uint16_t nus)
{
    __HAL_TIM_SET_COUNTER(DLY_TIM_Handle, 0);
    __HAL_TIM_ENABLE(DLY_TIM_Handle);
    while (__HAL_TIM_GET_COUNTER(DLY_TIM_Handle) < nus)
    {
    }
    __HAL_TIM_DISABLE(DLY_TIM_Handle);
}

