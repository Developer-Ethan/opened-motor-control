#include  "bsp_led.h"

/*************************************************************
 * led¶Ë¿Ú³õÊ¼»¯
 *************************************************************/
void LED_GPIO_Config(void)
{
	GPIO_InitType GPIO_InitStructure;

  RCC_AHB_Peripheral_Clock_Enable(LED_RED_CLK);

	GPIO_InitStructure.Pin        = LED_RED_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUT_PP;
	GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
	GPIO_Peripheral_Initialize(LED_RED_PORT, &GPIO_InitStructure);
	
	GPIO_Pins_Set(LED_RED_PORT,LED_RED_PIN);

}

