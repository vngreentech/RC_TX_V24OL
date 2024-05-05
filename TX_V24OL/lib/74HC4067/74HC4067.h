
#ifndef __74HC4067__
#define __74HC4067__

#include "Arduino.h"
#include "stdint.h"
#include "RF24.h"

#define SETRESOLUTION(BitResolution)  (analogReadResolution(BitResolution))
#define ANALOGREAD(PIN)               (analogRead(PIN))
#define WRITEPIN(PIN,VALUE)           (digitalWrite(PIN,VALUE))
#define SETPINOUTPUT(PIN)             (pinMode(PIN, OUTPUT))
#define SETPININPUT(PIN)              (pinMode(PIN, INPUT))

typedef enum
{
  _10_bit=10,
  _12_bit=12,
}BitResolution_enum;

typedef enum
{
  _74HC4067_Disable,
  _74HC4067_Enable,
}_74hc4067_enable_enum;

typedef enum
{
  PIN_0,
  PIN_1,
  PIN_2,
  PIN_3,
  PIN_4,
  PIN_5,
  PIN_6,
  PIN_7,
  PIN_8,
  PIN_9,
  PIN_10,
  PIN_11,
  PIN_12,
  PIN_13,
  PIN_14,
  PIN_15,
}_74HC4067_PIN_enum;

typedef struct
{
  uint32_t PIN_SIG;
  uint32_t PIN_EN;
  uint32_t PIN_S0;
  uint32_t PIN_S1;
  uint32_t PIN_S2;
  uint32_t PIN_S3;
  BitResolution_enum Bit_Resolution;
}_74HC4067_typedef;

void _74HC4067_Init(_74HC4067_typedef *_74HC4067_Object);
uint16_t _74HC4067_ReadPin(_74HC4067_typedef *_74HC4067_Object, _74HC4067_PIN_enum PIN_READ);
void _74HC4067_ENABLE(_74HC4067_typedef *_74HC4067_Object, _74hc4067_enable_enum Select);

#endif /* __74HC4067__ */

