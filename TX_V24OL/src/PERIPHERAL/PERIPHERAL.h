
#ifndef __PERIPHERAL__
#define __PERIPHERAL__

#include "APPLICATION.h"
#include "RF24.h"
#include "Adafruit_SPIDevice.h"

void PERIPHERAL_INIT(void);
void PERIPHERAL_MAIN(void);
void Check_CountDown(uint8_t StartState);

#endif /* __PERIPHERAL__ */
