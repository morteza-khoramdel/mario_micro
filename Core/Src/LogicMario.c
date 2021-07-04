/*
 * LogicMario.c
 *
 *  Created on: Jul 1, 2021
 *      Author: morteza
 */
#include "Map.h"
#include <LogicMario.h>
//0 for failed / 1 for successful /-1 for Game end /2 for
int check_forward() {
	if (current_state.clo < 60) {
		if (map[current_state.row][current_state.clo + 1] == NONE) {
			if (current_state.row
					== 2&& map[current_state.row +1][current_state.clo +1] == NONE) {
				map[current_state.row][current_state.clo] = NONE;
				map[current_state.row + 1][current_state.clo] = MARIO;
				current_state.row = current_state.row + 1;
				return 2;
			}
			map[current_state.row][current_state.clo] = NONE;
			map[current_state.row][current_state.clo + 1] = MARIO;
			current_state.clo = current_state.clo + 1;
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

void jump() {
	int type = type_jump();
	switch (type) {
	case 2:
		jump_up();
		jump_up();
		jump_down();
		jump_down();
		break;
	case 1:
		jump_up();
		jump_down();
		break;
	default:
		break;
	}
}
//0 for failed / and 1 for one jump /  2 for two jump / -1 for ended game
int type_jump() {
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
	setCursor(current_state.clo, current_state.row);
	write(NONE);
	map[current_state.row - 1][current_state.clo] = MARIO;
	current_state.row = current_state.row - 1;
	setCursor(current_state.clo, current_state.row);
	write(MARIO);
	if (current_state.row
			== 1&& map[current_state.row - 2][current_state.clo] == QUESTION_BOX) {
		current_state.score = current_state.score + 1;
	}

}
void jump_down() {
	map[current_state.row][current_state.clo] = NONE;
	setCursor(current_state.clo, current_state.row);
	write(NONE);
	map[current_state.row + 1][current_state.clo] = MARIO;
	current_state.row = current_state.row + 1;
	setCursor(current_state.clo, current_state.row);
	write(MARIO);
}

