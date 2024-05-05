
#ifndef __LCD__
#define __LCD__

#include "APPLICATION.h"

#define SCREEN_WIDTH  (128UL) // OLED display width, in pixels
#define SCREEN_HEIGHT (64UL)  // OLED display height, in pixels
#define OLED_RESET    (-1) 

void LCD_INIT(void);
void LCD_MAIN(void);

void ERROR_RF24(void);
void ERROR_EEPROM(void);

#endif /* __LCD__ */
