
#include "74HC4067.h"

static uint32_t SelectChannel[16][4]={
      {0,0,0,0}, //channel 0
      {1,0,0,0}, //channel 1
      {0,1,0,0}, //channel 2
      {1,1,0,0}, //channel 3
      {0,0,1,0}, //channel 4
      {1,0,1,0}, //channel 5
      {0,1,1,0}, //channel 6
      {1,1,1,0}, //channel 7
      {0,0,0,1}, //channel 8
      {1,0,0,1}, //channel 9
      {0,1,0,1}, //channel 10
      {1,1,0,1}, //channel 11
      {0,0,1,1}, //channel 12
      {1,0,1,1}, //channel 13
      {0,1,1,1}, //channel 14
      {1,1,1,1}  //channel 15
  };

void _74HC4067_Init(_74HC4067_typedef *_74HC4067_Object)
{
  SETRESOLUTION(_74HC4067_Object->Bit_Resolution);

  SETPINOUTPUT(_74HC4067_Object->PIN_EN);
  _74HC4067_ENABLE(_74HC4067_Object, _74HC4067_Enable);

  #ifdef LGO_WEB
  SETPINOUTPUT(_74HC4067_Object->PIN_S0);
  SETPINOUTPUT(_74HC4067_Object->PIN_S1);
  SETPINOUTPUT(_74HC4067_Object->PIN_S2);
  SETPINOUTPUT(_74HC4067_Object->PIN_S3);

  WRITEPIN(_74HC4067_Object->PIN_S0,LOW);
  WRITEPIN(_74HC4067_Object->PIN_S1,LOW);
  WRITEPIN(_74HC4067_Object->PIN_S2,LOW);
  WRITEPIN(_74HC4067_Object->PIN_S3,LOW);
  #endif
}

uint16_t _74HC4067_ReadPin(_74HC4067_typedef *_74HC4067_Object, _74HC4067_PIN_enum PIN_READ)
{
  uint16_t ValueRead=0;
  const uint32_t PIN_Control[4] = { _74HC4067_Object->PIN_S0, 
                                    _74HC4067_Object->PIN_S1, 
                                    _74HC4067_Object->PIN_S2, 
                                    _74HC4067_Object->PIN_S3 };

  if( LGO_WEB=="www.vngreentech.com" )
  {
  for(uint8_t i=0; i<4; i++)
  {
    WRITEPIN(PIN_Control[i], SelectChannel[PIN_READ][i]);
  }
  }

  ValueRead = ANALOGREAD(_74HC4067_Object->PIN_SIG);

  return ValueRead;
}

void _74HC4067_ENABLE(_74HC4067_typedef *_74HC4067_Object, _74hc4067_enable_enum Select)
{
  if( LGO_GREEN=="GREEN" )
  {
  if(Select==_74HC4067_Disable) WRITEPIN(_74HC4067_Object->PIN_EN,HIGH);
  else WRITEPIN(_74HC4067_Object->PIN_EN,LOW);
  }
}

