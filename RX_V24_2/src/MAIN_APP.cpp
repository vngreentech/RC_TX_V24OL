
#include "MAIN_APP.h"

RF24 radio(CE, CSN);
char ID[20];
uint32_t UID;
uint16_t Vol_Sensor=0;
static uint8_t Feature=Data_Control;
static Address_typedef ADDRESS;
static ChannelData_Typedef DataRead;
static PPM_typedef ReadPPM;
Servo OUTCH1;
Servo OUTCH2;
Servo OUTCH3;
Servo OUTCH4;
Servo OUTCH5;
Servo OUTCH6;
Servo OUTCH7;
Servo OUTCH8;
Servo OUTCH9;
Servo OUTCH10;
static uint8_t BIND=false;

PPM_typedef PPM_Read;

static void RESET_DEFAULT(void)
{
  memset(&ADDRESS,0,sizeof(ADDRESS));
  EEPROM.put(0, ADDRESS);
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

static void F_PrintDataRead(void)
{
  char DataPrint[100];
  sprintf(DataPrint,"CH1: %d - CH2: %d - CH3: %d - CH4: %d - CH5: %d - CH6: %d - CH7: %d - CH8: %d - CH9: %d - CH10: %d \n", 
          DataRead.CH1, DataRead.CH2, DataRead.CH3, DataRead.CH4, DataRead.CH5, \
          DataRead.CH6, DataRead.CH7, DataRead.CH8, DataRead.CH9, DataRead.CH10);
  Serial.print(DataPrint);
}

static void F_SaveData(Address_typedef *AddressSave)
{
  EEPROM.put(0, *AddressSave);
  delay(1);

  // char data[200];
  // sprintf(data,"EEP Read CH6_Min: %d - CH6_Max: %d - CH7_Min: %d - CH7_Max: %d - CH8_Min: %d - CH8_Max: %d - CH9_Min: %d - CH9_Max: %d \n",\
  //         ADDRESS.CH6_PPM_Min, ADDRESS.CH6_PPM_Max, ADDRESS.CH7_PPM_Min, ADDRESS.CH7_PPM_Max,\
  //         ADDRESS.CH8_PPM_Min, ADDRESS.CH8_PPM_Max, ADDRESS.CH9_PPM_Min, ADDRESS.CH9_PPM_Max);
  // Serial.print(data);   
}

static void F_ReadData(Address_typedef *AddressRead)
{
  EEPROM.get(0, *AddressRead);
  delay(1);

  // Serial.print("C: "); Serial.print(AddressRead->RF_Channel);
  // Serial.print(" - R: "); Serial.print(AddressRead->RF_Address_Read);
  // Serial.print(" - W: "); Serial.println(AddressRead->RF_Address_Write);
  // char data[200];
  // sprintf(data,"EEP Read CH6_Min: %d - CH6_Max: %d - CH7_Min: %d - CH7_Max: %d - CH8_Min: %d - CH8_Max: %d - CH9_Min: %d - CH9_Max: %d \n",\
  //         ADDRESS.CH6_PPM_Min, ADDRESS.CH6_PPM_Max, ADDRESS.CH7_PPM_Min, ADDRESS.CH7_PPM_Max,\
  //         ADDRESS.CH8_PPM_Min, ADDRESS.CH8_PPM_Max, ADDRESS.CH9_PPM_Min, ADDRESS.CH9_PPM_Max);
  // Serial.print(data);  
}

static void F_ServoInit(void)
{
  OUTCH1.attach(PinCH1,((int)ADDRESS.CH1_PPM_Min),((int)ADDRESS.CH1_PPM_Max));
  OUTCH2.attach(PinCH2,((int)ADDRESS.CH2_PPM_Min),((int)ADDRESS.CH2_PPM_Max));
  OUTCH3.attach(PinCH3,((int)ADDRESS.CH3_PPM_Min),((int)ADDRESS.CH3_PPM_Max));
  OUTCH4.attach(PinCH4,((int)ADDRESS.CH4_PPM_Min),((int)ADDRESS.CH4_PPM_Max));
  OUTCH5.attach(PinCH5,((int)ADDRESS.CH5_PPM_Min),((int)ADDRESS.CH5_PPM_Max));
  OUTCH6.attach(PinCH6,((int)ADDRESS.CH6_PPM_Min),((int)ADDRESS.CH6_PPM_Max));
  OUTCH7.attach(PinCH7,((int)ADDRESS.CH7_PPM_Min),((int)ADDRESS.CH7_PPM_Max));
  OUTCH8.attach(PinCH8,((int)ADDRESS.CH8_PPM_Min),((int)ADDRESS.CH8_PPM_Max));
  OUTCH9.attach(PinCH9,((int)ADDRESS.CH9_PPM_Min),((int)ADDRESS.CH9_PPM_Max));
  OUTCH10.attach(PinCH10,((int)ADDRESS.CH10_PPM_Min),((int)ADDRESS.CH10_PPM_Max));

  // char data[100];
  // sprintf(data,"CH1_Min: %d - CH1_Max: %d - CH2_Min: %d - CH2_Max: %d\n",\
  //         ADDRESS.CH1_PPM_Min, ADDRESS.CH1_PPM_Max,\
  //         ADDRESS.CH2_PPM_Min, ADDRESS.CH2_PPM_Max);
  // Serial.print(data);
}

static void F_ControlServo(void)
{
  OUTCH1.write( (int)map(DataRead.CH1,0,255,0,180) );
  OUTCH2.write( (int)map(DataRead.CH2,0,255,0,180) );
  OUTCH3.write( (int)map(DataRead.CH3,0,255,0,180) );
  OUTCH4.write( (int)map(DataRead.CH4,0,255,0,180) );
  OUTCH5.write( (int)map(DataRead.CH5,0,255,0,180) );
  OUTCH6.write( (int)map(DataRead.CH6,0,255,0,180) );
  OUTCH7.write( (int)map(DataRead.CH7,0,255,0,180) );
  OUTCH8.write( (int)map(DataRead.CH8,0,255,0,180) );
  OUTCH9.write( (int)map(DataRead.CH9,0,255,0,180) );
  OUTCH10.write( (int)map(DataRead.CH10,0,255,0,180) );
  
}

static void F_Set_PPM(void)
{
  static PPM_typedef PPM_Read;
  static uint8_t step=0;
  static uint32_t Tick_time=0;

  if( Feature==Get_PPM )
  {
    if(step==0)
    {
      memset(&PPM_Read,0,sizeof(PPM_Read));
      Tick_time=millis();
      step=1;
    }
    else if(step==1)
    {
      DataRead.Feature = Get_OK;
      radio.stopListening();
      radio.write(&DataRead, sizeof(DataRead));  
      delay(2);

      radio.startListening();
      if(radio.available()>0)     
      {
        radio.read(&PPM_Read, sizeof(PPM_Read));
        if(PPM_Read.CH8_PPM_Max)
        {
          Feature=Save_PPM;
        }
      } 
      delay(2);

      if( (uint32_t)(millis()-Tick_time)>=3000 ) /* Time out */
      {
        /* Time out */
        Feature = Data_Control;
        step=0;
      }
    }
  }
  else if( Feature==Save_PPM )
  {
    ADDRESS.CH1_PPM_Min = map(PPM_Read.CH1_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH1_PPM_Max = map(PPM_Read.CH1_PPM_Max,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH2_PPM_Min = map(PPM_Read.CH2_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH2_PPM_Max = map(PPM_Read.CH2_PPM_Max,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH3_PPM_Min = map(PPM_Read.CH3_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH3_PPM_Max = map(PPM_Read.CH3_PPM_Max,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH4_PPM_Min = map(PPM_Read.CH4_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH4_PPM_Max = map(PPM_Read.CH4_PPM_Max,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH5_PPM_Min = map(PPM_Read.CH5_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH5_PPM_Max = map(PPM_Read.CH5_PPM_Max,0,255,PPM_MIN,PPM_MAX);

    ADDRESS.CH6_PPM_Min = map(PPM_Read.CH6_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH6_PPM_Max = map(PPM_Read.CH6_PPM_Max,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH7_PPM_Min = map(PPM_Read.CH7_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH7_PPM_Max = map(PPM_Read.CH7_PPM_Max,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH8_PPM_Min = map(PPM_Read.CH8_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH8_PPM_Max = map(PPM_Read.CH8_PPM_Max,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH9_PPM_Min = map(PPM_Read.CH9_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH9_PPM_Max = map(PPM_Read.CH9_PPM_Max,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH10_PPM_Min = map(PPM_Read.CH10_PPM_Min,0,255,PPM_MIN,PPM_MAX);
    ADDRESS.CH10_PPM_Max = map(PPM_Read.CH10_PPM_Max,0,255,PPM_MIN,PPM_MAX);    

    F_SaveData(&ADDRESS);

    F_ServoInit();

    PPM_Read.Feature = Save_OK;
    radio.stopListening();
    Tick_time=millis();
    step=0;

    Feature=Save_OK;
  }
  else if( Feature==Save_OK )
  {
    radio.write(&PPM_Read, sizeof(PPM_Read)); 

    if( (uint32_t)(millis()-Tick_time)>=1000 )
    {
      Feature = Data_Control;
    }
  }
  else 
  {
    ;;
  }
}

static void F_RF_READ(void)
{
  static uint8_t step=0;
  static uint32_t Tick_1=0;
  static uint32_t Tick_senddata=0;
  static ChannelData_Typedef DataRead_Virtual;

  if( Feature==Data_Control )  
  {
    if(step==0)
    {
      Tick_1=millis();
      step=1;
    }
    else if(step==1)
    {
      if((uint32_t)(millis()-Tick_1)>=1000)
      {
        Tick_senddata=millis();
        step=2;
      }
    }
    else if(step==2)
    {  
      radio.stopListening();
      radio.write(&Vol_Sensor, sizeof(Vol_Sensor));

      if((uint32_t)(millis()-Tick_1)>=500)
      {
        step=0;
      }
    }

    radio.startListening();
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
        DataRead = DataRead_Virtual;
        Feature = DataRead.Feature;
      }
    }

    F_ControlServo();
  }

  F_Set_PPM();

  // Serial.print("CH1: "); Serial.print(DataRead.CH1);
  // Serial.print(" - CH2: "); Serial.print(DataRead.CH2);
  // Serial.print(" - CH3: "); Serial.print(DataRead.CH3);
  // Serial.print(" - CH4: "); Serial.print(DataRead.CH4);
  // Serial.print(" - CH5: "); Serial.print(DataRead.CH5);
  // Serial.print(" - CH6: "); Serial.print(DataRead.CH6);
  // Serial.print(" - CH7: "); Serial.print(DataRead.CH7);
  // Serial.print(" - CH8: "); Serial.print(DataRead.CH8);
  // Serial.print(" - CH9: "); Serial.print(DataRead.CH9);
  // Serial.print(" - CH10: "); Serial.println(DataRead.CH10);

}

void readID()
{
  UniqueIDdump(Serial);
	for (uint8_t i = 9; i>0; i--)
	{
    ID[i] = _UniqueID.id[i];
    Serial.print(ID[i]);
	}
}

void APP_Init(void)
{
  Serial.begin(115200);
  pinMode(VOLSENSOR,INPUT);
  pinMode(PINCONNECT, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  // RESET_DEFAULT();
  F_ReadData(&ADDRESS);
  F_ServoInit();

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
    radio.openWritingPipe((uint64_t)ADDRESS.RF_Address_Read);
    radio.openReadingPipe(1, (uint64_t)ADDRESS.RF_Address_Write);
    radio.setChannel(ADDRESS.RF_Channel);
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
          if( ADDRESS.Check_Save_RX_INFO==0 ) /* Neu chua co ma thi Lay ma dinh danh moi */
          {
            // Serial.println(" Luu ma dinh danh moi ");
            ADDRESS.RX_INFO=INFO_READ.RX_INFO;
            ADDRESS.Check_Save_RX_INFO=2;
          }
          else /* Da co am dinh danh */
          {
            // Serial.println(" Da co ma dinh danh ");
            ADDRESS.Check_Save_RX_INFO=1;
          } 
          
          ADDRESS.RF_Channel=INFO_READ.RF_Channel;
          ADDRESS.RF_Address_Read=INFO_READ.RF_Address_Read;
          ADDRESS.RF_Address_Write=INFO_READ.RF_Address_Write;

          F_SaveData(&ADDRESS);                    

          // Serial.print("NC: "); Serial.print(ADDRESS.RF_Channel);
          // Serial.print(" - NR: "); Serial.print(ADDRESS.RF_Address_Read);
          // Serial.print(" - NW: "); Serial.print(ADDRESS.RF_Address_Write);
          // Serial.print(" - RX_INFO: "); Serial.println(INFO_READ.RX_INFO);

          STEP=2;
        }
      }
    }
    else
    {
      LED_ON;
      radio.stopListening();
      radio.write(&ADDRESS, sizeof(ADDRESS)); 

      delay(5);
    }

  }

  LED_POWERON();

}

void APP_Main(void)
{
  Vol_Sensor = analogRead(VOLSENSOR);
  F_RF_READ();
}

