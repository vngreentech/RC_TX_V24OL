
#include "APPLICATION.h"
#include "RF24.h"
#include "Adafruit_SPIDevice.h"

#ifdef DEBUG
HardwareSerial Serial1(DEBUG_RX,DEBUG_TX);
#endif /* DEBUG_TX */

float PIN_TX;
float PIN_RX;

ConfigMachine_typedef Machine;
ChannelManage_typedef LastChannelConfig;
ChannelManage_typedef NewChannelConfig;

/*===================================================================
                        LOCAL FUCTION
===================================================================*/
void RESET_MACHINE_DEFAULT(void)
{
  memset(&Machine,0,sizeof(Machine));

  Machine.CheckSave = 113;
  Machine.ADDRESS.RF_Address_Read = DEFAULT_ADD_READ;
  Machine.ADDRESS.RF_Address_Write = DEFAULT_ADD_WRITE;
  Machine.ADDRESS.RF_Channel = DEFAULT_CHANNEL;

  Machine.ADDRESS.RX_INFO=0;
  Machine.ADDRESS.TX_INFO = abs((uint16_t)HAL_GetUIDw0()) + abs((uint16_t)HAL_GetUIDw1()) + abs((uint16_t)HAL_GetUIDw2());

  strcpy((char*)Machine.DUMMY_1,LGO_GREEN);
  strcpy((char*)Machine.ADDRESS.DUMMY_2,LGO_TECH);
  strcpy((char*)Machine.CHANNEL.DUMMY_3,LGO_WEB);
  strcpy((char*)Machine.DUMMY_4,LGO_MADEINVN);
  strcpy((char*)Machine.DUMMY_5,LGO_NhanNguyen);

  Machine.CHANNEL.Channel_1.Channel_Map=1;
  Machine.CHANNEL.Channel_1.Limit.MIN=0;
  Machine.CHANNEL.Channel_1.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_1.Limit.MAX=4096;
  Machine.CHANNEL.Channel_1.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_1.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_1.Trim_Value = Machine.CHANNEL.Channel_1.Limit.MIDDLE;
  Machine.CHANNEL.Channel_1.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_1.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_1.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_2.Channel_Map=2;
  Machine.CHANNEL.Channel_2.Limit.MIN=0;
  Machine.CHANNEL.Channel_2.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_2.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_2.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_2.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_2.Trim_Value = Machine.CHANNEL.Channel_2.Limit.MIDDLE;
  Machine.CHANNEL.Channel_2.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_2.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_2.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_3.Channel_Map=3;
  Machine.CHANNEL.Channel_3.Limit.MIN=0;
  Machine.CHANNEL.Channel_3.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_3.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_3.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_3.PPM_Max=PPM_MAX;  
  Machine.CHANNEL.Channel_3.Trim_Value = Machine.CHANNEL.Channel_3.Limit.MIDDLE;
  Machine.CHANNEL.Channel_3.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_3.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_3.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_4.Channel_Map=4;
  Machine.CHANNEL.Channel_4.Limit.MIN=0;
  Machine.CHANNEL.Channel_4.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_4.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_4.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_4.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_4.Trim_Value = Machine.CHANNEL.Channel_4.Limit.MIDDLE;
  Machine.CHANNEL.Channel_4.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_4.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_4.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_5.Channel_Map=5;
  Machine.CHANNEL.Channel_5.Limit.MIN=0;
  Machine.CHANNEL.Channel_5.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_5.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_5.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_5.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_5.Trim_Value = Machine.CHANNEL.Channel_5.Limit.MIDDLE;
  Machine.CHANNEL.Channel_5.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_5.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_5.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_6.Channel_Map=6;
  Machine.CHANNEL.Channel_6.Limit.MIN=0;
  Machine.CHANNEL.Channel_6.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_6.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_6.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_6.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_6.Trim_Value = Machine.CHANNEL.Channel_6.Limit.MIDDLE;
  Machine.CHANNEL.Channel_6.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_6.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_6.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_7.Channel_Map=7;
  Machine.CHANNEL.Channel_7.Limit.MIN=0;
  Machine.CHANNEL.Channel_7.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_7.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_7.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_7.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_7.Trim_Value = Machine.CHANNEL.Channel_7.Limit.MIDDLE;
  Machine.CHANNEL.Channel_7.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_7.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_7.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_8.Channel_Map=8;
  Machine.CHANNEL.Channel_8.Limit.MIN=0;
  Machine.CHANNEL.Channel_8.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_8.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_8.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_8.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_8.Trim_Value = Machine.CHANNEL.Channel_8.Limit.MIDDLE;
  Machine.CHANNEL.Channel_8.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_8.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_8.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_9.Channel_Map=9;
  Machine.CHANNEL.Channel_9.Limit.MIN=0;
  Machine.CHANNEL.Channel_9.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_9.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_9.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_9.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_9.Trim_Value = Machine.CHANNEL.Channel_9.Limit.MIDDLE;
  Machine.CHANNEL.Channel_9.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_9.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_9.Limit.TRIP_PERCENT=100;

  Machine.CHANNEL.Channel_10.Channel_Map=10;
  Machine.CHANNEL.Channel_10.Limit.MIN=0;
  Machine.CHANNEL.Channel_10.Limit.MIDDLE=2048;
  Machine.CHANNEL.Channel_10.Limit.MAX=4096;  
  Machine.CHANNEL.Channel_10.PPM_Min=PPM_MIN;
  Machine.CHANNEL.Channel_10.PPM_Max=PPM_MAX;
  Machine.CHANNEL.Channel_10.Trim_Value = Machine.CHANNEL.Channel_10.Limit.MIDDLE;
  Machine.CHANNEL.Channel_10.Limit.TRIP_MIN=0;
  Machine.CHANNEL.Channel_10.Limit.TRIP_MAX=255;
  Machine.CHANNEL.Channel_10.Limit.TRIP_PERCENT=100;

  memcpy(&LastChannelConfig,&Machine.CHANNEL,sizeof(Machine.CHANNEL));
  memcpy(&NewChannelConfig,&Machine.CHANNEL,sizeof(Machine.CHANNEL));

}

static void GET_UID(void)
{
  if( (Machine.ADDRESS.RF_Address_Read) != ( abs((uint16_t)HAL_GetUIDw0())) ) /* Save Add Read, write, channel */
  {
    Machine.ADDRESS.RF_Address_Read = abs( (uint16_t)HAL_GetUIDw0() );

    if( (Machine.ADDRESS.RF_Address_Write) != (abs((uint16_t)HAL_GetUIDw1())) ) /* ADD write */
    {
      Machine.ADDRESS.RF_Address_Write = abs((uint16_t)HAL_GetUIDw1());
    }

    /* Get Channel */
    if( abs((uint16_t)HAL_GetUIDw2())>=123) Machine.ADDRESS.RF_Channel=123;
    else Machine.ADDRESS.RF_Channel=abs((uint16_t)HAL_GetUIDw2());

    // Serial1.print("ADD Read: "); Serial1.print( Machine.ADDRESS.RF_Address_Read );
    // Serial1.print(" - ADD Write: "); Serial1.print( Machine.ADDRESS.RF_Address_Write );
    // Serial1.print(" - ADD Channel: "); Serial1.println( Machine.ADDRESS.RF_Channel );

    WRITE_CONFIG_MACHINE(&Machine);

  }
}

/*==================================================================*/

/*===================================================================
                      GLOBAL FUCTION
===================================================================*/
void APP_INIT(void)
{
  #ifdef DEBUG
  Serial1.begin(115200);
  #endif /* DEBUG_TX */

  /* I2C Init */
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.setClock(_I2C_SPEED_);
  Wire.begin();

  EEPROM_INIT();
  PERIPHERAL_INIT();
  LCD_INIT();

  RF_INIT();

  // RESET_MACHINE_DEFAULT();
  // WRITE_CONFIG_MACHINE(&Machine);

  LED_ON;BUZZER_ON;
  delay(100);
  LED_OF;BUZZER_OF;
  delay(100);

  LED_ON;BUZZER_ON;
  delay(100);
  LED_OF;BUZZER_OF;

}

void APP_MAIN(void)
{
  PERIPHERAL_MAIN();
  LCD_MAIN();
  RF_MAIN();
}
/*==================================================================*/

