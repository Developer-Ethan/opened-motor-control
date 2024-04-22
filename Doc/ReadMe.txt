1、功能说明
系统时钟120M  HSI
底层配置：
GPIO 输出引脚  
		PA6 I2C WP   PB7  LED灯
I2C   
		PA4  PA5
TIM1
		CH1 PA8    CH1N PA7    CH2 PA9    CH2N PB0    CH2 PA10    CH3N PB1
		CH4 上升到三角波顶点时触发一次中断计算
		CH7 CH8 CH9 触发ADC采样 在上升沿触发  PWM2  6K
	
TIM2
       TIM1和TIM2同步，使用TIM2的更新中断，因为TIM1的更新中断在上溢和下溢都会触发中断

TIM6
		1ms中断
		
TIM4_ETR		
PA11作为内部计数器的时钟源。来一个上升沿计数一次


Systick
		1ms延时
		
ADC   
PA0 电流   PA1母线电压

COMP2
PA3同向端  反向端为DAC输出 VC2  PA12输出同时输出到TIM1_BKIN

看门狗
增加了函数暂时未使用


下次装载时间


V0.0.2
 适配VSCODE
 增加TIM+DMA输入捕获

	
	