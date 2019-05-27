#ifndef _LCD_LS022_H
#define _LCD_LS022_H

#define Disp_with 320
#define Disp_height 240

#define lo(w) ((unsigned char)(w))
#define hi(w) ((unsigned char)(((unsigned int)(w) >> 8)))	

#define black  0,0,0       //
#define red    255,0,0     //
#define green  0,255,0     //
#define blue   0,0,255     //
#define orang  255,150,0   //
#define yelow  255,255,0   //
#define cyan   0,255,255   //
#define white  255,255,255 //
#define window 189,149,131 //
#define lgrey  218,225,235 //
#define contrast 160	//(unsigned char)(50 * 255 / 100)
extern void GPIO_Init(void);
//----------------------------------------------------------------------------------------------------------------------
void SendCom(unsigned int);
//----------------------------------------------------------------------------------------------------------------------
void SendDat(unsigned int);
//----------------------------------------------------------------------------------------------------------------------
void S6D04D1init(void);
//----------------------------------------------------------------------------------------------------------------------
void LCDclear(char mode,char color_r,char color_g, char color_b);
//----------------------------------------------------------------------------------------------------------------------
void LCDchar(unsigned int x, unsigned int y, char c, char color_r, char color_g,
		char color_b, char bgcolor_r, char bgcolor_g, char bgcolor_b,
		unsigned int Scale);
//----------------------------------------------------------------------------------------------------------------------
void SetWindow(unsigned int, unsigned int, unsigned int, unsigned int);
//----------------------------------------------------------------------------------------------------------------------
void LCDchislo(unsigned int x, unsigned int y, int ch, char color_r,
		char color_g, char color_b, char bgcolor_r, char bgcolor_g,
		char bgcolor_b);
//----------------------------------------------------------------------------------------------------------------------
void LCDpixel(unsigned int x, unsigned int y, char color_r, char color_g,
		char color_b);
//----------------------------------------------------------------------------------------------------------------------
void draw_bitmap0(unsigned int, unsigned int, const char *filename);
//----------------------------------------------------------------------------------------------------------------------
void Line(int, int, int, int, char color_r, char color_g, char color_b);
//----------------------------------------------------------------------------------------------------------------------
void Circle(int, int, int, char color_r, char color_g, char color_b);
//----------------------------------------------------------------------------------------------------------------------
void Rectangle(unsigned int, unsigned int, unsigned int, unsigned int,
		unsigned char, char color_r, char color_g, char color_b);
//----------------------------------------------------------------------------------------------------------------------
void Window(unsigned int, unsigned int, unsigned int, unsigned int, char,
		const char *);
//----------------------------------------------------------------------------------------------------------------------
void PutStr(unsigned int, unsigned int, const char *, char color_r,
		char color_g, char color_b, char bgcolor_r, char bgcolor_g,
		char bgcolor_b, unsigned int Scale);
//----------------------------------------------------------------------------------------------------------------------
void draw_bitmap24(unsigned int X, unsigned int Y, unsigned int Width,
		unsigned int Height, char *filename);
//----------------------------------------------------------------------------------------------------------------------
void DMA_Graf(unsigned int X, unsigned int Y, char * Ydata, char* last);

#endif

