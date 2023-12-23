#ifndef __key_h__
    #define __key_h__

#include "stm32f10x.h"

/*****************************************************/
//KEY1
#define KEY1_PERIPH  RCC_APB2Periph_GPIOB
#define KEY1_PORT    GPIOB
#define KEY1_PIN     GPIO_Pin_0
/*****************************************************/

/*****************************************************/
//KEY2
#define KEY2_PERIPH  RCC_APB2Periph_GPIOB
#define KEY2_PORT    GPIOB
#define KEY2_PIN     GPIO_Pin_1
/*****************************************************/

/*****************************************************/
//KEY3
#define KEY3_PERIPH  RCC_APB2Periph_GPIOB
#define KEY3_PORT    GPIOB
#define KEY3_PIN     GPIO_Pin_2
/*****************************************************/

/*****************************************************/
//KEY4
#define KEY4_PERIPH  RCC_APB2Periph_GPIOB
#define KEY4_PORT    GPIOB
#define KEY4_PIN     GPIO_Pin_3
/*****************************************************/

/*****************************************************/
//KEY5
#define KEY5_PERIPH  RCC_APB2Periph_GPIOB
#define KEY5_PORT    GPIOB
#define KEY5_PIN     GPIO_Pin_4
/*****************************************************/

/*****************************************************/
//KEY6
#define KEY6_PERIPH  RCC_APB2Periph_GPIOB
#define KEY6_PORT    GPIOB
#define KEY6_PIN     GPIO_Pin_5
/*****************************************************/


#define KEY1_sw(x) GPIO_WriteBit(KEY1_PORT, KEY1_PIN, (BitAction)(x))
#define KEY2_sw(x) GPIO_WriteBit(KEY2_PORT, KEY2_PIN, (BitAction)(x))
#define KEY3_sw(x) GPIO_WriteBit(KEY3_PORT, KEY3_PIN, (BitAction)(x))
#define KEY4_sw(x) GPIO_WriteBit(KEY4_PORT, KEY4_PIN, (BitAction)(x))
#define KEY5_sw(x) GPIO_WriteBit(KEY5_PORT, KEY5_PIN, (BitAction)(x))
#define KEY6_sw(x) GPIO_WriteBit(KEY6_PORT, KEY6_PIN, (BitAction)(x))

void key_init(
    uint8_t key1_state,
    uint8_t key2_state,
    uint8_t key3_state,
    uint8_t key4_state,
    uint8_t key5_state,
    uint8_t key6_state
);

uint8_t key_get_number();



#endif // !__key_h__
