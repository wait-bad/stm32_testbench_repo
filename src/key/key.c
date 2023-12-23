#include "key.h"

#include <stdint.h>

static void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
static void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}

static void key_gpio_init()
{
    // Initialize KEY1
    GPIO_InitTypeDef gpioDef;
    RCC_APB2PeriphClockCmd(KEY1_PERIPH, ENABLE);
    gpioDef.GPIO_Mode = GPIO_Mode_IPU;
    gpioDef.GPIO_Pin = KEY1_PIN;
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(KEY1_PORT, &gpioDef);

    // Initialize KEY2
    RCC_APB2PeriphClockCmd(KEY2_PERIPH, ENABLE);
    gpioDef.GPIO_Pin = KEY2_PIN;
    GPIO_Init(KEY2_PORT, &gpioDef);

    // Initialize KEY3
    RCC_APB2PeriphClockCmd(KEY3_PERIPH, ENABLE);
    gpioDef.GPIO_Pin = KEY3_PIN;
    GPIO_Init(KEY3_PORT, &gpioDef);

    // Initialize KEY4
    RCC_APB2PeriphClockCmd(KEY4_PERIPH, ENABLE);
    gpioDef.GPIO_Pin = KEY4_PIN;
    GPIO_Init(KEY4_PORT, &gpioDef);

    // Initialize KEY5
    RCC_APB2PeriphClockCmd(KEY5_PERIPH, ENABLE);
    gpioDef.GPIO_Pin = KEY5_PIN;
    GPIO_Init(KEY5_PORT, &gpioDef);

    // Initialize KEY6
    RCC_APB2PeriphClockCmd(KEY6_PERIPH, ENABLE);
    gpioDef.GPIO_Pin = KEY6_PIN;
    GPIO_Init(KEY6_PORT, &gpioDef);
}

static void key_state_initnal(
    uint8_t key1_state,
    uint8_t key2_state,
    uint8_t key3_state,
    uint8_t key4_state,
    uint8_t key5_state,
    uint8_t key6_state
)
{
    KEY1_sw(key1_state);
    KEY2_sw(key2_state);
    KEY3_sw(key3_state);
    KEY4_sw(key4_state);
    KEY5_sw(key5_state);
    KEY6_sw(key6_state);
}


void key_init(
    uint8_t key1_state,
    uint8_t key2_state,
    uint8_t key3_state,
    uint8_t key4_state,
    uint8_t key5_state,
    uint8_t key6_state
)
{
    key_gpio_init();
    key_state_initnal(key1_state,key2_state,key3_state,key4_state,key5_state,key6_state);

}


static int8_t one_key_get(GPIO_TypeDef* port, uint16_t pin,uint16_t long_judge_time, uint16_t long_press_threshold, uint16_t short_press_threshold) {

    // If the key is not pressed
    if (GPIO_ReadInputDataBit(port, pin) == 1) {
        return 0;  // Key not pressed
    }
    Delay_ms(10);
    uint16_t time = 0;
    // Timer to record the time the key is pressed
    while (time < 100) {
        Delay_ms(10);
        time++;
        // If the key is no longer pressed, break the loop
        if (GPIO_ReadInputDataBit(port, pin) == 1) {
            return short_press_threshold;
        }
    }
    // Wait for the key to be released
    while (GPIO_ReadInputDataBit(port, pin) == 0) {};// Empty loop
    Delay_ms(10);

    // Determine if it's a long press or a short press based on the time the key is pressed
    if (time>90)
    {
        return long_press_threshold;
    }
    else
    {
        return short_press_threshold;

    }
}

/**
 * @brief key capture programe 
 * 
 * @return uint8_t if no key return 0
 * if key return short or long 
 */
uint8_t key_get_number()
{
    // Wait for the key to stabilize
    Delay_ms(15);
    uint8_t return_num=0;
    return_num = one_key_get(KEY1_PORT, KEY1_PIN, 50, 7, 1);
    if (return_num!= 0){ return return_num; }
    return_num = one_key_get(KEY2_PORT, KEY2_PIN, 50, 8, 2);
    if (return_num!= 0){ return return_num; }
    return_num = one_key_get(KEY3_PORT, KEY3_PIN, 50, 9, 3);
    if (return_num!= 0){ return return_num; }
    return_num = one_key_get(KEY4_PORT, KEY4_PIN, 50, 10, 4);
    if (return_num!= 0){ return return_num; }
    return_num = one_key_get(KEY5_PORT, KEY5_PIN, 50, 11, 5);
    if (return_num!= 0){ return return_num; }
    return_num = one_key_get(KEY6_PORT, KEY6_PIN, 50, 12, 6);
    if (return_num!= 0){ return return_num; }
    return 0;
};

