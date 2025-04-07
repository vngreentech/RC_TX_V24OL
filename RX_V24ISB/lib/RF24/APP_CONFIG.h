
#ifndef __APP_CONFIG__
#define __APP_CONFIG__

#define PIN_BIND (PB6)
#define PIN_LED (PB7)

/* RF24 PIN */
#define MOSI (PA7)
#define MISO (PA6)
#define SCK  (PA5)
#define CE   (PB9)
#define CSN  (PB10)

/* I2C PIN */
#define SDA_PIN (PB7)
#define SCL_PIN (PB6)

/* 74HC4067 PIN */
#define SIG (PA0)
#define S0  (PB12)
#define S1  (PB13)
#define S2  (PB14)
#define S3  (PB15)

/* Aile, Ele, Thro, Rud */
#define CH1_AILE (PIN_0)
#define CH2_ELE  (PIN_1)
#define CH3_THRO (PIN_2)
#define CH4_RUD  (PIN_3)

/* 3 bien tro */
#define BIENTRO_1 (PIN_4)
#define BIENTRO_2 (PIN_5)
#define BIENTRO_3 (PIN_6)

/* 2 Switch 3 vi tri */
#define SW_3_POS_1 (PIN_7)
#define SW_3_POS_2 (PIN_8)

/* 4 switch ON/OFF */
#define SW_ONOF_1 (PIN_9)
#define SW_ONOF_2 (PIN_10)
#define SW_ONOF_3 (PIN_11)
#define SW_ONOF_4 (PIN_12)

/* Vol sensor */
#define VOL_SENSOR (PIN_13)

/* Button UP & DOWN */
#define BUTTON_UP   (PIN_14)
#define BUTTON_DOWN (PIN_15)

/* Button Menu OK & BACK */
#define BUTTON_OK   (PA8)
#define BUTTON_BACK (PA11)

/* LED & BUZZER */
#define LED     (PC13)
#define BUZZER  (PB8)

/* Button Strim */
#define CH1_BT1 (PA12)
#define CH1_BT2 (PA15)
#define CH2_BT1 (PB3)
#define CH2_BT2 (PB4)
#define CH3_BT1 (PB5)
#define CH3_BT2 (PA1)
#define CH4_BT1 (PB0)
#define CH4_BT2 (PB1)

/* DEBUG */
#define DEBUG_TX (PA9)
#define DEBUG_RX (PA10)

/*=======================*/

#define LGo_GREEN ("GREEN_d1")
#define LGo_TECH  ("TECHNOLOGY_d2")
#define LGo_WEB   ("www.vngreentech.com_d3")

#define LGo_MADEINVN ("MADE IN VIETNAM_d4")
#define LGo_NhanNguyen ("NhanNguyen_d5")

#define DEFAULT_ADD_READ (62345)
#define DEFAULT_ADD_WRITE (33777)
#define DEFAULT_CHANNEL (101)

#define PPM_MIN (550UL)
#define PPM_MAX (2400UL)

#define TIME_PRESS_LONG (1000)

#define DEBUG
// #define PRINT_DATAREAD_DRAW
// #define PRINT_DATA_SEND_RF

#define EEPROM_ADDRESS (0x50)
#define LCD_ADDRESS    (0x3C)

#define VOL_INPUT_TX (3.3)
#define VOL_INPUT_RX (5.0)

#define _I2C_SPEED_ (1000000)

#endif /* __APP_CONFIG__ */
