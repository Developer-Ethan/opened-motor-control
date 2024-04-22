
#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "n32g430.h"

#define LED_RED_PORT      GPIOA
#define LED_RED_CLK       RCC_AHB_PERIPH_GPIOA
#define LED_RED_PIN       GPIO_PIN_7|GPIO_PIN_1|GPIO_PIN_9

void LED_GPIO_Config(void);

#endif /* end of __BSP_LED_H */

