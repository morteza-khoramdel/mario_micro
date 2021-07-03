/*
 * LogicMario.c
 *
 *  Created on: Jul 1, 2021
 *      Author: morteza
 */
#include "Map.h"
#include <LogicMario.h>
//0 for failed and 1 for successful -1 for Game end
int check_forward() {
	if (map[current_state.row][current_state.clo + 1] == NONE) {
		if (current_state.clo < 60) {
			map[current_state.row][current_state.clo] = NONE;
			map[current_state.row][current_state.clo + 1] = MARIO;
			if (current_state.clo <= 19) {
				setCursor(current_state.clo, current_state.row);
			} else {
				setCursor(current_state.clo - 20, current_state.row);
			}
			write(NONE);
			current_state.clo = current_state.clo + 1;
			if (current_state.clo <= 19) {
				setCursor(current_state.clo, current_state.row);
			} else {
				setCursor(current_state.clo - 20, current_state.row);
			}
			write(MARIO);
			return 1;
		} else {
			printf("You Can't Forward Because Game is End");
			return -1;
		}
	} else {
		printf("You Can't Forward");
		return 0;

	}
}
//0 for failed and 1 for one jump 2 for two jump
int jump() {
	if (current_state.clo < 60) {
		if (map[current_state.row - 1][current_state.clo] == NONE
				&& map[current_state.row - 2][current_state.clo] == NONE) {
			map[current_state.row][current_state.clo] = NONE;
			map[current_state.row - 2][current_state.clo] = MARIO;
			return 2;
		} else if (map[current_state.row - 1][current_state.clo] == NONE) {
			if (map[current_state.row - 2][current_state.clo] == QUESTION_BOX) {
				current_state.score = ++current_state.score;
			}
			map[current_state.row][current_state.clo] = NONE;
			map[current_state.row - 2][current_state.clo] = MARIO;
			return 1;
		} else {
			printf("You Can't Jump");

		}
	} else {
		printf("You Can't Forward Because Game is End");
		return 0;

	}
}
