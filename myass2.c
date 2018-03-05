/* COMP20005 Engineering Computation
 * Assignment 2
 * Student Name: 	Chi-Jen Lee
 * Student ID:   	685769 
 * Note: This program assumes all input files will be correct.
 * Programming is fun!
 */

/* include the necessary libraries */
#include <stdio.h>
#include <stdlib.h>

/* define necessary constants */
#define NO_GO_CELL		0
#define PASSABLE_CELL	1

#define NO_REACH		0
#define YES_REACH		1

#define MAX_ROW 		100
#define MAX_COLUMN		100
#define MAX_COST		MAX_ROW*MAX_COLUMN

#define NOT_CHECKED		0
#define YES_CHECKED		1

#define NOT_ON_PATH		0
#define YES_ON_PATH		1

/* define the struct needed */
typedef struct {
	int state;
	int reachability;
	int cost;
	int check;
	int on_path;
} cell;

typedef struct {
	cell grid[MAX_ROW][MAX_COLUMN];
	int n_row;
	int n_column;

	int hassoln;
	int soln_cost;
} maze_t;

/* function prototypes */
void read_maze(maze_t *maze);
void print_stage_one(maze_t *maze);
void assign_reachability(maze_t *maze);
void recursive_assign(maze_t *maze, int row, int column);
void print_stage_two(maze_t *maze);
void recursive_cost(maze_t *maze, int row, int column, int cost);
void print_stage_three(maze_t *maze);
void label_final_path(maze_t *maze);
void print_stage_four(maze_t *maze);

/* the main program that holds everything together */
int
main(int argc, char **argv) {
	maze_t M;	/* the maze */

	read_maze(&M);
	print_stage_one(&M);

	assign_reachability(&M);
	print_stage_two(&M);
	print_stage_three(&M);

	if (M.hassoln) {
		label_final_path(&M);
		print_stage_four(&M);
	}

	return 0;
}

/* reads the maze from user input, such as a text file */
void read_maze(maze_t *maze) {
	int next;
	int row=0;
	int column=0;

	maze->n_row = 0;
	maze->n_column = 0;

	/* use an inner loop and outer loop structure to 
	loop through the text file */
	while ((next = getchar()) != EOF) {
			if (next == '#') {
				maze->grid[row][column].state = NO_GO_CELL;
				column++;
			} else if (next == '.') {
				maze->grid[row][column].state = PASSABLE_CELL;
				column++;
			}
		while ((next = getchar()) != '\n') {
			if (next == '#') {
				maze->grid[row][column].state = NO_GO_CELL;
				column++;
			} else if (next == '.') {
				maze->grid[row][column].state = PASSABLE_CELL;
				column++;
			}
		}
		row++;
		maze->n_row++;
		maze->n_column=column;
		column=0;
	}
}

/* prints the output required for stage one */
void print_stage_one(maze_t *maze) {
	int row;
	int column;

	printf("Stage 1\n");
	printf("=======\n");
	printf("maze has %d rows and %d columns\n", 
		maze->n_row, maze->n_column);

	for (row=0; row<maze->n_row; row++) {
		for (column=0; column<maze->n_column; column++) {
			if (maze->grid[row][column].state==NO_GO_CELL) {
				printf("##");
			} else if (maze->grid[row][column].state==PASSABLE_CELL) {
				printf("..");
			}
		}
		printf("\n");
	}
	printf("\n");
}

/* checks if cells can be reached or not */
void assign_reachability(maze_t *maze) {
	int row=0;
	int column=0;

	/* before assign starts, set all the cell to NOT_CHECKED and 
	NO_REACH and MAX_COST and NOT_ON_PATH.

	these for loops basically conducts all the initialisations 
	required */
	maze->soln_cost = MAX_COST;
	for (row=0; row<maze->n_row; row++) {
		for (column=0; column<maze->n_column; column++) {
			maze->grid[row][column].check = NOT_CHECKED;
			maze->grid[row][column].reachability = NO_REACH;
			maze->grid[row][column].cost = MAX_COST;
			maze->grid[row][column].on_path = NOT_ON_PATH;
		}
	}

	/* check reachability */
	/* check the first row first */
	row = 0;
	for (column=0; column<maze->n_column; column++) {
		if (maze->grid[row][column].state==PASSABLE_CELL) {
			maze->grid[row][column].reachability = YES_REACH;
			/* use recursive_assign function to check if cells
			are reachable */
			recursive_assign(maze, row, column);
			recursive_cost(maze, row, column, -1);
		}
	}

	/* check if there is solution */
	row = maze->n_row-1;
	maze->hassoln = 0;
	for(column=0; column<maze->n_column; column++) {
		if (maze->grid[row][column].reachability == YES_REACH) {
			maze->hassoln = 1;
			if (maze->soln_cost > maze->grid[row][column].cost) {
				maze->soln_cost = maze->grid[row][column].cost;
			}
		}
	}
}

/* recursive function used to assign reachability */
void recursive_assign(maze_t *maze, int row, int column) {

	/* first label the current cell as checked */
	maze->grid[row][column].check = YES_CHECKED;
	/* change reachability to YES_REACH */
	maze->grid[row][column].reachability = YES_REACH;

	/* then depending on the locaiton, check surrounding cells,
	if all surrounding cells are checked, then do nothing */

	/* check up cannot occur when your are at the first row */
	if (row != 0) {
		if (maze->grid[row-1][column].state == PASSABLE_CELL &&
			maze->grid[row-1][column].check == NOT_CHECKED) {
			recursive_assign(maze, row-1, column);
		}
	}

	/* check down cannot occur when you are at the last row */
	if (row != maze->n_row-1) {
		if (maze->grid[row+1][column].state == PASSABLE_CELL &&
			maze->grid[row+1][column].check == NOT_CHECKED) {
			recursive_assign(maze, row+1, column);
		}	
	}

	/* check left cannot occur when you are at the first column */
	if (column != 0) {
		if (maze->grid[row][column-1].state == PASSABLE_CELL &&
			maze->grid[row][column-1].check == NOT_CHECKED) {
			recursive_assign(maze, row, column-1);
		}	
	}

	/* check right cannot occur when you are at the last column */
	if (row != maze->n_column-1) {
		if (maze->grid[row][column+1].state == PASSABLE_CELL &&
			maze->grid[row][column+1].check == NOT_CHECKED) {
			recursive_assign(maze, row, column+1);
		}
	}

}

/* recursive function used to calculate the cost for each cell */
void recursive_cost(maze_t *maze, int row, int column, int cost) {
	int cell_cost;

	cell_cost = cost + 1;

	maze->grid[row][column].cost = cell_cost;

	/* initially at the origin with 0 cost */

	/* assign costs to surrounding cells */
		/* first check if surrounding cells cost is lower */
		/* if surrounding cell cost is lower than cost + 1,
		then do nothing */
		/* else assign the corresponding cost */

	/* call the recursive function on surrounding cell if assigning
	process occured, allowing the recursion to cascade through the 
	maze */

	/* similar to not checked and yes checked, this time instead 
	of check, we have comparison of cost, and if the cost comparison
	is passed the the recursive function is called */

	/* check up cannot occur when your are at the first row */
	if (row != 0) {
		if (maze->grid[row-1][column].state == PASSABLE_CELL &&
			maze->grid[row-1][column].cost >
			maze->grid[row][column].cost) {
			recursive_cost(maze, row-1, column,
				maze->grid[row][column].cost);
		}
	}

	/* check down cannot occur when you are at the last row */
	if (row != maze->n_row-1) {
		if (maze->grid[row+1][column].state == PASSABLE_CELL &&
			maze->grid[row+1][column].cost >
			maze->grid[row][column].cost) {
			recursive_cost(maze, row+1, column,
				maze->grid[row][column].cost);
		}
	}

	/* check left cannot occur when you are at the first column */
	if (column != 0) {
		if (maze->grid[row][column-1].state == PASSABLE_CELL &&
			maze->grid[row][column-1].cost >
			maze->grid[row][column].cost) {
			recursive_cost(maze, row, column-1,
				maze->grid[row][column].cost);
		}
	}

	/* check right cannot occur when you are at the last column */
	if (column != maze->n_column-1) {
		if (maze->grid[row][column+1].state == PASSABLE_CELL &&
			maze->grid[row][column+1].cost >
			maze->grid[row][column].cost) {
			recursive_cost(maze, row, column+1,
				maze->grid[row][column].cost);
		}
	}

}

/* function to print the required output for stage 2 */
void print_stage_two(maze_t *maze) {
	int row;
	int column;

	printf("Stage 2\n");
	printf("=======\n");
	if (maze->hassoln == 1) {
		printf("maze has a solution\n");
	} else {
		printf("maze does not have a solution\n");
	}

	for (row=0; row<maze->n_row; row++) {
		for (column=0; column<maze->n_column; column++) {
			if (maze->grid[row][column].state==NO_GO_CELL) {
				printf("##");
			} else if (maze->grid[row][column].state==PASSABLE_CELL) {
				if (maze->grid[row][column].reachability==YES_REACH) {
					printf("++");
				} else {
					printf("--");
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}

/* function to print the required output for stage 3 */
void print_stage_three(maze_t *maze) {
	int row;
	int column;

	printf("Stage 3\n");
	printf("=======\n");

	if (maze->hassoln == 1) {
		printf("maze has a solution with cost %d\n",maze->soln_cost);
	} else {
		printf("maze does not have a solution\n");
	}

	for (row=0; row<maze->n_row; row++) {
		for (column=0; column<maze->n_column; column++) {
			if (maze->grid[row][column].state==NO_GO_CELL) {
				printf("##");
			} else if (maze->grid[row][column].state==PASSABLE_CELL) {
				if (maze->grid[row][column].reachability==YES_REACH) {
					if ((maze->grid[row][column].cost%2)==0){
						printf("%02d",maze->grid[row][column].cost%100);
					} else {
						printf("++");
					}
				} else {
					printf("--");
				}
			}
		}
		printf("\n");
	}
	printf("\n");

}

/* function to label the solution path */
void label_final_path(maze_t *maze) {
	int row=0;
	int column=0;
	int exit_row=0;
	int exit_column=0;

	/* start from the very bottome of the maze */
	row = maze->n_row-1;
	for (column = 0; column<maze->n_column; column++) {
		if (maze->grid[row][column].cost == maze->soln_cost) {
			maze->grid[row][column].on_path = YES_ON_PATH;
			exit_row = row;
			exit_column = column;
			break;
		}
	}

	row = exit_row;
	column = exit_column;

	/* now start tracing all the way to the top */
	while (maze->grid[row][column].cost != 0) {
		/* check up cannot occur when you are at the first row */
		if (row != 0) {
			if (maze->grid[row-1][column].state == PASSABLE_CELL &&
				maze->grid[row-1][column].cost ==
				(maze->grid[row][column].cost-1) ) {
				maze->grid[row-1][column].on_path = YES_ON_PATH;
				row--;
				continue;
			}
		}

		if (row != maze->n_row-1) {
			if (maze->grid[row+1][column].state == PASSABLE_CELL &&
				maze->grid[row+1][column].cost ==
				(maze->grid[row][column].cost-1) ) {
				maze->grid[row+1][column].on_path = YES_ON_PATH;
				row++;
				continue;
			}
		}

		if (column != 0) {
			if (maze->grid[row][column-1].state == PASSABLE_CELL &&
				maze->grid[row][column-1].cost ==
				(maze->grid[row][column].cost-1) ) {
				maze->grid[row][column-1].on_path = YES_ON_PATH;
				column--;
				continue;
			}
		}

		if (column != maze->n_column-1) {
			if (maze->grid[row][column+1].state == PASSABLE_CELL &&
				maze->grid[row][column+1].cost ==
				(maze->grid[row][column].cost-1) ) {
				maze->grid[row][column+1].on_path = YES_ON_PATH;
				column++;
				continue;
			}
		}
	}
}

/* function to print the required output for stage 4 */
void print_stage_four(maze_t *maze) {
	int row;
	int column;

	printf("Stage 4\n");
	printf("=======\n");
	printf("maze solution\n");

	for (row=0; row<maze->n_row; row++) {
		for (column=0; column<maze->n_column; column++) {
			if (maze->grid[row][column].state==NO_GO_CELL) {
				printf("##");
			} else if (maze->grid[row][column].state==PASSABLE_CELL) {
				if (maze->grid[row][column].reachability==YES_REACH) {
					if (maze->grid[row][column].on_path == YES_ON_PATH) {
						if ((maze->grid[row][column].cost%2)==0){
							printf("%02d",maze->grid[row][column].cost%100);
						} else {
							printf("..");
						}
					} else {
						printf("  ");
					}
				} else {
					printf("--");
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}