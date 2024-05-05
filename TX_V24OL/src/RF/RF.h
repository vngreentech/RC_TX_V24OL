
#ifndef __RF__
#define __RF__

#include "APPLICATION.h"

extern uint8_t RF_RESULT_PPM; /* 1=OK, 2=TimeOut */
extern uint16_t RF_ReadData;
extern uint8_t RF_BIND_RESULT;
extern uint8_t RF_Check_Connect;
extern uint8_t Feature_send;

void RF_INIT(void);
void RF_MAIN(void);
void RF_BIND_MAIN(void);
void RF_Send_PPM(void);

#endif /* __RF__ */
