#include "C_Assist.h"

#define menuWidth	  1024
#define menuHeight  35
#define msgWidth    1024
#define msgHeight   162
#define	codeWidth	  1024
#define codeHeight	566

void work(const char *filename);
void click(int x0, int y0, int x1, int y1);
int getNum(int x,int y);
void menuWindow();
void msgWindow();
void codeWindow();
void printMenu();

struct normalNode *nHead;
struct errorNode *eHead;
struct identiferNode *iHead;

int stop;

int main()
{
    char *filename;
    initial_interface(filename);
    stop = 0;
    work(filename);
    free(nHead);
    free(eHead);
    free(iHead);
	  return 0;
}

void work(const char *filename)
{
  char *nowfile;
	int x,y,lastX,lastY;

	graph_mode(VESA_1024x768x8bit);
	menuWindow();
	codeWindow();
  msgWindow();
	printMenu();

  nowfile = filename;
  indexPrint(msgWidth+1, menuHeight+1, codeWidth, codeHeight, nowfile);
	//CLexAnalyser(nowfile,&nHead,&eHead,&iHead);
	//printCode(msgWidth+1,menuHeight+1,codeWidth,codeHeight,nHead);

	init_mouse();

	while (!stop)
	{
		if(leftPress()!=1)    
    {
        get_mouse_position(&x,&y); 
        if(x!=lastX || y!=lastY)
        {
            move_mouse(x,y);
    	      lastX = x;
            lastY = y;
        }
    }
    else if(MouseLeftFlag==1)  
  	{
    	  MouseLeftFlag=0;  
        get_mouse_position(&x,&y);
  	    switch(getNum(x,y))
  	    {
    	    case 1:
          {
    	    	removeComment(nowfile);
            CLexAnalyser(nowfile,&nHead,&eHead,&iHead);
            codeWindow();
            printCode(0,menuHeight+1,codeWidth,codeHeight,nHead);
    	    	break;
          }
    	    case 2:
          {
    	    		codeIndent(filename);
    	    		CLexAnalyser("indent.tmp",&nHead,&eHead,&iHead);
              //nowfile = "indent.tmp";
    	    		codeWindow();
    	    		printCode(0,menuHeight+1,codeWidth,codeHeight,nHead);
    	    		break;
          }
    	    case 3:
          {
    	    		msgWindow();
              //CLexAnalyser(nowfile,)
    	    		printError(0,menuHeight+codeHeight+1,msgWidth,msgHeight,eHead);
    	    		break;
          }
    	    case 4:
          {
    	    		msgWindow();
              printScore(200,600);
              //CLexAnalyser(nowfile,&nHead,&eHead,&iHead);
    	    		break;
          }
    	    case 5:
          {
    	    		stop = 1;
    	    		break;
          }
        }
    }
  }

	close_mouse();
  free(mouse.old_img);
  free(mouse.mask);
  free(mouse.img);
	closegraph();
}

void indexPrint(int beginX, int beginY, int width, int height, char *filename)
{
  FILE *fp;
  char buff[200];
  char *str;
  int currentX, currentY;
  int textViewPosX, textViewPosY;
  int textViewWidth, textViewHeight;
  int currentLine;

  textViewPosX = beginX + borderWidth;
  textViewPosY = beginY;
  textViewWidth = width - borderWidth;
  textViewHeight = height;
  currentX = textViewPosX;
  currentY = textViewPosY;
  currentLine = 0;

  setfillstyle(SOLID_FILL, LIGHTGRAY);
  bar(beginX, beginY, beginX + borderWidth, beginY + height);
  fp = fopen(filename,"r");
  while (fgets(&buff[0],199,fp)!=NULL)
  {
    currentY = currentY + charHeight;
    currentX = textViewPosX;
    currentLine ++;

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    itoa(currentLine, str, 10);
    outtextxy(currentX - borderWidth, currentY, str);
    setcolor(WHITE);
    buff[strlen(buff)-1] = '\0';
    outtextxy(currentX,currentY,buff);
  }
  fclose(fp);
}

void printScore(int x, int y)
{
  char str[3];
  int num = styleMark;
  itoa(num,str,10);
  setcolor(LIGHTRED);
  out_ttf_text_xy(x,y,"Your Score Is :","courier.ttf", 40);
  out_ttf_text_xy(x+500,y,str,"courier.ttf",45);

}

void printMenu()
{
  PIC *p[6];
  int i;

  setcolor(2);
  p[0] = get_ttf_text_pic("CA","courier.ttf",30);
  setcolor(15);
  p[1] = get_ttf_text_pic("语法高亮","simyahei.ttf",12);
  p[2] = get_ttf_text_pic("代码缩进","simyahei.ttf",12);
  p[3] = get_ttf_text_pic("错误提示","simyahei.ttf",12);
  p[4] = get_ttf_text_pic("风格评分","simyahei.ttf",12);
  p[5] = get_ttf_text_pic("返回","simyahei.ttf",12);

  draw_picture(0,0,p[0]);
  destroy_picture(p[0]);
  for (i=1; i<6; i++)
  {
    draw_picture(170+i*150,5,p[i]);
    destroy_picture(p[i]);
  }
  
}

void menuWindow()
{
	setfillstyle(1,21);
	bar(0,0,menuWidth,menuHeight);
	setcolor(15);
	rectangle(0,0,menuWidth,menuHeight);
}

void msgWindow()
{
	setfillstyle(1,25);
	bar(0,menuHeight+codeHeight+1,msgWidth,menuHeight+codeHeight+msgHeight);
}

void codeWindow()
{
	setfillstyle(1,18);
	bar(0,menuHeight+1,codeWidth,menuHeight+codeHeight);
}

void click(int x0, int y0, int x1, int y1)
{
	int i;
	setcolor(15);
	rectangle(x0+1,y0+1,x1-1,y1-1);
	delay(300);

	setcolor(21);
	rectangle(x0+1,y0+1,x1-1,y1-1);
}

int getNum(int x,int y)
{
	if (y>menuHeight) return -1;
	if (x>=280 && x<430) 
	{
		click(280,0,430,menuHeight);
		return 1;
	}
	if (x>=430 && x<580)
	{
		click(430,0,580,menuHeight);
		return 2;
	}
	if (x>=580 && x<730) 
	{
		click(580,0,730,menuHeight);
		return 3;
	}
	if (x>=730 && x<880)
	{
		click(730,0,880,menuHeight);
		return 4;
	}
	if (x>=880 && x<=1024)
	{
		click(880,0,1024,menuHeight);
		return 5;
	}
	return -1;
}
