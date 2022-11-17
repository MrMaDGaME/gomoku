#pragma once

#include <stddef.h>

typedef struct dimension {
    int columns;
    int lines;
} t_dim;

typedef struct vector {
    int x;
    int y;
    int i;
} t_vec;

typedef struct point {
    int col;
    int row;
} t_point;
