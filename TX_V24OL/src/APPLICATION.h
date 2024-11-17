
#ifndef __APPLICATION__
#define __APPLICATION__

#include <Arduino.h>
#include <string.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SH110X.h"
#include "I2C_eeprom.h"
#include "74HC4067.h"
#include <nRF24L01.h>
#include <RF24.h>
#include <SimpleKalmanFilter.h>

#include "VERSION.h"
#include "APP_CONFIG.h"
#include "EROM\EROM.h"
#include "LCD\LCD.h"
#include "PERIPHERAL\PERIPHERAL.h"
#include "RF\RF.h"

/*==========================================
            DEFINE CONTROLS
==========================================*/
#define LED_ON    (digitalWrite(LED, HIGH))
#define LED_OF    (digitalWrite(LED, LOW))
#define BUZZER_ON (digitalWrite(BUZZER, LOW))
#define BUZZER_OF (digitalWrite(BUZZER, HIGH))
/*=========================================*/

/*==========================================
                ENUMS
==========================================*/
typedef enum
{
  FALSE,
  TRUE
}TrueFalse_enum;

typedef enum 
{
  Data_Control,
  Get_PPM,
  Get_OK,
  Save_PPM,
  Save_OK
}DataFeature_enum;

typedef enum 
{
  Send_Data_Control,
  Send_PPM
}SendFeature_enum;

typedef enum
{
  IDLE,
  Ponten_1,
  Ponten_2,
  Ponten_3,
  Switch_OF_1,
  Switch_OF_2,
  Switch_OF_3,
  Switch_OF_4,
  Switch_3Pos_1,
  Switch_3Pos_2,
}SwitchAndPoten_enum;

typedef enum 
{
  SW1_MIN,
  SW1_MID,
  SW1_MAX,
  
  SW2_MIN,
  SW2_MID,
  SW2_MAX,
  
  SW3_MIN,
  SW3_MID,
  SW3_MAX,

  SW4_MIN,
  SW4_MID,
  SW4_MAX,
}MenuSetLockThrottle;
/*=========================================*/

/*==========================================
          TYPEDEFS & STRUCTURES
==========================================*/

typedef struct 
{
  volatile uint16_t CH1;
  volatile uint16_t CH2;
  volatile uint16_t CH3;
  volatile uint16_t CH4;
  volatile uint16_t BienTro_1;
  volatile uint16_t BienTro_2;
  volatile uint16_t BienTro_3;
  volatile uint16_t SW_3POS_1;
  volatile uint16_t SW_3POS_2;
  volatile uint16_t SWONOF_1;
  volatile uint16_t SWONOF_2;
  volatile uint16_t SWONOF_3;
  volatile uint16_t SWONOF_4;
  volatile uint16_t Sensor;
  volatile uint16_t BT_UP;
  volatile uint16_t BT_DOWN;
  
  volatile uint8_t BT_OK;
  volatile uint8_t BT_BACK;
  volatile uint8_t CH1_Strim_1;
  volatile uint8_t CH1_Strim_2;
  volatile uint8_t CH2_Strim_1;
  volatile uint8_t CH2_Strim_2;
  volatile uint8_t CH3_Strim_1;
  volatile uint8_t CH3_Strim_2;
  volatile uint8_t CH4_Strim_1;
  volatile uint8_t CH4_Strim_2;
  uint8_t dummy[2];
}ReadData_typedef;

typedef struct
{
  volatile uint16_t MIN;
  volatile uint16_t MIDDLE;
  volatile uint16_t MAX;
  volatile uint8_t TRIP_MIN;
  volatile uint8_t TRIP_MAX;
  volatile uint8_t TRIP_PERCENT;
}ChannelLimit_typedef;

typedef struct 
{
  volatile uint8_t Reverse;
  volatile uint8_t Channel_Map;
  volatile uint16_t Trim_Value;
  volatile uint16_t PPM_Min;
  volatile uint16_t PPM_Max;
  volatile ChannelLimit_typedef Limit;  
}ChannelInfo_typedef;

typedef struct 
{
  ChannelInfo_typedef Channel_1;
  ChannelInfo_typedef Channel_2;
  ChannelInfo_typedef Channel_3;
  ChannelInfo_typedef Channel_4;
  ChannelInfo_typedef Channel_5;
  ChannelInfo_typedef Channel_6;
  ChannelInfo_typedef Channel_7;
  ChannelInfo_typedef Channel_8;
  ChannelInfo_typedef Channel_9;
  ChannelInfo_typedef Channel_10;
  uint8_t DUMMY_3[20];
}ChannelManage_typedef;

typedef struct 
{
  volatile uint16_t RX_INFO;
  volatile uint16_t TX_INFO;
  volatile uint16_t RF_Address_Write;
  volatile uint16_t RF_Address_Read;
  volatile uint8_t RF_Channel;
  volatile uint8_t RF_Next_Channel;  
  volatile uint8_t Check_Save_RX_INFO;
  uint8_t DUMMY_2[20];
}Address_typedef;

typedef struct 
{
  volatile uint8_t CheckSave;
  float TX_PIN_LOW;
  float RX_PIN_LOW;
  uint8_t Minute;
  uint8_t Second;
  uint8_t Throttle_Lock;
  uint8_t DUMMY_1[20];
  Address_typedef ADDRESS;
  ChannelManage_typedef CHANNEL;
  uint8_t DUMMY_4[20];
  volatile uint16_t CRC_CheckSum;
  uint8_t DUMMY_5[18];
  volatile uint8_t CheckMixing;
  volatile uint8_t Throttle_Lock_Value;
}ConfigMachine_typedef;

typedef struct 
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
}DataSendControl_typedef;

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

}SendPPM_typedef;

/*=========================================*/

/*==========================================
            VARIABLES EXTERN
==========================================*/
extern ReadData_typedef DATA_READ;
extern float PIN_TX;
extern float PIN_RX;

extern ConfigMachine_typedef _Virtual_Machine_;
extern ConfigMachine_typedef Machine;
extern ChannelManage_typedef LastChannelConfig;
extern ChannelManage_typedef NewChannelConfig;

extern DataSendControl_typedef RF_DATA_SEND;

extern uint8_t READ_CONFIG_MACHINE(ConfigMachine_typedef *MachineConfig);
extern uint8_t WRITE_CONFIG_MACHINE(ConfigMachine_typedef *MachineConfig);

/*=========================================*/

/*==========================================
              GLOBAL FUNCTION
==========================================*/
void APP_INIT(void);
void APP_MAIN(void);
void RESET_MACHINE_DEFAULT(void);
/*========================================*/

#endif /* __APPLICATION__ */

