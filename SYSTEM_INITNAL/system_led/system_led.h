// system_led.h

#ifndef __SYSTEM_LED_H__
#define __SYSTEM_LED_H__

#include "stm32f10x.h"

/* default PC13 */
#define LED_PERIPH RCC_APB2Periph_GPIOC
#define LED_PORT GPIOC
#define LED_PIN GPIO_Pin_13

/**
 * @brief control system_led
 */
#define system_led_sw(x) GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction)(x))


/**
 * @brief system_led_initnal usually PC13
 * 
 * @param state 
 */
void system_led_init(uint8_t state)
{
    GPIO_InitTypeDef gpioDef;
    RCC_APB2PeriphClockCmd(LED_PERIPH, ENABLE);
    gpioDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioDef.GPIO_Pin = LED_PIN;
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LED_PORT, &gpioDef);

    system_led_sw(state);
}

#endif /* __SYSTEM_LED_H__ */
