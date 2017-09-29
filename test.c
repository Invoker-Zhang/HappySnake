#include "HappySnake.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	food.pos.x=2;
	food.pos.y=2;
	SnakeInit();
	FreshenScreen();
	char c;
	system("stty -icanon");
	FoodGenerate();
	while(1){
		usleep(1000*500);
		c=getchar();
		SnakeMove(c);
		FreshenScreen();
	}
	return 0;
}
