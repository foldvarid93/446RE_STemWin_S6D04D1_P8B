#include "font.h"
#include "lcd_ls022.h"
#include "main.h"
#include "LCDConf_FlexColor.h"
void SendCom(unsigned int cmd) {
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_CD_PIN, GPIO_PIN_RESET); //DC_Write(0);
	LCD_DATA_PORT->ODR &= 0xFFFFFF00;
	LCD_DATA_PORT->ODR |= cmd; //LCD_DATA_Write(com);
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_RESET); //WR_Write(0);
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_SET); //WR_Write(1);
}
void SendDat(unsigned int dat) {
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_CD_PIN, GPIO_PIN_SET); //DC_Write(1);
	LCD_DATA_PORT->ODR &= 0xFFFFFF00;
	LCD_DATA_PORT->ODR |= dat; //LCD_DATA_Write(dat);
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_RESET); //WR_Write(0);
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_SET); //WR_Write(1);
}
void S6D04D1init(void) {
	/**********************************************
	 TFT1P CODE Initialization of Truly

	 ************************************************
	 Panel:3.0 240400
	 Driver IC:S6D04D1X21-BAF8

	 ************************************************/
	GPIO_Init();
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_WR_PIN, GPIO_PIN_SET); //WR=0
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_RST_PIN, GPIO_PIN_RESET); //RES_Write(0);
	HAL_Delay(1);//1ms
	HAL_GPIO_WritePin(LCD_CONTROL_PORT, LCD_RST_PIN, GPIO_PIN_SET);	//RES_Write(1);
	//
	SendCom(0xE0);//MDDI Control 1 (E0h)
	SendDat(0x01);//VWAKE_EN=1, When VWAKE_EN is 1, client initiated wake-up is enabled

	SendCom(0x11);//Sleep Out (11h)
	HAL_Delay(150);

	SendCom(0xF3);//Power Control Register (F3h)
	SendDat(0x01);//VCI1_EN
	SendDat(0x00);//
	SendDat(0x00);//
	SendDat(0x0C);//Do not set any higher VCI1 level than VCI -0.15V. 0C 0A
	SendDat(0x03);//VGH和VGL 01 02VGH=6VCI1,VGL=-4VCI1.
	SendDat(0x75);//
	SendDat(0x75);//
	SendDat(0x30);//

	SendCom(0xF4);//VCOM Control Register (F4h)
	SendDat(0x4C);//
	SendDat(0x4C);//
	SendDat(0x44);//
	SendDat(0x44);//
	SendDat(0x22);//

	SendCom(0xF5);//Source Output Control Register (F5h)
	SendDat(0x10);//
	SendDat(0x22);//
	SendDat(0x05);//
	SendDat(0xF0);//
	SendDat(0x70);//
	SendDat(0x1F);//
	HAL_Delay(30);//

	SendCom(0xF3);//Power Control Register (F3h)
	SendDat(0x03);//

	HAL_Delay(30);

	SendCom(0xF3);//Power Control Register (F3h)
	SendDat(0x07);//

	HAL_Delay(30);

	SendCom(0xF3);//Power Control Register (F3h)
	SendDat(0x0F);//

	HAL_Delay(30);

	SendCom(0xF3);//Power Control Register (F3h)
	SendDat(0x1F);//

	HAL_Delay(30);

	SendCom(0xF3);//Power Control Register (F3h)
	SendDat(0x7F);//

	HAL_Delay(30);

	SendCom(0xF7);//Positive Gamma Control Register for Red (F7h)
	SendDat(0x80);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x05);
	SendDat(0x0D);
	SendDat(0x1F);
	SendDat(0x26);
	SendDat(0x2D);
	SendDat(0x14);
	SendDat(0x15);
	SendDat(0x26);
	SendDat(0x20);
	SendDat(0x01);
	SendDat(0x22);
	SendDat(0x22);

	SendCom(0xF8);//Negative Gamma Control Register for Red
	SendDat(0x80);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x07);
	SendDat(0x1E);
	SendDat(0x2A);
	SendDat(0x32);
	SendDat(0x10);
	SendDat(0x16);
	SendDat(0x36);
	SendDat(0x3C);
	SendDat(0x3B);
	SendDat(0x22);
	SendDat(0x22);

	SendCom(0xF9);//Positive Gamma Control Register for Green
	SendDat(0x80);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x05);
	SendDat(0x0D);
	SendDat(0x1F);
	SendDat(0x26);
	SendDat(0x2D);
	SendDat(0x14);
	SendDat(0x15);
	SendDat(0x26);
	SendDat(0x20);
	SendDat(0x01);
	SendDat(0x22);
	SendDat(0x22);

	SendCom(0xFA);//Negative Gamma Control Register for Green
	SendDat(0x80);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x07);
	SendDat(0x1E);
	SendDat(0x2A);
	SendDat(0x32);
	SendDat(0x10);
	SendDat(0x16);
	SendDat(0x36);
	SendDat(0x3C);
	SendDat(0x3B);
	SendDat(0x22);
	SendDat(0x22);

	SendCom(0xFB);//Positive Gamma Control Register for Blue
	SendDat(0x80);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x05);
	SendDat(0x0D);
	SendDat(0x1F);
	SendDat(0x26);
	SendDat(0x2D);
	SendDat(0x14);
	SendDat(0x15);
	SendDat(0x26);
	SendDat(0x20);
	SendDat(0x01);
	SendDat(0x22);
	SendDat(0x22);

	SendCom(0xFC);//Negative Gamma Control Register for Blue
	SendDat(0x80);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x07);
	SendDat(0x1E);
	SendDat(0x2A);
	SendDat(0x32);
	SendDat(0x10);
	SendDat(0x16);
	SendDat(0x36);
	SendDat(0x3C);
	SendDat(0x3B);
	SendDat(0x22);
	SendDat(0x22);

	//SendCom(0x35);
	SendCom(0x34); //Tearing Effect Line OFF (34h)

	SendCom(0x36);//Memory Data Access Control (36h)
	SendDat(0x08);//48);//08

	SendCom(0x3A);//Interface Pixel Format (3Ah)
	SendDat(0x77);

	SendCom(0xF2);//Display Control Register (F2h)
	SendDat(0x17);
	SendDat(0x17);
	SendDat(0x0F);
	SendDat(0x08);
	SendDat(0x08);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x06);
	SendDat(0x13);
	SendDat(0x00);

	SendCom(0xF6);//Interface Control Register (F6h)
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x00);
	SendDat(0x00);

	SendCom(0xFD);//Gate Control Register (FDh)
	SendDat(0x02);
	SendDat(0x01); //240*400

	HAL_Delay(20);

	SendCom(0x29);//Display On (29h)
	HAL_Delay(20);
}
void LCDclear(char mode,char color_r,char color_g, char color_b) {
	unsigned long int i;
	SendCom(0x2A + mode);//
	SendDat(0);
	SendDat(0);
	SendDat(1);
	SendDat(0x90);//400

	SendCom(0x2b - mode);//
	SendDat(0);
	SendDat(0);//
	SendDat(0);
	SendDat(240);//240
	SendCom(0x2C);//Memory Write (2Ch)
	for (i = 0; i < 96000; i++) {//(400*240)=96000pixel, 3byte per pixel 9600*10*3byte
		SendDat(color_r);
		SendDat(color_g);
		SendDat(color_b);
	}
}
//**********************************************************************************************************
void SetWindow(unsigned int Xs, unsigned int Ys, unsigned int Xe,unsigned int Ye) {
	SendCom(0x2A);
	SendDat(hi(Xs));
	SendDat(lo(Xs));
	SendDat(hi(Xe));
	SendDat(lo(Xe));
	SendCom(0x2B);
	SendDat(hi(Ys));
	SendDat(lo(Ys));
	SendDat(hi(Ye));
	SendDat(lo(Ye));
}
/*-----------------------------------------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////
void LCDchar0(unsigned int x, unsigned int y, char c, char color_r,	char color_g, char color_b, char bgcolor_r, char bgcolor_g,char bgcolor_b) {
	char h, ch, p, mask;

	SetWindow(x, y, x + 7, y + 14);

	SendCom(0x2C);

	for (h = 0; h < 14; h++) //
			{
		ch = font[c][0 + h];		//
		mask = 0x80;			//
		for (p = 0; p < 8; p++)  	// write the pixels
				{
			if (ch & mask) //
					{
				SendDat(color_r);
				SendDat(color_g);
				SendDat(color_b);
			} else		//
			{
				SendDat(bgcolor_r);
				SendDat(bgcolor_g);
				SendDat(bgcolor_b);
			}
			mask = mask / 2;			//
		}
	}
}
/////////////////////////////////////////////////////////////////
void LCDchar(unsigned int x, unsigned int y, char c, char color_r, char color_g,char color_b, char bgcolor_r, char bgcolor_g, char bgcolor_b,unsigned int Scale) {
	char h, ch, p, mask, i, j;

	j = 2;
	SetWindow(x, y, x + (8 * Scale) - 1, y + (14 * Scale));

	SendCom(0x2C);

	for (h = 0; h < 14; h++) // every column of the character
			{
		ch = font[c][0 + h];

		for (j = 0; j < Scale; j++) {
			mask = 0x80;
			for (p = 0; p < 8; p++)  // write the pixels
					{
				if (ch & mask) {
					for (i = 0; i < Scale; i++) {
						SendDat(color_r);
						SendDat(color_g);
						SendDat(color_b);
					}
				}

				else {
					for (i = 0; i < Scale; i++) {
						SendDat(bgcolor_r);
						SendDat(bgcolor_g);
						SendDat(bgcolor_b);
					}
				}
				mask = mask / 2;
			}
		}
	}
}

void LCDchislo(unsigned int XX, unsigned int y, int ch, char color_r,char color_g, char color_b, char bgcolor_r, char bgcolor_g,char bgcolor_b) {
	const unsigned int step[3] = { 100, 10, 1 };
	char atemp;
	unsigned char ii;

	for (ii = 0; ii < 3; ii++) {
		atemp = 0;
		while (ch >= step[ii]) {
			atemp++;
			ch -= step[ii]; //temp;
		}
		// + 0x30  ĐżĐµŃ€ĐµĐ˛ĐľĐ´ Ń�Đ¸ĐĽĐ˛ĐľĐ»Đ° Đ˛ ASCII
//					if ((atemp == 0) & (ii != 2)) {atemp = ' ';}
//					else {atemp = atemp + 0x30;}
		LCDchar(XX + ii * 8, y, atemp + 0x30, color_r, color_g, color_b,
				bgcolor_r, bgcolor_g, bgcolor_b, 1);
	}
}

///////////////////////////////////////////////
void LCDpixel(unsigned int x, unsigned int y, char color_r, char color_g,char color_b) {
	SetWindow(x, y, x, y);
	SendCom(0x2C);
	SendDat(color_r);
	SendDat(color_g);
	SendDat(color_b);
}
/////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************************************************************************
 description:            High level functions to work with graphic displays
 author:                 VDLab
 ***********************************************************************************************************************/
/*----------------------------------------------------------------------------------------------------------------------
 function:               Line
 description:            draw line by Bresenham algorithm
 input:                  Xstart,Ystart - line start coordinates
 Xend,Yend - line end coordinates
 output:                 none
 ----------------------------------------------------------------------------------------------------------------------*/
void Line(int Xstart, int Ystart, int Xend, int Yend, char color_r,	char color_g, char color_b) {
	unsigned int nTmp;
	unsigned int nAlt = 0;
	int x, y;                                    // where is the current pixel.
	int dx;   	                                // dx is the delta for x
	int dy;   	                                // dy is the delta for y
	int StepVal = 0; // variable for figuring out when to increment the other axis.
	if (Xstart > Xend && Ystart > Yend) {
		nTmp = Xend;
		Xend = Xstart;
		Xstart = nTmp;
		nTmp = Yend;
		Yend = Ystart;
		Ystart = nTmp;

		dx = Xend - Xstart;                         // dx is the delta for x
		dy = Yend - Ystart;                         // dy is the delta for y
	} else {
		dx = Xend - Xstart;                         // dx is the delta for x
		dy = Yend - Ystart;                         // dy is the delta for y
		if (dy < 0) {
			dy = -dy;
			nTmp = Yend;
			Yend = Ystart;
			Ystart = nTmp;
			nAlt = 1;
		} else if (dx < 0) {
			dx = -dx;
			nTmp = Xend;
			Xend = Xstart;
			Xstart = nTmp;
			nAlt = 1;
		}
	}
	if (nAlt) {
		if (dx >= dy)                        // The slope is less than 45 degres
				{
			y = Yend;
			for (x = Xstart; x <= Xend; x++) {
				LCDpixel(x, y, color_r, color_g, color_b);
				StepVal += dy;
				if (StepVal >= dx) // Increment y if enough x steps have been taken.
						{
					y--;
					StepVal -= dx; // Reset StepVal, but not to 0.  This gives even slopes.
				}
			}
		} else // The slope is greater than 45 degrees, just like above, but with y instead of x.
		{
			x = Xend;
			for (y = Ystart; y <= Yend; y++) {
				LCDpixel(x, y, color_r, color_g, color_b);
				StepVal += dx;
				if (StepVal >= dy) {
					x--;
					StepVal -= dy;
				}
			}
		}
		return;
	}
	if (dx >= dy)                            // The slope is less than 45 degres
			{
		y = Ystart;
		for (x = Xstart; x <= Xend; x++) {
			LCDpixel(x, y, color_r, color_g, color_b);
			StepVal += dy;
			if (StepVal >= dx) // Increment y if enough x steps have been taken.
					{
				y++;
				StepVal -= dx; // Reset StepVal, but not to 0.  This gives even slopes.
			}
		}
	} else // The slope is greater than 45 degrees, just like above, but with y instead of x.
	{
		x = Xstart;
		for (y = Ystart; y <= Yend; y++) {
			LCDpixel(x, y, color_r, color_g, color_b);
			StepVal += dx;
			if (StepVal >= dy) {
				x++;
				StepVal -= dy;
			}
		}
	}
	return;
}
/*----------------------------------------------------------------------------------------------------------------------
 function:               Circle
 description:            draw circle by Bresenham algorithm
 input:                  x,y - center coordinates
 r - radius of circle
 color - 16 bit value of color in RGB-565 format
 output:                 none
 ----------------------------------------------------------------------------------------------------------------------*/

void Circle(int x, int y, int r, char color_r, char color_g, char color_b) {
	int x1, y1, yk = 0;
	int sigma, delta, f;

	x1 = 0;
	y1 = r;
	delta = 2 * (1 - r);
	do {
		LCDpixel(x + x1, y + y1, color_r, color_g, color_b);
		LCDpixel(x - x1, y + y1, color_r, color_g, color_b);
		LCDpixel(x + x1, y - y1, color_r, color_g, color_b);
		LCDpixel(x - x1, y - y1, color_r, color_g, color_b);
		f = 0;
		if (y1 < yk)
			break;
		if (delta < 0) {
			sigma = 2 * (delta + y1) - 1;
			if (sigma <= 0) {
				x1++;
				delta += 2 * x1 + 1;
				f = 1;
			}
		} else if (delta > 0) {
			sigma = 2 * (delta - x1) - 1;
			if (sigma > 0) {
				y1--;
				delta += 1 - 2 * y1;
				f = 1;
			}
		}
		if (!f) {
			x1++;
			y1--;
			delta += 2 * (x1 - y1 - 1);
		}
	} while (1);
}
/*----------------------------------------------------------------------------------------------------------------------
 function:               Grid
 description:            draw scope like grid
 input:                  type - if =1 - draws center of screen lines
 output:                 none
 ----------------------------------------------------------------------------------------------------------------------*/
/*
 void Grid(char type)
 {
 unsigned int x, y;

 if (type)
 {
 //    Line(0,120,319,120);
 //    Line(160,1,160,238);
 }
 for(y=0;y<240;y+=20)
 {
 for(x=0;x<320;x+=20)
 {
 //		LCDpixel(x,y,color_r,color_g,color_b);
 }
 }
 //Line(0,0,319,0);
 //Line(0,1,0,239);
 //Line(1,239,319,239);
 //Line(319,1,319,238);
 }
 /*----------------------------------------------------------------------------------------------------------------------*/
// function:               PutStr
// description:            put string to display
// input:                  x,y - position of text start
// *str - pointer to string to output
// output:                 none
/*----------------------------------------------------------------------------------------------------------------------*/
void PutStr(unsigned int x, unsigned int y, const char *str, char color_r,char color_g, char color_b, char bgcolor_r, char bgcolor_g,char bgcolor_b, unsigned int Scale) {
	char cmprr;

	while ((cmprr = *str++)) {
		LCDchar(x, y, cmprr, color_r, color_g, color_b, bgcolor_r, bgcolor_g,
				bgcolor_b, Scale);
		x += 8 * Scale;
		if (x > Disp_with - 9)
			return;
	}
}
/*----------------------------------------------------------------------------------------------------------------------
 function:               Rectangle
 description:            draw rectangle
 input:                  x,y - upper left corner coordinates
 width - width of rectangle
 height -height of rectangle
 Filled - if =1 - rectangle is filled
 output:                 none
 ----------------------------------------------------------------------------------------------------------------------*/
void Rectangle(unsigned int X, unsigned int Y, unsigned int Width,unsigned int Height, unsigned char Filled, char color_r, char color_g,char color_b) {
	unsigned long tmp;

	SetWindow(X, Y, X + (Width - 1), Y + (Height - 1));
	if (Filled) {
		tmp = (unsigned long) Height * Width;
		SendCom(0x2C);
		do {
			SendDat(color_r);
			SendDat(color_g);
			SendDat(color_b);
		} while (tmp--);
	} else {
		Line(X, Y, X + (Width - 1), Y, color_r, color_g, color_b);
		Line(X, Y + 1, X, Y + (Height - 1), color_r, color_g, color_b);
		Line(X + 1, Y + (Height - 1), X + (Width - 1), Y + (Height - 1),
				color_r, color_g, color_b);
		Line(X + (Width - 1), Y + 1, X + (Width - 1), Y + (Height - 1), color_r,
				color_g, color_b);
	}
}
/*----------------------------------------------------------------------------------------------------------------------
 function:               Window
 description:            draw windows95 like window
 input:                  x,y - upper left corner coordinates
 width - width of window
 height -height of window
 header - pointer to window header string
 output:                 none
 ----------------------------------------------------------------------------------------------------------------------*/
void Window(unsigned int X, unsigned int Y, unsigned int Width,	unsigned int Height, char type, const char *header) {
//Line(X,Y,X+(Width-1),Y,color_r,color_g,color_b);
//Line(X,Y+1,X,Y+(Height-1));
//Line(X+1,Y+(Height-1),X+(Width-1),Y+(Height-1),color_r,color_g,color_b);
//Line(X+(Width-1),Y+1,X+(Width-1),Y+(Height-1),color_r,color_g,color_b); 

	Rectangle(X + 1, Y + 1, Width - 2, Height - 2, 0, window);

	Rectangle(X + 2, Y + 2, Width - 4, 14, 1, blue);
	PutStr(X + 4, Y + 2, header, white, blue, 1);

	Line(X + 1, Y + 16, X + (Width - 2), Y + 16, window);
//--------client region----------------------------------------
	switch (type) {
	case 0: {
		Rectangle(X + 2, Y + 17, (Width - 4), Height - 19, 1, window);
		break;
	}
	case 1: {
		Rectangle(X + 2, Y + 17, (Width - 4), Height - 19, 0, black);
		Rectangle(X + 3, Y + 18, (Width - 6), (Height - 21), 1, white);
		break;
	}
	case 2: {
		Rectangle(X + 2, Y + 17, (Width - 4), Height - 19, 1, black);
		break;
	}
	default: {
		Rectangle(X + 2, Y + 17, (Width - 4), Height - 19, 0, black);

		Rectangle(X + 3, Y + 18, (Width - 6), (Height - 21), 1, lgrey);
		break;
	}
	}
}
///////////////////////////////////////////////////////////////
/***** private variables *****/
char RGB_buff[720] = { 0 };	// for pf_read of bitmap data	Đ Đ°Đ·ĐĽĐµŃ€ Đ±Ń�Ń„ĐµŃ€Đ° Ń�Ń‚Ń€ĐľĐşĐ¸
unsigned char bitmap_width;
unsigned int bitmap_height;
unsigned int count, row, column, line; //pixel
long data_start;
unsigned int rb;

/***** private functions *****/
void draw_from_24bpp(unsigned int x, unsigned int y);

// 24-bit Color to RRRGGGBB format
//#define RGB8(R,G,B)			( (R&0xE0) | ((G&0xE0)>>3) | ((B&0xC0)>>6) )

/***** exported function *****/
void draw_bitmap0(unsigned int x, unsigned int y, const char *filename) {
	unsigned char DW_buff[4] = { 0 };
	unsigned char W_buff[2] = { 0 };
	long compression_method;
	unsigned int bits_per_pixel;

//	//pf_lseek(0x00);
//	pf_read(W_buff, 2, &rb);			// 0x00
//	//if( (W_buff[0]=='B') && (W_buff[1]=='M') ){
//	//	PutStr(5, 120,"found BMP file",red,green);
//	//	PutStr(15, 110,filename,red,green);
//		pf_lseek(0x0A);					// 0x0A	- offset where the bitmap data (pixels) can be found.
//		pf_read(DW_buff, 4, &rb);
//		data_start = LD_DWORD(DW_buff);
//
//		pf_read(DW_buff, 4, &rb);		// 0x0E (dummy read)
//
//		pf_read(DW_buff, 4, &rb);		// 0x12
//		bitmap_width = DW_buff [0];     // Đ˘ĐľĐ´ŃŚĐşĐľ Đ´Đ»ŃŹ Đ¸Đ·ĐľĐ±Ń€Đ°Đ¶ĐµĐ˝Đ¸ŃŹ ĐĽĐµĐ˝ŃŚŃ�Đµ 256 ĐżĐľ ĐłĐľŃ€Đ¸Đ·ĐľĐ˝Ń‚Đ°Đ»Đ¸
//		pf_read(DW_buff, 4, &rb);		// 0x16
//		 bitmap_height = (DW_buff [1] << 8) + DW_buff [0];
// 
	//if( (bitmap_width>240) || (bitmap_height>320) ){
	//	PutStr(25, 100,"size error",red,green);
	//	return;
	//}

	//pf_read(W_buff, 2, &rb);		// 0x1A

	//pf_read(W_buff, 2, &rb);		// 0x1C	(bits/pixel)
	//bits_per_pixel = LD_WORD(W_buff);
	//if( (bits_per_pixel!=24) && (bits_per_pixel!=8) && (bits_per_pixel!=4) && (bits_per_pixel!=1) ){
	//if( (bits_per_pixel!=24) ){
	//	PutStr(25, 100,"not supported",red,green);
	//	return;
	//}

	//pf_read(DW_buff, 4, &rb);		// 0x1E
	//compression_method = LD_DWORD(DW_buff);
	//if( compression_method != 0 ){
	//	PutStr(25, 100,"not supported",red,green);
	//	return;
	//	}

	//	if(bits_per_pixel == 24)
	draw_from_24bpp(50, 50);	//	draw_from_24bpp(x,y);

//	}
//	else{
//		PutStr(25, 100,"invalid file.",red,green);
//		}
}

/*** 24 bits per pixel format ***/
void draw_from_24bpp(unsigned int x, unsigned int y) {
	unsigned int total;

	x = x + 0x01;
	y = y + 0x01;

	total = (bitmap_width << 1) + bitmap_width;	// max 960 = 320 columns * 3 RGB bytes
	if ((total % 4) != 0)
		total += 4 - (total % 4);// should be multiple of DWORD size (4 bytes)

//	SendCom(0x36);   // pixel write direction
	// 7:Mx  6:MY  5:90ĐłŃ€Đ°Đ´Ń�Ń�ĐľĐ˛  4:LAO  3:RGB 2:x  1:x  0:x ĐžŃ‚Đ˝ĐľŃ�Đ¸Ń‚Ń�ŃŹ ĐşĐľ Đ˛Ń�ĐµĐĽŃ� Ń‚Đ°Đ±Đ»Đľ!!!!
//	SendDat(0x40);
	//SetWindow(x,y,bitmap_width,bitmap_height);

	SetWindow(0, 0, 149, 150);

	extern char bmptest[];

//memset(RGB_buff,120,720);
//memcpy(RGB_buff, &bmptest[200],720);

	SendCom(0x2C);

//	pf_lseek(data_start);		// go to the start of bitmap data
///////for( row = bitmap_height; row>0; row--){
	for (row = 50; row > 0; row--) {
//		pf_read(RGB_buff, total, &rb);
		for (column = 0; column < 150; column++) {
			count = (column << 1) + column;	// count = column * 3;
			//pixel = RGB8( RGB_buff[count +0], RGB_buff[count + 1], RGB_buff[count + 2]); 
			SendDat(RGB_buff[count + 2]);
			SendDat(RGB_buff[count + 1]);
			SendDat(RGB_buff[count + 0]);
			//SendDat(125);SendDat(125);SendDat(125);
		}
	}
//Rectangle(0,0, 50, 50,1,255, 0, 0);
}

//##########################################################################################################################

void draw_bitmap24over(unsigned int X, unsigned int Y, unsigned int Width,unsigned int Height, char *filename) {
	unsigned long tmp;

//extern char bmptest[];	

	SetWindow(X, Y, X + (Width - 1), Y + (Height - 1));

	tmp = (unsigned long) Height * Width;
	unsigned long i;
	SendCom(0x2C);
	for (i = 0; i < tmp; i++) {
		SendDat(filename[(3 * i) + 2]);
		SendDat(filename[(3 * i) + 1]);
		SendDat(filename[(3 * i) + 0]);
	};
}
//-----------------------------------------------------------------------------------------------------

void draw_bitmap24(unsigned int X, unsigned int Y, unsigned int Width,unsigned int Height, char *filename) {
	unsigned long tmp;

	SetWindow(X, Y, X + (Width - 1), Y + (Height - 1));

	tmp = (unsigned long) Height * Width;

	SendCom(0x2C);
	do {
		SendDat(filename[(3 * tmp) + 2]);
		SendDat(filename[(3 * tmp) + 1]);
		SendDat(filename[(3 * tmp) + 0]);
	} while (tmp--);;
}
//----------------------------------------------------------------------------------------------------

