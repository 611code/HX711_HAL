#ifndef HX711_HX711_H
#define HX711_HX711_H
#include "gpio.h"
#include "Delay_us.h"

#define GapValue 244
#define HX711_SCK_PORT GPIOA
#define HX711_SCK_PIN GPIO_PIN_3
#define HX711_DT_PORT GPIOA
#define HX711_DT_PIN GPIO_PIN_2

extern uint32_t HX711_Buffer;
extern uint32_t Weight_Maopi;
extern int32_t Weight_Shiwu;
extern uint8_t Flag_Error;


void HX711_Init(void);
uint32_t HX711_Read(void);
void Get_Maopi(void);
void Get_Weight(void);



#endif //HX711_HX711_H
