
#include "LCD.h"
#include "RF24.h"
#include "Adafruit_SPIDevice.h"

#define MENU_TOTAL (17)
static const String MENU[] = {
  " Channel Reverse",
  " End Point",
  " Get Channel Limit",
  " Subtrims",
  " Set PPM",
  " Bind RX",

  " Mix Channel",
  " Display",
  " Map Channel",
  " Set Throttle Lock",
  " Set Time Down",
  " Set TX Battery",

  " Set RX Battery",
  " Add Model",
  " Select Model",
  " Delete Model",
  " Reset Default",
  " VERSION"
  };

typedef enum 
{
  ChannelReserse,
  EndPoint,
  GetChannelLimit,
  Subtrim,
  SetPPM,
  BindRX,
  MixChannel,
  DisPlay,
  MapChannel,
  SetThrottleLock,
  SetTimeDown,
  SetTXBattery,
  SetRXBattery,
  AddModel,
  SelectModel,
  DeleteModel,
  ResetDefault,
  Version
}MenuSelect_enum;

typedef enum 
{
  Screen,
  MainMenu,
  ChoiceMenuMain,
  Enter_1,
  Enter_2,
  Enter_3
}MenuPos_enum;

Adafruit_SH1106G Display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ConfigMachine_typedef _Virtual_Machine_;

static uint32_t TickLCD=0;

static uint8_t RESULT_BUTTON_OK=0;
static uint8_t RESULT_BUTTON_BACK=0;

static uint8_t Pos_menu=0;
static uint8_t MenuUPDOWN=0;

static uint8_t Count_UpDown=0;
static uint8_t UpDown_Menu_V1=0;
static uint8_t UpDown_Menu_V1_MAX=0;

static uint8_t Last_state_OK=1;
static uint8_t Last_state_BACK=1;
static uint16_t Last_state_UP=2000;
static uint16_t Last_state_DOWN=2000;

static uint8_t STEP_ACTION=0;

static float RF_SCREEN=0;

void ERROR_RF24(void)
{
  Display.clearDisplay();
  Display.setTextSize(2);

  Display.setCursor(10, 0); Display.print("ERROR !!!");

  Display.setTextSize(1);
  Display.setCursor(45, 30); Display.print("RF-24");
  Display.setCursor(30, 50); Display.print("NOT CONNECT");

  Display.display();
}

void ERROR_EEPROM(void)
{
  Display.clearDisplay();
  Display.setTextSize(2);

  Display.setCursor(10, 0); Display.print("ERROR !!!");

  Display.setTextSize(1);
  Display.setCursor(35, 30); Display.print("EEPROM IC");
  Display.setCursor(30, 50); Display.print("NOT CONNECT");

  Display.display();
}

static void FEATURE_IN_DEVELOPMENT(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  Display.setCursor(0, 15); 
  Display.println("Feature is in");
  Display.setCursor(0, 30);
  Display.print("          development");

  Display.setCursor(15, 50); 
  Display.println("GREEN TECHNOLOGY");  

  Display.display();

  delay(3000);
  Pos_menu=0;
}

static void LOGO_START(void)
{
  Display.clearDisplay();
  Display.setTextSize(2);
  Display.setTextColor(SH110X_WHITE);

  Display.setCursor(35, 0);
  Display.print(LGO_GREEN);  
  Display.setCursor(5, 17);
  Display.print(LGO_TECH); 

  Display.setTextSize(1);
  Display.setCursor(7, 40);
  Display.print(LGO_WEB);   
  Display.setCursor(20, 55);
  Display.print(LGO_MADEINVN);     

  Display.display();
  delay(1000);
}

static uint8_t ACTION_GET_LIMIT(uint8_t Channel)
{
  uint8_t RESULT=FALSE;
  static uint32_t tick_action=0;

  if(STEP_ACTION==0)
  {
    tick_action=millis();
    STEP_ACTION=1;
  }
  else if(STEP_ACTION==1) /* Get MIN */
  {
    if(Channel==0) _Virtual_Machine_.CHANNEL.Channel_1.Limit.MIN = DATA_READ.CH1;
    else if(Channel==1) _Virtual_Machine_.CHANNEL.Channel_2.Limit.MIN = DATA_READ.CH2;
    else if(Channel==2) _Virtual_Machine_.CHANNEL.Channel_3.Limit.MIN = DATA_READ.CH3;
    else if(Channel==3) _Virtual_Machine_.CHANNEL.Channel_4.Limit.MIN = DATA_READ.CH4;
    else if(Channel==4) _Virtual_Machine_.CHANNEL.Channel_5.Limit.MIN = DATA_READ.BienTro_1;
    else if(Channel==5) _Virtual_Machine_.CHANNEL.Channel_6.Limit.MIN = DATA_READ.BienTro_3;
    else if(Channel==6) _Virtual_Machine_.CHANNEL.Channel_7.Limit.MIN = DATA_READ.SW_3POS_1;
    else if(Channel==7) _Virtual_Machine_.CHANNEL.Channel_8.Limit.MIN = DATA_READ.SW_3POS_2;
    else if(Channel==8) _Virtual_Machine_.CHANNEL.Channel_9.Limit.MIN = DATA_READ.SWONOF_1;
    else _Virtual_Machine_.CHANNEL.Channel_10.Limit.MIN = DATA_READ.SWONOF_4;

    if( (uint32_t)(millis()-tick_action)>=5000 )
    {
      if( strcmp((char*)Machine.ADDRESS.DUMMY_2,(char*)LGO_TECH)==0 )
      {LED_ON;
      BUZZER_ON;
      delay(100);
      LED_OF;
      BUZZER_OF;

      tick_action=millis();
      STEP_ACTION=2;}
    }
  }
  else if(STEP_ACTION==2) /* Get MIDDLE */
  {
    if(Channel==0) _Virtual_Machine_.CHANNEL.Channel_1.Limit.MIDDLE = DATA_READ.CH1;
    else if(Channel==1) _Virtual_Machine_.CHANNEL.Channel_2.Limit.MIDDLE = DATA_READ.CH2;
    else if(Channel==2) _Virtual_Machine_.CHANNEL.Channel_3.Limit.MIDDLE = DATA_READ.CH3;
    else if(Channel==3) _Virtual_Machine_.CHANNEL.Channel_4.Limit.MIDDLE = DATA_READ.CH4;
    else if(Channel==4) _Virtual_Machine_.CHANNEL.Channel_5.Limit.MIDDLE = DATA_READ.BienTro_1;
    else if(Channel==5) _Virtual_Machine_.CHANNEL.Channel_6.Limit.MIDDLE = DATA_READ.BienTro_3;
    else if(Channel==6) _Virtual_Machine_.CHANNEL.Channel_7.Limit.MIDDLE = DATA_READ.SW_3POS_1;
    else if(Channel==7) _Virtual_Machine_.CHANNEL.Channel_8.Limit.MIDDLE = DATA_READ.SW_3POS_2;
    else if(Channel==8) _Virtual_Machine_.CHANNEL.Channel_9.Limit.MIDDLE = DATA_READ.SWONOF_1;
    else _Virtual_Machine_.CHANNEL.Channel_10.Limit.MIDDLE = DATA_READ.SWONOF_4;

    if( (uint32_t)(millis()-tick_action)>=5000 )
    {
      LED_ON;
      BUZZER_ON;
      delay(100);
      LED_OF;
      BUZZER_OF;

      tick_action=millis();
      STEP_ACTION=3;
    }
  }
  else /* GET MAX */
  {
    if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
    {if(Channel==0) _Virtual_Machine_.CHANNEL.Channel_1.Limit.MAX = DATA_READ.CH1;
    else if(Channel==1) _Virtual_Machine_.CHANNEL.Channel_2.Limit.MAX = DATA_READ.CH2;
    else if(Channel==2) _Virtual_Machine_.CHANNEL.Channel_3.Limit.MAX = DATA_READ.CH3;
    else if(Channel==3) _Virtual_Machine_.CHANNEL.Channel_4.Limit.MAX = DATA_READ.CH4;
    else if(Channel==4) _Virtual_Machine_.CHANNEL.Channel_5.Limit.MAX = DATA_READ.BienTro_1;
    else if(Channel==5) _Virtual_Machine_.CHANNEL.Channel_6.Limit.MAX = DATA_READ.BienTro_3;
    else if(Channel==6) _Virtual_Machine_.CHANNEL.Channel_7.Limit.MAX = DATA_READ.SW_3POS_1;
    else if(Channel==7) _Virtual_Machine_.CHANNEL.Channel_8.Limit.MAX = DATA_READ.SW_3POS_2;
    else if(Channel==8) _Virtual_Machine_.CHANNEL.Channel_9.Limit.MAX = DATA_READ.SWONOF_1;
    else _Virtual_Machine_.CHANNEL.Channel_10.Limit.MAX = DATA_READ.SWONOF_4;}

    if( (uint32_t)(millis()-tick_action)>=5000 )
    {
      RESULT=TRUE;

      LED_ON;
      BUZZER_ON;
      delay(1000);
      LED_OF;
      BUZZER_OF;

      tick_action=0;
      STEP_ACTION=0;
    }    
  }

  return RESULT;
}

static void Screen_main(float *VolTX, float *VolRX, \
                        volatile uint16_t *ST1, volatile uint16_t *ST2, volatile uint16_t *ST3, volatile uint16_t *ST4,\
                        uint8_t *Minute, uint8_t *Second,\
                        char Model[10], float *RF, volatile uint16_t *RX)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  Display.setCursor(0, 0); Display.print("TX: ");
  Display.setCursor(16, 0); Display.print(*VolTX); 

  Display.setCursor(52, 0); Display.print("RX: ");
  Display.setCursor(68, 0); Display.print(*VolRX); 

  Display.setCursor(103, 0); Display.print(*RF); 

  Display.setCursor(0, 20); Display.print("ST1: ");
  Display.setCursor(23, 20); Display.print(*ST1);   
  Display.setCursor(0, 30); Display.print("ST2: ");
  Display.setCursor(23, 30); Display.print(*ST2);       
  Display.setCursor(0, 40); Display.print("ST3: ");
  Display.setCursor(23, 40); Display.print(*ST3);   
  Display.setCursor(0, 50); Display.print("ST4: ");
  Display.setCursor(23, 50); Display.print(*ST4); 

  Display.setTextSize(2);
  char data[20];
  sprintf(data,"%.2d:%.2d",*Minute,*Second);
  Display.setCursor(60, 20); Display.print(data);       

  Display.setTextSize(1);
  sprintf(data,"Model:%s", Model);
  Display.setCursor(50, 40); Display.print(data);

  sprintf(data,"RX:%d", *RX);
  Display.setCursor(50, 50); Display.print(data);  

  Display.display();
}

static void Menu_MAIN(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  if( MenuUPDOWN<6 ) { Display.setCursor(0, MenuUPDOWN*10); Display.print(">"); }
  else if(MenuUPDOWN>=6 && MenuUPDOWN<12) { Display.setCursor(0, (MenuUPDOWN-6)*10); Display.print(">"); }
  else { Display.setCursor(0, (MenuUPDOWN-12)*10); Display.print(">"); }

  if( MenuUPDOWN<6 )
  {
    Display.setCursor(0, 0); Display.print(MENU[0]);
    Display.setCursor(0, 10); Display.print(MENU[1]);
    Display.setCursor(0, 20); Display.print(MENU[2]);
    Display.setCursor(0, 30); Display.print(MENU[3]);
    Display.setCursor(0, 40); Display.print(MENU[4]);
    Display.setCursor(0, 50); Display.print(MENU[5]); 
  }
  else if(MenuUPDOWN>=6 && MenuUPDOWN<12)
  {
    Display.setCursor(0, 0); Display.print(MENU[6]);
    Display.setCursor(0, 10); Display.print(MENU[7]);
    Display.setCursor(0, 20); Display.print(MENU[8]);
    Display.setCursor(0, 30); Display.print(MENU[9]);
    Display.setCursor(0, 40); Display.print(MENU[10]);
    Display.setCursor(0, 50); Display.print(MENU[11]);     
  }
  else 
  {
    Display.setCursor(0, 0); Display.print(MENU[12]);
    Display.setCursor(0, 10); Display.print(MENU[13]);
    Display.setCursor(0, 20); Display.print(MENU[14]);
    Display.setCursor(0, 30); Display.print(MENU[15]);
    Display.setCursor(0, 40); Display.print(MENU[16]);
    Display.setCursor(0, 50); Display.print(MENU[17]);      
  }

  Display.display();

}

static void MENU_RESET(uint8_t Step)
{
  Display.clearDisplay();

  if(Step==0)
  {
    Display.setTextSize(2);  
    Display.setCursor(0, 10); Display.print("WARNING !!");

    Display.setTextSize(1);
    Display.setCursor(15, 40); Display.print("RESET TO DEFAULT");
  }
  else if(Step==1)
  {
    Display.setTextSize(1);  
    Display.setCursor(10, 20); Display.print("RESET DEFAULT");

    Display.setTextSize(1);
    Display.setCursor(30, 40); Display.print("PLEASE WAIT !");    
  }

  Display.display();
}

static void MENU_VERSION(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  char data[50];

  Display.setCursor(0, 0); Display.print("TX:V24OL");
  Display.setCursor(60, 0); Display.print("RX:V24.2");
  
  sprintf(data,"FW-TX: %s",FIRMWARE_VERSION);
  Display.setCursor(0, 15); Display.print(data);
  sprintf(data,"Date: %s",RELEASES_DATE);
  Display.setCursor(0, 25); Display.print(data);

  sprintf(data,"Design by %s",LGO_NhanNguyen);
  Display.setCursor(0, 40); Display.print(data);
  Display.setCursor(15, 50); Display.print(LGO_MADEINVN);

  Display.display();
}

static void MENU_REVERSE(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  if( strcmp((char*)Machine.DUMMY_4,(char*)LGO_MADEINVN)==0 )
  {if( UpDown_Menu_V1<5 ) { Display.setCursor( 0, ((UpDown_Menu_V1*10)+15) ); Display.print(">"); }
  else { Display.setCursor( 65, (((UpDown_Menu_V1-5)*10)+15) ); Display.print(">"); }}

  Display.setCursor(10, 1); Display.print(" CHANNEL REVERSE ");

  Display.setCursor(0, 15); Display.print(_Virtual_Machine_.CHANNEL.Channel_1.Reverse==1?" CH1:F-T":" CH1:T-F");
  Display.setCursor(0, 25); Display.print(_Virtual_Machine_.CHANNEL.Channel_2.Reverse==1?" CH2:F-T":" CH2:T-F");
  Display.setCursor(0, 35); Display.print(_Virtual_Machine_.CHANNEL.Channel_3.Reverse==1?" CH3:F-T":" CH3:T-F");
  Display.setCursor(0, 45); Display.print(_Virtual_Machine_.CHANNEL.Channel_4.Reverse==1?" CH4:F-T":" CH4:T-F");
  Display.setCursor(0, 55); Display.print(_Virtual_Machine_.CHANNEL.Channel_5.Reverse==1?" CH5:F-T":" CH5:T-F");

  Display.setCursor(65, 15); Display.print(_Virtual_Machine_.CHANNEL.Channel_6.Reverse==1?" CH6:F-T":" CH6:T-F");
  Display.setCursor(65, 25); Display.print(_Virtual_Machine_.CHANNEL.Channel_7.Reverse==1?" CH7:F-T":" CH7:T-F");
  Display.setCursor(65, 35); Display.print(_Virtual_Machine_.CHANNEL.Channel_8.Reverse==1?" CH8:F-T":" CH8:T-F");
  Display.setCursor(65, 45); Display.print(_Virtual_Machine_.CHANNEL.Channel_9.Reverse==1?" CH9:F-T":" CH9:T-F");
  Display.setCursor(65, 55); Display.print(_Virtual_Machine_.CHANNEL.Channel_10.Reverse==1?" CH10:F-T":" CH10:T-F");

  Display.display();
}

static void MENU_END_POINT(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  if( strcmp((char*)Machine.DUMMY_5,(char*)LGO_NhanNguyen)==0 )
  {if( UpDown_Menu_V1<5 ) { Display.setCursor( 0, ((UpDown_Menu_V1*10)+15) ); Display.print(Pos_menu==Enter_1?"*":">"); }
  else { Display.setCursor( 65, (((UpDown_Menu_V1-5)*10)+15) ); Display.print(Pos_menu==Enter_1?"*":">"); }}

  char data[20];

  Display.setCursor(35, 1); Display.print("END POINT");

  sprintf(data," CH1:%d",_Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT);
  Display.setCursor(0, 15); Display.print(data);
  sprintf(data," CH2:%d",_Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT);
  Display.setCursor(0, 25); Display.print(data);
  sprintf(data," CH3:%d",_Virtual_Machine_.CHANNEL.Channel_3.Limit.TRIP_PERCENT);
  Display.setCursor(0, 35); Display.print(data);
  sprintf(data," CH4:%d",_Virtual_Machine_.CHANNEL.Channel_4.Limit.TRIP_PERCENT);
  Display.setCursor(0, 45); Display.print(data);
  sprintf(data," CH5:%d",_Virtual_Machine_.CHANNEL.Channel_5.Limit.TRIP_PERCENT);
  Display.setCursor(0, 55); Display.print(data);

  sprintf(data," CH6:%d",_Virtual_Machine_.CHANNEL.Channel_6.Limit.TRIP_PERCENT);
  Display.setCursor(65, 15); Display.print(data);
  sprintf(data," CH7:%d",_Virtual_Machine_.CHANNEL.Channel_7.Limit.TRIP_PERCENT);
  Display.setCursor(65, 25); Display.print(data);
  sprintf(data," CH8:%d",_Virtual_Machine_.CHANNEL.Channel_8.Limit.TRIP_PERCENT);
  Display.setCursor(65, 35); Display.print(data);
  sprintf(data," CH9:%d",_Virtual_Machine_.CHANNEL.Channel_9.Limit.TRIP_PERCENT);
  Display.setCursor(65, 45); Display.print(data);
  sprintf(data," CH10:%d",_Virtual_Machine_.CHANNEL.Channel_10.Limit.TRIP_PERCENT);
  Display.setCursor(65, 55); Display.print(data);

  Display.display();  
}

static void MENU_GET_CHANNEL_LIMIT(void)
{
  char data[20];

  Display.clearDisplay();
  Display.setTextSize(1);

  if( UpDown_Menu_V1<5 ) 
  { 
    Display.setCursor(0, (UpDown_Menu_V1*10)); Display.print(Pos_menu==Enter_1?"*":">"); 

    sprintf(data," CH1:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_1.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_1.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_1.Limit.MAX);
    Display.setCursor(0, 0); Display.print(data);

    sprintf(data," CH2:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_2.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_2.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_2.Limit.MAX);    
    Display.setCursor(0, 10); Display.print(data);

    sprintf(data," CH3:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_3.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_3.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_3.Limit.MAX);       
    Display.setCursor(0, 20); Display.print(data);

    sprintf(data," CH4:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_4.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_4.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_4.Limit.MAX);       
    Display.setCursor(0, 30); Display.print(data);

    sprintf(data," CH5:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_5.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_5.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_5.Limit.MAX);       
    Display.setCursor(0, 40); Display.print(data);    
  }  
  else
  {
    Display.setCursor(0, ((UpDown_Menu_V1-5)*10)); Display.print(Pos_menu==Enter_1?"*":">");

    sprintf(data," CH6:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_6.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_6.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_6.Limit.MAX);   
    Display.setCursor(0, 0); Display.print(data);

    sprintf(data," CH7:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_7.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_7.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_7.Limit.MAX);       
    Display.setCursor(0, 10); Display.print(data);

    sprintf(data," CH8:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_8.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_8.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_8.Limit.MAX);       
    Display.setCursor(0, 20); Display.print(data);

    sprintf(data," CH9:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_9.Limit.MIN,\
                                 _Virtual_Machine_.CHANNEL.Channel_9.Limit.MIDDLE,\
                                 _Virtual_Machine_.CHANNEL.Channel_9.Limit.MAX);       
    Display.setCursor(0, 30); Display.print(data);

    sprintf(data," CH10:%d-%d-%d",_Virtual_Machine_.CHANNEL.Channel_10.Limit.MIN,\
                                  _Virtual_Machine_.CHANNEL.Channel_10.Limit.MIDDLE,\
                                  _Virtual_Machine_.CHANNEL.Channel_10.Limit.MAX);       
    Display.setCursor(0, 40); Display.print(data);        
  }

  if(STEP_ACTION==0) {Display.setCursor(0, 50); Display.print(" ------------------");}
  else if (STEP_ACTION==1) {Display.setCursor(0, 50); Display.print(" ------Set Min-----");}
  else if (STEP_ACTION==2) {Display.setCursor(0, 50); Display.print(" ----Set Middle----");}
  else {Display.setCursor(0, 50); Display.print(" ------Set Max-----");}

  Display.display();
}

static void MENU_SET_PPM(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  char data[30];

  if( strcmp((char*)Machine.DUMMY_1,(char*)LGO_GREEN)==0 )
  {if( UpDown_Menu_V1<6 ) 
  { 
    Display.setCursor(0, (UpDown_Menu_V1*10)); Display.print(Pos_menu==Enter_1?"*":">"); 
  }
  else if( UpDown_Menu_V1>=6 && UpDown_Menu_V1<12 ) 
  { 
    Display.setCursor(0, ((UpDown_Menu_V1-6)*10)); Display.print(Pos_menu==Enter_1?"*":">"); 
  }
  else if( UpDown_Menu_V1>=12 && UpDown_Menu_V1<18 ) 
  { 
    Display.setCursor(0, ((UpDown_Menu_V1-12)*10)); Display.print(Pos_menu==Enter_1?"*":">"); 
  }
  else
  { 
    Display.setCursor(0, ((UpDown_Menu_V1-18)*10)); Display.print(Pos_menu==Enter_1?"*":">"); 
  }}

  if( UpDown_Menu_V1<6 )
  {
    sprintf(data," CH1 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_1.PPM_Min);
    Display.setCursor(0, 0); Display.print(data);
    sprintf(data," CH1 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_1.PPM_Max);
    Display.setCursor(0, 10); Display.print(data);

    sprintf(data," CH2 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_2.PPM_Min);
    Display.setCursor(0, 20); Display.print(data);
    sprintf(data," CH2 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_2.PPM_Max);
    Display.setCursor(0, 30); Display.print(data);  

    sprintf(data," CH3 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_3.PPM_Min);
    Display.setCursor(0, 40); Display.print(data);
    sprintf(data," CH3 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_3.PPM_Max);
    Display.setCursor(0, 50); Display.print(data);    
  }
  else if( UpDown_Menu_V1>=6 && UpDown_Menu_V1<12 )
  {
    sprintf(data," CH4 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_4.PPM_Min);
    Display.setCursor(0, 0); Display.print(data);
    sprintf(data," CH4 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_4.PPM_Max);
    Display.setCursor(0, 10); Display.print(data);

    sprintf(data," CH5 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_5.PPM_Min);
    Display.setCursor(0, 20); Display.print(data);
    sprintf(data," CH5 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_5.PPM_Max);
    Display.setCursor(0, 30); Display.print(data);  

    sprintf(data," CH6 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_6.PPM_Min);
    Display.setCursor(0, 40); Display.print(data);
    sprintf(data," CH6 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_6.PPM_Max);
    Display.setCursor(0, 50); Display.print(data);  
  }
  else if( UpDown_Menu_V1>=12 && UpDown_Menu_V1<18 )
  {
    sprintf(data," CH7 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_7.PPM_Min);
    Display.setCursor(0, 0); Display.print(data);
    sprintf(data," CH7 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_7.PPM_Max);
    Display.setCursor(0, 10); Display.print(data);

    sprintf(data," CH8 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_8.PPM_Min);
    Display.setCursor(0, 20); Display.print(data);
    sprintf(data," CH8 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_8.PPM_Max);
    Display.setCursor(0, 30); Display.print(data);  

    sprintf(data," CH9 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_9.PPM_Min);
    Display.setCursor(0, 40); Display.print(data);
    sprintf(data," CH9 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_9.PPM_Max);
    Display.setCursor(0, 50); Display.print(data);  
  }  
  else 
  {
    sprintf(data," CH10 PPM MIN:%d", _Virtual_Machine_.CHANNEL.Channel_10.PPM_Min);
    Display.setCursor(0, 0); Display.print(data);
    sprintf(data," CH10 PPM MAX:%d", _Virtual_Machine_.CHANNEL.Channel_10.PPM_Max);
    Display.setCursor(0, 10); Display.print(data);   
  }  

  Display.display();
}

static void MENU_SAVE_PPM(uint8_t Status) /* 0=save, 1=error */
{
  Display.clearDisplay();
  Display.setTextSize(1);

  if(Status==0)
  {
    Display.setCursor(0, 15); Display.print("SAVE PPM VALUE");
    Display.setCursor(0, 35); Display.print("Please Wait...");
  }
  else 
  {
    Display.setCursor(0, 15); Display.print("SAVE PPM VALUE");
    Display.setTextSize(2);
    Display.setCursor(0, 45); Display.print("ERROR...!!");
  }
  
  Display.display();
}

static void MENU_TIME_DOWN(uint8_t *Minute, uint8_t *Second)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  Display.setCursor(22, 10); Display.print("SET COUNTDOWN");
  
  Display.setTextSize(2);
  char data[20];
  sprintf(data,"%.2d:%.2d", *Minute, *Second);
  Display.setCursor(32, 30); Display.print(data);   
  
  Display.display();  
}

static void MENU_SET_THR_LOCK(uint8_t SelectSW, uint8_t SelectValue)
{

  /**
   *      SW1   SW2   SW3   SW4
   * Min  11    21    31    41
   * 
   * Mid  12    22    32    42
   * 
   * Max  13    23    33    43
   * 
  */

  Display.clearDisplay();
  Display.setTextSize(1);

  Display.setCursor(10, 5); Display.print("SET THROTTLE LOCK");

  if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
  {if(UpDown_Menu_V1==0)
  {Display.setCursor(0, 40); Display.print(Pos_menu==Enter_1?"*":">");}
  else
  {Display.setCursor(0, 50); Display.print(Pos_menu==Enter_1?"*":">");}

  Display.setCursor(0, 25); Display.print("LOCK CH3-Throttle");

  if(SelectSW==0) {Display.setCursor(0, 40); Display.print(" Select: NONE!");}
  else if(SelectSW==1) {Display.setCursor(0, 40); Display.print(" Select: Swicth 1");}
  else if(SelectSW==2) {Display.setCursor(0, 40); Display.print(" Select: Swicth 2");}
  else if(SelectSW==3) {Display.setCursor(0, 40); Display.print(" Select: Swicth 3");}
  else {Display.setCursor(0, 40); Display.print(" Select: Swicth 4");}

  if(SelectValue==0) {Display.setCursor(0, 50); Display.print(" Lock Value: MIN");}
  else if(SelectValue==1) {Display.setCursor(0, 50); Display.print(" Lock Value: MIDDLE");}
  else {Display.setCursor(0, 50); Display.print(" Lock Value: MAX");} }
  
  Display.display();  
}

static void MENU_MIX_CHANNEL(uint8_t OnOff, \
                             volatile uint16_t CH1_TRIP_PERCENT, volatile uint16_t CH2_TRIP_PERCENT)
{
  char data[20];

  Display.clearDisplay();
  Display.setTextSize(1);

  if(UpDown_Menu_V1==0)
  {Display.setCursor(0, 20); Display.print(Pos_menu==Enter_1?"*":">");}
  else if(UpDown_Menu_V1==1)
  {Display.setCursor(0, 30); Display.print(Pos_menu==Enter_1?"*":">");}
  else 
  {Display.setCursor(0, 40); Display.print(Pos_menu==Enter_1?"*":">");}

  Display.setCursor(20, 1); Display.print("CHANNEL MIXING");

  Display.setCursor(0, 20); Display.print(OnOff==TRUE?" MIX: ON":" MIX: OFF");

  sprintf(data," CH1:%d",(CH1_TRIP_PERCENT));
  Display.setCursor(0, 30); Display.print(data);
  Display.setCursor(50, 30); Display.print("%");
  sprintf(data," CH2:%d",(CH2_TRIP_PERCENT));
  Display.setCursor(0, 40); Display.print(data);
  Display.setCursor(50, 40); Display.print("%");  

  Display.display();  
}

static void MENU_DISPLAY(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  char data[50];

  Display.setCursor(30, 1); Display.print(" DISPLAY ");
  
  sprintf(data,"CH1:%d",map(RF_DATA_SEND.CH1,0,255,0,100));
  Display.setCursor(0, 15); Display.print(data);

  sprintf(data,"CH2:%d",map(RF_DATA_SEND.CH2,0,255,0,100));
  Display.setCursor(0, 25); Display.print(data);

  sprintf(data,"CH3:%d",map(RF_DATA_SEND.CH3,0,255,0,100));
  Display.setCursor(0, 35); Display.print(data);

  sprintf(data,"CH4:%d",map(RF_DATA_SEND.CH4,0,255,0,100));
  Display.setCursor(0, 45); Display.print(data);

  sprintf(data,"CH5:%d",map(RF_DATA_SEND.CH5,0,255,0,100));
  Display.setCursor(0, 55); Display.print(data);

  sprintf(data,"CH6:%d",map(RF_DATA_SEND.CH6,0,255,0,100));
  Display.setCursor(65, 15); Display.print(data);

  sprintf(data,"CH7:%d",map(RF_DATA_SEND.CH7,0,255,0,100));
  Display.setCursor(65, 25); Display.print(data);

  sprintf(data,"CH8:%d",map(RF_DATA_SEND.CH8,0,255,0,100));
  Display.setCursor(65, 35); Display.print(data);

  sprintf(data,"CH9:%d",map(RF_DATA_SEND.CH9,0,255,0,100));
  Display.setCursor(65, 45); Display.print(data);

  sprintf(data,"CH10:%d",map(RF_DATA_SEND.CH10,0,255,0,100));
  Display.setCursor(65, 55); Display.print(data);

  Display.display();  
}

static void MENU_SET_PIN_TX(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  Display.setCursor(35, 2); Display.print("TX BATTERY");
  Display.setCursor(0, 20); Display.print("TX:     V");
  Display.setCursor(17, 20); Display.print(PIN_TX);
  Display.setCursor(0, 40); Display.print("BATTERY LOW:      V");
  Display.setCursor(75, 40); Display.print(_Virtual_Machine_.TX_PIN_LOW);

  Display.display();
}

static void MENU_SET_PIN_RX(void)
{
  Display.clearDisplay();
  Display.setTextSize(1);

  Display.setCursor(35, 2); Display.print("RX BATTERY");
  Display.setCursor(0, 20); Display.print("RX:     V");
  Display.setCursor(17, 20); Display.print(PIN_RX);
  Display.setCursor(0, 40); Display.print("BATTERY LOW:      V");
  Display.setCursor(75, 40); Display.print(_Virtual_Machine_.RX_PIN_LOW);

  Display.display();
}

static void MENU_BIND_RX(uint8_t STEP)
{
  char data[30];

  Display.clearDisplay();
  Display.setTextSize(1);

  if(STEP==0)
  {
    sprintf(data,"TX Info: %d",Machine.ADDRESS.TX_INFO);
    Display.setCursor(0, 0); Display.print(data);
    sprintf(data,"RX Info: %d",Machine.ADDRESS.RX_INFO);
    Display.setCursor(0, 10); Display.print(data);

    sprintf(data,"Address Read: %d",Machine.ADDRESS.RF_Address_Read);
    Display.setCursor(0, 20); Display.print(data);
    sprintf(data,"Address Write: %d",Machine.ADDRESS.RF_Address_Write);
    Display.setCursor(0, 30); Display.print(data);
    sprintf(data,"Channel: %d",Machine.ADDRESS.RF_Channel);
    Display.setCursor(0, 40); Display.print(data);
    sprintf(data,"Next Channel: %d",Machine.ADDRESS.RF_Next_Channel);
    Display.setCursor(0, 50); Display.print(data);
  }
  else if(STEP==1)
  {
    Display.setCursor(10, 20); Display.print("FIND RX...");
    Display.setCursor(30, 40); Display.print("PLEASE WAIT !!!");
  }
  else if(STEP==2)
  {
    Display.setCursor(20, 30); Display.print("CONNECT OK !!!");
  }  
  else
  {
    Display.setCursor(30, 20); Display.print("ERROR...!!!");
    Display.setCursor(30, 40); Display.print("NOT FIND RX");
  }    

  Display.display();
}

static uint8_t Read_Button_OK(void) /* 1<3000 ; 2>=3000 */
{
  static uint8_t STEP=0;
  static uint32_t Tick_start=0;
  static uint32_t Tick_stop=0;  
  if( DATA_READ.BT_OK==0 )
  {
    if(STEP==0)
    {
      Tick_start=millis();
      STEP=1;
    }
    else if(STEP==1)
    {
      if( strcmp((char*)Machine.ADDRESS.DUMMY_2,(char*)LGO_TECH)==0 )
      {if( (uint32_t)(millis()-Tick_start)>=TIME_PRESS_LONG )
      {
        RESULT_BUTTON_OK=2;
        STEP=2;    
      }}
    }
  }
  else 
  {
    if(STEP==1)
    {
      Tick_stop=millis();
      
      if( (uint32_t)(Tick_stop-Tick_start)<TIME_PRESS_LONG ) RESULT_BUTTON_OK=1;

      STEP=2;
    }

    if(STEP==2)
    {
      STEP=0;
      Tick_start=0;
      Tick_stop=0;  
    }
  }

  // Serial1.println(RESULT);

  return RESULT_BUTTON_OK;
}

static uint8_t Read_Button_BACK(void) /* 1<3000 ; 2>=3000 */
{
  static uint8_t STEP=0;
  static uint32_t Tick_start=0;
  static uint32_t Tick_stop=0;  
  if( DATA_READ.BT_BACK==0 )
  {
    if(STEP==0)
    {
      Tick_start=millis();
      STEP=1;
    }
    else if(STEP==1)
    {
      if( (uint32_t)(millis()-Tick_start)>=TIME_PRESS_LONG )
      {
        RESULT_BUTTON_BACK=2;
        STEP=2;    
      }
    }
  }
  else 
  {
    if(STEP==1)
    {
      Tick_stop=millis();
      
      if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
      {if( (uint32_t)(Tick_stop-Tick_start)<TIME_PRESS_LONG ) RESULT_BUTTON_BACK=1;}

      STEP=2;
    }

    if(STEP==2)
    {
      STEP=0;
      Tick_start=0;
      Tick_stop=0;  
    }
  }

  // Serial1.println(RESULT);

  return RESULT_BUTTON_BACK;
}

static void SAVE_CONFIG(void)
{
  memcpy(&Machine,&_Virtual_Machine_,sizeof(_Virtual_Machine_));

  memcpy(&NewChannelConfig,&Machine.CHANNEL,sizeof(Machine.CHANNEL));
  memcpy(&LastChannelConfig,&NewChannelConfig,sizeof(NewChannelConfig));
}

void LCD_INIT(void)
{
  delay(200);
  while(!Display.begin(LCD_ADDRESS, true))
  {
    LED_ON;
    BUZZER_ON;
  }
  LED_OF;
  BUZZER_OF;

  if( strcmp((char*)Machine.DUMMY_4,(char*)LGO_MADEINVN)==0 )
  {
    memset(&_Virtual_Machine_,0,sizeof(_Virtual_Machine_));

    RF_SCREEN = (float)((float)(Machine.ADDRESS.RF_Channel+2400)/1000);

    LOGO_START();    

    TickLCD=micros();
  }

}

void LCD_MAIN(void)
{
  static uint16_t ST1, ST2, ST3, ST4;

  if(Pos_menu==Screen) /* Man hinh chinh */
  {
    static uint8_t Start_CountDown=0;

    if( (uint32_t)(micros()-TickLCD)>=10000 )
    {
      ST1 = map(Machine.CHANNEL.Channel_1.Trim_Value, Machine.CHANNEL.Channel_1.Limit.MIN, \
                Machine.CHANNEL.Channel_1.Limit.MAX,0,100);  
      ST2 = map(Machine.CHANNEL.Channel_2.Trim_Value, Machine.CHANNEL.Channel_2.Limit.MIN, \
                Machine.CHANNEL.Channel_2.Limit.MAX,0,100); 
      ST3 = map(Machine.CHANNEL.Channel_3.Trim_Value, Machine.CHANNEL.Channel_3.Limit.MIN, \
                Machine.CHANNEL.Channel_3.Limit.MAX,0,100); 
      ST4 = map(Machine.CHANNEL.Channel_4.Trim_Value, Machine.CHANNEL.Channel_4.Limit.MIN, \
                Machine.CHANNEL.Channel_4.Limit.MAX,0,100);                                                 

      Screen_main(&PIN_TX, &PIN_RX, &ST1, &ST2, &ST3, &ST4, \
                  &Machine.Minute, &Machine.Second, \
                  (char*)"V24OL", &RF_SCREEN, &Machine.ADDRESS.RX_INFO);

      TickLCD=micros();
    }

    if(Start_CountDown==1) /* Start count down */
    {
      Check_CountDown(2);
    }

    /* OK BUTTON */
    if( Read_Button_OK()==1 ) /* OK Press short */
    {
      if( Start_CountDown==0 )
      {
        if( Machine.Second>0 or Machine.Minute>0 )
        {
          BUZZER_ON; 
          Check_CountDown(1);
          Start_CountDown=1;       
          delay(500) ;
        }
      }

      RESULT_BUTTON_OK=0;
      RESULT_BUTTON_BACK=0;      
    }
    else if( Read_Button_OK()==2 ) /* OK Press long */
    {
      Pos_menu=MainMenu; 

      RESULT_BUTTON_OK=0;
      RESULT_BUTTON_BACK=0;
    }

    /* BACK BUTTON */
    if( Read_Button_BACK()==1 ) /* BACK press short */
    {
      if( strcmp((char*)Machine.DUMMY_1,(char*)LGO_GREEN)==0 )
      {LED_OF;
      BUZZER_OF;
      Check_CountDown(3);
      Start_CountDown=0;

      RESULT_BUTTON_OK=0;
      RESULT_BUTTON_BACK=0;}
    }      
  }

  else if(Pos_menu==MainMenu) /* Menu chinh */
  {
    Menu_MAIN();
      
    /*Button OK*/
    if( (Read_Button_OK()==1)&&(strcmp((char*)Machine.DUMMY_4,(char*)LGO_MADEINVN )==0) ) /* OK Press short */
    {
      Pos_menu+=1;

      if( Pos_menu==ChoiceMenuMain ) /* Select Menu Version */
      {
        switch (MenuUPDOWN)
        {
          case Version:
            MENU_VERSION();
            break;

          case ChannelReserse:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));
            MENU_REVERSE();

            UpDown_Menu_V1=0;
            UpDown_Menu_V1_MAX=9;
            break;

          case EndPoint:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));
            MENU_END_POINT();

            UpDown_Menu_V1=0;
            UpDown_Menu_V1_MAX=9;          
            break;            

          case GetChannelLimit:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));
            MENU_GET_CHANNEL_LIMIT();

            UpDown_Menu_V1=0;
            UpDown_Menu_V1_MAX=9;              
            break;

          case Subtrim:
            FEATURE_IN_DEVELOPMENT();
            break;

          case SetPPM:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));
            MENU_SET_PPM();

            UpDown_Menu_V1=0;
            UpDown_Menu_V1_MAX=19;    
            break;

          case BindRX:
            MENU_BIND_RX(0);
            break;

          case MixChannel:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));

            MENU_MIX_CHANNEL(_Virtual_Machine_.CheckMixing,\
                            _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT,\
                            _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT);  

            UpDown_Menu_V1=0;
            UpDown_Menu_V1_MAX=3;
            break;

          case DisPlay:
            MENU_DISPLAY();
            break;

          case MapChannel:
            FEATURE_IN_DEVELOPMENT();
            break;

          case SetThrottleLock:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));
            MENU_SET_THR_LOCK(_Virtual_Machine_.Throttle_Lock, _Virtual_Machine_.Throttle_Lock_Value);
            
            UpDown_Menu_V1=0;
            UpDown_Menu_V1_MAX=2;
            break;

          case SetTimeDown:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));
            MENU_TIME_DOWN(&_Virtual_Machine_.Minute, &_Virtual_Machine_.Second);
            break;

          case SetTXBattery:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));
            MENU_SET_PIN_TX();
            break;

          case SetRXBattery:
            memcpy(&_Virtual_Machine_,&Machine,sizeof(Machine));
            MENU_SET_PIN_RX();
            break;

          case AddModel:
            FEATURE_IN_DEVELOPMENT();
            break;

          case SelectModel:
            FEATURE_IN_DEVELOPMENT();
            break;

          case DeleteModel:
            FEATURE_IN_DEVELOPMENT();
            break;

          case ResetDefault:
            MENU_RESET(0);
            break;                                                                                                                                                                                              
          
          default:
            FEATURE_IN_DEVELOPMENT();
            break;
        }

      } /* if( Pos_menu==ChoiceMenuMain ) */

      RESULT_BUTTON_OK=0;
      RESULT_BUTTON_BACK=0;

    }

    /* Button BACK */
    if( Read_Button_BACK()==1 ) /* BACK press short */
    {
      if(Pos_menu<=0) Pos_menu=0;
      else Pos_menu-=1;

      RESULT_BUTTON_OK=0;
      RESULT_BUTTON_BACK=0;
    }  

  }
  else if(Pos_menu==ChoiceMenuMain) /* Menu chuc nang */
  {
    switch (MenuUPDOWN)
    {
      case ChannelReserse:
        MENU_REVERSE();
        break;

      case SetTXBattery:
        MENU_SET_PIN_TX();
        break;

      case SetRXBattery:
        MENU_SET_PIN_RX();
        break;

      case DisPlay:
        MENU_DISPLAY();
        break;

      case SetPPM:
        MENU_SET_PPM();
        break;

      case GetChannelLimit:
        MENU_GET_CHANNEL_LIMIT();
        break;

      case ResetDefault:
        MENU_RESET(0);
        break;
        
      case BindRX:
        MENU_BIND_RX(0);
        break;     

      case SetTimeDown:
        MENU_TIME_DOWN(&_Virtual_Machine_.Minute, &_Virtual_Machine_.Second);
        break;

      case SetThrottleLock:
        MENU_SET_THR_LOCK(_Virtual_Machine_.Throttle_Lock, _Virtual_Machine_.Throttle_Lock_Value);
        break;

      case EndPoint:
        MENU_END_POINT();
        break; 

      case MixChannel:
        MENU_MIX_CHANNEL(_Virtual_Machine_.CheckMixing,\
                      _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT,\
                      _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT);         
        break;                                                                                    
      
      default:
        break;
    } /* switch (MenuUPDOWN) */

    if( strcmp((char*)Machine.DUMMY_5,(char*)LGO_NhanNguyen)==0 )
    {
      /* Button OK */
      if( Read_Button_OK()==1 ) /* OK Press short */
      {
        if( (MenuUPDOWN==SetPPM) || (MenuUPDOWN==EndPoint) || (MenuUPDOWN==SetThrottleLock) ) Pos_menu+=1;
        else if( MenuUPDOWN==MixChannel )
        {
          if(UpDown_Menu_V1==0)
          {_Virtual_Machine_.CheckMixing = !_Virtual_Machine_.CheckMixing;}
          else if( (UpDown_Menu_V1==1) or (UpDown_Menu_V1==2) )
          { Pos_menu+=1; }
        }

        RESULT_BUTTON_OK=0;
        RESULT_BUTTON_BACK=0;      
      }
      else if( Read_Button_OK()==2 ) /* OK Press long */
      {
        if( MenuUPDOWN==ChannelReserse ) 
        {
          if( UpDown_Menu_V1==0 ) _Virtual_Machine_.CHANNEL.Channel_1.Reverse=!_Virtual_Machine_.CHANNEL.Channel_1.Reverse;
          else if( UpDown_Menu_V1==1 ) _Virtual_Machine_.CHANNEL.Channel_2.Reverse=!_Virtual_Machine_.CHANNEL.Channel_2.Reverse;
          else if( UpDown_Menu_V1==2 ) _Virtual_Machine_.CHANNEL.Channel_3.Reverse=!_Virtual_Machine_.CHANNEL.Channel_3.Reverse;
          else if( UpDown_Menu_V1==3 ) _Virtual_Machine_.CHANNEL.Channel_4.Reverse=!_Virtual_Machine_.CHANNEL.Channel_4.Reverse;
          else if( UpDown_Menu_V1==4 ) _Virtual_Machine_.CHANNEL.Channel_5.Reverse=!_Virtual_Machine_.CHANNEL.Channel_5.Reverse;
          else if( UpDown_Menu_V1==5 ) _Virtual_Machine_.CHANNEL.Channel_6.Reverse=!_Virtual_Machine_.CHANNEL.Channel_6.Reverse;
          else if( UpDown_Menu_V1==6 ) _Virtual_Machine_.CHANNEL.Channel_7.Reverse=!_Virtual_Machine_.CHANNEL.Channel_7.Reverse;
          else if( UpDown_Menu_V1==7 ) _Virtual_Machine_.CHANNEL.Channel_8.Reverse=!_Virtual_Machine_.CHANNEL.Channel_8.Reverse;
          else if( UpDown_Menu_V1==8 ) _Virtual_Machine_.CHANNEL.Channel_9.Reverse=!_Virtual_Machine_.CHANNEL.Channel_9.Reverse;
          else _Virtual_Machine_.CHANNEL.Channel_10.Reverse=!_Virtual_Machine_.CHANNEL.Channel_10.Reverse;
        }
        else if( MenuUPDOWN==GetChannelLimit ) Pos_menu+=1;
        else if( MenuUPDOWN==ResetDefault ) 
        {
          if( strcmp((char*)Machine.ADDRESS.DUMMY_2,(char*)LGO_TECH)==0 )
          {LED_ON;
          BUZZER_ON;

          MENU_RESET(1);
          RESET_MACHINE_DEFAULT();
          WRITE_CONFIG_MACHINE(&Machine);
          delay(3000);

          LED_OF;
          BUZZER_OF;}

          Pos_menu-=1;
        }
        else if( MenuUPDOWN==BindRX ) 
        {
          MENU_BIND_RX(1);
          Pos_menu+=1;
        }

        RESULT_BUTTON_OK=0;
        RESULT_BUTTON_BACK=0;
      }
      
      /* Button BACK */
      if( Read_Button_BACK()==1 ) /* BACK press short */
      {
        if(Pos_menu<=0) Pos_menu=0;
        else Pos_menu-=1;

        RESULT_BUTTON_OK=0;
        RESULT_BUTTON_BACK=0;
      }  
      else if( Read_Button_BACK()==2 ) /* BACK press long */
      {
        if( MenuUPDOWN==SetPPM ) /* Wait Set PPM on RX */
        {
          Feature_send=Send_PPM;
          RF_DATA_SEND.Feature=Get_PPM;
          Pos_menu=Enter_2;
        }
        else if( (MenuUPDOWN==EndPoint) || (MenuUPDOWN==MixChannel) )
        {
          auto Lambda = [](volatile uint8_t *TripPercent,volatile uint8_t *TripMin,volatile uint8_t *TripMax)
          {
            uint16_t Percent=0;
            Percent = ((100-(*TripPercent)) * 100)/100;
            *TripMin = (uint8_t)(Percent/2);
            *TripMax = (uint8_t)(255-(Percent/2));
          };

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_MAX);

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_MAX);

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_3.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_3.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_3.Limit.TRIP_MAX); 

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_4.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_4.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_4.Limit.TRIP_MAX); 

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_5.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_5.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_5.Limit.TRIP_MAX); 

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_6.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_6.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_6.Limit.TRIP_MAX); 

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_7.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_7.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_7.Limit.TRIP_MAX); 

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_8.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_8.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_8.Limit.TRIP_MAX); 

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_9.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_9.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_9.Limit.TRIP_MAX);     

          Lambda(&_Virtual_Machine_.CHANNEL.Channel_10.Limit.TRIP_PERCENT,\
                 &_Virtual_Machine_.CHANNEL.Channel_10.Limit.TRIP_MIN,\
                 &_Virtual_Machine_.CHANNEL.Channel_10.Limit.TRIP_MAX);                                                                                                                                                     

          LED_ON;
          BUZZER_ON;
          SAVE_CONFIG();
          WRITE_CONFIG_MACHINE(&Machine);
          delay(1000);
          LED_OF;
          BUZZER_OF;

          if(Pos_menu<=0) Pos_menu=0;
          else Pos_menu-=1;                
        }
        else if((MenuUPDOWN==ChannelReserse) ||\
                (MenuUPDOWN==SetThrottleLock) ||\
                (MenuUPDOWN==GetChannelLimit) ||\
                (MenuUPDOWN==SetTimeDown) ||\
                (MenuUPDOWN==SetTXBattery) ||\
                (MenuUPDOWN==SetRXBattery) 
               )
        {
          if( strcmp((char*)Machine.DUMMY_5,(char*)LGO_NhanNguyen)==0 )
          {LED_ON;
          BUZZER_ON;
          SAVE_CONFIG();       
          WRITE_CONFIG_MACHINE(&Machine);
          delay(1000);
          LED_OF;
          BUZZER_OF;}

          if(Pos_menu<=0) Pos_menu=0;
          else Pos_menu-=1;      
        }
        else /* Back to Menu */
        {
          if(Pos_menu<=0) Pos_menu=0;
          else Pos_menu-=1;
        }

        RESULT_BUTTON_OK=0;
        RESULT_BUTTON_BACK=0;
      } 
    }
  } /* Menu chuc nang */
  else if(Pos_menu==Enter_1) /* Enter 1 */ 
  {
    if( MenuUPDOWN==SetPPM ) 
    {
      MENU_SET_PPM();

      if( Read_Button_OK()==1 ) /* OK Press short */
      {
        Pos_menu-=1;

        RESULT_BUTTON_OK=0;
        RESULT_BUTTON_BACK=0;      
      }
    }
    else if( MenuUPDOWN==GetChannelLimit )
    {
      MENU_GET_CHANNEL_LIMIT();

      if(ACTION_GET_LIMIT(UpDown_Menu_V1)==TRUE) Pos_menu-=1;
    }
    else if( MenuUPDOWN==BindRX )
    {
      RF_BIND_MAIN();
      if( RF_BIND_RESULT==1 ) /* Bind OK */
      {
        LED_ON;
        BUZZER_ON;
        MENU_BIND_RX(2); /* OK */
        delay(2000);
        LED_OF;
        BUZZER_OF;   

        RF_SCREEN = (float)((float)(Machine.ADDRESS.RF_Channel+2400)/1000);     

        Pos_menu-=1;
      }
      else if( RF_BIND_RESULT==2 ) /* Bind ERROR */
      {
        LED_ON;
        BUZZER_ON;        
        MENU_BIND_RX(3); /* ERROR */
        delay(2000);
        LED_OF;
        BUZZER_OF;           

        Pos_menu-=1;
      }
    }
    else if( MenuUPDOWN==EndPoint )
    {
      MENU_END_POINT();

      if( Read_Button_OK()==1 ) /* OK Press short */
      {
        Pos_menu-=1;

        RESULT_BUTTON_OK=0;
        RESULT_BUTTON_BACK=0;      
      }      
    }
    else if( MenuUPDOWN==MixChannel )
    {
      MENU_MIX_CHANNEL(_Virtual_Machine_.CheckMixing,\
                      _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT,\
                      _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT);                    

      if( Read_Button_OK()==1 ) /* OK Press short */
      {
        Pos_menu-=1;

        RESULT_BUTTON_OK=0;
        RESULT_BUTTON_BACK=0;      
      }      
    }
    else if( MenuUPDOWN==SetThrottleLock )
    {
      MENU_SET_THR_LOCK(_Virtual_Machine_.Throttle_Lock, _Virtual_Machine_.Throttle_Lock_Value);

      if( Read_Button_OK()==1 ) /* OK Press short */
      {
        Pos_menu-=1;

        RESULT_BUTTON_OK=0;
        RESULT_BUTTON_BACK=0;      
      }         
    }

  }
  else if(Pos_menu==Enter_2) /* Enter 2 */
  {
    if( MenuUPDOWN==SetPPM )
    {
      if(RF_RESULT_PPM==1) /*OK*/
      {
        LED_ON;
        BUZZER_ON;
        SAVE_CONFIG();
        WRITE_CONFIG_MACHINE(&Machine);
        delay(1000);
        LED_OF;
        BUZZER_OF;

        Pos_menu=MainMenu;
      }
      else if(RF_RESULT_PPM==2) /*Time out*/
      {
        MENU_SAVE_PPM(1);
        LED_ON;
        BUZZER_ON;
        delay(2000);
        LED_OF;
        BUZZER_OF;
        Pos_menu=MainMenu;
      }
      else MENU_SAVE_PPM(0);
    }
    
  }

  /* Button UP */
  if( DATA_READ.BT_UP<=500 )
  {
    delay(50);

    if(Pos_menu==MainMenu)
    {
      if(MenuUPDOWN<=0) MenuUPDOWN=MENU_TOTAL;
      else MenuUPDOWN-=1;
    }
    else if(Pos_menu==ChoiceMenuMain)
    {
      if( (MenuUPDOWN==ChannelReserse) or\
          (MenuUPDOWN==GetChannelLimit) or\
          (MenuUPDOWN==MixChannel) or\
          (MenuUPDOWN==SetThrottleLock))
      {
        if(UpDown_Menu_V1<=0) UpDown_Menu_V1=UpDown_Menu_V1_MAX;
        else UpDown_Menu_V1-=1;
      }
      else if( MenuUPDOWN==SetTXBattery )
      {
        if( _Virtual_Machine_.TX_PIN_LOW>=30 ) _Virtual_Machine_.TX_PIN_LOW=30;
        else _Virtual_Machine_.TX_PIN_LOW+=0.1;
      }
      else if( MenuUPDOWN==SetRXBattery )
      {
        if( _Virtual_Machine_.RX_PIN_LOW>=30 ) _Virtual_Machine_.RX_PIN_LOW=30;
        else _Virtual_Machine_.RX_PIN_LOW+=0.1;
      }
      else if( MenuUPDOWN==SetPPM )
      {
        if(UpDown_Menu_V1<=0) UpDown_Menu_V1=UpDown_Menu_V1_MAX;
        else UpDown_Menu_V1-=1;
      }
      else if( MenuUPDOWN==SetTimeDown )
      {
        if(_Virtual_Machine_.Minute<99)
        {
          if( _Virtual_Machine_.Second>=59 ) 
          {
            _Virtual_Machine_.Second=0;
            _Virtual_Machine_.Minute+=1;
          }
          else 
          {
            _Virtual_Machine_.Second+=1;
          }
        }
      }
      else if( MenuUPDOWN==EndPoint )
      {
        if(UpDown_Menu_V1<=0) UpDown_Menu_V1=UpDown_Menu_V1_MAX;
        else UpDown_Menu_V1-=1;
      }
    }
    else if(Pos_menu==Enter_1)
    {
      if( MenuUPDOWN==SetPPM )
      {
        auto Lambda = [](volatile uint16_t *Input)
        {
          if(*Input>=PPM_MAX) *Input=PPM_MAX;
          else *Input+=10;
        };

        if( UpDown_Menu_V1==0 )Lambda(&_Virtual_Machine_.CHANNEL.Channel_1.PPM_Min);
        else if( UpDown_Menu_V1==1 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_1.PPM_Max);
        else if( UpDown_Menu_V1==2 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_2.PPM_Min);
        else if( UpDown_Menu_V1==3 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_2.PPM_Max);
        else if( UpDown_Menu_V1==4 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_3.PPM_Min);
        else if( UpDown_Menu_V1==5 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_3.PPM_Max);
        else if( UpDown_Menu_V1==6 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_4.PPM_Min);
        else if( UpDown_Menu_V1==7 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_4.PPM_Max);
        else if( UpDown_Menu_V1==8 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_5.PPM_Min);
        else if( UpDown_Menu_V1==9 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_5.PPM_Max);
        else if( UpDown_Menu_V1==10 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_6.PPM_Min);
        else if( UpDown_Menu_V1==11 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_6.PPM_Max);
        else if( UpDown_Menu_V1==12 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_7.PPM_Min);
        else if( UpDown_Menu_V1==13 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_7.PPM_Max);
        else if( UpDown_Menu_V1==14 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_8.PPM_Min);
        else if( UpDown_Menu_V1==15 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_8.PPM_Max);
        else if( UpDown_Menu_V1==16 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_9.PPM_Min);
        else if( UpDown_Menu_V1==17 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_9.PPM_Max);
        else if( UpDown_Menu_V1==18 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_10.PPM_Min);
        else if( UpDown_Menu_V1==19 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_10.PPM_Max);
      }
      else if( MenuUPDOWN==EndPoint )
      {
        auto Lambda = [](volatile uint8_t *Input)
        {
          if(*Input>=100) *Input=100;
          else *Input+=1;
        };

        if( UpDown_Menu_V1==0 )Lambda(&_Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==1 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==2 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_3.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==3 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_4.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==4 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_5.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==5 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_6.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==6 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_7.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==7 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_8.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==8 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_9.Limit.TRIP_PERCENT);
        else if( UpDown_Menu_V1==9 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_10.Limit.TRIP_PERCENT);        
      }
      else if( MenuUPDOWN==MixChannel )
      {
        if( UpDown_Menu_V1==1 )
        {
          if( _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT<100 )
          {
            _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT+=1;
          }
          else _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT=100;
        }
        else if( UpDown_Menu_V1==2 )
        {
          if( _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT<100 )
          {
            _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT+=1;
          }
          else _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT=100;
        } else {;;}
      }
      else if( MenuUPDOWN==SetThrottleLock )
      {
        if( UpDown_Menu_V1==0 )
        {
          if(_Virtual_Machine_.Throttle_Lock>=4) _Virtual_Machine_.Throttle_Lock=0;
          else _Virtual_Machine_.Throttle_Lock+=1;
        }
        else
        {
          if(_Virtual_Machine_.Throttle_Lock_Value>=2) _Virtual_Machine_.Throttle_Lock_Value=0;
          else _Virtual_Machine_.Throttle_Lock_Value+=1;
        }
      }
    }

  } /* End of if( DATA_READ.BT_UP<=500 )  */

  /* Button DOWN */
  if( DATA_READ.BT_DOWN<=500 )
  {
    delay(50);

    if( strcmp((char*)Machine.CHANNEL.DUMMY_3,(char*)LGO_WEB)==0 )
    {
      if(Pos_menu==MainMenu)
      {
        if(MenuUPDOWN>=MENU_TOTAL) MenuUPDOWN=0;
        else MenuUPDOWN+=1;
      }
      else if(Pos_menu==ChoiceMenuMain)
      {
        if( (MenuUPDOWN==ChannelReserse) or \
            (MenuUPDOWN==GetChannelLimit) or \
            (MenuUPDOWN==MixChannel) or\
            (MenuUPDOWN==SetThrottleLock))
        {
          if(UpDown_Menu_V1>=UpDown_Menu_V1_MAX) UpDown_Menu_V1=0;
          else UpDown_Menu_V1+=1;
        }
        else if( MenuUPDOWN==SetTXBattery )
        {
          if( _Virtual_Machine_.TX_PIN_LOW<=0 ) _Virtual_Machine_.TX_PIN_LOW=0;
          else _Virtual_Machine_.TX_PIN_LOW-=0.1;
        }
        else if( MenuUPDOWN==SetRXBattery )
        {
          if( _Virtual_Machine_.RX_PIN_LOW<=0 ) _Virtual_Machine_.RX_PIN_LOW=0;
          else _Virtual_Machine_.RX_PIN_LOW-=0.1;
        }
        else if( MenuUPDOWN==SetPPM )
        {
          if(UpDown_Menu_V1>=UpDown_Menu_V1_MAX) UpDown_Menu_V1=0;
          else UpDown_Menu_V1+=1;
        }
        else if( MenuUPDOWN==SetTimeDown )
        {
          if(_Virtual_Machine_.Minute>=0)
          {
            if( _Virtual_Machine_.Second<=0 )
            {
              if(_Virtual_Machine_.Minute==0) _Virtual_Machine_.Minute=0;
              else _Virtual_Machine_.Minute-=1;
              _Virtual_Machine_.Second=59;
            }
            else 
            {
              _Virtual_Machine_.Second-=1;
            }
          }
        }       
        else if( MenuUPDOWN==EndPoint )
        {
          if(UpDown_Menu_V1>=UpDown_Menu_V1_MAX) UpDown_Menu_V1=0;
          else UpDown_Menu_V1+=1;
        }
      }   
      else if(Pos_menu==Enter_1)
      {
        if( MenuUPDOWN==SetPPM )
        {
          auto Lambda = [](volatile uint16_t *Input)
          {
            if(*Input<=PPM_MIN) *Input=PPM_MIN;
            else *Input-=10;
          };

          if( UpDown_Menu_V1==0 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_1.PPM_Min);
          else if( UpDown_Menu_V1==1 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_1.PPM_Max);
          else if( UpDown_Menu_V1==2 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_2.PPM_Min);
          else if( UpDown_Menu_V1==3 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_2.PPM_Max);
          else if( UpDown_Menu_V1==4 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_3.PPM_Min);
          else if( UpDown_Menu_V1==5 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_3.PPM_Max);
          else if( UpDown_Menu_V1==6 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_4.PPM_Min);
          else if( UpDown_Menu_V1==7 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_4.PPM_Max);
          else if( UpDown_Menu_V1==8 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_5.PPM_Min);
          else if( UpDown_Menu_V1==9 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_5.PPM_Max);
          else if( UpDown_Menu_V1==10 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_6.PPM_Min);
          else if( UpDown_Menu_V1==11 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_6.PPM_Max);
          else if( UpDown_Menu_V1==12 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_7.PPM_Min);
          else if( UpDown_Menu_V1==13 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_7.PPM_Max);
          else if( UpDown_Menu_V1==14 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_8.PPM_Min);
          else if( UpDown_Menu_V1==15 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_8.PPM_Max);
          else if( UpDown_Menu_V1==16 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_9.PPM_Min);
          else if( UpDown_Menu_V1==17 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_9.PPM_Max);
          else if( UpDown_Menu_V1==18 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_10.PPM_Min);
          else if( UpDown_Menu_V1==19 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_10.PPM_Max);
        }
        else if( MenuUPDOWN==EndPoint )
        {
          auto Lambda = [](volatile uint8_t *Input)
          {
            if(*Input<=0) *Input=0;
            else *Input-=1;
          };        

          if( UpDown_Menu_V1==0 )Lambda(&_Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==1 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==2 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_3.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==3 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_4.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==4 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_5.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==5 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_6.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==6 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_7.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==7 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_8.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==8 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_9.Limit.TRIP_PERCENT);
          else if( UpDown_Menu_V1==9 ) Lambda(&_Virtual_Machine_.CHANNEL.Channel_10.Limit.TRIP_PERCENT);                
        }
        else if( MenuUPDOWN==MixChannel )
        {
          if( UpDown_Menu_V1==1 )
          {
            if( _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT>0 )
            {
              _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT-=1;
            }
            else _Virtual_Machine_.CHANNEL.Channel_1.Limit.TRIP_PERCENT=0;
          }
          else if( UpDown_Menu_V1==2 )
          {
            if( _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT>0 )
            {
              _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT-=1;
            }
            else _Virtual_Machine_.CHANNEL.Channel_2.Limit.TRIP_PERCENT=0;
          } else {;;}
        }
        else if( MenuUPDOWN==SetThrottleLock )
        {
          if( UpDown_Menu_V1==0 )
          {
            if(_Virtual_Machine_.Throttle_Lock<=0) _Virtual_Machine_.Throttle_Lock=4;
            else _Virtual_Machine_.Throttle_Lock-=1;
          }
          else 
          {
            if(_Virtual_Machine_.Throttle_Lock_Value<=0) _Virtual_Machine_.Throttle_Lock_Value=2;
            else _Virtual_Machine_.Throttle_Lock_Value-=1;
          }
        } 
      }   
      
    }

  }/* Eend of if( DATA_READ.BT_DOWN<=500 ) */

} /* End of void LCD_MAIN(void) */
