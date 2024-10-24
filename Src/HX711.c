//
// Created by 18681 on 24-10-6.
//
#include "HX711.h"

uint32_t HX711_Buffer;
uint32_t Weight_Maopi;
int32_t Weight_Shiwu;


void HX711_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    //HX711_SCK为推挽输出
    GPIO_InitStruct.Pin = HX711_SCK_PIN;				 // 端口配置
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 		 //推挽输出
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		 //IO口速度为50MHz
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(HX711_SCK_PORT, &GPIO_InitStruct); //根据设定参数初始化
    //HX711_DT 输入模式
    GPIO_InitStruct.Pin = HX711_DT_PIN;				 // 端口配置
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 		 // 输入上拉
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(HX711_DT_PORT, &GPIO_InitStruct); //根据设定参数初始化

    HAL_GPIO_WritePin(HX711_SCK_PORT,HX711_SCK_PIN,RESET);					//初始化设置为0
}

uint32_t HX711_Read(void)	//增益128
{
    unsigned long count;
    unsigned char i;
    HAL_GPIO_WritePin(HX711_DT_PORT,HX711_DT_PIN,SET);
    Delay_us(1);
    HAL_GPIO_WritePin(HX711_SCK_PORT,HX711_SCK_PIN,RESET);
    count=0;
    while(HAL_GPIO_ReadPin(HX711_DT_PORT,HX711_DT_PIN));
    for(i=0;i<24;i++)
    {
        HAL_GPIO_WritePin(HX711_SCK_PORT,HX711_SCK_PIN,SET);
        count=count<<1;
        Delay_us(1);
        HAL_GPIO_WritePin(HX711_SCK_PORT,HX711_SCK_PIN,RESET);
        if(HAL_GPIO_ReadPin(HX711_DT_PORT,HX711_DT_PIN))
            count++;
        Delay_us(1);
    }
    HAL_GPIO_WritePin(HX711_SCK_PORT,HX711_SCK_PIN,SET);
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
    Delay_us(1);
    HAL_GPIO_WritePin(HX711_SCK_PORT,HX711_SCK_PIN,RESET);
    return(count);
}

void Get_Maopi(void)
{
    Weight_Maopi = HX711_Read();
}
void Get_Weight(void)
{
    HX711_Buffer = HX711_Read();
    if(HX711_Buffer > Weight_Maopi)
    {
        Weight_Shiwu = HX711_Buffer;
        Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//获取实物的AD采样数值。
        Weight_Shiwu = (int32_t)((float)Weight_Shiwu/GapValue+5); 	//计算实物的实际重量
    }
    else
    {
        Weight_Shiwu=0;
    }
}