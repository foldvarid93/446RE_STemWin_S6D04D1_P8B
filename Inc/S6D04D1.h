#ifndef LCDCONF_H
#define LCDCONF_H
#include "GUI.h"
#include "stm32f4xx.h"

#define	LCD_DATA_PORT				GPIOB
#define	LCD_CONTROL_PORT			GPIOA
#define LCD_RD_PIN					GPIO_PIN_8
#define LCD_WR_PIN					GPIO_PIN_9
#define LCD_CD_PIN					GPIO_PIN_10
#define LCD_CS_PIN					GPIO_PIN_11
#define LCD_RST_PIN					GPIO_PIN_12

void LcdWriteReg(U8 Data);
U8 LcdReadReg(void);
void LcdWriteData(U8 Data);
void LcdWriteDataMultiple(U8 * pData, int NumItems);
void LcdReadDataMultiple(U8 * pData, int NumItems);
void GPIO_Init(void);
void LcdInit(void);

#endif
