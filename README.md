# LVGL_MENU
Keil5 project

1. USE Ctrl+H find this according to the annotation，then place the Draw Pixel function of your screen drivers here.
/*Put a pixel to the display. For example:*/				
ssd1306_DrawPixel(x, y, color_p->full);
/*put_px(x, y, *color_p)*/

2. your screen initial function can put here. 
/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
	ssd1306_Init();
		
}

3. your Screen resolution for example mine is lcd128*64.
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES     (128)    
#define MY_DISP_VER_RES     (64)   



4. Sign up the button .
/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id)
{

    /*Your code comes here*/
		if(PAin(4)==0&&id==0)
		{
			
			
			return true;
		}
//		else
//		{
//			PEout(14)=1;
//		}

    return false;
}
