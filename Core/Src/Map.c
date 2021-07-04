#include <Map.h>
#include "stm32f3xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include "LiquidCrystal.h"
#include <time.h>
#include "LogicMario.h"
typedef unsigned char byte;
byte Brick[] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
byte Mario[] = { 0x0F, 0x0E, 0x0E, 0x04, 0x1F, 0x04, 0x0A, 0x11 };
byte QuestionBox[] = { 0x1F, 0x1B, 0x15, 0x1D, 0x19, 0x1B, 0x1F, 0x1B };
byte Pipe_Left[] = { 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x07, 0x07 };
byte Pipe_Right[] = { 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1C, 0x1C };
byte Ground[] = { 0x1F, 0x1F, 0x11, 0x1B, 0x15, 0x1B, 0x11, 0x1F };
byte Flag[] = { 0x03, 0x07, 0x0F, 0x1F, 0x01, 0x01, 0x01, 0x01 };
byte Blade[] = { 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x1F, 0x1F, 0x18 };
byte None[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void create_rows() {
	srand(time(0));
	init_custom_chars();
	init_blade();
	//generate rows
	row_zero();
	row_one();
	row_two();
	row_three();
	init_print_map();
}
void row_zero() {

	for (int var = 1; var < 60; ++var) {
		int random = rand();
		if (random % 5 == 0) {
			map[0][var] = QUESTION_BOX;
		} else if (random % 5 == 1) {
			map[0][var] = BRICK;
		} else {
			map[0][var] = NONE;
		}
	}

}
void row_one() {
	for (int var = 1; var < 60; ++var) {
		map[1][var] = NONE;
	}
}

void row_two() {
	//init mario
	map[2][3] = MARIO; //16
	current_state.row = 2; //2
	current_state.clo = 3; //16 //47 1000
	current_state.health = 3;
	map[2][2] = NONE;
	map[2][1] = NONE;
	//init flag
	map[2][59] = FLAG;
	for (int var = 4; var < 60; ++var) {
		int random = rand();
		if (random % 13 == 0) {
			if (var != 59) {
				map[2][var] = PIPE_LEFT;
				map[2][var + 1] = PIPE_RIGHT;
				var++;
			} else {
				map[2][var] = NONE;
			}

		} else {
			map[2][var] = NONE;
		}
	}

}

void row_three() {
	for (int var = 1; var < 60; ++var) {
		int random = rand();
		if (random % 7 == 0) {
			if (map[2][var] == PIPE_LEFT || map[2][var] == PIPE_RIGHT) {
				map[3][var] = GROUND;
			} else {
				map[3][var] = NONE;
			}
		} else {
			map[3][var] = GROUND;
		}
	}
}
void init_custom_chars() {
	createChar(BLADE, Blade);
	createChar(FLAG, Flag);
	createChar(GROUND, Ground);
	createChar(PIPE_LEFT, Pipe_Left);
	createChar(PIPE_RIGHT, Pipe_Right);
	createChar(QUESTION_BOX, QuestionBox);
	createChar(MARIO, Mario);
	createChar(BRICK, Brick);
	createChar(NONE, None);

}
void init_print_map() {
	setCursor(1, 0);
	for (int i = 1; i < 20; i++) {
		write(map[0][i]);
	}
	setCursor(1, 2);
	for (int i = 1; i < 20; i++) {
		write(map[2][i]);
	}
	setCursor(1, 3);
	for (int i = 1; i < 20; i++) {
		write(map[3][i]);
	}

}
void print_map() {
	//flag
	if (current_start_map == 59) {
		setCursor(59, 2);
		write(FLAG);
	}

	// reduce health and game over for waiting mario
	if (current_state.clo == current_start_map -1) {

		if (current_state.health > 0) {
			reset_state();
		} else {
			is_game_over = 1;
			clear();
			setCursor(6, 2);
			print("GAME OVER");
			setCursor(0, 0);
			HAL_TIM_Base_Stop_IT(&htim2);

		}
		return;
	}
	shift_mario();

	//if go to pit
		if (current_state.row == 3) {
			if (current_state.health > 0) {
				reset_state();
			} else {
				is_game_over = 1;
				clear();
				setCursor(6, 2);
				print("GAME OVER");
				setCursor(0, 0);
				HAL_TIM_Base_Stop_IT(&htim2);

			}
		}
	setCursor(1, 0);
	for (int i = current_start_map; i < current_start_map + 19; i++) {
		if (map[0][i] != MARIO) {
			write(map[0][i]);
		}
	}
	setCursor(1, 2);
	for (int i = current_start_map; i < current_start_map + 19; i++) {
		if (map[2][i] != MARIO) {
			write(map[2][i]);
		}
	}
	setCursor(1, 3);
	for (int i = current_start_map; i < current_start_map + 19; i++) {
		if (map[3][i] != MARIO) {
			write(map[3][i]);
		}
	}


}
void shift_display() {
	if (current_start_map + 20 < 60) {
		print_map();
		current_start_map++;
	} else {
		clear();
		setCursor(0, 0);
		print("END GAME");
		setCursor(0, 0);
		HAL_TIM_Base_Stop_IT(&htim2);

	}

}
void clear_display() {
	for (int var = 0; var < 4; ++var) {
		setCursor(0, var);
		print("                    ");
	}
	setCursor(0, 0);
}
void shift_mario() {
	setCursor(current_state.clo - current_start_map + 1, current_state.row);
	write(NONE);
	setCursor(current_state.clo - current_start_map, current_state.row);
	write(MARIO);

}
void init_blade() {
	//init blade
	for (int var = 0; var < 4; ++var) {
		setCursor(0, var);
		map[var][0] = BLADE;
		write(BLADE);
	}
}
void reset_state() {
	clear();
	current_state.health = current_state.health - 1;
	current_start_map = 0;
	map[2][3] = MARIO; //16
	setCursor(3, 2);
	write(MARIO);
	current_state.row = 2; //2
	current_state.clo = 3; //16 //47 1000
	map[2][2] = NONE;
	map[2][1] = NONE;
	start = 0;
	init_blade();
	HAL_TIM_Base_Stop_IT(&htim2);
}
