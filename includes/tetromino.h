#ifndef TETROMINO_H
#define TETROMINO_H

typedef struct {
    char **array;
    int width, row, col;
} Tetromino;

Tetromino current;

const Tetromino StructsArray[7] = {
    // Z-shaped block
    {
        (char *[]){
            (char []){0, 1, 1},
            (char []){1, 1, 0},
            (char []){0, 0, 0}
        }, 3, 3, 3
    },
    // Reverse Z-shaped block
    {
        (char *[]){
            (char []){1, 1, 0},
            (char []){0, 1, 1},
            (char []){0, 0, 0}
        }, 3, 3, 3
    },
    // T-shaped block
    {
        (char *[]){
            (char []){0, 1, 0},
            (char []){1, 1, 1},
            (char []){0, 0, 0}
        }, 3, 3, 3
    },
    // Reverse L-shaped block
    {
        (char *[]){
            (char []){0, 0, 1},
            (char []){1, 1, 1},
            (char []){0, 0, 0}
        }, 3, 3, 3
    },
    // L-shaped block
    {
        (char *[]){
            (char []){1, 0, 0},
            (char []){1, 1, 1},
            (char []){0, 0, 0}
        }, 3, 3, 3
    },
    // Square block
    {
        (char *[]){
            (char []){1, 1},
            (char []){1, 1}
        }, 2, 2, 3
    },
    // Line block
    {
        (char *[]){
            (char []){0, 0, 0, 0},
            (char []){1, 1, 1, 1},
            (char []){0, 0, 0, 0},
            (char []){0, 0, 0, 0}
        }, 4, 4, 4
    }
};

#endif // TETROMINO_H
