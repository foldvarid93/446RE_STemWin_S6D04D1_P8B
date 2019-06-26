#ifndef LCDCONF_H
#define LCDCONF_H

#include "GUI.h"
#include "stm32f4xx.h"
#include "LCD_Private.h"
#include "GUI_Private.h"
#include "LCD_ConfDefaults.h"

#define	LCD_DATA_PORT				GPIOB
#define	LCD_CONTROL_PORT			GPIOB
#define LCD_CD_PIN					GPIO_PIN_8
#define LCD_RD_PIN					GPIO_PIN_9
#define LCD_WR_PIN					GPIO_PIN_10
#define LCD_CS_PIN					GPIO_PIN_12
#define LCD_RST_PIN					GPIO_PIN_13
//SET defines
#define LCD_CD_PIN_SET				0x00000100
#define LCD_RD_PIN_SET				0x00000200
#define LCD_WR_PIN_SET				0x00000400
#define LCD_CS_PIN_SET				0x00001000
#define LCD_RST_PIN_SET				0x00002000
//RESET defines
#define LCD_CD_PIN_RESET			0x01000000
#define LCD_RD_PIN_RESET			0x02000000
#define LCD_WR_PIN_RESET			0x04000000
#define LCD_CS_PIN_RESET			0x10000000
#define LCD_RST_PIN_RESET			0x20000000
//
void LcdWriteReg(U8 Data);
U8 LcdReadData(void);
void LcdWriteData(U8 Data);
void LcdWriteDataMultiple(U8 * pData, int NumItems);
void LcdReadDataMultiple(U8 * pData, int NumItems);
void GPIO_Init(void);
void LcdInit(void);
//void LcdClear(char mode,char color_r,char color_g, char color_b);
void LcdClear(U16 color);
void ReadReg(U8 Reg, U8 * pData, U8 NumItems);
void DrawPixel(U16 x,U16 y,U16 color);
#endif
