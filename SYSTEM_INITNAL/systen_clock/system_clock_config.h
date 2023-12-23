#ifndef __system_h__
#define __system_h__
#include "stm32f10x.h"
#include "stm32f10x_flash.c"

/*初始化RCC并配置系统时钟频率*/
void HSE_Init(uint32_t RCC_PLLMul_x)//范围2-16
{
    //ErrorStatus HSEStatus;//定义
	__IO uint32_t HSEStatus=0;
    //重置RCC，否则不会有效果
    RCC_DeInit();
 
    //使能HSE
    RCC_HSEConfig(RCC_HSE_ON);
	//获取HSI状态，等待HSI稳定
    HSEStatus=RCC_WaitForHSEStartUp();
 
   //判断HSE的状态，是否已启动
    if(HSEStatus==SUCCESS)
    {
        //flash预取指使能
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//flash预取指等待时间配置
        FLASH_SetLatency(FLASH_Latency_2);
 
       //对AHB APB1 APB2分频
        RCC_HCLKConfig( RCC_SYSCLK_Div1 );
        RCC_PCLK1Config( RCC_HCLK_Div2 );
        RCC_PCLK2Config( RCC_HCLK_Div1 );
 
 
        //配置PLL时钟源和倍频因子（官方库中声明要先设置后打开PLL）
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
        //使能PLL
        RCC_PLLCmd(ENABLE);
 
        //等待PLL状态稳定后跳出语句
        while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY) == RESET);
        //等待系统时钟切换完成
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK );
        while(RCC_GetSYSCLKSource()!=0x08);
    }
	else
	{
		//HSE启动识别，当启动错误时在此操作
	}
    //flash预取指使能
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    //flash预取指等待时间配置
    FLASH_SetLatency(FLASH_Latency_2);
}


#endif // !__system_h__