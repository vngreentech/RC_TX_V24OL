
#ifndef __MAIN_APP__
#define __MAIN_APP__

/*======================================================
              Include Files
========================================================*/
#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <ArduinoUniqueID.h>
/*======================================================*/

/*======================================================
              Defines & Macros
========================================================*/
#define SCK   13
#define MOSI  11
#define MISO  12
#define CE    9
#define CSN   10
#define PINCONNECT  3
#define PinCH1 (A0)
#define PinCH2 (A1)
#define PinCH3 (A2)
#define PinCH4 (A3)
#define PinCH5 (A4)
#define PinCH6 (A5)
#define PinCH7 4
#define PinCH8 5
#define PinCH9 6
#define PinCH10 7
#define LED 2
#define VOLSENSOR (A6)

/* CONTROL */
#define LED_ON (digitalWrite(LED, HIGH))
#define LED_OFF (digitalWrite(LED, LOW))
#define READ_BIND (digitalRead(PINCONNECT))

/* Config RX Address */
#define RX_ADDRESS (39563) /* 0-65536 */
#define RF_CHANNEL (111)    /* 0-124 */

/* PPM value config */
#define PPM_MIN (550UL)
#define PPM_MAX (2400UL)

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
              GLOBAL VARIABLES DECLARATIONS
========================================================*/
/*======================================================*/

/*======================================================
              GLOBAL FUNCTION DECLARATIONS
========================================================*/
void APP_Init(void);
void APP_Main(void);
/*======================================================*/

#endif /* __MAIN_APP__ */


