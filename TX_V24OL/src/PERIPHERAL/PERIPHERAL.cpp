
#include "PERIPHERAL.h"
#include "RF24.h"
#include "Adafruit_SPIDevice.h"

static SimpleKalmanFilter KALMAN_CH1(2, 2, 0.1);
static SimpleKalmanFilter KALMAN_CH2(2, 2, 0.1);
static SimpleKalmanFilter KALMAN_CH3(2, 2, 0.1);
static SimpleKalmanFilter KALMAN_CH4(2, 2, 0.1);
static SimpleKalmanFilter KALMAN_BT1(2, 2, 0.1);
static SimpleKalmanFilter KALMAN_BT2(2, 2, 0.1);
static SimpleKalmanFilter KALMAN_BT3(2, 2, 0.1);
static SimpleKalmanFilter KALMAN_SW1(2, 2, 0.1);
static SimpleKalmanFilter KALMAN_SW2(2, 2, 0.1);

HardwareTimer Timer_Read_Data(TIM3);
static uint8_t Flag_Read_Data;
static uint8_t Flag_Check_CountDown;
static uint8_t Flag_Check_Throttle;

static _74HC4067_typedef _74HC4067_;

ReadData_typedef DATA_READ;

void Read_Data(void)
{
  Flag_Read_Data=TRUE;
}

static void F_Read_Button(volatile uint8_t *DataRead, int F_ReadButton, \
                          volatile uint16_t *LimitMin, volatile uint16_t *LimitMax, volatile uint16_t *StrimValue, uint8_t UpDown)
{
  *DataRead = F_ReadButton;

  if( *DataRead==0 )
  {
    BUZZER_ON;

    if( strcmp((char*)Machine.DUMMY_4,(char*)LGO_MADEINVN)==0 )
    {if( UpDown==false ) 
    {
      if( *StrimValue > (*LimitMin) ) *StrimValue-=30;
      else *StrimValue = (*LimitMin);
    }
    else
    {
      if( *StrimValue < (*LimitMax) ) *StrimValue+=30;
      else *StrimValue = (*LimitMax);
    }}    
  }
}

static uint8_t F_SoftMap(volatile uint16_t *ReadChannel, volatile uint16_t LimitMin,volatile uint16_t LimitMiddle, volatile uint16_t LimitMax,\
                         volatile uint8_t *Trip_Min, volatile uint8_t *Trip_Max, volatile uint8_t *ConvertCheck)
{
  uint16_t DataConvert=*ReadChannel;
  DataConvert = constrain(DataConvert, LimitMin, LimitMax);

  if( strcmp((char*)Machine.ADDRESS.DUMMY_2,(char*)LGO_TECH)==0 )
  {if( strcmp((char*)Machine.DUMMY_4,(char*)LGO_MADEINVN)==0 )
  {
    if( DataConvert<=LimitMiddle ) DataConvert = map(DataConvert, LimitMin, LimitMiddle, *Trip_Min, 127);
    else DataConvert = map(DataConvert, LimitMiddle, LimitMax, 128, *Trip_Max); 
  }

  if( (*ConvertCheck)==true ) DataConvert = (uint8_t)(255-(uint8_t)DataConvert);}

  return (uint8_t)DataConvert;
}

static void Read_Button_Strim(void)
{
  F_Read_Button(&DATA_READ.CH1_Strim_1, digitalRead(CH1_BT1), &Machine.CHANNEL.Channel_1.Limit.MIN, \
                &Machine.CHANNEL.Channel_1.Limit.MAX, &NewChannelConfig.Channel_1.Trim_Value, false); /* CH1 - */
  F_Read_Button(&DATA_READ.CH1_Strim_2, digitalRead(CH1_BT2), &Machine.CHANNEL.Channel_1.Limit.MIN, \
                &Machine.CHANNEL.Channel_1.Limit.MAX, &NewChannelConfig.Channel_1.Trim_Value, true);  /* CH1 + */

  if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
  {F_Read_Button(&DATA_READ.CH2_Strim_1, digitalRead(CH2_BT1), &Machine.CHANNEL.Channel_2.Limit.MIN, \
                &Machine.CHANNEL.Channel_2.Limit.MAX, &NewChannelConfig.Channel_2.Trim_Value, false); /* CH2 - */
  F_Read_Button(&DATA_READ.CH2_Strim_2, digitalRead(CH2_BT2), &Machine.CHANNEL.Channel_2.Limit.MIN, \
                &Machine.CHANNEL.Channel_2.Limit.MAX, &NewChannelConfig.Channel_2.Trim_Value, true);  /* CH2 + */

  F_Read_Button(&DATA_READ.CH3_Strim_1, digitalRead(CH3_BT1), &Machine.CHANNEL.Channel_3.Limit.MIN, \
                &Machine.CHANNEL.Channel_3.Limit.MAX, &NewChannelConfig.Channel_3.Trim_Value, false); /* CH3 - */
  F_Read_Button(&DATA_READ.CH3_Strim_2, digitalRead(CH3_BT2), &Machine.CHANNEL.Channel_3.Limit.MIN, \
                &Machine.CHANNEL.Channel_3.Limit.MAX, &NewChannelConfig.Channel_3.Trim_Value, true);}  /* CH3 + */    

  F_Read_Button(&DATA_READ.CH4_Strim_1, digitalRead(CH4_BT1), &Machine.CHANNEL.Channel_4.Limit.MIN, \
                &Machine.CHANNEL.Channel_4.Limit.MAX, &NewChannelConfig.Channel_4.Trim_Value, false); /* CH4 - */
  F_Read_Button(&DATA_READ.CH4_Strim_2, digitalRead(CH4_BT2), &Machine.CHANNEL.Channel_4.Limit.MIN, \
                &Machine.CHANNEL.Channel_4.Limit.MAX, &NewChannelConfig.Channel_4.Trim_Value, true);  /* CH4 + */ 

  if( (NewChannelConfig.Channel_1.Trim_Value!=Machine.CHANNEL.Channel_1.Trim_Value) || \
      (NewChannelConfig.Channel_2.Trim_Value!=Machine.CHANNEL.Channel_2.Trim_Value) || \
      (NewChannelConfig.Channel_3.Trim_Value!=Machine.CHANNEL.Channel_3.Trim_Value) || \
      (NewChannelConfig.Channel_4.Trim_Value!=Machine.CHANNEL.Channel_4.Trim_Value) )                                           
  {
    memcpy(&Machine.CHANNEL,&NewChannelConfig,sizeof(NewChannelConfig));
    memcpy(&LastChannelConfig,&NewChannelConfig,sizeof(NewChannelConfig));

    WRITE_CONFIG_MACHINE(&Machine);
  }
                       
}

static void READ_ALL_DATA(void)
{
  if( strcmp((char*)Machine.DUMMY_5,(char*)LGO_NhanNguyen)==0 )
  {
    DATA_READ.CH1 = _74HC4067_ReadPin(&_74HC4067_, CH1_AILE);
    DATA_READ.CH1 = KALMAN_CH1.updateEstimate((float)DATA_READ.CH1);
    DATA_READ.CH2 = _74HC4067_ReadPin(&_74HC4067_, CH2_ELE);
    DATA_READ.CH2 = KALMAN_CH2.updateEstimate((float)DATA_READ.CH2);
  }

  if( Flag_Check_Throttle==true )
  {
    DATA_READ.CH3 = _74HC4067_ReadPin(&_74HC4067_, CH3_THRO);
    DATA_READ.CH3 = KALMAN_CH3.updateEstimate((float)DATA_READ.CH3);
  }
  else 
  {
    if( Machine.Throttle_Lock_Value==0 )/*MIN*/
    {
      DATA_READ.CH3 = Machine.CHANNEL.Channel_3.Limit.MIN;
    }
    else if( Machine.Throttle_Lock_Value==1 )/*MIDDLE*/
    {
      DATA_READ.CH3 = Machine.CHANNEL.Channel_3.Limit.MIDDLE;
    }
    else /* MAX */
    {
      DATA_READ.CH3 = Machine.CHANNEL.Channel_3.Limit.MAX;
    }
  }

  DATA_READ.CH4 = _74HC4067_ReadPin(&_74HC4067_, CH4_RUD);
  DATA_READ.CH4 = KALMAN_CH4.updateEstimate((float)DATA_READ.CH4);

  if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
  {
    DATA_READ.BienTro_1 = _74HC4067_ReadPin(&_74HC4067_, BIENTRO_1);
    DATA_READ.BienTro_1 = KALMAN_BT1.updateEstimate((float)DATA_READ.BienTro_1);
    DATA_READ.BienTro_2 = _74HC4067_ReadPin(&_74HC4067_, BIENTRO_2);
    DATA_READ.BienTro_2 = KALMAN_BT2.updateEstimate((float)DATA_READ.BienTro_2);
    DATA_READ.BienTro_3 = _74HC4067_ReadPin(&_74HC4067_, BIENTRO_3);
    DATA_READ.BienTro_3 = KALMAN_BT3.updateEstimate((float)DATA_READ.BienTro_3);

    DATA_READ.SW_3POS_1 = _74HC4067_ReadPin(&_74HC4067_, SW_3_POS_1);
    DATA_READ.SW_3POS_1 = KALMAN_SW1.updateEstimate((float)DATA_READ.SW_3POS_1);
    DATA_READ.SW_3POS_2 = _74HC4067_ReadPin(&_74HC4067_, SW_3_POS_2);
    DATA_READ.SW_3POS_2 = KALMAN_SW2.updateEstimate((float)DATA_READ.SW_3POS_2);

    DATA_READ.SWONOF_1 = _74HC4067_ReadPin(&_74HC4067_, SW_ONOF_1);
    DATA_READ.SWONOF_2 = _74HC4067_ReadPin(&_74HC4067_, SW_ONOF_2);
    DATA_READ.SWONOF_3 = _74HC4067_ReadPin(&_74HC4067_, SW_ONOF_3);
    DATA_READ.SWONOF_4 = _74HC4067_ReadPin(&_74HC4067_, SW_ONOF_4);
    DATA_READ.Sensor = _74HC4067_ReadPin(&_74HC4067_, VOL_SENSOR);
    DATA_READ.BT_UP = _74HC4067_ReadPin(&_74HC4067_, BUTTON_UP);
    DATA_READ.BT_DOWN = _74HC4067_ReadPin(&_74HC4067_, BUTTON_DOWN);
  }
 
  DATA_READ.BT_OK = digitalRead(BUTTON_OK);
  DATA_READ.BT_BACK = digitalRead(BUTTON_BACK);

  Read_Button_Strim();

  #ifdef PRINT_DATAREAD_DRAW
  char data[100];
  sprintf(data," \n====================\n Ch1: %d - ch2: %d - Ch3: %d - Ch4: %d - ", 
  DATA_READ.CH1, DATA_READ.CH2,\
  DATA_READ.CH3, DATA_READ.CH4);
  Serial1.print(data);                                                           

  sprintf(data,"tro1: %d - tro2: %d - tro3: %d - 3pos1: %d - 3pos2: %d \n", 
  DATA_READ.BienTro_1, DATA_READ.BienTro_2,\
  DATA_READ.BienTro_3, DATA_READ.SW_3POS_1, DATA_READ.SW_3POS_2);  
  Serial1.print(data);

  sprintf(data,"SW1: %d - SW2: %d - SW3: %d - SW4: %d - SS: %d - UP: %d - DOWN: %d - ", \
  DATA_READ.SWONOF_1, DATA_READ.SWONOF_2, DATA_READ.SWONOF_3, DATA_READ.SWONOF_4, \
  DATA_READ.Sensor, DATA_READ.BT_UP, DATA_READ.BT_DOWN);   
  Serial1.print(data);

  sprintf(data,"OK: %d - BACK: %d - 11: %d - 12: %d - 21: %d - 22: %d - 31: %d - 32: %d - 41: %d - 42: %d \n =============== \n", \
  DATA_READ.BT_OK, DATA_READ.BT_BACK, DATA_READ.CH1_Strim_1, DATA_READ.CH1_Strim_2, DATA_READ.CH2_Strim_1, DATA_READ.CH2_Strim_2, \
  DATA_READ.CH3_Strim_1, DATA_READ.CH3_Strim_2, DATA_READ.CH4_Strim_1, DATA_READ.CH4_Strim_2);     
  Serial1.print(data);
  
  delay(500);
  #endif

}

static void Convert_RF_Data_Send(void)
{
  static uint8_t READ_CH1, READ_CH2;

  READ_CH1=F_SoftMap(&DATA_READ.CH1,\
                      Machine.CHANNEL.Channel_1.Limit.MIN,Machine.CHANNEL.Channel_1.Trim_Value, Machine.CHANNEL.Channel_1.Limit.MAX, \
                      &Machine.CHANNEL.Channel_1.Limit.TRIP_MIN,&Machine.CHANNEL.Channel_1.Limit.TRIP_MAX, \
                      &Machine.CHANNEL.Channel_1.Reverse);

  READ_CH2=F_SoftMap(&DATA_READ.CH2,\
                      Machine.CHANNEL.Channel_2.Limit.MIN,Machine.CHANNEL.Channel_2.Trim_Value, Machine.CHANNEL.Channel_2.Limit.MAX, \
                      &Machine.CHANNEL.Channel_2.Limit.TRIP_MIN,&Machine.CHANNEL.Channel_2.Limit.TRIP_MAX, \
                      &Machine.CHANNEL.Channel_2.Reverse);

  if( Machine.CheckMixing==TRUE )
  {
    if( READ_CH2<(Machine.CHANNEL.Channel_2.Limit.MIDDLE) )
    {    
      if( ( ((READ_CH1)-(READ_CH2))+127 )<=Machine.CHANNEL.Channel_1.Limit.TRIP_MIN ) 
      { RF_DATA_SEND.CH1=Machine.CHANNEL.Channel_1.Limit.TRIP_MIN; }
      else if( ( ((READ_CH1)-(READ_CH2))+127 )>=Machine.CHANNEL.Channel_1.Limit.TRIP_MAX ) 
      { RF_DATA_SEND.CH1=Machine.CHANNEL.Channel_1.Limit.TRIP_MAX; }
      else RF_DATA_SEND.CH1 = ((READ_CH1)-(READ_CH2))+127;

      if( ( ((READ_CH1)+(READ_CH2))-127 )<=Machine.CHANNEL.Channel_2.Limit.TRIP_MIN ) 
      { RF_DATA_SEND.CH2=Machine.CHANNEL.Channel_2.Limit.TRIP_MIN; }
      else if(( ((READ_CH1)+(READ_CH2))-127 )>=Machine.CHANNEL.Channel_2.Limit.TRIP_MAX) 
      { RF_DATA_SEND.CH2=Machine.CHANNEL.Channel_2.Limit.TRIP_MAX; }
      else RF_DATA_SEND.CH2 = ( ((READ_CH1)+(READ_CH2))-127 );
    }

    if( READ_CH2>(Machine.CHANNEL.Channel_2.Limit.MIDDLE) )
    {
      READ_CH1 = map(READ_CH1,\
                      Machine.CHANNEL.Channel_1.Limit.TRIP_MIN, Machine.CHANNEL.Channel_1.Limit.TRIP_MAX,\
                      Machine.CHANNEL.Channel_1.Limit.TRIP_MAX, Machine.CHANNEL.Channel_1.Limit.TRIP_MIN);          

      if( ( ((READ_CH1)-(READ_CH2))+127 )<=Machine.CHANNEL.Channel_1.Limit.TRIP_MIN ) 
      { RF_DATA_SEND.CH1=Machine.CHANNEL.Channel_1.Limit.TRIP_MIN; }
      else if( ( ((READ_CH1)-(READ_CH2))+127 )>=Machine.CHANNEL.Channel_1.Limit.TRIP_MAX ) 
      { RF_DATA_SEND.CH1=Machine.CHANNEL.Channel_1.Limit.TRIP_MAX; }
      else RF_DATA_SEND.CH1 = (((READ_CH1)-(READ_CH2))+127);

      if((((READ_CH1)+(READ_CH2))-127)<=Machine.CHANNEL.Channel_2.Limit.TRIP_MIN) 
      { RF_DATA_SEND.CH2=Machine.CHANNEL.Channel_2.Limit.TRIP_MIN; }
      else if((((READ_CH1)+(READ_CH2))-127)>=Machine.CHANNEL.Channel_2.Limit.TRIP_MAX) 
      { RF_DATA_SEND.CH2=Machine.CHANNEL.Channel_2.Limit.TRIP_MAX; }
      else RF_DATA_SEND.CH2 = (((READ_CH1)+(READ_CH2))-127);
    }    
  }  
  else 
  {
    RF_DATA_SEND.CH1 = READ_CH1;
    RF_DATA_SEND.CH2 = READ_CH2;
  }                           

  if( strcmp((char*)Machine.DUMMY_4,(char*)LGO_MADEINVN)==0 )
  {
  RF_DATA_SEND.CH3=F_SoftMap(&DATA_READ.CH3,\
                             Machine.CHANNEL.Channel_3.Limit.MIN,Machine.CHANNEL.Channel_3.Trim_Value, Machine.CHANNEL.Channel_3.Limit.MAX, \
                             &Machine.CHANNEL.Channel_3.Limit.TRIP_MIN,&Machine.CHANNEL.Channel_3.Limit.TRIP_MAX, \
                             &Machine.CHANNEL.Channel_3.Reverse);                             

  RF_DATA_SEND.CH4=F_SoftMap(&DATA_READ.CH4,\
                             Machine.CHANNEL.Channel_4.Limit.MIN,Machine.CHANNEL.Channel_4.Trim_Value, Machine.CHANNEL.Channel_4.Limit.MAX, \
                             &Machine.CHANNEL.Channel_4.Limit.TRIP_MIN,&Machine.CHANNEL.Channel_4.Limit.TRIP_MAX, \
                             &Machine.CHANNEL.Channel_4.Reverse);     

  if( Machine.CHANNEL.Channel_5.Reverse==0 )
  {RF_DATA_SEND.CH5 = map(DATA_READ.BienTro_1,Machine.CHANNEL.Channel_5.Limit.MIN,Machine.CHANNEL.Channel_5.Limit.MAX,\
                          Machine.CHANNEL.Channel_5.Limit.TRIP_MIN,Machine.CHANNEL.Channel_5.Limit.TRIP_MAX);}
  else RF_DATA_SEND.CH5 = map(DATA_READ.BienTro_1,Machine.CHANNEL.Channel_5.Limit.MIN,Machine.CHANNEL.Channel_5.Limit.MAX,\
                          Machine.CHANNEL.Channel_5.Limit.TRIP_MAX,Machine.CHANNEL.Channel_5.Limit.TRIP_MIN);

  if( Machine.CHANNEL.Channel_6.Reverse==0 )
  {RF_DATA_SEND.CH6 = map(DATA_READ.BienTro_3,Machine.CHANNEL.Channel_6.Limit.MIN,Machine.CHANNEL.Channel_6.Limit.MAX,\
                          Machine.CHANNEL.Channel_6.Limit.TRIP_MIN,Machine.CHANNEL.Channel_6.Limit.TRIP_MAX);}
  else RF_DATA_SEND.CH6 = map(DATA_READ.BienTro_3,Machine.CHANNEL.Channel_6.Limit.MIN,Machine.CHANNEL.Channel_6.Limit.MAX,\
                          Machine.CHANNEL.Channel_6.Limit.TRIP_MAX,Machine.CHANNEL.Channel_6.Limit.TRIP_MIN);
  }

  if( Machine.CHANNEL.Channel_7.Reverse==0 )
  {
    if( (DATA_READ.SW_3POS_1>=(Machine.CHANNEL.Channel_7.Limit.MIN-20)) && (DATA_READ.SW_3POS_1<(Machine.CHANNEL.Channel_7.Limit.MIN+20)) )
    {
      RF_DATA_SEND.CH7=Machine.CHANNEL.Channel_7.Limit.TRIP_MIN;
    }
    else if( (DATA_READ.SW_3POS_1>=(Machine.CHANNEL.Channel_7.Limit.MIDDLE-20)) && (DATA_READ.SW_3POS_1<(Machine.CHANNEL.Channel_7.Limit.MIDDLE+20)) )
    {
      RF_DATA_SEND.CH7=128;
    }
    else if( (DATA_READ.SW_3POS_1>=(Machine.CHANNEL.Channel_7.Limit.MAX-20)) && (DATA_READ.SW_3POS_1<(Machine.CHANNEL.Channel_7.Limit.MAX+20)) )
    {
      RF_DATA_SEND.CH7=Machine.CHANNEL.Channel_7.Limit.TRIP_MAX;
    }
    else {;;}    
  }
  else 
  {
    if( (DATA_READ.SW_3POS_1>=(Machine.CHANNEL.Channel_7.Limit.MIN-20)) && (DATA_READ.SW_3POS_1<(Machine.CHANNEL.Channel_7.Limit.MIN+20)) )
    {
      RF_DATA_SEND.CH7=Machine.CHANNEL.Channel_7.Limit.TRIP_MAX;
    }
    else if( (DATA_READ.SW_3POS_1>=(Machine.CHANNEL.Channel_7.Limit.MIDDLE-20)) && (DATA_READ.SW_3POS_1<(Machine.CHANNEL.Channel_7.Limit.MIDDLE+20)) )
    {
      RF_DATA_SEND.CH7=128;
    }
    else if( (DATA_READ.SW_3POS_1>=(Machine.CHANNEL.Channel_7.Limit.MAX-20)) && (DATA_READ.SW_3POS_1<(Machine.CHANNEL.Channel_7.Limit.MAX+20)) )
    {
      RF_DATA_SEND.CH7=Machine.CHANNEL.Channel_7.Limit.TRIP_MIN;
    }
    else {;;}        
  }

  if( Machine.CHANNEL.Channel_8.Reverse==0 )
  {
    if( (DATA_READ.SW_3POS_2>=(Machine.CHANNEL.Channel_8.Limit.MIN-20)) && (DATA_READ.SW_3POS_2<(Machine.CHANNEL.Channel_8.Limit.MIN+20)) )
    {
      RF_DATA_SEND.CH8=Machine.CHANNEL.Channel_8.Limit.TRIP_MIN;
    }
    else if( (DATA_READ.SW_3POS_2>=(Machine.CHANNEL.Channel_8.Limit.MIDDLE-20)) && (DATA_READ.SW_3POS_2<(Machine.CHANNEL.Channel_8.Limit.MIDDLE+20)) )
    {
      RF_DATA_SEND.CH8=128;
    }
    else if( (DATA_READ.SW_3POS_2>=(Machine.CHANNEL.Channel_8.Limit.MAX-20)) && (DATA_READ.SW_3POS_2<(Machine.CHANNEL.Channel_8.Limit.MAX+20)) )
    {
      RF_DATA_SEND.CH8=Machine.CHANNEL.Channel_8.Limit.TRIP_MAX;
    }
    else {;;}    
  }
  else 
  {
    if( (DATA_READ.SW_3POS_2>=(Machine.CHANNEL.Channel_8.Limit.MIN-20)) && (DATA_READ.SW_3POS_2<(Machine.CHANNEL.Channel_8.Limit.MIN+20)) )
    {
      RF_DATA_SEND.CH8=Machine.CHANNEL.Channel_8.Limit.TRIP_MAX;
    }
    else if( (DATA_READ.SW_3POS_2>=(Machine.CHANNEL.Channel_8.Limit.MIDDLE-20)) && (DATA_READ.SW_3POS_2<(Machine.CHANNEL.Channel_8.Limit.MIDDLE+20)) )
    {
      RF_DATA_SEND.CH8=128;
    }
    else if( (DATA_READ.SW_3POS_2>=(Machine.CHANNEL.Channel_8.Limit.MAX-20)) && (DATA_READ.SW_3POS_2<(Machine.CHANNEL.Channel_8.Limit.MAX+20)) )
    {
      RF_DATA_SEND.CH8=Machine.CHANNEL.Channel_8.Limit.TRIP_MIN;
    }
    else {;;}        
  }  

  if( Machine.CHANNEL.Channel_9.Reverse==0 )
  {
    if( DATA_READ.SWONOF_1>=2000 ) RF_DATA_SEND.CH9=Machine.CHANNEL.Channel_9.Limit.TRIP_MAX;
    else RF_DATA_SEND.CH9=Machine.CHANNEL.Channel_9.Limit.TRIP_MIN;
  }
  else 
  {
    if( DATA_READ.SWONOF_1>=2000 ) RF_DATA_SEND.CH9=Machine.CHANNEL.Channel_9.Limit.TRIP_MIN;
    else RF_DATA_SEND.CH9=Machine.CHANNEL.Channel_9.Limit.TRIP_MAX;
  }
  
  if( Machine.CHANNEL.Channel_10.Reverse==0 )
  {
    if( DATA_READ.SWONOF_4>=2000 ) RF_DATA_SEND.CH10=Machine.CHANNEL.Channel_10.Limit.TRIP_MAX;
    else RF_DATA_SEND.CH10=Machine.CHANNEL.Channel_10.Limit.TRIP_MIN;
  }
  else 
  {
    if( DATA_READ.SWONOF_4>=2000 ) RF_DATA_SEND.CH10=Machine.CHANNEL.Channel_10.Limit.TRIP_MIN;
    else RF_DATA_SEND.CH10=Machine.CHANNEL.Channel_10.Limit.TRIP_MAX;
  }
  

  #ifdef PRINT_DATA_SEND_RF
  char data[100];
  sprintf(data,"ch1: %d - ch2: %d - ch3: %d - ch4: %d - ch5: %d - ch6: %d - ch7: %d - ch8: %d - ch9: %d - ch10: %d\n",\
          RF_DATA_SEND.CH1,RF_DATA_SEND.CH2,RF_DATA_SEND.CH3,RF_DATA_SEND.CH4,RF_DATA_SEND.CH5,RF_DATA_SEND.CH6,\
          RF_DATA_SEND.CH7,RF_DATA_SEND.CH8,RF_DATA_SEND.CH9,RF_DATA_SEND.CH10);
  Serial1.print(data);
  #endif /* PRINT_DATA_SEND_RF */
}

static void Check_PIN_TXRX(void)
{
  if( (PIN_TX<=Machine.TX_PIN_LOW && PIN_TX>1) or \
      (PIN_RX<=Machine.RX_PIN_LOW && PIN_RX>1) )
  {
    if( (PIN_RX<=Machine.RX_PIN_LOW && PIN_RX>1) && (RF_Check_Connect==TRUE) )
    {
      BUZZER_ON;
      LED_ON;
    }
    else 
    {
      BUZZER_OF;
      LED_OF;
    }

    if( (PIN_TX<=Machine.TX_PIN_LOW && PIN_TX>1) )
    {
      BUZZER_ON;
      LED_ON;
    }
  }
  else 
  {
    if( Flag_Check_CountDown==false )
    {
      BUZZER_OF;
    }
    
    if(RF_Check_Connect==true)
    {
      LED_OF;
    }
  }
}

static void Check_Throttle(void)
{
  if( strcmp((char*)Machine.DUMMY_5,(char*)LGO_NhanNguyen)==0 )
  {if( Machine.Throttle_Lock==1 )
  {
    (DATA_READ.SWONOF_1<2000)?Flag_Check_Throttle=TRUE:Flag_Check_Throttle=FALSE;
  }
  else if( Machine.Throttle_Lock==2 )
  {
    (DATA_READ.SWONOF_2<2000)?Flag_Check_Throttle=TRUE:Flag_Check_Throttle=FALSE;
  }
  else if( Machine.Throttle_Lock==3 )
  {
    (DATA_READ.SWONOF_3<2000)?Flag_Check_Throttle=TRUE:Flag_Check_Throttle=FALSE;
  }
  else if( Machine.Throttle_Lock==4 )
  {
    (DATA_READ.SWONOF_4<2000)?Flag_Check_Throttle=TRUE:Flag_Check_Throttle=FALSE;
  }
  else {Flag_Check_Throttle=TRUE;}}
}

float VoltageTX(void)
{
  float adc_voltage  = float( float(DATA_READ.Sensor * (VOL_INPUT_TX)) / 4095.0); 
  float VOL = float( adc_voltage / float(7500.0/ float(30000.0+7500.0)) ) ; 
  
  return VOL;
}

float VoltageRX(void)
{
  float adc_voltage  = float( float(RF_ReadData * (VOL_INPUT_RX)) / 1024.0); 
  float VOL = float( adc_voltage / float(7500.0/float(30000.0+7500.0)) ) ; 
  
  return VOL;
}

void Check_CountDown(uint8_t StartState)
{
  static uint32_t CountDown=0;
  static uint32_t Tick_time=0;  
  static uint16_t LastMinute=0;
  static uint16_t LastSecond=0;
  static uint32_t ElapsedTime=0;
  static uint32_t Remain=0;

  if(StartState==1)
  {
    CountDown=((Machine.Minute*60)+Machine.Second);
    LastMinute=Machine.Minute;
    LastSecond=Machine.Second;

    Tick_time=millis();
    ElapsedTime = (uint32_t)((millis()-Tick_time)/1000);
    Remain = CountDown - ElapsedTime;
  }
  else if(StartState==2) 
  {
    if(Remain>0) 
    {
      Machine.Minute = Remain/60;
      Machine.Second = Remain%60;

      ElapsedTime = (uint32_t)((millis()-Tick_time)/1000);
      Remain = CountDown - ElapsedTime;

      Flag_Check_CountDown=true;
    }
    else 
    {
      Remain=0;
      Machine.Minute = 0;
      Machine.Second = 0;

      BUZZER_ON;
      LED_ON;
    }
  }
  else 
  {
    if( Flag_Check_CountDown==true )
    {
      Machine.Minute = LastMinute;
      Machine.Second = LastSecond;
      Flag_Check_CountDown=false;
    }
  }
}

void PERIPHERAL_INIT(void)
{
  _74HC4067_.Bit_Resolution=_12_bit;
  _74HC4067_.PIN_SIG=SIG;
  _74HC4067_.PIN_S0=S0;
  _74HC4067_.PIN_S1=S1;
  _74HC4067_.PIN_S2=S2;
  _74HC4067_.PIN_S3=S3;
  _74HC4067_.PIN_EN=0;
  _74HC4067_Init(&_74HC4067_);  

  pinMode(PA2, INPUT);
  randomSeed(analogRead(PA2));

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(BUTTON_OK,INPUT);
  pinMode(BUTTON_BACK,INPUT);

  pinMode(CH1_BT1,INPUT);
  pinMode(CH1_BT2,INPUT);
  pinMode(CH2_BT1,INPUT);
  pinMode(CH2_BT2,INPUT);
  pinMode(CH3_BT1,INPUT);
  pinMode(CH3_BT2,INPUT);
  pinMode(CH4_BT1,INPUT);
  pinMode(CH4_BT2,INPUT);

  if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
  {
    Timer_Read_Data.pause();
    Timer_Read_Data.setOverflow((1000*10), MICROSEC_FORMAT); /* 10ms */
    Timer_Read_Data.attachInterrupt(Read_Data);
    Timer_Read_Data.resume();    
  }
}

void PERIPHERAL_MAIN(void)
{
  if( Flag_Read_Data==TRUE )
  {
    READ_ALL_DATA();
    Convert_RF_Data_Send();

    PIN_TX = VoltageTX();
    PIN_RX = VoltageRX();

    Flag_Read_Data=FALSE;
  }

  Check_PIN_TXRX();
  Check_Throttle();

}




