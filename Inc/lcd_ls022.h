#ifndef _LCD_LS022_H
#define _LCD_LS022_H

#define Disp_with 320
#define Disp_height 240

#define lo(w) ((unsigned char)(w))
#define hi(w) ((unsigned char)(((unsigned int)(w) >> 8)))	
	
#define black  0,0,0       // черный
#define red    255,0,0     // красный
#define green  0,255,0     // зеленый
#define blue   0,0,255     // синий
#define orang  255,150,0   // оранжевый
#define yelow  255,255,0   // жолтый
#define cyan   0,255,255   // бирюзовый
#define white  255,255,255 // белый
#define window 189,149,131 //  в 16 бит: 0x9BEF  ?????13 31 15???
#define lgrey  218,225,235 // светлосерый

	
//ПЕРЕДАЧА КОМАНДЫ В ТАБЛО
 void SendCom(unsigned int);
//-----------------------------
//ПЕРЕДАЧА ДАННЫХ В ТАБЛО
 void SendDat(unsigned int);
//-----------------------------
//ИНИЦИАЛИЗАЦИЯ ДИСПЛЕЯ
 void LCDinit(char mode);     // c учетом ориентации 0- горизонтальная   1 - вертикальная
//-----------------------------
//ОЧИСТКА ДИСПЛЕЯ (ПО ВЕРТИКАЛИ!!!)
 void LCDclear(char mode);
//-----------------------------------------------------------------
//ВЫВОД СИМВОЛА ASCII В УКАЗАННОЙ ПОЗИЦИИ С ЗАДАННЫМ ЦВЕТОМ И ФОНОМ
 void LCDchar(unsigned int x, unsigned int y, char c, char color_r, char color_g, char color_b, char bgcolor_r, char bgcolor_g, char bgcolor_b, unsigned int Scale);
//-----------------------------------------------------------------
//ОПРЕДЕЛЕНИЕ ОБЛАСТИ ВЫВОДА КАРТИНКИ ИЛИ ПИКСЕЛЯ 
 void SetWindow(unsigned int, unsigned int, unsigned int, unsigned int);
//-----------------------------------------------------------------
//ВЫВОД ЧИСЛА ДО 999 В УКАЗАННОЙ ПОЗИЦИИ С ЗАДАННЫМ ЦВЕТОМ И ФОНОМ  
 void LCDchislo(unsigned int x, unsigned int y, int ch, char color_r, char color_g, char color_b, char bgcolor_r, char bgcolor_g, char bgcolor_b);
//-----------------------------------------------------------------
//ВЫВОД ЦВЕТНОГО ПИКСЕЛЯ ПО УКАЗАННЫМ КООРДИНАТАМ 
 void LCDpixel(unsigned int x,unsigned int y, char color_r, char color_g, char color_b);
//----------------------------------------------------------------------------------------------------------------------
// Void Draw_bitmap
//ВЫВОДИТ BMP ФАЙЛ НА ЭКРАН - РАЗРЕШЕНИЕ 240Х320 24 БИТ ЦВЕТ, С НАЧАЛЬНЫМИ КООРДИНАТАМИ X,Y
//Выводить следует "по вертикали", т.к. буфер в ОЗУ содержит одну строку, а оно не резиновое
//Если надо по горизонтали на весь экран, то надо задать размерность массива RGB 320х3 вместо 240х3
// А лучше развернуть файл
void draw_bitmap0(unsigned int, unsigned int, const char *filename);
/*----------------------------------------------------------------------------------------------------------------------
function:               Line
description:            draw line by Bresenham algorithm 
input:                  Xstart,Ystart - line start coordinates
                        Xend,Yend - line end coordinates
                        color - 24 bit value of color in RGB format
output:                 none
----------------------------------------------------------------------------------------------------------------------*/
void Line(int, int, int, int, char color_r, char color_g, char color_b);
/*----------------------------------------------------------------------------------------------------------------------
function:               Circle
description:            draw circle by Bresenham algorithm 
input:                  x,y - center coordinates
                        r - radius of circle
                        color - 16 bit value of color in RGB-565 format
output:                 none
----------------------------------------------------------------------------------------------------------------------*/
void Circle(int, int, int, char color_r, char color_g, char color_b);

/*----------------------------------------------------------------------------------------------------------------------
function:               Rectangle
description:            draw rectangle
input:                  x,y - upper left corner coordinates
                        width - width of rectangle
                        height -height of rectangle
                        Filled - if =1 - rectangle is filled
output:                 none
----------------------------------------------------------------------------------------------------------------------*/
void Rectangle(unsigned int, unsigned int, unsigned int, unsigned int, unsigned char, char color_r, char color_g, char color_b);
/*----------------------------------------------------------------------------------------------------------------------
function:               Window
description:            draw windows95 like window :)
input:                  x,y - upper left corner coordinates
                        width - width of window
                        height -height of window
                        type   type of window
                        header - pointer to window header string 
output:                 none
----------------------------------------------------------------------------------------------------------------------*/
void Window(unsigned int, unsigned int, unsigned int, unsigned int, char, const char *);
/*----------------------------------------------------------------------------------------------------------------------
function:               Grid
description:            draw scope like grid
input:                  type - if =1 - draws center of screen lines 
output:                 none
----------------------------------------------------------------------------------------------------------------------*/
//void Grid(char type);
/*----------------------------------------------------------------------------------------------------------------------
function:               PutStr
description:            put string to display
input:                  x,y - position of text start
                        *str - pointer to string to output
output:                 none
----------------------------------------------------------------------------------------------------------------------*/
void PutStr(unsigned int, unsigned int , const char *, char color_r, char color_g, char color_b, char bgcolor_r, char bgcolor_g, char bgcolor_b, unsigned int Scale);

#define contrast 160	//(unsigned char)(50 * 255 / 100)

//#####################################################################################################################

void draw_bitmap24(unsigned int X, unsigned int Y, unsigned int Width, unsigned int Height,char *filename);
//void  DMA_bitmap24(unsigned int X, unsigned int Y, unsigned int Width, unsigned int Height,char *filename);
//void Graf128(unsigned int X, unsigned int Y, char *filename);
void DMA_Graf(unsigned int X, unsigned int Y, char * Ydata , char* last);

#endif



