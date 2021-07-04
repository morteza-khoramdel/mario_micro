/*
 * SevenSegment.c
 *
 *  Created on: Jul 4, 2021
 *      Author: morteza
 */
#include "stm32f3xx.h"

void numberTOBCD(int i) {
	int x1 = i & 1;
	int x2 = i & 2;
	int x3 = i & 4;
	int x4 = i & 8;
	if (x1 > 0)
		x1 = 1;
	if (x2 > 0)
		x2 = 1;
	if (x3 > 0)
		x3 = 1;
	if (x4 > 0)
		x4 = 1;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, x1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, x2);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, x3);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, x4);

}
void submitNumbers(int a1, int a2, int a3, int a4) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
			0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 1);
	numberTOBCD(a4);
	HAL_Delay(3);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3, 1);
	numberTOBCD(a3);
	HAL_Delay(3);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3, 1);
	numberTOBCD(a2);
	HAL_Delay(3);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, 1);
	numberTOBCD(a1);
	HAL_Delay(3);
}
