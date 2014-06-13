/*
 *
 *  Filename:  C_Assist.h
 *  Created:  03/08/2014
 *  Author:  Leo Lee , leeleo3x@gmail.com
 *
 */

#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include "CLex/CLex.h"

#define MAX_LINE_LENGTH 128
#define MAX_LINE_SUM 500
#define Key_Left    0x4b00
#define Key_Right 	0x4d00
#define Key_Down	0x5000
#define Key_Up		0x4800
#define Key_Esc		0x011b
#define Key_Enter	0x1c0d
#define Key_Delete  0x0e08
#define Key_Tab		0x0f09
#define TAB "    "

struct 
{
  int x, y;
  struct picture *old_img;
  struct picture *mask;
  struct picture *img;
} mouse;

const int borderWidth = 15;
const int charHeight = 15;
const int charWidth = 8;
int MouseLeftFlag = 0;
int styleMark;

/*code indent module*/
void codeIndent(const char * fileName);

/*CAnalyser*/
void CLexAnalyser(char file[], struct normalNode ** nHead, struct errorNode ** eHead, struct identiferNode ** iHead);
void printCode(int beginX, int beginY, int width, int height, struct normalNode * normalPoint);
void printError(int beginX, int beginY,int width,int height, struct errorNode * errorPoint);
void printScore();
void indexPrint(int beginX, int beginY, int width, int height, char *filename);
int getStyleMark();

/*Print Content*/
void printContent(int beginX, int beginY, int width, int height, struct normalNode * normalPoint, struct errorNode * errorPoint); 
void removeComment(char *filename);
int initial_interface(char *filename);

int init_mouse();
void get_mouse_position(int *x,int *y);
void move_mouse();
void close_mosuse();
int leftPress();
