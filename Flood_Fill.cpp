#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAZE_WIDTH 16
#define MAZE_HEIGHT 16
#define N 1
#define E 2
#define S 4
#define W 8
#define NUM_OF_OP(OP) (OP>>4)
#define V 16

typedef struct cord {
	uint8_t row;
	uint8_t col;
	struct cord * next_cord;
} Cord;

typedef struct stack {
	Cord * first;
} Stack;

/* ---------- Stack ---------- */
Stack* create_stack();
Cord* create_cord(uint8_t row, uint8_t col);
void push(Stack* stack, uint8_t row, uint8_t col);
Cord* pop(Stack* stack);

/* ---------- Maze Level ---------- */
void view_full_maze();
void navigate();
void init_maze();
void view_current_maze();
void move_to_next_cell();
void update_maze_value();

/* ---------- Cell Level ---------- */
void update_cell_with_wall_info();
void mark_current_cell_as_visited();
uint8_t find_new_wall();
uint8_t find_new_north_wall();
uint8_t find_new_west_wall();
uint8_t find_new_south_wall();
uint8_t find_new_east_wall();
uint8_t has_a_north_wall(uint8_t cell);
uint8_t has_a_west_wall(uint8_t cell);
uint8_t has_a_south_wall(uint8_t cell);
uint8_t has_an_east_wall(uint8_t cell);
uint8_t is_visited(uint8_t cell);
uint8_t north_cell_is_visited();
uint8_t west_cell_is_visited();
uint8_t south_cell_is_visited();
uint8_t east_cell_is_visited();
uint8_t mouse_is_at_cell(uint8_t row, uint8_t col);
uint8_t distance_of(Cord * c);
uint8_t min_open_neighbor_distance_of(Cord * c);
void set_distance_of(Cord * c, uint8_t d);


/* ---------- Global Variables ---------- */
// Paste Wall map values created from excel sheet here
uint8_t PSEUDO_MAP[MAZE_WIDTH][MAZE_HEIGHT] = { { 14,14,14,14,13,5,6,14,14,12,5,4,4,4,5,6 },{ 9,1,1,2,12,5,3,8,2,10,14,10,11,8,6,10 },{ 12,5,4,1,3,12,5,3,8,3,8,3,12,3,10,10 },{ 10,14,11,12,5,1,6,14,8,7,11,12,3,13,2,10 },{ 9,0,5,0,6,14,11,8,1,7,12,3,12,5,2,10 },{ 14,9,5,2,9,2,12,3,13,4,3,12,3,12,3,10 },{ 8,4,5,2,13,2,8,5,7,10,12,3,13,1,4,3 },{ 10,10,13,0,5,2,11,12,4,0,0,7,12,7,9,6 },{ 11,9,5,2,13,0,7,9,3,11,11,12,2,13,5,2 },{ 13,6,14,10,13,0,5,4,5,4,4,3,9,5,6,10 },{ 14,10,10,10,13,0,7,10,12,3,10,12,5,5,0,3 },{ 10,9,1,2,13,0,6,11,11,14,11,10,13,6,8,7 },{ 8,4,5,0,7,10,8,5,6,9,4,1,6,10,9,7 },{ 11,11,14,10,12,2,10,14,9,4,3,12,3,9,4,7 },{ 13,5,1,3,10,10,11,8,7,10,13,1,4,5,0,6 },{ 13,5,5,5,1,3,13,1,5,1,5,5,1,7,11,11 } };

// Cells' distance from the center
uint8_t DISTANCE[MAZE_WIDTH][MAZE_HEIGHT] = { { 14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14 },{ 13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13 },{ 12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12 },{ 11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11 },{ 10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10 },{ 9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9 },{ 8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8 },{ 7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7 },{ 7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7 },{ 8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8 },{ 9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9 },{ 10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10 },{ 11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11 },{ 12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12 },{ 13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13 },{ 14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14 } };

// Wall map that the robot has to fill
uint8_t WALL_MAP[MAZE_WIDTH][MAZE_HEIGHT] = { { 12,4,4,4,4,4,4,4,4,4,4,4,4,4,4,6 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },{ 9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3 } };

Cord * current_mouse_position;
uint8_t option_for_next_move;
uint8_t move;


int main()
{
	while (true) {
		int input;
		printf("1. View the full maze\n");
		printf("2. Go to navigation\n");
		printf("Please enter: ");
		scanf_s(" %d", &input);
		getchar();
		if (input == 1) 
			view_full_maze();
		else
			navigate();
	}
    return 0;
}

/* ---------- Maze Level ---------- */
void view_full_maze() {
	printf("+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
	for (int8_t r = MAZE_HEIGHT - 1; r >= 0; r--) {   // print row by row
		for (int8_t c = 0; c < MAZE_WIDTH; c++) {   // print cells and vertical walls
			if (has_a_west_wall(PSEUDO_MAP[r][c]))
				printf("|");
			else
				printf(" ");
			printf("   ");
		}
		printf("|\n");
		for (int8_t c = 0; c < MAZE_WIDTH; c++) {   // print posts and horizontal walls
			printf("+");
			if (has_a_south_wall(PSEUDO_MAP[r][c]))
				printf("---");
			else
				printf("   ");
		}
		printf("+\n");
	}
}
void navigate() {
	init_maze();

	while (true) {
		view_current_maze();

		printf("Press ENTER key to Continue\n");
		getchar();

		move_to_next_cell();

		mark_current_cell_as_visited();

		if (find_new_wall())
			update_maze_value();
	}
}
void init_maze() {
	// hardcord a wall between cell (0,0) and cell (0,1)
	WALL_MAP[0][0] |= V;
	WALL_MAP[0][0] |= E;
	WALL_MAP[0][1] |= W;

	// set current mouse position to (0,0)
	current_mouse_position = (Cord*)malloc(sizeof(Cord));
	current_mouse_position->row = 0;
	current_mouse_position->col = 0;
	current_mouse_position->next_cord = NULL;
}
void view_current_maze() {
	printf("+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
	for (int8_t r = MAZE_HEIGHT - 1; r >= 0; r--) {   // print row by row
		for (int8_t c = 0; c < MAZE_WIDTH; c++) {   // print cells and vertical walls
			if (has_a_west_wall(WALL_MAP[r][c]))
				printf("|");
			else
				printf(" ");
			if (mouse_is_at_cell(r, c)) {
				switch (move) {
				case N:
					printf("^");
					break;
				case W:
					printf("<");
					break;
				case S:
					printf("v");
					break;
				case E:
					printf(">");
					break;
				default:
					printf("^");
					break;
				}
			}
			else if (is_visited(WALL_MAP[r][c]))
				printf("*");
			else
				printf(" ");
			DISTANCE[r][c] >= 10 ? printf("%d", DISTANCE[r][c]) : printf("%d ", DISTANCE[r][c]);
		}
		printf("|\n");
		for (int8_t c = 0; c < MAZE_WIDTH; c++) {   // print posts and horizontal walls
			printf("+");
			if (has_a_south_wall(WALL_MAP[r][c]))
				printf("---");
			else 
				printf("   ");
		}
		printf("+\n");
	}
}
void move_to_next_cell() {

	/*
	* Go to the neighbor cell with the smallest distance
	* If more than one cell has the same smallest distance value
	* - Prefer Cell that is not yet visited
	* - if cells are all visisted or all not yet visited, prefer cell that is in the current direction
	* - (so that the robot does not have to turn)
	* - no preference otherwise
	*/

	min_open_neighbor_distance_of(current_mouse_position);		// this modifies option_for_next_move
	if (NUM_OF_OP(option_for_next_move) == 0)
		move = option_for_next_move & 0x0F;
	else {
		if ((option_for_next_move & N) && !north_cell_is_visited())
			move = N;
		else if ((option_for_next_move & W) && !west_cell_is_visited())
			move = W;
		else if ((option_for_next_move & S) && south_cell_is_visited())
			move = S;
		else if ((option_for_next_move & E) && east_cell_is_visited())
			move = E;
		else if ((option_for_next_move & N) && move == N)
			move = N;
		else if ((option_for_next_move & W) && move == W)
			move = W;
		else if ((option_for_next_move & S) && move == S)
			move = S;
		else if ((option_for_next_move & E) && move == E)
			move = E;
		else if (option_for_next_move & N)
			move = N;
		else if (option_for_next_move & W)
			move = W;
		else if (option_for_next_move & S)
			move = S;
		else if (option_for_next_move & E)
			move = E;
	}

	switch (move) {
	case N:
		current_mouse_position->row++;
		break;
	case W:
		current_mouse_position->col--;
		break;
	case S:
		current_mouse_position->row--;
		break;
	case E:
		current_mouse_position->col++;
		break;
	default:
		printf("error ????\n");
		break;
	}
}
void update_maze_value() {
	
	/*
	 * Push current cell and the cells adjacent to the new walls onto the stack	
	 * While the Stack is not empty:
	 * - current_cell <- pop the top of the Stack
	 * - the distance of current_cell should be the minimum open neigbor distance + 1
	 * - if not, set it to that value and push all open neighbors to the Stack
	 */

	Stack * cell_stack = create_stack();
	push(cell_stack, current_mouse_position->row, current_mouse_position->col);

	if (find_new_north_wall())
		push(cell_stack, current_mouse_position->row + 1, current_mouse_position->col);
	if (find_new_west_wall())
		push(cell_stack, current_mouse_position->row, current_mouse_position->col - 1);
	if (find_new_south_wall())
		push(cell_stack, current_mouse_position->row - 1, current_mouse_position->col);
	if (find_new_east_wall()) 
		push(cell_stack, current_mouse_position->row, current_mouse_position->col + 1);

	update_cell_with_wall_info();

	while (cell_stack->first != NULL) {
		Cord * current_cell = pop(cell_stack);
		if (distance_of(current_cell)!= 0 && distance_of(current_cell)!= min_open_neighbor_distance_of(current_cell) + 1) {
			set_distance_of(current_cell, min_open_neighbor_distance_of(current_cell) + 1);
			
			if (!has_a_north_wall(WALL_MAP[current_cell->row][current_cell->col]))
				push(cell_stack, current_cell->row + 1, current_cell->col);
			if (!has_a_west_wall(WALL_MAP[current_cell->row][current_cell->col]))
				push(cell_stack, current_cell->row, current_cell->col - 1);
			if (!has_a_south_wall(WALL_MAP[current_cell->row][current_cell->col]))
				push(cell_stack, current_cell->row - 1, current_cell->col);
			if (!has_an_east_wall(WALL_MAP[current_cell->row][current_cell->col]))
				push(cell_stack, current_cell->row, current_cell->col + 1);
		}
		free(current_cell);
	}
	
}

/* ---------- Stack ---------- */
Stack* create_stack() {
	Stack * stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) { "Malloc Failed\n"; return NULL; }
	stack->first = NULL;
	return stack;
}
Cord* create_cord(uint8_t row, uint8_t col) {
	Cord* c = (Cord*)malloc(sizeof(Cord));
	if (c == NULL) { "Malloc Failed\n"; return NULL; }
	c->row = row;
	c->col = col;
	c->next_cord = NULL;
	return c;
}
void push(Stack* stack, uint8_t row, uint8_t col) {
	if (stack == NULL)      // NULL stack
		stack = create_stack();
	if (stack->first == NULL)      // Empty stack
		stack->first = create_cord(row, col);
	else {
		Cord * current = stack->first;
		while (current->next_cord != NULL)
			current = current->next_cord;
		current->next_cord = create_cord(row, col);
	}
}
Cord* pop(Stack* stack) {
	Cord * return_cord = (Cord*)malloc(sizeof(Cord));
	if (stack == NULL)    //  NULL stack
		printf("Stack does not exist. Pop Failed\n");
	else if (stack->first == NULL)   // Empty stack
		printf("Stack is already empty. Pop Failed\n");
	else if (stack->first->next_cord == NULL) {       // Stack of size 1
		*return_cord = *(stack->first);
		free(stack->first); stack->first = NULL;
		return return_cord;
	}
	else {
		Cord * current = stack->first;
		while (current->next_cord->next_cord != NULL)
			current = current->next_cord;
		*return_cord = *(current->next_cord);
		free(current->next_cord); current->next_cord = NULL;
		return return_cord;
	}
}

/* ---------- Cell Level ---------- */
void update_cell_with_wall_info() {
	uint8_t row = current_mouse_position->row; 
	uint8_t col = current_mouse_position->col;
	if (find_new_north_wall()) {
		WALL_MAP[row][col] |= N;
		WALL_MAP[row + 1][col] |= S;
	}
	if (find_new_west_wall()) {
		WALL_MAP[row][col] |= W;
		WALL_MAP[row][col-1] |= E;
	}
	if (find_new_south_wall()) {
		WALL_MAP[row][col] |= S;
		WALL_MAP[row - 1][col] |= N;
	}
	if (find_new_east_wall()) {
		WALL_MAP[row][col] |= E;
		WALL_MAP[row][col + 1] |= W;
	}
}
void mark_current_cell_as_visited() {
	WALL_MAP[current_mouse_position->row][current_mouse_position->col] |= V;
}
uint8_t find_new_wall() {
	return find_new_north_wall() || find_new_west_wall() || find_new_south_wall() || find_new_east_wall();
}
uint8_t find_new_north_wall() {
	return has_a_north_wall(PSEUDO_MAP[current_mouse_position->row][current_mouse_position->col]) &&
		!has_a_north_wall(WALL_MAP[current_mouse_position->row][current_mouse_position->col]);
}
uint8_t find_new_west_wall() {
	return has_a_west_wall(PSEUDO_MAP[current_mouse_position->row][current_mouse_position->col]) &&
		!has_a_west_wall(WALL_MAP[current_mouse_position->row][current_mouse_position->col]);
}
uint8_t find_new_south_wall() {
	return has_a_south_wall(PSEUDO_MAP[current_mouse_position->row][current_mouse_position->col]) &&
		!has_a_south_wall(WALL_MAP[current_mouse_position->row][current_mouse_position->col]);
}
uint8_t find_new_east_wall() {
	return has_an_east_wall(PSEUDO_MAP[current_mouse_position->row][current_mouse_position->col]) &&
		!has_an_east_wall(WALL_MAP[current_mouse_position->row][current_mouse_position->col]);
}
uint8_t has_a_north_wall(uint8_t cell) {
	return (cell&N) != 0;
}
uint8_t has_a_west_wall(uint8_t cell) {
	return (cell&W) != 0;
}
uint8_t has_a_south_wall(uint8_t cell) {
	return (cell&S) != 0;
}
uint8_t has_an_east_wall(uint8_t cell) {
	return (cell&E) != 0;
}
uint8_t is_visited(uint8_t cell) {
	return (cell&V) != 0;
}
uint8_t north_cell_is_visited() {
	return is_visited(WALL_MAP[current_mouse_position->row + 1][current_mouse_position->col]);
}
uint8_t west_cell_is_visited() {
	return is_visited(WALL_MAP[current_mouse_position->row][current_mouse_position->col - 1]);
}
uint8_t south_cell_is_visited() {
	return is_visited(WALL_MAP[current_mouse_position->row - 1][current_mouse_position->col]);
}
uint8_t east_cell_is_visited() {
	return is_visited(WALL_MAP[current_mouse_position->row][current_mouse_position->col + 1]);
}
uint8_t mouse_is_at_cell(uint8_t row, uint8_t col) {
	return (row == current_mouse_position->row && col == current_mouse_position->col);
}
uint8_t distance_of(Cord * c) {
	return DISTANCE[c->row][c->col];
}
uint8_t min_open_neighbor_distance_of(Cord * c) {
	uint8_t current_cell = WALL_MAP[c->row][c->col];
	uint8_t min_open_neighbor_distance = 255;
	option_for_next_move = 0;
	if (!has_a_north_wall(current_cell)) {
		uint8_t north_cell_distance = DISTANCE[c->row + 1][c->col];
		if (min_open_neighbor_distance > north_cell_distance) {
			min_open_neighbor_distance = north_cell_distance;
			option_for_next_move = N;
		}
	}
	if (!has_a_west_wall(current_cell)) {
		uint8_t west_cell_distance = DISTANCE[c->row][c->col - 1];
		if (min_open_neighbor_distance > west_cell_distance) {
			min_open_neighbor_distance = west_cell_distance;
			option_for_next_move = W;
		}
		else if (min_open_neighbor_distance == west_cell_distance) {
			option_for_next_move |= W;
			option_for_next_move += 16;
		}
	}
	if (!has_a_south_wall(current_cell)) {
		uint8_t south_cell_distance = DISTANCE[c->row - 1][c->col];
		if (min_open_neighbor_distance > south_cell_distance) {
			min_open_neighbor_distance = south_cell_distance;
			option_for_next_move = S;
		}
		else if (min_open_neighbor_distance == south_cell_distance) {
			option_for_next_move |= S;
			option_for_next_move += 16;
		}
	}
	if (!has_an_east_wall(current_cell)) {
		uint8_t east_cell_distance = DISTANCE[c->row][c->col + 1];
		if (min_open_neighbor_distance > east_cell_distance) {
			min_open_neighbor_distance = east_cell_distance;
			option_for_next_move = E;
		}
		else if (min_open_neighbor_distance == east_cell_distance) {
			option_for_next_move |= E;
			option_for_next_move += 16;
		}
	}
	return min_open_neighbor_distance;
}
void set_distance_of(Cord * c, uint8_t d) {
	DISTANCE[c->row][c->col] = d;
}