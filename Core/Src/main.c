/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint32_t lastShow = 0;
uint32_t delay123 = 0;
uint32_t delayAdc1 = 0;
uint32_t delaySpeed = 0;
uint32_t jumpDelay = 0;
unsigned char uartData[1];
unsigned char massage[100];
int coinsNumber = 47;
int speed = 35;
int action = 0;
int jump = 0;
int pause = 0;
int four = 1;
int game = 0;
int map[4][60];
int position[2] = {2, 2};
int lastPosition[2] = {2, 2};
int startGamebutton = 0;
int icounter = 0;
int life = 3;
int lastLife = 3;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */

typedef unsigned char byte;

byte blade[] = {
	0x18,
	0x1C,
	0x1F,
	0x1C,
	0x18,
	0x1C,
	0x1F,
	0x1C
};

byte mario[] = {
  0x0E,
  0x0E,
  0x04,
  0x0E,
  0x1F,
  0x15,
  0x0E,
  0x1B
};


byte brick[] = {
  0x1F,
  0x15,
  0x0A,
  0x15,
  0x0A,
  0x15,
  0x0A,
  0x1F
};

byte box[] = {
  0x1F,
  0x15,
  0x1B,
  0x13,
  0x15,
  0x11,
  0x15,
  0x1F
};

byte ground[] = {
  0x1F,
  0x1B,
  0x0B,
  0x1E,
  0x17,
  0x0F,
  0x1D,
  0x1F
};

byte leftPipe[] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x0F,
  0x0F
};

byte rightPipe[] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1E,
  0x1E
};

byte flag[] = {
  0x1F,
  0x15,
  0x0B,
  0x05,
  0x03,
  0x01,
  0x01,
  0x01
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(HAL_GetTick() > lastShow + 300 ){

		if (GPIO_Pin == GPIO_PIN_0)
		{
			for(int i = 0 ; i < 4 ; i++){
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
				//S1
				if(i == 0){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0)){
//					  print("7");
					  action = 7;
				  }
				}
				//S2
				else if(i == 1){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0)){
					  if(game == 1 && pause != 1){
						  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
						  action = 8;
					  }
				  }
				}
				//S3
				else if(i == 2){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0)){
//					  print("9");
					  action = 9;
				  }
				}
				//S4
				else if(i == 3){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0)){
//					  print("A");
					  life--;
				  }
				}
			}
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		}
		if (GPIO_Pin == GPIO_PIN_1)
		{
			for(int i = 0 ; i < 4 ; i++){
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
				//S5
				if(i == 0){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)){
//					  print("4");
					  action = 4;
				  }
				}
				//S6
				else if(i == 1){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)){
//					  print("5");
					  if(pause == 0){
						  pause = 1;
					  }else{
						  pause = 0;
					  }
					  action = 5;
				  }
				}
				//S7
				else if(i == 2){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)){
//					  print("6");
					  action = 6;
				  }
				}
				//S8
				else if(i == 3){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)){
//					  print("B");
				  }
				}
			}
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		}
		if (GPIO_Pin == GPIO_PIN_2)
		{
			for(int i = 0 ; i < 4 ; i++){
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
				//S9
				if(i == 0){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2)){
//					  print("1");
					  action = 1;
				  }
				}
				//S10
				else if(i == 1){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2)){
//					  print("2");
					  action = 2;
				  }
				}
				//S11
				else if(i == 2){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2)){
//					  print("3");
					  action = 3;
				  }
				}
				//S12
				else if(i == 3){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2)){
//					  print("C");
				  }
				}
			}
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		}
		if (GPIO_Pin == GPIO_PIN_3)
		{
			for(int i = 0 ; i < 4 ; i++){
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
				//S13
				if(i == 0){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3)){
//					  print("E");
					  game = 2;
				  }
				}
				//S14
				else if(i == 1){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3)){
//					  print("0");
					  action = 0;
				  }
				}
				//S15
				else if(i == 2){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3)){
//					  print("S");
					  if(game == 0){
						  startGamebutton = 1;
						  coinsNumber = 0;
					  }
				  	}
				}
				//S16
				else if(i == 3){
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
				  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3)){
//					  print("D");
					  coinsNumber++;
				  }
				}
			}
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		}

		lastShow = HAL_GetTick();
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
    	switch (uartData[0]){
    		case '1':
    			//TODO
    			action = 1;
    			break;
    		case '2':
    			//TODO
    			action = 2;
    			break;
    		case '3':
    			//TODO
    			action = 3;
    			break;
    		case '4':
    			//TODO
    			action = 4;
    			break;
    		case '5':
    			//TODO
				if(pause == 0){
					pause = 1;
				}else{
					pause = 0;
				}
    			action = 5;
    			break;
    		case '6':
    			//TODO
    			action = 6;
    			break;
    		case '7':
    			//TODO
    			action = 7;
    			break;
    		case '8':
    			//TODO
    			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
    			action = 8;
    			break;
    		case '9':
    			//TODO
    			action = 9;
    			break;
    	}
        HAL_UART_Receive_IT(&huart2, uartData, sizeof(uartData));
    }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	////Mario
	if (htim->Instance == TIM3)
	{

		if(game == 1 && pause == 0){

			lastPosition[0] = position[0];
			lastPosition[1] = position[1];

			if(life == 2 && lastLife == 3){
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 0);
				lastLife = 2;
			}
			if(life == 1  && lastLife == 2){
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 0);
				lastLife = 1;
			}
			if(life == 0  && lastLife == 1){
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
//				game = 2;
				lastLife = 0;
				pause = 1;
				setCursor(1, 1);
				print("Life = 0 Game Over");
			}

			if(position[1] > icounter){
				setCursor(position[1] - icounter, position[0]);
				write(1);
			}
//			else{
//				setCursor(position[1] - icounter + 1, position[0]);
//				print(" ");
//				game = 2;
//			}
			switch(action){
				case 9:

					break;
				case 8:
					  if(map[position[0] - 1][position[1]] == -1){
						  if(map[position[0] - 2][position[1]] == -1){
							  jump = 2;
						  }else{
							  jump = 1;
						  }
					  }
					break;
				case 7:

					break;
				case 6:
					  if(map[position[0]][position[1] + 1] == -1){
//						  lastPosition[0] = position[0];
//						  lastPosition[1] = position[1];
						  position[1]++;
//						  map[lastPosition[0]][lastPosition[1]] = -1;
	//					  map[position[0]][position[1]] = 1;
					  }
					break;
				case 5:

					break;
				case 4:

					break;
				case 3:

					break;
				case 2:

					break;
				case 1:

					break;
				case 0:

					break;
			}
			action = 0;
			if(HAL_GetTick() > jumpDelay + (speed * 30) )
				if(jump != 0){
					if(jump == 1){

					}
					if(jump == 2){

					}
				}

			jumpDelay = HAL_GetTick();
		}
	}

	////Playground
	if (htim->Instance == TIM2)
	{
		////Behind The Game
		if(game == 0){
			if(startGamebutton == 1){
				//Set Values
				game = 1;
				startGamebutton = 0;


				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 1);
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 1);
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
				//// Generating Random Map
			    srand(HAL_ADC_GetValue(&hadc1));
			    //pre-arranged
			    for(int i = 0 ; i < 4 ; i++){
			    	for(int j = 0 ; j < 60 ; j++){
			    		map[i][j] = -1;
			    	}
			    }
				map[3][0] = 4;
				map[3][1] = 4;
				map[3][2] = 4;
				map[3][3] = 4;
				map[2][0] = 0;
				map[1][0] = 0;
				map[0][0] = 0;
				map[2][58] = 7;
				//row 3
				for(int i = 4 ; i < 60 ; i++){
					int temp = 4*(rand()%5);
					if(temp == 0){
						map[3][i] = -1;
					}else{
						map[3][i] = 4;
					}

				}
				//row 2
				for(int i = 5 ; i < 56 ; i++){
					int temp = 5*(rand()%2);
					if(temp != 0 && map[2][i-1] != 6){
						if(map[3][i] == 4 && map[3][i+1] == 4 ){
							map[2][i] = 5;
							i++;
							map[2][i] = 6;
						}
					}
				}
				//row 0
				for(int i = 3 ; i < 56 ; i++){
					int temp = 2*(rand()%3);
					if(temp == 2){
						map[0][i] = 2;
					}
					if(temp == 4){
						map[0][i] = 3;
					}
				}
				////Finish Generation

				clear();
				position[0] = 2;
				position[0] = 2;
				lastPosition[0] = 2;
				lastPosition[1] = 2;

			}
		}


		//// On the Game
		if(game == 1 && pause == 0){

			//**
			//Show the start

			if(icounter < 41 && HAL_GetTick() >= delaySpeed + 400 - (speed * 20)){
				setCursor(0, 3);
				write(map[3][icounter]);
				for(int j = 1 ; j < 20 ; j++){
					for(int k = 0 ; k < 4 ; k++){
						if(!((position[0] == k) && (position[1] == j + icounter))){
							if(map[k][j + icounter] != -1){
								setCursor(j, k);
								write(map[k][j + icounter]);
							}else{
								if(map[k][j + icounter - 1] != -1){
									setCursor(j, k);
									print(" ");
								}
							}
						}else{
							if(position[1] < icounter + 1){
								game = 2;
							}
						}
					}
				}
				for(int l = 0 ; l < 3 ; l++){
					setCursor(0, l);
					write(0);
				}


				icounter++;
			}
			//Game Over
			if (game == 2){
				setCursor(4, 1);
				sprintf(massage, "SPEED : %d", speed);
				print(massage);
				setCursor(4, 2);
				sprintf(massage, "SCORE : %d", coinsNumber);
				print(massage);
				setCursor(4, 3);
				print("Game Over");
			}

			////End Show
			// Win
			if( position[0] == 2 && position[1] == 58){
				game = 3;
			}
			if(game == 3 || icounter >= 41){
				clear();
				setCursor(4, 0);
				write(0xfc);
				setCursor(4, 1);
				sprintf(massage, "SPEED : %d", speed);
				print(massage);
				setCursor(4, 2);
				sprintf(massage, "SCORE : %d", coinsNumber);
				print(massage);
				setCursor(2, 3);
				print("Congratulations !");
			}


			delaySpeed = HAL_GetTick();

		}
	}
    if (htim->Instance == TIM4)
    {
		switch (four){
			case 1 :
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 , 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15 , 0);
				//write your code to do when first LED on
				int temp = speed / 10;
				toBCDConverter(temp % 10);
				four++;
				break;
			case 2 :
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15 , 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14 , 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2 , 1);
				//write your code to do when second LED on
				toBCDConverter(speed % 10);
				four++;
				break;
			case 3 :
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2 , 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14 , 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13 , 0);
				//write your code to do when thrid LED on
				temp = coinsNumber / 10;
				toBCDConverter(temp % 10);
				four++;
				break;
			case 4 :
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13 , 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 , 0);
				//write your code to do when forth LED on
				toBCDConverter(coinsNumber % 10);
				four = 1;
				break;
		}

    }

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
//    	if(HAL_GetTick() >= delayAdc1 + 250 ){

			int x = HAL_ADC_GetValue(&hadc1);
			speed = (x*15/4014)+5;
			unsigned char data[100] = "";
			int n = sprintf(data, "%d : %d\n", x, speed);
			HAL_UART_Transmit(&huart2, data, n, 1000);

//    	}
//			float fx = ((float) x * 100/4014);

//			HAL_UART_Transmit(&huart2, data, n, 1000);
//    	}

//    	delayAdc1 = HAL_GetTick();
		HAL_ADC_Start_IT(&hadc1);

    }
}

void toBCDConverter(int i){
	int x1 = i & 1;
	int x2 = i & 2;
	int x3 = i & 4;
	int x4 = i & 8;
	if(x1 > 0) x1 = 1;
	if(x2 > 0) x2 = 1;
	if(x3 > 0) x3 = 1;
	if(x4 > 0) x4 = 1;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, x1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, x2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, x3);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, x4);
}




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
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  LiquidCrystal(GPIOD, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
  begin(20, 4);

  HAL_ADC_Start_IT(&hadc1);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_UART_Receive_IT(&huart2, uartData, sizeof(uartData));
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);

  createChar(0, blade);
  createChar(1, mario);
  createChar(2, brick);
  createChar(3, box);
  createChar(4, ground);
  createChar(5, leftPipe);
  createChar(6, rightPipe);
  createChar(7, flag);

	setCursor(2, 2);
	write(1);
	setCursor(0, 3);
	write(4);
	setCursor(1, 3);
	write(4);
	setCursor(2, 3);
	write(4);
	setCursor(3, 3);
	write(4);
	setCursor(0, 2);
	write(0);
	setCursor(0, 1);
	write(0);
	setCursor(0, 0);
	write(0);
	setCursor(19, 2);
	write(7);
	//row 3
	for(int i = 4 ; i < 20 ; i++){
		int temp = 4*(rand()%5);
		if(temp != 0){
			setCursor(i, 3);
			write(4);
		}
	}
	//row 2
	for(int i = 5 ; i < 16 ; i++){
		int temp = 5*(rand()%5);
		if(temp == 0){
			setCursor(i, 2);
			write(5);
			i++;
			setCursor(i, 2);
			write(6);
		}
	}
	//row 0
	for(int i = 3 ; i < 16 ; i++){
		int temp = 2*(rand()%3);
		if(temp == 2){
			setCursor(i, 0);
			write(2);
		}
		if(temp == 4){
			setCursor(i, 0);
			write(3);
		}
	}

	setCursor(2, 1);
	print("Press S To Start");
	setCursor(5, 1);

  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 3599;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 3599;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 10000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 7199;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 100;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|GPIO_PIN_7|LD4_Pin|LD3_Pin
                          |LD5_Pin|LD7_Pin|LD9_Pin|LD10_Pin
                          |LD8_Pin|LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin PE7 LD4_Pin LD3_Pin
                           LD5_Pin LD7_Pin LD9_Pin LD10_Pin
                           LD8_Pin LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|GPIO_PIN_7|LD4_Pin|LD3_Pin
                          |LD5_Pin|LD7_Pin|LD9_Pin|LD10_Pin
                          |LD8_Pin|LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : MEMS_INT3_Pin MEMS_INT4_Pin */
  GPIO_InitStruct.Pin = MEMS_INT3_Pin|MEMS_INT4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB12
                           PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
