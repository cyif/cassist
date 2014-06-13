#include "C_Assist.h"

#define titleX  150
#define titleY  150
#define contentX    230
#define contentY    520

int initial_interface(char *filename)
{
    char key;
    char *str;
    int length=0;
    int currentX = 380;
    int currentY = 530;
    graph_mode(VESA_1024x768x8bit);
    /*setbkcolor(WHITE);
    bar(0,0,1024,768);
    load_8bit_bmp(0,0,"index.bmp");
    setcolor(BLACK);*/

    setfillstyle(1,21);
    bar(0,0,1024,768);

    setcolor(LIGHTRED);
    out_ttf_text_xy(titleX, titleY, "C 语 言 教 学 助 手", "simyahei.ttf", 60);  
    rectangle(200,500,800,600);
    out_ttf_text_xy(contentX,contentY,"请输入文件名：","simyahei.ttf", 15);

    key = getch();
    while (key != '\r' && key != 27)
    {
        filename[length++] = key;
        sprintf(str,"%c",key);
        outtextxy(currentX,currentY,str);
        currentX+=10;
        key = getch();
    }
    filename[length] = 0;
    closegraph();
    if (key == 27) 
        return 0;
    else 
        return 1;
}

/*int main()
{
    char *filename;
    initial_interface(filename);
}*/