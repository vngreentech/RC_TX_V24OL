
#include "EROM.h"

I2C_eeprom EER(EEPROM_ADDRESS, I2C_DEVICESIZE_24LC256, &Wire);

uint8_t READ_CONFIG_MACHINE(ConfigMachine_typedef *MachineConfig)
{
  uint16_t Lenght;
  uint8_t RESULT=FALSE;

  uint8_t Buffer[sizeof(ConfigMachine_typedef)];
  Lenght=EER.readBlock(0,Buffer,sizeof(ConfigMachine_typedef));
  memcpy(MachineConfig,Buffer,sizeof(ConfigMachine_typedef));

  if( Lenght==(sizeof(ConfigMachine_typedef)) ) RESULT=TRUE;

  return RESULT;
}

uint8_t WRITE_CONFIG_MACHINE(ConfigMachine_typedef *MachineConfig)
{
  uint8_t RESULT=FALSE;
  uint8_t Buffer[sizeof(ConfigMachine_typedef)];
  memcpy(Buffer,MachineConfig,sizeof(ConfigMachine_typedef));

  if(EER.writeBlock(0,Buffer,sizeof(ConfigMachine_typedef))==0)
  {
    RESULT=TRUE;
  }

  return RESULT;
}

void EEPROM_INIT(void)
{
  EER.begin();
  while (!EER.isConnected())
  {
    ERROR_EEPROM();
    LED_ON;
    BUZZER_ON;
  }
  LED_OF;
  BUZZER_OF;

  READ_CONFIG_MACHINE(&Machine);

  memcpy(&LastChannelConfig,&Machine.CHANNEL,sizeof(Machine.CHANNEL));
  memcpy(&NewChannelConfig,&Machine.CHANNEL,sizeof(Machine.CHANNEL));

  if( Machine.CheckSave!=113 )
  {
    RESET_MACHINE_DEFAULT();
    WRITE_CONFIG_MACHINE(&Machine);
  }
}

void EEMROM_MAIN(void)
{

}
