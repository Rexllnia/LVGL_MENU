# LVGL_MENU
Keil5 project

1. USE Ctrl+H find this according to the annotation，then place the Draw Pixel function of your screen drivers here.
用Ctrl+H来按照注释寻找到对应位置，放置一个画一个像素点的函数
/*Put a pixel to the display. For example:*/				
ssd1306_DrawPixel(x, y, color_p->full);
/*put_px(x, y, *color_p)*/

2. your screen initial function can put here. 
初始化函数可以放这里
/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
	ssd1306_Init();
		
}

3. your Screen resolution for example mine is lcd128*64.
设置分辨率
#define MY_DISP_HOR_RES     (128)    
#define MY_DISP_VER_RES     (64)   



4. Sign up the button .
注册按钮
static bool button_is_pressed(uint8_t id)
{

    /*Your code comes here*/
		if(PAin(4)==0&&id==0)
		{
			
			
			return true;
		}
    return false;
}

5.Here to set Tick . 
设置心跳
#define LV_TICK_CUSTOM 0 
#if LV_TICK_CUSTOM
#define LV_TICK_CUSTOM_INCLUDE "stm32f4xx_hal.h"         /*Header for the system time function*/
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (HAL_GetTick())    /*Expression evaluating to current system time in ms*/
宏定义LV_TICK_CUSTOM用来设置心跳方式，0代表定时器方式，1代表HAL库自带滴答定时器方式


6.main function
主函数
  /* USER CODE BEGIN WHILE */
  while (1)
  {
lv_timer_handler();
//		lv_task_handler();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
lv_timer_handler();

