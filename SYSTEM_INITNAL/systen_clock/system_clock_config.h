#ifndef __system_h__
#define __system_h__
#include "stm32f10x.h"
#include "stm32f10x_flash.c"

/*��ʼ��RCC������ϵͳʱ��Ƶ��*/
void HSE_Init(uint32_t RCC_PLLMul_x)//��Χ2-16
{
    //ErrorStatus HSEStatus;//����
	__IO uint32_t HSEStatus=0;
    //����RCC�����򲻻���Ч��
    RCC_DeInit();
 
    //ʹ��HSE
    RCC_HSEConfig(RCC_HSE_ON);
	//��ȡHSI״̬���ȴ�HSI�ȶ�
    HSEStatus=RCC_WaitForHSEStartUp();
 
   //�ж�HSE��״̬���Ƿ�������
    if(HSEStatus==SUCCESS)
    {
        //flashԤȡָʹ��
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//flashԤȡָ�ȴ�ʱ������
        FLASH_SetLatency(FLASH_Latency_2);
 
       //��AHB APB1 APB2��Ƶ
        RCC_HCLKConfig( RCC_SYSCLK_Div1 );
        RCC_PCLK1Config( RCC_HCLK_Div2 );
        RCC_PCLK2Config( RCC_HCLK_Div1 );
 
 
        //����PLLʱ��Դ�ͱ�Ƶ���ӣ��ٷ���������Ҫ�����ú��PLL��
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
        //ʹ��PLL
        RCC_PLLCmd(ENABLE);
 
        //�ȴ�PLL״̬�ȶ����������
        while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY) == RESET);
        //�ȴ�ϵͳʱ���л����
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK );
        while(RCC_GetSYSCLKSource()!=0x08);
    }
	else
	{
		//HSE����ʶ�𣬵���������ʱ�ڴ˲���
	}
    //flashԤȡָʹ��
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    //flashԤȡָ�ȴ�ʱ������
    FLASH_SetLatency(FLASH_Latency_2);
}


#endif // !__system_h__