
#ifndef _screen_
#define _screen_

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/ioctl.h>

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37
#define BLACK_BRIGHT 90
#define RED_BRIGHT 91
#define GREEN_BRIGHT 92
#define YELLOW_BRIGHT 93
#define BLUE_BRIGHT 94
#define MAGENTA_BRIGHT 95
#define CYAN_BRIGHT 96
#define WHITE_BRIGHT 97

extern uint16_t screenWidth;
extern uint16_t screenHeight;

void screenInit(void);

void screenDeinit(void);

void screenReset(void);

void screenClear(void);

void screenPut(int8_t x,int8_t y,uint8_t c);

void screenColorPut(int8_t x,int8_t y,int8_t fg,int8_t bg,uint8_t c);

void screenPrint(int8_t x,int8_t y,char* format,...);

void screenColorPrint(int8_t x,int8_t y,int8_t fg,int8_t bg,char* format,...);

void screenColor(int8_t fg,int8_t bg);

#endif

