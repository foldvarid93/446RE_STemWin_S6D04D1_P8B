#include "S6D04D1.h"

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
void LcdWriteReg(U8 Data) {
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_CD_PIN, GPIO_PIN_RESET); //DC_Write(0);
	LCD_DATA_PORT->ODR &= 0xFFFFFF00;
	LCD_DATA_PORT->ODR |= Data; //LCD_DATA_Write(com);
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_RESET); //WR_Write(0);
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_SET); //WR_Write(1);
}
/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
U8 LcdReadReg(void) {
  // ... TBD by user
	return 0;
}
/********************************************************************
*
*       LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
void LcdWriteData(U8 Data) {
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_CD_PIN, GPIO_PIN_SET); //DC_Write(1);
	LCD_DATA_PORT->ODR &= 0xFFFFFF00;
	LCD_DATA_PORT->ODR |= Data; //LCD_DATA_Write(dat);
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_RESET); //WR_Write(0);
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_SET); //WR_Write(1);
}
/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
void LcdWriteDataMultiple(U8 * pData, int NumItems) {
	//LCD_CONTROL_PORT->BSRR=0x08000000;//CS:Low
  while (NumItems--) {
		HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_CD_PIN, GPIO_PIN_SET); //DC_Write(1);
		LCD_DATA_PORT->ODR &= 0xFFFFFF00;
		LCD_DATA_PORT->ODR |= *pData++; //LCD_DATA_Write(dat);
		HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_RESET); //WR_Write(0);
		HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_SET); //WR_Write(1);
  }
}
/********************************************************************
*
*       LcdReadDataMultiple
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
*       GPIO init
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
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_SET); //WR=0
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_RST_PIN, GPIO_PIN_RESET); //RES_Write(0);
	HAL_Delay(1);//1ms
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_RST_PIN, GPIO_PIN_SET);	//RES_Write(1);
	//
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
	LcdWriteData(0x08);//48);//08

	LcdWriteReg(0x3A);//Interface Pixel Format (3Ah)
	LcdWriteData(0x77);

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
	LcdWriteData(0x00);
	LcdWriteData(0x00);
	LcdWriteData(0x00);

	LcdWriteReg(0xFD);//Gate Control Register (FDh)
	LcdWriteData(0x02);
	LcdWriteData(0x01); //240*400

	HAL_Delay(20);

	LcdWriteReg(0x29);//Display On (29h)
	HAL_Delay(20);
}
