/*
 * ************************************************
 * 
 * STM32 blink demo
 * 
 * CPU:     STM32F103C8
 * PIN:     PA1
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "dealy.h"
#include "system_clock_config.h"
#include "system_led.h"
#include "key.h"

void delay(int x)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < 1000; j++)
            __NOP();
    }
}

int main()
{
    uint16_t num=0;
    uint16_t i=0;
    HSE_Init(RCC_PLLMul_9);

    //key_init(1,1,1,1,1,1);
    system_led_init(1);
    while (9)
    {
        Delay_ms(1000);
        //num = key_get_number();
        system_led_sw(1);
        Delay_ms(1000);
        //num = key_get_number();
        system_led_sw(0);
    }

}
