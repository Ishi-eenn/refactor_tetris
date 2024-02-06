#include "tetris.h"

char Table[FIELD_ROW][FIELD_COL] = {0};
int final = 0;
char GameOn = true;

t_time time111 = {.timer = 400000, .decrease = 1000};

typedef struct {
	char **array;
	int width, row, col;
} Struct;
Struct current;

const Struct StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

void print_game_field(){
	for(int i = 0; i < FIELD_ROW; i++){
		for(int j = 0; j < FIELD_COL; j++){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
}

void displayGameOver() {
	print_game_field();
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
}

Struct FunctionCS(Struct shape){
	Struct new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
	 for(int i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(int j = 0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
	}
	return new_shape;
}

void freeShapeArray(Struct shape){
	for(int i = 0; i < shape.width; i++){
		free(shape.array[i]);
	}
	free(shape.array);
}

int FunctionCP(Struct shape){
	char **array = shape.array;
	for(int i = 0; i < shape.width;i++) {
		for(int j = 0; j < shape.width; j++){
			if((shape.col + j < 0 || shape.col + j >= FIELD_COL || shape.row + i >= FIELD_ROW)){
				if(array[i][j])
					return false;

			}
			else if(Table[shape.row + i][shape.col + j] && array[i][j])
				return false;
		}
	}
	return true;
}

void FunctionRS(Struct shape){
	Struct temp = FunctionCS(shape);
	for(int i = 0, width = shape.width; i < width ; i++){
		for(int j = 0, k = width - 1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	freeShapeArray(temp);
}

void FunctionPT(){
	char Buffer[FIELD_ROW][FIELD_COL] = {0};
	for(int i = 0; i < current.width; i++){
		for(int j = 0; j < current.width; j++){
			if(current.array[i][j])
				Buffer[current.row + i][current.col + j] = current.array[i][j];
		}
	}
	clear();
	for(int i = 0; i < FIELD_COL - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(int i = 0; i < FIELD_ROW; i++){
		for(int j = 0; j < FIELD_COL; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}

struct timeval before_now, now;
int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) - ((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > time111.timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}

void title() {
	for(int i = 0; i < current.width ;i++){
		for(int j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Table[current.row + i][current.col + j] = current.array[i][j];
		}
	}
}

void clearCompletedRow(int row);
void generateNewShape();

void handleFailedMove() {
	title();
	int sum, count = 0;

	for (int n = 0; n < FIELD_ROW; n++) {
		sum = 0;

		for (int m = 0; m < FIELD_COL; m++) {
			sum += Table[n][m];
		}

		if (sum == FIELD_COL) {
			count++;
			clearCompletedRow(n);
			time111.timer -= time111.decrease--;
		}
	}

	final += 100 * count;
	generateNewShape();
	if (!FunctionCP(current)) {
		GameOn = false;
	}
}

void clearCompletedRow(int row) {
	int k;
	for (k = row; k >= 1; k--) {
		for (int l = 0; l < FIELD_COL; l++) {
			Table[k][l] = Table[k - 1][l];
		}
	}

	for (int l = 0; l < FIELD_COL; l++) {
		Table[k][l] = 0;
	}
}

void generateNewShape() {
	Struct new_shape = FunctionCS(StructsArray[rand() % 7]);
	new_shape.col = rand() % (FIELD_COL - new_shape.width + 1);
	new_shape.row = 0;
	freeShapeArray(current);
	current = new_shape;
}

int main() {
	srand(time(0));
	final = 0;
	int c;
	initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	Struct new_shape = FunctionCS(StructsArray[rand()%7]);
	new_shape.col = rand()%(FIELD_COL-new_shape.width+1);
	new_shape.row = 0;
	freeShapeArray(current);
	current = new_shape;
	if(!FunctionCP(current)){
		GameOn = false;
	}
	FunctionPT();
	while(GameOn){
		if ((c = getch()) != ERR) {
			Struct temp = FunctionCS(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(FunctionCP(temp))
						current.row++;
					else {
						title();
						int sum, count=0;
						for(int n=0;n<FIELD_ROW;n++){
							sum = 0;
							for(int m=0;m< FIELD_COL;m++) {
								sum+=Table[n][m];
							}
							if(sum==FIELD_COL){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<FIELD_COL;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<FIELD_COL;l++)
									Table[k][l]=0;
								time111.timer-=time111.decrease--;
							}
						}
						final += 100*count;
						Struct new_shape = FunctionCS(StructsArray[rand()%7]);
						new_shape.col = rand()%(FIELD_COL-new_shape.width+1);
						new_shape.row = 0;
						freeShapeArray(current);
						current = new_shape;
						if(!FunctionCP(current)){
							GameOn = false;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCP(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCP(temp))
						current.col--;
					break;
				case 'w':
					FunctionRS(temp);
					if(FunctionCP(temp))
						FunctionRS(current);
					break;
			}
			freeShapeArray(temp);
			FunctionPT();
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			Struct temp = FunctionCS(current);
			temp.row++;
			if (FunctionCP(temp))
				current.row++;
			else
				handleFailedMove();
			freeShapeArray(temp);
			FunctionPT();
			gettimeofday(&before_now, NULL);
		}
	}
	freeShapeArray(current);
	endwin();
	displayGameOver();
 return 0;
}
