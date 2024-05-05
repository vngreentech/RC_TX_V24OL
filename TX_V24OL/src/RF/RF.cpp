
#include "RF.h"
#include "RF24.h"
#include "Adafruit_SPIDevice.h"

DataSendControl_typedef RF_DATA_SEND;
uint16_t RF_ReadData;

RF24 radio(CE, CSN);

uint8_t RF_RESULT_PPM=0; /* 1=OK, 2=TimeOut */
uint8_t RF_BIND_RESULT=0;
uint8_t RF_Check_Connect=false;
uint8_t Feature_send=Send_Data_Control;

void RF_INIT_BIND(void)
{
  radio.openWritingPipe((uint64_t)33444);
  radio.openReadingPipe(1, (uint64_t)11111);
  if( strcmp((char*)Machine.DUMMY_1,(char*)LGO_GREEN)==0 )
  {
  radio.setChannel(111);    
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);        
  }
}

void RF_BIND_MAIN(void)
{
  static bool LEDSTATE=0;
  static uint8_t Step=0;
  static uint32_t Tick_timeout=0;
  static uint32_t Tick_action=0;
  static Address_typedef New_Add;
  static Address_typedef Info_Read;

  if(Step==0)
  {
    RF_INIT_BIND();

    memset(&New_Add,0,sizeof(New_Add));
    memset(&Info_Read,0,sizeof(Info_Read));

    if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
    {
    New_Add.RX_INFO = random(10000,99999);
    New_Add.TX_INFO = Machine.ADDRESS.TX_INFO;
    New_Add.RF_Address_Read = random(1000,65000);
    New_Add.RF_Address_Write = random(1000,65000);
    New_Add.RF_Channel = random(90,123);
    }

    Tick_timeout=millis();
    Tick_action=millis();
    LEDSTATE=0;
    RF_BIND_RESULT=0;
    Step=1;
  }
  else if(Step==2) /* OK */
  {   

    if(Info_Read.Check_Save_RX_INFO==2) /* Luu ma dinh danh moi */
    {
      Machine.ADDRESS.RX_INFO = New_Add.RX_INFO;
    }
    else if(Info_Read.Check_Save_RX_INFO==1) /* Da co ma dinh danh */
    {
      if( Info_Read.RX_INFO != Machine.ADDRESS.RX_INFO )
      {
        Machine.ADDRESS.RX_INFO = Info_Read.RX_INFO;
      }
    }
    
    if( strcmp((char*)Machine.DUMMY_4,(char*)LGO_MADEINVN)==0 )
    {
    Machine.ADDRESS.RF_Address_Read = New_Add.RF_Address_Read;
    Machine.ADDRESS.RF_Address_Write = New_Add.RF_Address_Write;
    Machine.ADDRESS.RF_Channel = New_Add.RF_Channel;

    WRITE_CONFIG_MACHINE(&Machine);
    }

    RF_BIND_RESULT=1;
    Step=0;
  }
  else if(Step==3) /* ERROR */
  {
    RF_BIND_RESULT=2;
    Step=0;
  }

  while(Step==1)
  {
    if( (uint32_t)(millis()-Tick_action)>=200 )
    {
      LEDSTATE=!LEDSTATE;
      Tick_action=millis();
    }
    if(LEDSTATE==0)
    {
      BUZZER_ON;
      LED_ON;
    }
    else
    {
      BUZZER_OF;
      LED_OF;
    }

    if( (uint32_t)(millis()-Tick_timeout)>=10000 ) /* 30s ERROR */
    {
      Step=3;
      break;
    }

    radio.stopListening(); //Ngưng nhận
    radio.write(&New_Add, sizeof(New_Add));
    delay(5);

    radio.startListening(); //Bắt đầu nhận
    if(!radio.available());
    radio.read(&Info_Read, sizeof(Info_Read));               

    if( Info_Read.RF_Channel==New_Add.RF_Channel && \
        Info_Read.RF_Address_Read==New_Add.RF_Address_Read && \
        Info_Read.RF_Address_Write==New_Add.RF_Address_Write
      )
    {
      // Serial1.print("NC: "); Serial1.print(Info_Read.RF_Channel);
      // Serial1.print(" - NR: "); Serial1.print(Info_Read.RF_Address_Read);
      // Serial1.print(" - NW: "); Serial1.print(Info_Read.RF_Address_Write);
      // Serial1.print(" - RX_INFO: "); Serial1.println(Info_Read.RX_INFO);           

      Step=2;
      break;
    }

    if( Step==2 or Step==3 ) 
    {
      BUZZER_OF;
      LED_OF;
      break;
    }

    delay(5);

  }

}

void RF_Send_PPM(void)
{
  static DataSendControl_typedef DataRead;
  static SendPPM_typedef PPM_Send;
  static SendPPM_typedef PPM_Read;   
  static uint8_t Step=0;
  static uint32_t TickTime=0;

  if( Step==0 )
  {
    if( strcmp((char*)Machine.DUMMY_5,(char*)LGO_NhanNguyen)==0 )
    {
    memset( &DataRead,0,sizeof(DataRead) );
    memset( &PPM_Send,0,sizeof(PPM_Send) );
    memset( &PPM_Read,0,sizeof(PPM_Read) );

    PPM_Send.Feature = Save_PPM;
    PPM_Send.CH1_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_1.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH1_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_1.PPM_Max,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH2_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_2.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH2_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_2.PPM_Max,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH3_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_3.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH3_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_3.PPM_Max,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH4_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_4.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH4_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_4.PPM_Max,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH5_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_5.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH5_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_5.PPM_Max,PPM_MIN,PPM_MAX,0,255);

    PPM_Send.CH6_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_6.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH6_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_6.PPM_Max,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH7_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_7.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH7_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_7.PPM_Max,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH8_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_8.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH8_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_8.PPM_Max,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH9_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_9.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH9_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_9.PPM_Max,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH10_PPM_Min = map(_Virtual_Machine_.CHANNEL.Channel_10.PPM_Min,PPM_MIN,PPM_MAX,0,255);
    PPM_Send.CH10_PPM_Max = map(_Virtual_Machine_.CHANNEL.Channel_10.PPM_Max,PPM_MIN,PPM_MAX,0,255);}

    RF_RESULT_PPM=0;
    TickTime=millis();
    Step=1;
  }
  else if( Step==1 )
  {
    RF_DATA_SEND.Feature=Get_PPM;
    radio.stopListening();
    radio.write(&RF_DATA_SEND, sizeof(RF_DATA_SEND));

    radio.startListening();
    if(radio.available()>0)   
    {
      radio.read(&DataRead, sizeof(DataRead));    

      if(DataRead.Feature==Get_OK)
      {
        Step=2;
      }
    }
  }
  else if(Step==2)
  {
    radio.stopListening();
    radio.write(&PPM_Send, sizeof(PPM_Send));

    radio.startListening();
    if(radio.available()>0)   
    {
      radio.read(&PPM_Read, sizeof(PPM_Read));    

      if(PPM_Read.Feature==Save_OK)
      {
        RF_RESULT_PPM=1;
        Feature_send=Send_Data_Control;
        RF_DATA_SEND.Feature=Data_Control;
        Step=0;
      }
    }
  }
  else {;;}

  if( Step==1 || Step==2 )
  {
    if( (uint32_t)(millis()-TickTime)>=3000 )
    {
      RF_RESULT_PPM=2; /* Time Out */
      Feature_send=Send_Data_Control;
      RF_DATA_SEND.Feature=Data_Control;
      Step=0;
    }
  }

}

void RF_INIT(void)
{
  while (!radio.begin()) 
  {
    ERROR_RF24();
    LED_ON;
    BUZZER_ON;
  } 
  LED_OF;
  BUZZER_OF;  

  if( strcmp((char*)Machine.DUMMY_5,(char*)LGO_NhanNguyen)==0 )
  {
    radio.setAutoAck(true);
    radio.openWritingPipe((uint64_t)Machine.ADDRESS.RF_Address_Write);
    radio.openReadingPipe(1, (uint64_t)Machine.ADDRESS.RF_Address_Read);
    radio.setChannel(Machine.ADDRESS.RF_Channel);                  
    radio.setDataRate(RF24_250KBPS); 
    radio.setPALevel(RF24_PA_MAX); 

    RF_DATA_SEND.Feature=Data_Control;
    Feature_send=Send_Data_Control;
  }

}

void RF_MAIN(void)
{
  static uint16_t READ_Vol_RX_Virtual;

  if( Feature_send==Send_Data_Control )
  {
    if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
    {
      radio.stopListening();
      radio.write(&RF_DATA_SEND, sizeof(RF_DATA_SEND));
      if(radio.write(&RF_DATA_SEND, sizeof(RF_DATA_SEND))==true)
      {
        RF_Check_Connect=true;
        LED_OF;
      }
      else 
      {
        RF_Check_Connect=false;
        LED_ON;
      }
      // delay(2);
    }

    radio.startListening();
    if(radio.available()>0)   
    {
      radio.read(&READ_Vol_RX_Virtual, sizeof(READ_Vol_RX_Virtual));    

      if( READ_Vol_RX_Virtual>=0 && READ_Vol_RX_Virtual<=4095 )
      {
        RF_ReadData=READ_Vol_RX_Virtual;
      }
    }
    // Serial1.print("Vol nhan: "); Serial1.println(RF_ReadData);
    // delay(2);
  }
  else 
  {
    RF_Send_PPM();
  }

}
