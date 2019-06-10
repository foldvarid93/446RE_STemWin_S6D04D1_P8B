#include "S6D04D1.h"
/*********************************************************************
*
*Local functions
*
**********************************************************************
*/
/********************************************************************
*
*LcdWriteReg
*
* Function description:
*   Sets display register
*/
void LcdWriteReg(U8 Data) {
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET|LCD_CD_PIN_RESET;//DC=0, WR=0
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00)|Data;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;//WR=1
}
/********************************************************************
*
*LcdWriteReg
*
* Function description:
*   Sets display register
*/
U8 LcdReadData(void) {
	U8 data;
	LCD_CONTROL_PORT->BSRR = LCD_RD_PIN_RESET|LCD_CD_PIN_SET;//DC=1, RD=0
	data=(U8)(LCD_DATA_PORT->IDR&0x000000FF);
	LCD_CONTROL_PORT->BSRR = LCD_RD_PIN_SET; //RD=1
	return data;
}
/********************************************************************
*
*LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
void LcdWriteData(U8 Data) {
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET|LCD_CD_PIN_SET;//DC=1, WR=0
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00)|Data;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;//WR=1
}
/********************************************************************
*
*LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
void LcdWriteDataMultiple(U8 * pData, int NumItems) {
	while (NumItems--) {
		LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET|LCD_CD_PIN_SET;//DC=1, WR=0
		LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00)|*pData++;
		LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;//WR=1
	}
}
/********************************************************************
*
*LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
void LcdReadDataMultiple(U8 * pData, int NumItems) {
  while (NumItems--) {
    // ... TBD by user
  }
}
/********************************************************************
*
*Read register
*
* Function description:
*
*/
void ReadReg(U8 Reg, U8 * pData, U8 NumItems) {
	//send register address
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET|LCD_CD_PIN_RESET;//DC=0, WR=0
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00)|Reg;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;//WR=1
	//set port to input
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	//dummy read
	LCD_CONTROL_PORT->BSRR = LCD_RD_PIN_RESET|LCD_CD_PIN_SET;//DC=1, RD=0
	LCD_CONTROL_PORT->BSRR = LCD_RD_PIN_SET; //RD=1
	//read
	while (NumItems--) {
		LCD_CONTROL_PORT->BSRR = LCD_RD_PIN_RESET|LCD_CD_PIN_SET;//DC=1, RD=0
		*pData++=(U8)(LCD_DATA_PORT->IDR&0x000000FF);
		LCD_CONTROL_PORT->BSRR = LCD_RD_PIN_SET; //RD=1
	}
	//set port to output
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/********************************************************************
*
*GPIO init
*
* Function description:
*
*/
void GPIO_Init(void){

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 PA10 PA11
                           PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/********************************************************************
*
* S6D04D1 driver init
*
* Function description:
*
*/
void LcdInit(void) {
	GPIO_Init();
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET|LCD_RD_PIN_SET|LCD_CD_PIN_SET|LCD_RST_PIN_RESET;//WR=1,RD=1,DC=1,RES=0;
	HAL_Delay(1);//1ms
	LCD_CONTROL_PORT->BSRR = LCD_RST_PIN_SET;
/*
	U8 array[5];
	ReadReg(0x0C, array, 1);*/

	LcdWriteReg(0xE0);//MDDI Control 1 (E0h)
	LcdWriteData(0x01);//VWAKE_EN=1, When VWAKE_EN is 1, client initiated wake-up is enabled

	LcdWriteReg(0x11);//Sleep Out (11h)
	HAL_Delay(150);

	LcdWriteReg(0xF3);//Power Control Register (F3h)
	LcdWriteData(0x01);//VCI1_EN
	LcdWriteData(0x00);//
	LcdWriteData(0x00);//
	LcdWriteData(0x0C);//Do not set any higher VCI1 level than VCI -0.15V. 0C 0A
	LcdWriteData(0x03);//VGH和VGL 01 02VGH=6VCI1,VGL=-4VCI1.
	LcdWriteData(0x75);//
	LcdWriteData(0x75);//
	LcdWriteData(0x30);//

	LcdWriteReg(0xF4);//VCOM Control Register (F4h)
	LcdWriteData(0x4C);//
	LcdWriteData(0x4C);//
	LcdWriteData(0x44);//
	LcdWriteData(0x44);//
	LcdWriteData(0x22);//

	LcdWriteReg(0xF5);//Source Output Control Register (F5h)
	LcdWriteData(0x10);//
	LcdWriteData(0x22);//
	LcdWriteData(0x05);//
	LcdWriteData(0xF0);//
	LcdWriteData(0x70);//
	LcdWriteData(0x1F);//
	HAL_Delay(30);//

	LcdWriteReg(0xF3);//Power Control Register (F3h)
	LcdWriteData(0x03);//

	HAL_Delay(30);

	LcdWriteReg(0xF3);//Power Control Register (F3h)
	LcdWriteData(0x07);//

	HAL_Delay(30);

	LcdWriteReg(0xF3);//Power Control Register (F3h)
	LcdWriteData(0x0F);//

	HAL_Delay(30);

	LcdWriteReg(0xF3);//Power Control Register (F3h)
	LcdWriteData(0x1F);//

	HAL_Delay(30);

	LcdWriteReg(0xF3);//Power Control Register (F3h)
	LcdWriteData(0x7F);//

	HAL_Delay(30);

	LcdWriteReg(0xF7);//Positive Gamma Control Register for Red (F7h)
	LcdWriteData(0x80);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x05);
	LcdWriteData(0x0D);
	LcdWriteData(0x1F);
	LcdWriteData(0x26);
	LcdWriteData(0x2D);
	LcdWriteData(0x14);
	LcdWriteData(0x15);
	LcdWriteData(0x26);
	LcdWriteData(0x20);
	LcdWriteData(0x01);
	LcdWriteData(0x22);
	LcdWriteData(0x22);

	LcdWriteReg(0xF8);//Negative Gamma Control Register for Red
	LcdWriteData(0x80);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x07);
	LcdWriteData(0x1E);
	LcdWriteData(0x2A);
	LcdWriteData(0x32);
	LcdWriteData(0x10);
	LcdWriteData(0x16);
	LcdWriteData(0x36);
	LcdWriteData(0x3C);
	LcdWriteData(0x3B);
	LcdWriteData(0x22);
	LcdWriteData(0x22);

	LcdWriteReg(0xF9);//Positive Gamma Control Register for Green
	LcdWriteData(0x80);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x05);
	LcdWriteData(0x0D);
	LcdWriteData(0x1F);
	LcdWriteData(0x26);
	LcdWriteData(0x2D);
	LcdWriteData(0x14);
	LcdWriteData(0x15);
	LcdWriteData(0x26);
	LcdWriteData(0x20);
	LcdWriteData(0x01);
	LcdWriteData(0x22);
	LcdWriteData(0x22);

	LcdWriteReg(0xFA);//Negative Gamma Control Register for Green
	LcdWriteData(0x80);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x07);
	LcdWriteData(0x1E);
	LcdWriteData(0x2A);
	LcdWriteData(0x32);
	LcdWriteData(0x10);
	LcdWriteData(0x16);
	LcdWriteData(0x36);
	LcdWriteData(0x3C);
	LcdWriteData(0x3B);
	LcdWriteData(0x22);
	LcdWriteData(0x22);

	LcdWriteReg(0xFB);//Positive Gamma Control Register for Blue
	LcdWriteData(0x80);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x05);
	LcdWriteData(0x0D);
	LcdWriteData(0x1F);
	LcdWriteData(0x26);
	LcdWriteData(0x2D);
	LcdWriteData(0x14);
	LcdWriteData(0x15);
	LcdWriteData(0x26);
	LcdWriteData(0x20);
	LcdWriteData(0x01);
	LcdWriteData(0x22);
	LcdWriteData(0x22);

	LcdWriteReg(0xFC);//Negative Gamma Control Register for Blue
	LcdWriteData(0x80);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x07);
	LcdWriteData(0x1E);
	LcdWriteData(0x2A);
	LcdWriteData(0x32);
	LcdWriteData(0x10);
	LcdWriteData(0x16);
	LcdWriteData(0x36);
	LcdWriteData(0x3C);
	LcdWriteData(0x3B);
	LcdWriteData(0x22);
	LcdWriteData(0x22);

	//LcdWriteReg(0x35);
	LcdWriteReg(0x34); //Tearing Effect Line OFF (34h)

	LcdWriteReg(0x36);//Memory Data Access Control (36h)
	LcdWriteData(0x80);//48);//08

	LcdWriteReg(0x3A);//Interface Pixel Format (3Ah)
	LcdWriteData(0x55);//101-16bit/pixel
	//ReadReg(0x0C, array, 1);//

	LcdWriteReg(0xF2);//Display Control Register (F2h)
	LcdWriteData(0x17);
	LcdWriteData(0x17);
	LcdWriteData(0x0F);
	LcdWriteData(0x08);
	LcdWriteData(0x08);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x06);
	LcdWriteData(0x13);
	LcdWriteData(0x00);

	LcdWriteReg(0xF6);//Interface Control Register (F6h)
	LcdWriteData(0x00);
	LcdWriteData(0x80);
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	//ReadReg(0xF6, array, 4);//

	LcdWriteReg(0xFD);//Gate Control Register (FDh)
	LcdWriteData(0x02);
	LcdWriteData(0x01); //240*400

	HAL_Delay(20);

	LcdWriteReg(0x29);//Display On (29h)
	//ReadReg(0x0B, array, 1);//read MADCTL
	HAL_Delay(20);
}
/********************************************************************
*
* clear screen
*
* Function description:
*
*/
void LcdClear(U16 color) {
	unsigned long int i;

	/*
	//1,5s full lcd clear
	LcdWriteReg(0x2A + mode);
	LcdWriteData(0);
	LcdWriteData(0);
	LcdWriteData(1);
	LcdWriteData(0x90);	//400

	LcdWriteReg(0x2b - mode);	//
	LcdWriteData(0);
	LcdWriteData(0);	//
	LcdWriteData(0);
	LcdWriteData(239);	//240
	LcdWriteReg(0x2C);	//Memory Write (2Ch)
	for (i = 0; i < 96000; i++) {//(400*240)=96000pixel, 3byte per pixel 9600*10*3byte
		LcdWriteData((U8) (color >> 8));
		LcdWriteData((U8) color);
	}*/

	//20ms full lcd clear if color is black
	//34ms full lcd clear any other colors
	LCD_CONTROL_PORT->BSRR = LCD_CD_PIN_RESET|LCD_WR_PIN_RESET;
	//LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00) | 0x2B ;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET | LCD_CD_PIN_SET;
	//LcdWriteData(xh);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00);
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
	//LcdWriteData((U8)x);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00);
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
	//LcdWriteData(xh);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00) | 0x01;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
	//LcdWriteData((U8)x);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00) | 0x90;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET | LCD_CD_PIN_RESET;
	//y
	//LcdWriteReg(0x2A);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00) | 0x2A;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET | LCD_CD_PIN_SET;
	//LcdWriteData(yh);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00);
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
	//LcdWriteData((U8)y);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00);
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
	//LcdWriteData(yh);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00);
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
	//LcdWriteData((U8)y);//
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00) | 0xEF;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET | LCD_CD_PIN_RESET;
	//color
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
	LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00) | 0x2C;
	LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET | LCD_CD_PIN_SET;
	if(color==0x0000){//black
		LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00);
		for (i = 0; i < 96000; i++) { //(400*240)=96000pixel, 3byte per pixel 9600*10*3byte
			//LcdWriteData((U8)(PixelIndex>>8));//Upper byte
			LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
			LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
			//LcdWriteData((U8)PixelIndex);//Lower byte
			LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
			LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
		}
	}
	else{//other colors
		U8 colorH = (U8) (color >> 8);
		U8 colorL = (U8) color;
		for (i = 0; i < 96000; i++) { //(400*240)=96000pixel, 3byte per pixel 9600*10*3byte
			//LcdWriteData((U8)(PixelIndex>>8));//Upper byte
			LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
			LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00) | colorH;
			LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
			//LcdWriteData((U8)PixelIndex);//Lower byte
			LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_RESET;
			LCD_DATA_PORT->ODR = (LCD_DATA_PORT->ODR & 0xFFFFFF00) | colorL;
			LCD_CONTROL_PORT->BSRR = LCD_WR_PIN_SET;
		}
	}
}
/********************************************************************
*
* draw pixel
*
* Function description:
*
*/
void DrawPixel(U16 x,U16 y,U16 color) {
	  LcdWriteReg(0x2B);//
	  LcdWriteData(x>>8);//start upper byte
	  LcdWriteData((U8)x);//start lower byte

	  LcdWriteData(x>>8);//end upper byte
	  LcdWriteData((U8)x);//end lower byte

	  LcdWriteReg(0x2A);//
	  LcdWriteData(y>>8);//start upper byte
	  LcdWriteData((U8)y);//start lower byte

	  LcdWriteData(y>>8);//end upper byte
	  LcdWriteData((U8)y);//end lower byte

	  LcdWriteReg(0x2C);//Memory Write (2Ch)
	  LcdWriteData((U8)(color>>8));
	  LcdWriteData((U8)color);
}
/*
 *End
 */
