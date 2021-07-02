#include <Map.h>
#include "stm32f3xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include "LiquidCrystal.h"
#include <time.h>
#include "LogicMario.h"
typedef unsigned char byte;
byte Brick[] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
byte Mario[] = {
  0x0F,
  0x0E,
  0x0E,
  0x04,
  0x1F,
  0x04,
  0x0A,
  0x11
};
byte QuestionBox[] = { 0x1F, 0x1B, 0x15, 0x1D, 0x19, 0x1B, 0x1F, 0x1B };
byte Pipe_Left[] = { 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x07, 0x07 };
byte Pipe_Right[] = { 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1C, 0x1C };
byte Ground[] = { 0x1F, 0x1F, 0x11, 0x1B, 0x15, 0x1B, 0x11, 0x1F };
byte Flag[] = { 0x03, 0x07, 0x0F, 0x1F, 0x01, 0x01, 0x01, 0x01 };
byte Blade[] = { 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x1F, 0x1F, 0x18 };
byte None[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
int current_start_map = 0; //start map from this variable to after 20
void create_rows() {
	srand(time(0));
	init_custom_chars();
	for (int var = 0; var < 4; ++var) {
		setCursor(0, var);
		map[var][0] = BLADE;
		write(BLADE);
	}
	//init mario
	map[2][2] = MARIO;
	current_state.row = 2;
	current_state.clo = 2;
	current_state.health = 3;
	setCursor(2, 2);
	write(MARIO);
	//init flag
	map[2][59] = FLAG;
	//generate rows
	row_zero();
	row_one();
	row_two();
	row_three();
	init_print_map();
	display();
	initialized_map = 1;
}
void row_zero() {

	for (int var = 1; var < 60; ++var) {
		int random = rand();
		if (random % 5 == 0) {
			map[0][var] = BRICK;
		} else if (random % 5 == 1) {
			map[0][var] = QUESTION_BOX;
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
	for (int var = 2; var < 60; ++var) {
		int random = rand();
		if (random % 5 == 0) {
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
	//row zero
	for (int var = 1; var < 20; ++var) {
		setCursor(var, 0);
		if (map[0][var] == BRICK) {
			write(BRICK);
		} else if (map[0][var] == QUESTION_BOX) {
			write(QUESTION_BOX);
		} else if (map[0][var] == NONE) {
			write(NONE);
		}
	}

	//row two
	for (int var = 1; var < 20; ++var) {
		setCursor(var, 2);
		if (map[2][var] == PIPE_LEFT) {
			write(PIPE_LEFT);
		} else if (map[2][var] == PIPE_RIGHT) {
			write(PIPE_RIGHT);
		} else if (map[2][var] == NONE) {
			write(NONE);
		}
	}

	//row three
	for (int var = 1; var < 20; ++var) {
		setCursor(var, 3);
		if (map[3][var] == GROUND) {
			write(GROUND);
		} else if (map[3][var] == NONE) {
			write(NONE);
		}
	}
}
void print_map() {
	//flag
	if(current_start_map ==59 ){
		setCursor(59, 2);
		write(FLAG);
	}

	// reduce health and game over
	if(current_state.clo == current_start_map)
	{

		if (current_state.health >0) {
			current_state.health = current_state.health -1;
			current_start_map = 0;
		}else{
			is_game_over =1 ;
			clear();
			setCursor(6, 2);
			print("GAME OVER");
			setCursor(0, 0);
		}
		return;
	}
	current_state.clo = current_state.clo +1 ;
	//row zero
	for (int var = current_start_map + 1; var < current_start_map + 20; ++var) {
		setCursor(var - current_start_map, 0);
		if (map[0][var] == BRICK) {
			write(BRICK);
		} else if (map[0][var] == QUESTION_BOX) {
			write(QUESTION_BOX);
		} else if (map[0][var] == NONE) {
			write(NONE);
		}
	}

	//row two
	for (int var = current_start_map + 1; var < current_start_map + 20; ++var) {
		setCursor(var - current_start_map, 2);
		if (map[2][var] == PIPE_LEFT) {
			write(PIPE_LEFT);
		} else if (map[2][var] == PIPE_RIGHT) {
			write(PIPE_RIGHT);
		} else if (map[2][var] == NONE) {
			write(NONE);
		}
	}

	//row three
	for (int var = current_start_map + 1; var < current_start_map + 20; ++var) {
		setCursor(var - current_start_map, 3);
		if (map[3][var] == GROUND) {
			write(GROUND);
		} else if (map[3][var] == NONE) {
			write(NONE);
		}
	}
}
void shift_display() {
	if (current_start_map + 20 < 60) {
		current_start_map++;
		print_map();
	} else {
		clear();
		setCursor(0, 0);
		print("END GAME");
		setCursor(0, 0);

	}

}
void clear_display() {
	for (int var = 0; var < 4; ++var) {
		setCursor(0, var);
		print("                    ");
	}
	setCursor(0, 0);
}

