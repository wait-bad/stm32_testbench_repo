/*
 * ************************************************
 * 
 * STM32 blink demo
 * 
 * CPU:     STM32F103C8
 * PIN:     pc13 system_led
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "dealy.h"
#include "system_clock_config.h"
#include "system_led.h"
#include "key.h"
#include "Serial.h"

uint16_t time_counter = 0;

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
    int variable_int = 42;
    float variable_float = 3.14;
    char variable_char = 'A';

    HSE_Init(RCC_PLLMul_9);

    // 使用Serial_Printf打印整数、浮点数和字符
    //Serial_Printf("Integer: %d, Float: %.2f, Char: %c", variable_int, variable_float, variable_char);

    //key_init(1,1,1,1,1,1);
    system_led_init(1);
    Serial_Init();
    while (9)
    {
        Delay_ms(300);
        //num = key_get_number();
        system_led_sw(1);
        time_counter++;
        Delay_ms(300);
        //num = key_get_number();
        system_led_sw(0);
        time_counter++;
        Serial_Printf("Integer: %d \n",time_counter);
    }

}
