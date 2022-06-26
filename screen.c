
#include "screen.h"

//this whole file is based on ansi escape codes:
//https://en.wikipedia.org/wiki/ANSI_escape_code

//clear the screen
void screenClear(void)
{
 printf("\033[H\033[J");
 fflush(stdout);
}

//reset printing attributes
void screenReset(void)
{
 printf("\033[0m");
 fflush(stdout);
}

//put a char at x,y using current attributes
void screenPut(int8_t x,int8_t y,uint8_t c)
{
 printf("\033[%d;%dH%c",y+1,x+1,c);
 fflush(stdout);
}

//put a char at x,y changing foreground and background colors
void screenColorPut(int8_t x,int8_t y,int8_t fg,int8_t bg,uint8_t c)
{
 printf("\033[%d;%dH\033[%d;%dm%c",y+1,x+1,bg+10,fg,c);
 //reset the screen attributes since this fg and bg are just for this print
 screenReset();
 fflush(stdout);
}

//print a string at x,y using current attributes
void screenPrint(int8_t x,int8_t y,char* format,...)
{
 va_list argumentList;
 //get the variadic function arguments
 va_start(argumentList,format);
 printf("\033[%d;%dH",y+1,x+1);
 //use vprintf since it takes a va_list while printf takes a ...
 vprintf(format,argumentList);
 fflush(stdout);
 va_end(argumentList);
}

//print a string at x,y changing foreground and background colors
void screenColorPrint(int8_t x,int8_t y,int8_t fg,int8_t bg,char* format,...)
{
 va_list argumentList;
 va_start(argumentList,format);
 printf("\033[%d;%dH\033[%d;%dm",y+1,x+1,bg+10,fg);
 vprintf(format,argumentList);
 //reset the screen attributes since this fg and bg are just for this print
 screenReset();
 fflush(stdout);
 va_end(argumentList);
}

//change foreground and background colors attribute
void screenColor(int8_t fg,int8_t bg)
{
 printf("\033[%d;%dm",bg+10,fg);
 fflush(stdout);
}

