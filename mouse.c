#include "C_Assist.h"

#define MOUSE_SIZE               16   
#define MOUSE_MOVE               0x01
#define MOUSE_LEFT_BUTTON_DOWN   0x02
#define MOUSE_LEFT_BUTTON_UP     0x04
#define MOUSE_RIGHT_BUTTON_DOWN  0x08
#define MOUSE_RIGHT_BUTTON_UP    0x10
#define MOUSE_MIDDLE_BUTTON_DOWN 0x20
#define MOUSE_MIDDLE_BUTTON_UP   0x40

void (far *old_mouse_event_handler)(int event, int x, int y);
void draw_mouse(int x, int y);
void recover_mouse_background(void);
void save_mouse_background(int x, int y);
void expand_mask_to_image(word m[16], byte *p, byte color, int width, int height);
void build_mouse_image();

word screen_mask[] =
{
   /* 16 words of screen mask */
   0x3FFF, /*0011111111111111*/
   0x1FFF, /*0001111111111111*/
   0x0FFF, /*0000111111111111*/
   0x07FF, /*0000011111111111*/
   0x03FF, /*0000001111111111*/
   0x01FF, /*0000000111111111*/
   0x00FF, /*0000000011111111*/
   0x007F, /*0000000001111111*/
   0x01FF, /*0000000111111111*/
   0x10FF, /*0001000011111111*/
   0xB0FF, /*1011000011111111*/
   0xF87F, /*1111100001111111*/
   0xF87F, /*1111100001111111*/
   0xFC3F, /*1111110000111111*/
   0xFC3F, /*1111110000111111*/
   0xFE1F, /*1111111000011111*/
};

word cursor_mask[] =
{
   /* 16 words of cursor mask */
   0x0000, /*0000000000000000*/
   0x4000, /*0100000000000000*/
   0x6000, /*0110000000000000*/
   0x7000, /*0111000000000000*/
   0x7800, /*0111100000000000*/
   0x7C00, /*0111110000000000*/
   0x7E00, /*0111111000000000*/
   0x7F00, /*0111111100000000*/
   0x7C00, /*0111110000000000*/
   0x4600, /*0100011000000000*/
   0x0600, /*0000011000000000*/
   0x0300, /*0000001100000000*/
   0x0300, /*0000001100000000*/
   0x0180, /*0000000110000000*/
   0x0180, /*0000000110000000*/
   0x00C0, /*0000000011000000*/
};


void get_mouse_position(int *x,int *y) 
{
	union REGS ireg,oreg;
  ireg.w.ax=3; 
	int86(0x33,&ireg,&oreg); 
	*x=oreg.w.cx; 
	*y=oreg.w.dx;  
}

int leftPress() 
{
   ireg.w.ax=3; 
	int86(0x33,&ireg,&oreg);
	delay(30);   
	if(oreg.w.bx&1)    
	   MouseLeftFlag=1;
	return oreg.w.bx&1; 
}

void expand_mask_to_image(word m[16], byte *p, byte color, int width, int height)
{
   int i, j;
   for(i=0; i<height; i++)
   {
      for(j=0; j<width; j++)
      {
         if(m[i] & 1<<(width-1-j))
            p[i*width+j] = color;
         else
            p[i*width+j] = 0x00;
      }
   }
}

void build_mouse_image(void)
{
   mouse.old_img = malloc(imagesize(0, 0, MOUSE_SIZE-1, MOUSE_SIZE-1));
   mouse.mask = malloc(imagesize(0, 0, MOUSE_SIZE-1, MOUSE_SIZE-1)); 
   mouse.img = malloc(imagesize(0, 0, MOUSE_SIZE-1, MOUSE_SIZE-1));
   mouse.mask->picwidth = mouse.mask->picheight = MOUSE_SIZE;
   mouse.img->picwidth = mouse.img->picheight = MOUSE_SIZE;
   expand_mask_to_image(screen_mask, &mouse.mask->buffer, 0xFF, MOUSE_SIZE, MOUSE_SIZE);
   expand_mask_to_image(cursor_mask, &mouse.img->buffer, WHITE, MOUSE_SIZE, MOUSE_SIZE);
}

void save_mouse_background(int x, int y)
{
   getimage(x, y, x+MOUSE_SIZE-1, y+MOUSE_SIZE-1, mouse.old_img);
   mouse.x = x;
   mouse.y = y;
}

void draw_mouse(int x, int y)
{
   putimage(x, y, mouse.mask, AND_PUT);
   putimage(x, y, mouse.img, OR_PUT);
}

void recover_mouse_background(void)
{
   putimage(mouse.x, mouse.y, mouse.old_img, COPY_PUT);
}

void move_mouse(int x, int y)
{
   recover_mouse_background();
   save_mouse_background(x, y);
   draw_mouse(x, y);
}

int init_mouse()
{
   int x=_width/2, y=_height/2;
   union REGS r;
   struct SREGS sr;

   r.w.ax = 0;    
   int86(0x33, &r, &r);
   if(r.w.ax != 0xFFFF)
      return 0;

   r.w.ax = 0x0007; 
   r.w.cx = 0;
   r.w.dx = _width-1;
   int86(0x33, &r, &r);
   r.w.ax = 0x0008; 
   r.w.cx = 0;
   r.w.dx = _height-1;
   int86(0x33, &r, &r);

   r.w.ax = 0x0004; 
   r.w.cx = x;
   r.w.dx = y;
   int86(0x33, &r, &r);

   r.w.ax = 2;    
   int86(0x33, &r, &r);

   r.w.ax = 0x0014; 
   r.w.cx = MOUSE_MOVE | MOUSE_LEFT_BUTTON_DOWN | MOUSE_LEFT_BUTTON_UP |
            MOUSE_RIGHT_BUTTON_DOWN | MOUSE_RIGHT_BUTTON_UP; 
   memset(&sr, 0, sizeof(sr));
   int86x(0x33, &r, &r, &sr);
   //old_mouse_event_handler = MK_FP(sr.es, r.x.edx);

   build_mouse_image();
   save_mouse_background(x, y);
   move_mouse(x, y);

   return 1;
}

void close_mouse()
{
   union REGS r;
   struct SREGS sr;
   r.w.ax = 0x0014; 
   r.w.cx = 0;
   //r.x.edx = FP_OFF(old_mouse_event_handler);
   memset(&sr, 0, sizeof(sr));
   //sr.es   = FP_SEG(old_mouse_event_handler);
   int86x(0x33, &r, &r, &sr);
}