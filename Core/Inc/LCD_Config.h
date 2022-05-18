
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H 

#define _LCD_USE_FREERTOS 0
#define _LCD_COLS         16
#define _LCD_ROWS         2

#define _LCD_RS_PORT      GPIOB
#define _LCD_RS_PIN       GPIO_PIN_9

#define _LCD_E_PORT       GPIOB
#define _LCD_E_PIN        GPIO_PIN_7

#define _LCD_RW_PORT      GPIOB
#define _LCD_RW_PIN       GPIO_PIN_8

#define _LCD_D4_PORT      GPIOB
#define _LCD_D4_PIN		  GPIO_PIN_6

#define _LCD_D5_PORT      GPIOB
#define _LCD_D5_PIN       GPIO_PIN_5

#define _LCD_D6_PORT      GPIOB
#define _LCD_D6_PIN       GPIO_PIN_4

#define _LCD_D7_PORT      GPIOB
#define _LCD_D7_PIN       GPIO_PIN_3

#endif

