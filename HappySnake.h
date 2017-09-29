#ifndef _HAPPYSNAKE_H_
#define _HAPPYSNAKE_H_
#define MOVEAREA_X 30
#define MOVEAREA_Y 20
#define SCREEN_X (MOVEAREA_X+2*2)
#define SCREEN_Y (MOVEAREA_Y+2*2)
typedef struct Pos{
	int x;
	int y;
}Pos;
typedef struct Food{
	Pos pos;

}Food;
Food food;

typedef struct Snake{
	Pos *pos;
	int length;
}Snake;
Snake snake;
int pixel[SCREEN_Y][SCREEN_X];
//pixel type:
#define FRAME 1 
#define BLANK 0
#define BODY 2
#define HEAD 3
#define FOOD 4


void SnakeInit();
void FoodGenerate();
int IsCrash();
int SnakeMove(char direction);
void WritePixel();
void FreshenScreen();

#endif
