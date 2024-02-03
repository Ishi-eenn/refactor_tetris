#ifndef TETRIS_H
 # define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

#define FIELD_ROW 20
#define FIELD_COL 15

typedef struct {
	suseconds_t	timer;
	int			decrease;
} t_time;

#endif
