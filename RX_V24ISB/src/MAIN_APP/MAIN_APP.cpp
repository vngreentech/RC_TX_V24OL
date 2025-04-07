
#include "MAIN_APP.h"

HardwareSerial BUS_Serial(DEBUG_RX, DEBUG_TX);

static uint8_t Feature=Data_Control;
static ConfigMachine_typedef CONFIG_MACHINE;
static Address_typedef AddressRead;
static ChannelData_Typedef DataRead;
static uint8_t BIND=false;
static bool lost_connection=false;
static uint32_t BusTimeCheck=0;

RF24 radio(CE, CSN);

static uint8_t reverseBits(uint8_t b) 
{
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;

  return b;
}

static void invertSBUS(uint8_t *buffer, size_t length) 
{
  for (size_t i = 0; i < length; i++) 
  {
    buffer[i] = reverseBits(buffer[i]);
  }
}

static void RESET_DEFAULT(void)
{
  memset(&CONFIG_MACHINE,0,sizeof(CONFIG_MACHINE));

  CONFIG_MACHINE.ADDRESS.RF_Address_Write=11111;
  CONFIG_MACHINE.ADDRESS.RF_Address_Read=33444;
  CONFIG_MACHINE.ADDRESS.RF_Channel=111;

  CONFIG_MACHINE.PPM_CONFIG.CH1_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH1_PPM_Max = PPM_MAX;
  CONFIG_MACHINE.PPM_CONFIG.CH2_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH2_PPM_Max = PPM_MAX;
  CONFIG_MACHINE.PPM_CONFIG.CH3_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH3_PPM_Max = PPM_MAX;
  CONFIG_MACHINE.PPM_CONFIG.CH4_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH4_PPM_Max = PPM_MAX;
  CONFIG_MACHINE.PPM_CONFIG.CH5_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH5_PPM_Max = PPM_MAX;

  CONFIG_MACHINE.PPM_CONFIG.CH6_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH6_PPM_Max = PPM_MAX;
  CONFIG_MACHINE.PPM_CONFIG.CH7_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH7_PPM_Max = PPM_MAX;
  CONFIG_MACHINE.PPM_CONFIG.CH8_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH8_PPM_Max = PPM_MAX;
  CONFIG_MACHINE.PPM_CONFIG.CH9_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH9_PPM_Max = PPM_MAX;
  CONFIG_MACHINE.PPM_CONFIG.CH10_PPM_Min = PPM_MIN;
  CONFIG_MACHINE.PPM_CONFIG.CH10_PPM_Max = PPM_MAX;    

  CONFIG_MACHINE.Check_config=113;

  EEPROM.put(0, CONFIG_MACHINE);
}

static void LED_POWERON(void)
{
  for(int i=0; i<=2; i++)
  {
    LED_ON;
    delay(200);
    LED_OFF;
    delay(200);
  }
}

static void F_SAVE_CONFIG_MACHINE(ConfigMachine_typedef *ConfigSave)
{
  EEPROM.put(0, *ConfigSave);
  delay(1);

  // char data[200];
  // sprintf(data,"EEP Read CH6_Min: %d - CH6_Max: %d - CH7_Min: %d - CH7_Max: %d - CH8_Min: %d - CH8_Max: %d - CH9_Min: %d - CH9_Max: %d \n",\
  //         ADDRESS.CH6_PPM_Min, ADDRESS.CH6_PPM_Max, ADDRESS.CH7_PPM_Min, ADDRESS.CH7_PPM_Max,\
  //         ADDRESS.CH8_PPM_Min, ADDRESS.CH8_PPM_Max, ADDRESS.CH9_PPM_Min, ADDRESS.CH9_PPM_Max);
  // Serial.print(data);   
}

static void F_READ_CONFIG_MACHINE(ConfigMachine_typedef *ConfigRead)
{
  if( LGo_TECH == "TECHNOLOGY_d2" )
  {
    EEPROM.get(0, *ConfigRead);
  }
  
  delay(1);

  // Debug.print("TX info: "); Debug.print(ConfigRead->ADDRESS.TX_INFO);
  // Debug.print(" - RX info: "); Debug.print(ConfigRead->ADDRESS.RX_INFO);

  // Debug.print(" - Channel: "); Debug.print(ConfigRead->ADDRESS.RF_Channel);
  // Debug.print(" - Read: "); Debug.print(ConfigRead->ADDRESS.RF_Address_Read);
  // Debug.print(" - Write: "); Debug.println(ConfigRead->ADDRESS.RF_Address_Write);

  // char data[200];
  // sprintf(data,"EEP Read CH6_Min: %d - CH6_Max: %d - CH7_Min: %d - CH7_Max: %d - CH8_Min: %d - CH8_Max: %d - CH9_Min: %d - CH9_Max: %d \n",\
  //         ADDRESS.CH6_PPM_Min, ADDRESS.CH6_PPM_Max, ADDRESS.CH7_PPM_Min, ADDRESS.CH7_PPM_Max,\
  //         ADDRESS.CH8_PPM_Min, ADDRESS.CH8_PPM_Max, ADDRESS.CH9_PPM_Min, ADDRESS.CH9_PPM_Max);
  // Serial.print(data);  
}

static void F_RF_READ(void)
{
  static uint32_t Tick_Disconnect=0;
  static ChannelData_Typedef DataRead_Virtual;

  static uint8_t Last_Count_Connect=0;

  if( Feature==Data_Control )  
  {
    if( LGo_WEB == "www.vngreentech.com_d3" )
    {
      radio.startListening();
    }
    
    if(radio.available()>0)     
    {
      radio.read(&DataRead_Virtual, sizeof(DataRead_Virtual));
      if( (DataRead_Virtual.CH1>=0 && DataRead_Virtual.CH1<=255)&&\
          (DataRead_Virtual.CH2>=0 && DataRead_Virtual.CH2<=255)&&\
          (DataRead_Virtual.CH3>=0 && DataRead_Virtual.CH3<=255)&&\
          (DataRead_Virtual.CH4>=0 && DataRead_Virtual.CH4<=255)&&\
          (DataRead_Virtual.CH5>=0 && DataRead_Virtual.CH5<=255)&&\
          (DataRead_Virtual.CH6>=0 && DataRead_Virtual.CH6<=255)&&\
          (DataRead_Virtual.CH7>=0 && DataRead_Virtual.CH7<=255)&&\
          (DataRead_Virtual.CH8>=0 && DataRead_Virtual.CH8<=255)&&\
          (DataRead_Virtual.CH9>=0 && DataRead_Virtual.CH9<=255)&&\
          (DataRead_Virtual.CH10>=0 && DataRead_Virtual.CH10<=255)
        )
      {
        if( LGo_NhanNguyen == "NhanNguyen_d5" )
        {
          DataRead = DataRead_Virtual;
          Feature = DataRead.Feature;
        }
      }
    }

    if( DataRead.Count_Connect > Last_Count_Connect )
    {
      Last_Count_Connect = DataRead.Count_Connect;

      lost_connection=false;
      LED_OFF;

      Tick_Disconnect=millis();
    }
    else if( DataRead.Count_Connect < Last_Count_Connect ) 
    {
      Last_Count_Connect = DataRead.Count_Connect;

      lost_connection=false;
      LED_OFF;

      Tick_Disconnect=millis();      
    }    
    else //Lost connect
    {
      if( (uint32_t)(millis() - Tick_Disconnect) >= TIME_CHECK_CONNECT ) // >1s -> Led on
      {
        lost_connection=true;
        LED_ON;
      }
    }
  }

  // Serial.print("Last Count connect: "); Serial.print(Last_Count_Connect);
  // Serial.print(" - Count connect: "); Serial.print(DataRead.Count_Connect);
  // Debug.print(" - CH1: "); Debug.print(DataRead.CH1);
  // Debug.print(" - CH2: "); Debug.print(DataRead.CH2);
  // Debug.print(" - CH3: "); Debug.print(DataRead.CH3);
  // Debug.print(" - CH4: "); Debug.print(DataRead.CH4);
  // Debug.print(" - CH5: "); Debug.print(DataRead.CH5);
  // Debug.print(" - CH6: "); Debug.print(DataRead.CH6);
  // Debug.print(" - CH7: "); Debug.print(DataRead.CH7);
  // Debug.print(" - CH8: "); Debug.print(DataRead.CH8);
  // Debug.print(" - CH9: "); Debug.print(DataRead.CH9);
  // Debug.print(" - CH10: "); Debug.println(DataRead.CH10);
  // Debug.println();

  delay(1);
}

#ifdef SBUS
static void F_Send_SBUS(ChannelData_Typedef *rxData) 
{
  uint8_t sbusPacket[25] = {SBUS_HEADER};
  uint16_t channels[16];

  if (!lost_connection) 
  {
    channels[0]  = map(rxData->CH1, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[1]  = map(rxData->CH2, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[2]  = map(rxData->CH3, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[3]  = map(rxData->CH4, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[4]  = map(rxData->CH5, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[5]  = map(rxData->CH6, 0, 255, SBUS_MIN, SBUS_MAX); 
    channels[6]  = map(rxData->CH7, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[7]  = map(rxData->CH8, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[8]  = map(rxData->CH9, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[9]  = map(rxData->CH10, 0, 255, SBUS_MIN, SBUS_MAX);
    channels[10]  = SBUS_MID;
    channels[11]  = SBUS_MID;
    channels[12]  = SBUS_MID;
    channels[13]  = SBUS_MID;
    channels[14]  = SBUS_MID;
    channels[15]  = SBUS_MID;
  } 
  else //lost connect
  {
    for (int i = 0; i < 16; i++) 
    {
      channels[i] = SBUS_MID;
    }
  }

  sbusPacket[0] = SBUS_HEADER;

  sbusPacket[1]  = (channels[0] & 0x07FF);
  sbusPacket[2]  = ((channels[0] >> 8) | (channels[1] << 3));
  sbusPacket[3]  = ((channels[1] >> 5) | (channels[2] << 6));
  sbusPacket[4]  = (channels[2] >> 2);
  sbusPacket[5]  = ((channels[2] >> 10) | (channels[3] << 1));
  sbusPacket[6]  = ((channels[3] >> 7) | (channels[4] << 4));
  sbusPacket[7]  = ((channels[4] >> 4) | (channels[5] << 7));
  sbusPacket[8]  = (channels[5] >> 1);
  sbusPacket[9]  = ((channels[5] >> 9) | (channels[6] << 2));
  sbusPacket[10] = ((channels[6] >> 6) | (channels[7] << 5));
  sbusPacket[11] = (channels[7] >> 3);
  sbusPacket[12] = (channels[8] & 0x07FF);
  sbusPacket[13] = ((channels[8] >> 8) | (channels[9] << 3));
  sbusPacket[14] = ((channels[9] >> 5) | (channels[10] << 6));
  sbusPacket[15] = (channels[10] >> 2);
  sbusPacket[16] = ((channels[10] >> 10) | (channels[11] << 1));
  sbusPacket[17] = ((channels[11] >> 7) | (channels[12] << 4));
  sbusPacket[18] = ((channels[12] >> 4) | (channels[13] << 7));
  sbusPacket[19] = (channels[13] >> 1);
  sbusPacket[20] = ((channels[13] >> 9) | (channels[14] << 2));
  sbusPacket[21] = ((channels[14] >> 6) | (channels[15] << 5));
  sbusPacket[22] = (channels[15] >> 3);

  sbusPacket[23] = 0;
  if (lost_connection) 
  {
    sbusPacket[23] |= (1 << 2); // Frame Lost Bit
    sbusPacket[23] |= (1 << 3); // Failsafe Bit
  }  
  
  sbusPacket[24] = SBUS_FOOTER;

  BUS_Serial.write(sbusPacket, 25);
}
#endif /* SBUS */

#ifdef IBUS
static void F_Send_iBUS(ChannelData_Typedef *rxData) 
{
  uint8_t ibusPacket[32];
  uint16_t channels[14];

  if( LGo_MADEINVN == ("MADE IN VIETNAM_d4") )
  {
  ibusPacket[0] = IBUS_HEADER_1;
  ibusPacket[1] = IBUS_HEADER_2;
  }

  if(!lost_connection) /* connect OK */
  {
    /*[1000,2000] (iBUS)*/
    channels[0]  = map(rxData->CH1,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[1]  = map(rxData->CH2,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[2]  = map(rxData->CH3,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[3]  = map(rxData->CH4,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[4]  = map(rxData->CH5,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[5]  = map(rxData->CH6,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[6]  = map(rxData->CH7,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[7]  = map(rxData->CH8,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[8]  = map(rxData->CH9,  0, 255, IBUS_MIN, IBUS_MAX);
    channels[9]  = map(rxData->CH10, 0, 255, IBUS_MIN, IBUS_MAX);
    channels[10] = IBUS_MID;
    channels[11] = IBUS_MID;
    channels[12] = IBUS_MID;
    channels[13] = IBUS_MID;
  }
  else //lost connect
  {
    for (int i = 0; i < 14; i++) 
    {
      channels[i] = IBUS_MID;
    }
  }

  /* First LSB */
  for (int i = 0; i < 14; i++) 
  {
    if( LGo_GREEN == ("GREEN_d1") )
    {
    ibusPacket[2 + i * 2] = channels[i] & 0xFF;       // LSB
    ibusPacket[3 + i * 2] = (channels[i] >> 8) & 0xFF; // MSB
    }
  }

  /* Cal checksum basic */
  uint16_t checksum = 0xFFFF;
  for (int i = 0; i < 30; i++) 
  {
    checksum -= ibusPacket[i];
  }

  ibusPacket[30] = checksum & 0xFF;
  ibusPacket[31] = (checksum >> 8) & 0xFF;

  if(!lost_connection) /* connect OK */
  {
    BUS_Serial.write(ibusPacket, 32);
  }
  else 
  {
    
  }
}
#endif /* IBUS */

void MAIN_Init(void) 
{
  #ifdef SBUS
  BUS_Serial.begin(SBUS_BAUDRATE, SBUS_SERIAL_CONFIG);
  #endif

  #ifdef IBUS
  BUS_Serial.begin(IBUS_BAUDRATE, IBUS_SERIAL_CONFIG);
  #endif

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BIND, INPUT_PULLUP);

  // RESET_DEFAULT();
  F_READ_CONFIG_MACHINE(&CONFIG_MACHINE);

  if( CONFIG_MACHINE.Check_config!=113 )
  {
    RESET_DEFAULT();
  }

  while (!radio.begin()) {LED_ON;} 
  LED_OFF;  

  if( READ_BIND==0 ) /* Bind mode */
  {
    radio.openWritingPipe((uint64_t)11111);
    radio.openReadingPipe(1,(uint64_t)33444);
    radio.setChannel(111);   
    radio.setPALevel(RF24_PA_MAX); 
    radio.setDataRate(RF24_250KBPS); 
    radio.startListening();

    BIND=true;
  }
  else 
  {
    radio.setAutoAck(true);
    radio.openWritingPipe((uint64_t)CONFIG_MACHINE.ADDRESS.RF_Address_Read);
    radio.openReadingPipe(1, (uint64_t)CONFIG_MACHINE.ADDRESS.RF_Address_Write);
    radio.setChannel(CONFIG_MACHINE.ADDRESS.RF_Channel);
    radio.setPALevel(RF24_PA_MAX);                   
    radio.setDataRate(RF24_250KBPS); 
    radio.startListening();
  }

  while (BIND==true)
  {
    static bool LEDSTATE=0;
    static uint8_t STEP=0;
    static uint32_t lasttick=0;
    static Address_typedef INFO_READ;

    if(STEP==0)
    {
      memset(&INFO_READ,0,sizeof(INFO_READ));
      STEP=1;
    }
    else if(STEP==1)
    {
      if( (uint32_t)(millis()-lasttick)>=200 )
      {
        LEDSTATE=!LEDSTATE;
        lasttick=millis();
      }
      if(LEDSTATE==0) LED_ON;
      else LED_OFF;

      if(radio.available()>0)
      {
        radio.read(&INFO_READ, sizeof(INFO_READ));
        // Serial.print("NC: "); Serial.print(INFO_READ.RF_Channel);
        // Serial.print(" - NR: "); Serial.print(INFO_READ.RF_Address_Read);
        // Serial.print(" - NW: "); Serial.print(INFO_READ.RF_Address_Write);
        // Serial.print(" - RX_INFO: "); Serial.println(INFO_READ.RX_INFO);        

        if( (INFO_READ.RF_Channel>0&&INFO_READ.RF_Channel<=120) && \
            (INFO_READ.RF_Address_Read>0&&INFO_READ.RF_Address_Read<=65535) && \
            (INFO_READ.RF_Address_Write>0&&INFO_READ.RF_Address_Write<=65535) && \
            (INFO_READ.RX_INFO>=10000&&INFO_READ.RX_INFO<=99999))
        {
          if( CONFIG_MACHINE.ADDRESS.Check_Save_RX_INFO==0 ) /* Neu chua co ma thi Lay ma dinh danh moi */
          {
            // Serial.println(" Luu ma dinh danh moi ");
            CONFIG_MACHINE.ADDRESS.RX_INFO=INFO_READ.RX_INFO;
            CONFIG_MACHINE.ADDRESS.Check_Save_RX_INFO=1;
            AddressRead.Check_Save_RX_INFO=2;
          }
          else /* Da co am dinh danh */
          {
            // Serial.println(" Da co ma dinh danh ");
            AddressRead.RX_INFO = CONFIG_MACHINE.ADDRESS.RX_INFO;
            AddressRead.Check_Save_RX_INFO=1;
          } 
          
          AddressRead.RF_Channel=INFO_READ.RF_Channel;
          AddressRead.RF_Address_Read=INFO_READ.RF_Address_Read;
          AddressRead.RF_Address_Write=INFO_READ.RF_Address_Write;

          CONFIG_MACHINE.ADDRESS.RF_Channel = AddressRead.RF_Channel;
          CONFIG_MACHINE.ADDRESS.RF_Address_Read = AddressRead.RF_Address_Read;
          CONFIG_MACHINE.ADDRESS.RF_Address_Write = AddressRead.RF_Address_Write;

          F_SAVE_CONFIG_MACHINE(&CONFIG_MACHINE);                    

          // Serial.print("NC: "); Serial.print(ADDRESS.RF_Channel);
          // Serial.print(" - NR: "); Serial.print(ADDRESS.RF_Address_Read);
          // Serial.print(" - NW: "); Serial.print(ADDRESS.RF_Address_Write);
          // Serial.print("C_Machine INFO: "); Serial.print(CONFIG_MACHINE.ADDRESS.RX_INFO);
          // Serial.print(" - RX_INFO: "); Serial.println(INFO_READ.RX_INFO);

          STEP=2;
        }
      }
    }
    else
    {
      LED_ON;
      radio.stopListening();
      radio.write(&AddressRead, sizeof(AddressRead)); 

      delay(5);
    }

  }

  LED_POWERON();
  
  BusTimeCheck = millis();
}

void MAIN_APP(void) 
{
  F_RF_READ();

  #ifdef SBUS
  if ( (uint32_t)(millis() - BusTimeCheck) >= SBUS_INTERVAL) 
  #endif /*SBUS*/
  #ifdef IBUS
  if ( (uint32_t)(millis() - BusTimeCheck) >= IBUS_INTERVAL)
  #endif /*IBUS*/
  {
    #ifdef SBUS
      F_Send_SBUS(&DataRead);
    #endif

    #ifdef IBUS
      F_Send_iBUS(&DataRead);
    #endif

    BusTimeCheck = millis();
  }

  // delay(1);
}

