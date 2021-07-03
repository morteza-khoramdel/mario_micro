/*
 * MapCreator.h
 *
 *  Created on: Jun 30, 2021
 *      Author: morteza
 */

#ifndef INC_MAPCREATOR_H_
#define INC_MAPCREATOR_H_
#define BRICK  0
#define MARIO 1
#define QUESTION_BOX 2
#define PIPE_LEFT 3
#define PIPE_RIGHT 4
#define FLAG 5
#define BLADE 6
#define NONE 7
#define GROUND 8

struct mario_state {
	int row;
	int clo;
	int score;
	int health	 ;
};
struct mario_state current_state;
int map[4][60];

#endif /* INC_MAPCREATOR_H_ */
int is_game_over ;


void create_rows();
void init_custom_chars();
void row_zero();
void row_two();
void row_three();
void init_print_map();
void clear_display();
void row_one();
void shift_display();
