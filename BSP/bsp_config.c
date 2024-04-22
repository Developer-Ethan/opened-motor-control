#include "bsp_config.h"
#include "bsp_tim.h"
#include "bsp_led.h"
#include "bsp_adc.h"
#include "i2c_eeprom.h"

__IO uint32_t TimingDelay = 0;
/*************************************************************
 * 所有外设时钟初始化
 *************************************************************/
void RCC_Configuration(void)
{
		NVIC_Priority_Group_Set(NVIC_PER3_SUB1_PRIORITYGROUP);
	
		RCC_Pclk1_Config(RCC_HCLK_DIV8);		//设置APB1的时钟频率为15Mhz同时TIM2时钟频率为30MHz
    // Enable TIM1 clocks
    RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_TIM1);
		RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM2);
		RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM4);
		RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM6);
    // Enable DMA clocks
    RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_DMA);

    // Enable GPIOA GPIOB clocks
    RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_GPIOA | RCC_AHB_PERIPH_GPIOB);
    RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_AFIO);

    // Enable ADC clocks
    RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_ADC);//使能ADC时钟

    ADC_Clock_Mode_Config(ADC_CKMOD_AHB, RCC_ADCHCLK_DIV4);//ADC_HCLK使能->寄存器访问时钟；ADC PLL时钟被禁用；同步时钟选择AHB，4分频作为ADC_CLK
    RCC_ADC_1M_Clock_Config(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8);//ADC_1MCLK配置，为1MHZ

    // Enable COMP clocks
    RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_COMP_FILT);

    //I2C1  clocks enable
    RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_I2C1);
}


/*************************************************************
 * 比较器初始化，需要根据实际的计算值调整VC2的值
 *************************************************************/
void COMP_Configuratoin(void)
{
    COMP_InitType COMP_Initial;

    /*Set ref1  voltage div*/
//	  /*min 0.05v,  设置保护电压为3.038 4.6A  */
//    COMP_Voltage_Reference_Config(0, DISABLE, 58, ENABLE, 0, DISABLE);

		/*min 0.05v,  设置保护电压为3.165 5A  */
    COMP_Voltage_Reference_Config(0, DISABLE, 61, ENABLE, 0, DISABLE);
	
    /*Initial comp1*/
    COMP_Initializes_Structure(&COMP_Initial);
    COMP_Initial.SampWindow = 30;
    COMP_Initial.Threshold = 20;
    COMP_Initial.ClkPsc = 1;
    COMP_Initial.FilterEn = ENABLE;
    COMP_Initial.InpSel = COMP2_INPSEL_PA3;
    COMP_Initial.InmSel = COMP2_INMSEL_VREF_VC2;
    COMP_Initializes(COMP2, &COMP_Initial);

    /*trig initial as tim1 break*/
    COMP_Output_Trigger_Config(COMP2, COMP2_OUTSEL_TIM1_BKIN);

    /*enable comp*/
    COMP_ON(COMP2);
}

/*************************************************************
* 空闲端口初始化，初始化为推挽输出，低电平
 *************************************************************/
void IDLE_GPIO_Config(void)
{
	GPIO_InitType GPIO_InitStructure;
	
	RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_GPIOD);
	
	GPIO_Structure_Initialize(&GPIO_InitStructure);
	
	/*PD14 PD15 */
	// GPIO_InitStructure.Pin       = GPIO_PIN_14 | GPIO_PIN_15;				
	// GPIO_InitStructure.GPIO_Current = GPIO_DS_2MA;
	// GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT_PP;		
	// GPIO_Peripheral_Initialize(GPIOD, &GPIO_InitStructure);
	
	
	// GPIO_Pins_Reset(GPIOA,GPIO_PIN_2 | GPIO_PIN_15);
	// GPIO_Pins_Reset(GPIOB,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7);
	// GPIO_Pins_Reset(GPIOD,GPIO_PIN_14 | GPIO_PIN_15);
}

/*************************************************************
 * 端口初始化
 *************************************************************/
void GPIO_Config(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_Structure_Initialize(&GPIO_InitStructure);
    /*配置GPIO为推挽输出功能 */
    GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT_PP;
    GPIO_InitStructure.Pin       = GPIO_PIN_6;					//I2C WP引脚
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = GPIO_PIN_5;				 //LED1灯引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT_PP;
    GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = GPIO_PIN_12;				 //LED2灯引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT_PP;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = GPIO_PIN_3;				 //Key1
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT_PP;
    GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);

    /*配置 I2C 引脚  I2C1  SCK(PA4) SDA(PA5)  AF8*/
    GPIO_InitStructure.Pin            = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF8_I2C1;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

    /*配置 TIM1, CH1(PA8),CH2(PA9),CH3(PA10) CH1N(PA7),CH2N(PB0),CH3N(PB1)*/
    GPIO_Structure_Initialize(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM1;
    GPIO_InitStructure.Pin        = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM1;
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_INPUT;
		GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_DOWN;
		GPIO_InitStructure.GPIO_Alternate = GPIO_AF9_TIM4;
    GPIO_InitStructure.Pin        = GPIO_PIN_11;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
		
    /*配置 ADC*/
    GPIO_Structure_Initialize(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    //current
    GPIO_InitStructure.Pin       = GPIO_PIN_7;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

    GPIO_Structure_Initialize(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    //Voltage
    GPIO_InitStructure.Pin       = GPIO_PIN_2;
    GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);

    /*配置比较器 COMP2*/
    // GPIO_Structure_Initialize(&GPIO_InitStructure);
    // GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
    // GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    // GPIO_InitStructure.Pin       = GPIO_PIN_3;			//inp
    // GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

    // GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    // GPIO_InitStructure.Pin            = GPIO_PIN_12;//out
    // GPIO_InitStructure.GPIO_Alternate = GPIO_AF8_COMP2;
    // GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
    // COMP_Configuratoin();
		
		//IDLE_GPIO_Config();
		
//		GPIO_Structure_Initialize(&GPIO_InitStructure);
//    GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
//    GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_TIM2;
//    GPIO_InitStructure.Pin        = GPIO_PIN_15;
//    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
}




/*************************************************************
 * systick Configures
 *************************************************************/
void SysTick_Configuration(uint32_t freq)
{
    /* Config  SysTick  */
    SysTick_Config(SystemClockFrequency / freq);
}


/*************************************************************
 *  ms延时程序,1ms为一个单位
 *  nTime: 延时时间
 *************************************************************/
void Delay_ms(__IO u32 nTime)
{
    TimingDelay = nTime;

    while (TimingDelay != 0);
}

/*************************************************************
 *  获取节拍程序
 *  在 SysTick 中断函数 SysTick_Handler()调用
 *************************************************************/
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}


/*************************************************************
 *独立看门狗初始化
 *配置为500ms
 *复位时间计算：LSI频率为30KHZ想要配置为500mS 即为2Hz
 *40000/128/2 = 156  128为时钟分频
 *************************************************************/
void IWDG_Config(void)
{
    /* The timeout may varies due to LSI frequency dispersion */
    /* Disable write protection to IWDG_PREDIV and IWDG_RELV registers */
    IWDG_Write_Protection_Disable();

    /* IWDG counter clock */
    IWDG_Prescaler_Division_Set(IWDG_CONFIG_PRESCALER_DIV128);

    /* Sets IWDG reload value */
    /* Set counter reload value to obtain x second IWDG TimeOut.
     Counter Reload Value Time = x(second)/IWDG counter clock period
                               = x(second) / (LSI/IWDG_prescaler)
    */
    IWDG_Counter_Reload(156);

    /* Reload counter with IWDG_PREDIV value in IWDG_RELV register to prevent reset */
    IWDG_Key_Reload();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();

}

/*************************************************************
 * 系统初始化
 *************************************************************/
void System_Init(void)
{    
    RCC_Configuration();
    __disable_irq();
    //SysTick_Configuration(1000);
    GPIO_Config();
    TIM1_PWM_Init(SET);
//		TIM4_ETR_Init();
		TIM6_1Khz_Init();
		TIM4_Capture_Config();
    Adc_Init();

    __enable_irq();
		switch_pwm(INV_ALL_OFF);
	
		I2C_EE_Init();
}

void FLASH_Read_Out_Protection(void)
{
	if (FLASH_Read_Out_Protection_Status_Get() == RESET)		//先读取下读保护标志位有没有置位，如果没有置位则使能读保护
	{
		 FLASH_Unlock();
		 FLASH_Read_Out_Protection_L1_Enable();
		 FLASH_Lock();
		 NVIC_SystemReset();			//软复位，生效读保护
	}
}
