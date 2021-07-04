/*
 * LogicMario.c
 *
 *  Created on: Jul 1, 2021
 *      Author: morteza
 */
#include "Map.h"
#include <LogicMario.h>
#include "SevenSegment.h"
//0 for failed / 1 for successful /-1 for Game end /2 for
int check_forward() {
	if (current_state.clo < 60) {
		if (map[current_state.row][current_state.clo + 1] == NONE) {
			if (current_state.row
					== 2&& map[current_state.row +1][current_state.clo +1] == NONE) {
				map[current_state.row][current_state.clo] = NONE;
				setCursor(current_state.clo, current_state.row);
				write(NONE);
				current_state.row = current_state.row + 1;
				map[current_state.row][current_state.clo] = MARIO;
				setCursor(current_state.clo, current_state.row);
				write(MARIO);
				return 2;
			}
			map[current_state.row][current_state.clo] = NONE;
			setCursor(current_state.clo - current_start_map + 1,
					current_state.row);
			write(NONE);
			current_state.clo = current_state.clo + 1;
			map[current_state.row][current_state.clo] = MARIO;
			setCursor(current_state.clo - current_start_map, current_state.row);
			write(MARIO);
			return 1;

		} else {
			printf("You Can't Forward");
			return 0;
		}
	} else {
		printf("You Can't Forward Because Game is End");
		return -1;
	}
}

//0 for failed / and 1 for one jump /  2 for two jump / -1 for ended game
int get_type_jump() {
	if (current_state.clo < 60) {
		if (map[current_state.row - 1][current_state.clo] == NONE
				&& map[current_state.row - 2][current_state.clo] == NONE) {
			return 2;
		} else if (map[current_state.row - 1][current_state.clo] == NONE) {
			return 1;
		} else {
			printf("You Can't Jump");
			return 0;
		}
	} else {
		printf("You Can't Forward Because Game is End");
		return -1;

	}
}
void jump_up() {
	map[current_state.row][current_state.clo] = NONE;
	setCursor(current_state.clo - current_start_map + 1, current_state.row);
	write(NONE);
	map[current_state.row - 1][current_state.clo] = MARIO;
	current_state.row = current_state.row - 1;
	setCursor(current_state.clo - current_start_map + 1, current_state.row);
	write(MARIO);
	if (current_state.row
			== 1&& map[current_state.row - 2][current_state.clo] == QUESTION_BOX) {
		current_state.score = current_state.score + 1;
		score_1  = current_state.score % 10;
		score_2  =current_state.score /10;
		submitNumbers(speed_seven_1, speed_seven_2, score_1, score_2);
	}

}
void jump_down() {
	map[current_state.row][current_state.clo] = NONE;
	setCursor(current_state.clo - current_start_map + 1, current_state.row);
	write(NONE);
	map[current_state.row + 1][current_state.clo] = MARIO;
	current_state.row = current_state.row + 1;
	setCursor(current_state.clo - current_start_map + 1, current_state.row);
	write(MARIO);
}
void jump() {
	if (state_jump < 4) {
		switch (type_jump) {
		case 2:
			switch (state_jump) {
			case 0:
			case 1:
				jump_up();
				break;
			case 2:
			case 3:
				jump_down();
				break;
			}
			state_jump++;
			break;
		case 1:
			if (state_jump == 0) {
				jump_up();
			} else if (state_jump == 1) {
				jump_down();
			}
			state_jump++;
			break;
		}
	} else {
		state_jump = 0;
		type_jump = 0;
	}
}

