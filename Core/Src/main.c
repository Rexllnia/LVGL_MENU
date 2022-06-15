/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "i2c.h"
#include "lwip.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
//#include "lv_demo_benchmark.h"
#include "lv_port_indev.h"
#include "lv_port_disp.h"
#include "lvgl.h"
#include "ssd1306_tests.h"
#include "sys.h"
#include "stdio.h"
#include "ssd1306_fonts.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    static uint32_t time = 0;
//	if(htim->Instance == TIM6)  // ???6???
//	{
//         lv_tick_inc(1);
//	}
//}
static void anim_x_cb(void * var, int32_t v)
{
    lv_obj_set_x(var, v);
}

//static void sw_event_cb(lv_event_t * e)
//{
//    lv_obj_t * sw = lv_event_get_target(e);
//    lv_obj_t * label = lv_event_get_user_data(e);

//    if(lv_obj_has_state(sw, LV_STATE_CHECKED)) {
//        lv_anim_t a;
//        lv_anim_init(&a);
//        lv_anim_set_var(&a, label);
//        lv_anim_set_values(&a, lv_obj_get_x(label), 20);
//        lv_anim_set_time(&a, 500);
//        lv_anim_set_exec_cb(&a, anim_x_cb);
//        lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
//        lv_anim_start(&a);
//    } else {
//        lv_anim_t a;
//        lv_anim_init(&a);
//        lv_anim_set_var(&a, label);
//        lv_anim_set_values(&a, lv_obj_get_x(label), 0);
//        lv_anim_set_time(&a, 500);
//        lv_anim_set_exec_cb(&a, anim_x_cb);
//        lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
//        lv_anim_start(&a);
//    }

//}
static void event_cb2(lv_event_t * e)
{
    static unsigned int cnt = 1;
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * label = lv_event_get_user_data(e);
	 

//   
//    lv_label_set_text_fmt(label, "%u", cnt);
    cnt++;
		if(cnt==4)
		{
			cnt=1;
		}
		switch(cnt){
			case 1:
				lv_label_set_text_fmt(label, "VIDEO");
							break;
			case 2:
				lv_label_set_text_fmt(label, "AUDIO");
							break;
			case 3:
				lv_label_set_text_fmt(label, "Github");
				break;
		}
		lv_anim_t a;
		lv_anim_init(&a);
		lv_anim_set_var(&a, label);
		lv_anim_set_values(&a, lv_obj_get_x(label), 0);
		lv_anim_set_time(&a, 500);
		lv_anim_set_exec_cb(&a, anim_x_cb);
		lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
		lv_anim_start(&a);
		
}
static void event_cb(lv_event_t * e)
{
    static unsigned int cnt = 1;
    lv_obj_t * btn = lv_event_get_target(e);
//    lv_obj_t * label = lv_event_get_user_data(e);
	 
    lv_obj_t * img = lv_event_get_user_data(e);
		LV_IMG_DECLARE(github_logo);
//   
//    lv_label_set_text_fmt(label, "%u", cnt);
    cnt++;
		if(cnt==4)
		{
			cnt=1;
		}
		switch(cnt){
			case 1:
			lv_img_set_src(img, &LV_SYMBOL_VIDEO);lv_obj_center(img);
							break;
			case 2:
			lv_img_set_src(img, &LV_SYMBOL_AUDIO);lv_obj_center(img);
							break;
			case 3:
				lv_img_set_src(img, &github_logo);
							lv_obj_center(img);break;
		}

		
		lv_anim_t a2;
		lv_anim_init(&a2);
		lv_anim_set_var(&a2, img);
		lv_anim_set_values(&a2, lv_obj_get_x(img), 0);
		lv_anim_set_time(&a2, 500);
		lv_anim_set_exec_cb(&a2, anim_x_cb);
		lv_anim_set_path_cb(&a2, lv_anim_path_overshoot);
		lv_anim_start(&a2);
}
/**
 * Start animation on an event
 */
void lv_example_anim_1(void)
{
		static lv_style_t style_btn;  
//		lv_style_set_bg_color(&style_btn, lv_color_black());
	
    lv_obj_t * btn = lv_btn_create(lv_scr_act());
		lv_obj_set_pos(btn, 10, 10);
    lv_obj_set_size(btn, 10, 10);

    
		lv_obj_add_style(btn, &style_btn, LV_STATE_DEFAULT);

	
	
    lv_obj_t * label = lv_label_create(lv_scr_act());
   lv_label_set_text(label, "Click!");
   lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
//		lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, (void *)label);
		lv_obj_t * img = lv_img_create(lv_scr_act());
//	LV_IMG_DECLARE(github_logo);
//								lv_img_set_src(img, &github_logo);
//							lv_obj_center(img);
		lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, (void *)img);
		lv_obj_add_event_cb(btn, event_cb2, LV_EVENT_CLICKED, (void *)label);
		
}


//void lv_button_click_event_test()
//{
//	static lv_style_t style_btn;   
//	/* ??????????? */
//    lv_style_init(&style_btn);
//    lv_style_set_radius(&style_btn, 10);                                        //????
//    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);                              //?????
//    lv_style_set_bg_color(&style_btn, lv_color_black());  //??????
////    lv_style_set_bg_grad_color(&style_btn, lv_palette_main(LV_PALETTE_NONE));   //??????
////    lv_style_set_bg_grad_dir(&style_btn, LV_GRAD_DIR_VER);                      //??????

//    lv_style_set_border_color(&style_btn, lv_color_black());                    //??????
//    lv_style_set_border_opa(&style_btn, LV_OPA_20);                             //??????
//    lv_style_set_border_width(&style_btn, 2);                                   //???????

//    lv_style_set_text_color(&style_btn, lv_color_white());                      //???????

//   /****************************************************??1***********************************************************/
//    /*????????????*/
//    lv_obj_t* btn = lv_btn_create(lv_scr_act());
//    /* ?????????
//    * ???,?????????????
//	
//    * ?? lv_obj_remove_style_all ???????????? */
//		lv_obj_t * info_label = lv_label_create(lv_scr_act());
//		lv_obj_set_pos(info_label, 0, 50);
//    lv_label_set_text(info_label, "None");
//		lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, info_label);
//    lv_obj_remove_style_all(btn);
//    lv_obj_set_pos(btn, 10, 10);
//    lv_obj_set_size(btn, 80, 25);
//    lv_obj_add_style(btn, &style_btn, LV_STATE_DEFAULT);            //???????
//    /*???????*/
//    lv_obj_t* label = lv_label_create(btn);
//    lv_label_set_text(label, "Button");
//    lv_obj_center(label);
//		

//}


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM6_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  MX_LWIP_Init();
  /* USER CODE BEGIN 2 */
//	OLED_Init(hi2c1);
//lv_init();                  // lvgl???,?????????,???????????
//lv_port_disp_init();       // ??????

// lvgl_first_demo_start();

lv_init();                  // lvgl???,?????????,???????????
//ssd1306_TestAll();
lv_port_disp_init();        // ??????
lv_port_indev_init();
//lv_button_click_event_test();
lv_example_anim_1();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

		lv_task_handler();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

