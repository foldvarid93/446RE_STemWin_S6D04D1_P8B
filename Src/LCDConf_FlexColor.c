/*********************************************************************
*          Portions COPYRIGHT 2016 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_Template.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include <LCDConf_FlexColor.h>
#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "stm32f4xx.h"
/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS  240 // To be adapted to x-screen size
#define YSIZE_PHYS  320 // To be adapted to y-screen size

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif
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
static void LcdWriteReg(U8 Data) {
	LCD_CONTROL_PORT->BSRR=0x0E000000;//CD:Low, CS:Low, WR:Low
	LCD_DATA_PORT->ODR&=0xFFFFFF00;
	LCD_DATA_PORT->ODR|=Data;
	asm("NOP");
	//LCD_CONTROL_PORT->BSRR=0x02000000; //WR:Low
	LCD_CONTROL_PORT->BSRR=0x00000A00;//WR:High, CS:High
}

/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
static U8 LcdReadReg(void) {
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
static void LcdWriteData(U8 Data) {
	LCD_CONTROL_PORT->BSRR=0x0A000400;//CD:High, CS:Low
	LCD_DATA_PORT->ODR&=0xFFFFFF00;
	LCD_DATA_PORT->ODR|=Data;
	asm("NOP");
	//LCD_CONTROL_PORT->BSRR=0x02000000; //WR:Low
	LCD_CONTROL_PORT->BSRR=0x00000A00;//WR:High, CS:High
}

/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
volatile int time=0;
static void LcdWriteDataMultiple(U8 * pData, int NumItems) {
	//LCD_CONTROL_PORT->BSRR=0x08000000;//CS:Low
  while (NumItems--) {
		LCD_CONTROL_PORT->BSRR=0x0A000400;//CD:High, CS:Low, WR:Low
		LCD_DATA_PORT->ODR&=0xFFFFFF00;
		LCD_DATA_PORT->ODR|=*pData++;
		//LCD_CONTROL_PORT->BSRR=0x02000000; //WR:Low
		LCD_CONTROL_PORT->BSRR=0x00000A00;//WR:High
  }
  //LCD_CONTROL_PORT->BSRR=0x00000800;//CS:High
  time++;
  if(time==309){
	  asm("NOP") ;
  }
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void LcdReadDataMultiple(U8 * pData, int NumItems) {
  while (NumItems--) {
    // ... TBD by user
  }
}
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
//ILI9341 driver init
void LcdInit(void) {
	GPIO_Init();
	LCD_CONTROL_PORT->BSRR=0x10000F00;//WR:High, CS:High, RD: High, RST: Low
	HAL_Delay(2);//Reset delay
	LCD_CONTROL_PORT->BSRR=0x00001000;//RST:High
	for(uint8_t i=0; i<3; i++)  {
		LcdWriteReg(0x00);
	} // Three extra 0x00s
	LCD_CONTROL_PORT->BSRR=0x00000800;//CS:High

//ILI9341 initialization sequence

	LcdWriteReg(0x01);//soft reset
	HAL_Delay(1000);
	//power control A
	LcdWriteReg(0xCB);
	LcdWriteData(0x39);
	LcdWriteData(0x2C);
	LcdWriteData(0x00);
	LcdWriteData(0x34);
	LcdWriteData(0x02);

	//power control B
	LcdWriteReg(0xCF);
	LcdWriteData(0x00);
	LcdWriteData(0xC1);
	LcdWriteData(0x30);

	//driver timing control A
	LcdWriteReg(0xE8);
	LcdWriteData(0x85);
	LcdWriteData(0x00);
	LcdWriteData(0x78);

	//driver timing control B
	LcdWriteReg(0xEA);
	LcdWriteData(0x00);
	LcdWriteData(0x00);

	//power on sequence control
	LcdWriteReg(0xED);
	LcdWriteData(0x64);
	LcdWriteData(0x03);
	LcdWriteData(0x12);
	LcdWriteData(0x81);

	//pump ratio control
	LcdWriteReg(0xF7);
	LcdWriteData(0x20);

	//power control,VRH[5:0]
	LcdWriteReg(0xC0);
	LcdWriteData(0x23);

	//Power control,SAP[2:0];BT[3:0]
	LcdWriteReg(0xC1);
	LcdWriteData(0x10);

	//vcm control
	LcdWriteReg(0xC5);
	LcdWriteData(0x3E);
	LcdWriteData(0x28);

	//vcm control 2
	LcdWriteReg(0xC7);
	LcdWriteData(0x86);

	//memory access control
	LcdWriteReg(0x36);
	LcdWriteData(0x48);

	//pixel format
	LcdWriteReg(0x3A);
	LcdWriteData(0x55);

	//frameration control,normal mode full colours
	LcdWriteReg(0xB1);
	LcdWriteData(0x00);
	LcdWriteData(0x18);

	//display function control
	LcdWriteReg(0xB6);
	LcdWriteData(0x08);
	LcdWriteData(0x82);
	LcdWriteData(0x27);

	//3gamma function disable
	LcdWriteReg(0xF2);
	LcdWriteData(0x00);

	//gamma curve selected
	LcdWriteReg(0x26);
	LcdWriteData(0x01);

	//set positive gamma correction
	LcdWriteReg(0xE0);
	LcdWriteData(0x0F);
	LcdWriteData(0x31);
	LcdWriteData(0x2B);
	LcdWriteData(0x0C);
	LcdWriteData(0x0E);
	LcdWriteData(0x08);
	LcdWriteData(0x4E);
	LcdWriteData(0xF1);
	LcdWriteData(0x37);
	LcdWriteData(0x07);
	LcdWriteData(0x10);
	LcdWriteData(0x03);
	LcdWriteData(0x0E);
	LcdWriteData(0x09);
	LcdWriteData(0x00);

	//set negative gamma correction
	LcdWriteReg(0xE1);
	LcdWriteData(0x00);
	LcdWriteData(0x0E);
	LcdWriteData(0x14);
	LcdWriteData(0x03);
	LcdWriteData(0x11);
	LcdWriteData(0x07);
	LcdWriteData(0x31);
	LcdWriteData(0xC1);
	LcdWriteData(0x48);
	LcdWriteData(0x08);
	LcdWriteData(0x0F);
	LcdWriteData(0x0C);
	LcdWriteData(0x31);
	LcdWriteData(0x36);
	LcdWriteData(0x0F);

	//exit sleep
	LcdWriteReg(0x11);
	HAL_Delay(120);
	//display on
	LcdWriteReg(0x29);
}
//S6D04D1 driver init
/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_565, 0, 0);//16bit color flexcolor driver
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Orientation
  //
  Config.Orientation = GUI_SWAP_XY;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set controller and operation mode
  //
  PortAPI.pfWrite8_A0  = LcdWriteReg;
  PortAPI.pfWrite8_A1  = LcdWriteData;
  PortAPI.pfWriteM8_A1  = LcdWriteDataMultiple;
  PortAPI.pfRead8_A1  = LcdReadReg;
  PortAPI.pfReadM8_A1 = LcdReadDataMultiple;
/*
  PortAPI.pfWrite16_A0  = LcdWriteReg;
  PortAPI.pfWrite16_A1  = LcdWriteData;
  PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = LcdReadDataMultiple;
*/
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C0B8);//ILI9341, 16bit color, 8 bit bus, no cache
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
	//LcdInit();//ili9341 init code
	  S6D04D1init();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/

