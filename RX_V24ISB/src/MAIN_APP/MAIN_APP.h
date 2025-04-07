
#ifndef __MAIN_APP__
#define __MAIN_APP__

#include <Arduino.h>
#include <string.h>
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include "APP_CONFIG.h"
#include <nRF24L01.h>
#include <RF24.h>

/*======================================================
              Defines & Macros
========================================================*/

/* CONTROL */
#define LED_ON    (digitalWrite(PIN_LED, HIGH))
#define LED_OFF   (digitalWrite(PIN_LED, LOW))
#define READ_BIND (digitalRead(PIN_BIND))

/* Config RX Address */
#define RX_ADDRESS (39563) /* 0-65536 */
#define RF_CHANNEL (111)    /* 0-124 */

/* PPM value config */
#define PPM_MIN (550UL)
#define PPM_MAX (2400UL)

#define TIME_CHECK_CONNECT (500UL)

// #define SBUS
#define IBUS

/* Config SBUS */
#ifdef SBUS
#define SBUS_HEADER   (0x0F)
#define SBUS_FOOTER   (0x00)
#define SBUS_BAUDRATE (100000)
#define SBUS_SERIAL_CONFIG (SERIAL_8E2)
#define SBUS_INTERVAL (18)

// #define SBUS_MIN (172)
// #define SBUS_MID (991)
// #define SBUS_MAX (1811)

#define SBUS_MIN (0)
#define SBUS_MID (1024)
#define SBUS_MAX (2047)
#endif /* SBUS */

/* Config IBUS */
#ifdef IBUS
#define IBUS_HEADER_1   (0x20)
#define IBUS_HEADER_2   (0x40)
#define IBUS_FOOTER   (0x00)
#define IBUS_BAUDRATE (115200)
#define IBUS_SERIAL_CONFIG (SERIAL_8N1)
#define IBUS_INTERVAL (10)

#define IBUS_MIN (1000)
#define IBUS_MID (1500)
#define IBUS_MAX (2000)
#endif /* IBUS */

/*======================================================*/

/*======================================================
              ENUMS
========================================================*/
typedef enum 
{
  Data_Control,
  Get_PPM,
  Get_OK,
  Save_PPM,
  Save_OK
}DataFeature_enum;
/*======================================================*/

/*======================================================
              TYPEDEFS & STRUCTURES
========================================================*/
typedef struct ChannelData
{
  volatile uint8_t Feature;
  volatile uint8_t CH1;
  volatile uint8_t CH2;
  volatile uint8_t CH3;
  volatile uint8_t CH4;
  volatile uint8_t CH5;
  volatile uint8_t CH6;
  volatile uint8_t CH7;
  volatile uint8_t CH8;
  volatile uint8_t CH9;
  volatile uint8_t CH10;
  volatile uint8_t Count_Connect;
  volatile uint8_t dummy[3];
}ChannelData_Typedef;

typedef struct 
{
  volatile uint16_t RX_INFO;
  volatile uint16_t TX_INFO;
  volatile uint16_t RF_Address_Write;
  volatile uint16_t RF_Address_Read;
  volatile uint8_t RF_Channel;
  volatile uint8_t RF_Next_Channel;  
  volatile uint8_t Check_Save_RX_INFO;
  uint8_t dummy[20];

}Address_typedef;

typedef struct 
{
  volatile uint8_t Feature;
  uint8_t dummy[3];

  volatile uint8_t CH1_PPM_Min;
  volatile uint8_t CH1_PPM_Max;
  volatile uint8_t CH2_PPM_Min;
  volatile uint8_t CH2_PPM_Max;
  volatile uint8_t CH3_PPM_Min;
  volatile uint8_t CH3_PPM_Max;
  volatile uint8_t CH4_PPM_Min;
  volatile uint8_t CH4_PPM_Max;
  volatile uint8_t CH5_PPM_Min;
  volatile uint8_t CH5_PPM_Max;

  volatile uint8_t CH6_PPM_Min;
  volatile uint8_t CH6_PPM_Max;
  volatile uint8_t CH7_PPM_Min;
  volatile uint8_t CH7_PPM_Max;
  volatile uint8_t CH8_PPM_Min;
  volatile uint8_t CH8_PPM_Max;
  volatile uint8_t CH9_PPM_Min;
  volatile uint8_t CH9_PPM_Max;
  volatile uint8_t CH10_PPM_Min;
  volatile uint8_t CH10_PPM_Max;      

}PPM_READ_typedef;

typedef struct 
{
  volatile uint16_t CH1_PPM_Min;
  volatile uint16_t CH1_PPM_Max;
  volatile uint16_t CH2_PPM_Min;
  volatile uint16_t CH2_PPM_Max;
  volatile uint16_t CH3_PPM_Min;
  volatile uint16_t CH3_PPM_Max;
  volatile uint16_t CH4_PPM_Min;
  volatile uint16_t CH4_PPM_Max;
  volatile uint16_t CH5_PPM_Min;
  volatile uint16_t CH5_PPM_Max;

  volatile uint16_t CH6_PPM_Min;
  volatile uint16_t CH6_PPM_Max;
  volatile uint16_t CH7_PPM_Min;
  volatile uint16_t CH7_PPM_Max;
  volatile uint16_t CH8_PPM_Min;
  volatile uint16_t CH8_PPM_Max;
  volatile uint16_t CH9_PPM_Min;
  volatile uint16_t CH9_PPM_Max;
  volatile uint16_t CH10_PPM_Min;
  volatile uint16_t CH10_PPM_Max;      

}PPM_SAVE_typedef;

typedef struct
{
  volatile uint8_t Check_config;
  Address_typedef ADDRESS;
  PPM_SAVE_typedef PPM_CONFIG;
}ConfigMachine_typedef;
/*======================================================*/

/*======================================================
              GLOBAL FUNCTION DECLARATIONS
========================================================*/
void MAIN_Init(void);
void MAIN_APP(void);
/*======================================================*/

#endif /* __MAIN_APP__ */
