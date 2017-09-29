#include <stdio.h>
#include <time.h>
#include "HappySnake.h"
#include <stdlib.h>
#define above(a,b) ((a.x==b.x&&a.y+1==b.y)?1:0)
#define below(a,b) ((a.x==b.x&&a.y-1==b.y)?1:0)
#define left(a,b) ((a.y==b.y&&a.x+1==b.x)?1:0)
#define right(a,b) ((a.y==b.y&&a.x-1==b.x)?1:0)

void FreshenScreen(){
	system("clear");
	for(int i=0;i<SCREEN_Y;i++){
		for(int j=0;j<SCREEN_X;j++){
			switch(pixel[i][j]){
				case FRAME:
					printf("/");break;
				case BLANK:
					printf(" ");break;
				case BODY:
					printf("*");break;
				case HEAD:
					printf("#");break;
				case FOOD:
					printf("$");break;
				default:break;
			}
			fflush(stdout);
		}
		printf("\n\r");
		fflush(stdout);
	}
}

void SnakeInit(){
	{
		snake.pos=(Pos *)malloc(sizeof(Pos)*SCREEN_X*SCREEN_Y);
		if(!snake.pos)
			printf("fail to malloc int SnakeInit");
		snake.length=0;
	}
	for(int i=0;i<SCREEN_X;i++){
		pixel[0][i]=FRAME;
		pixel[1][i]=FRAME;
		pixel[SCREEN_Y-2][i]=FRAME;
		pixel[SCREEN_Y-1][i]=FRAME;
	}
	for(int i=0;i<SCREEN_Y;i++){
		pixel[i][0]=FRAME;
		pixel[i][1]=FRAME;
		pixel[i][SCREEN_X-2]=FRAME;
		pixel[i][SCREEN_X-1]=FRAME;
	}
	snake.pos[2].x=2+MOVEAREA_X/2;
	snake.pos[2].y=2+MOVEAREA_Y/2;
	snake.pos[1].x=snake.pos[2].x+1;
	snake.pos[1].y=snake.pos[2].y;
	snake.pos[0].x=snake.pos[1].x+1;
	snake.pos[0].y=snake.pos[1].y;
	snake.length=3;
	DrawSnake();
}

void DrawSnake(){
	for(int i=2;i<2+MOVEAREA_Y;i++){
		for(int j=2;j<2+MOVEAREA_X;j++)
			pixel[i][j]=BLANK;
	}
	int i=0;
	pixel[food.pos.y][food.pos.x]=FOOD;
	pixel[snake.pos[snake.length-1].y][snake.pos[snake.length-1].x]=HEAD;
	for(i=0;i<snake.length-1;i++){
		pixel[snake.pos[i].y][snake.pos[i].x]=BODY; 
	}
}

int SnakeMove(char direction){
	char origin_direction='w';
	if(snake.pos[snake.length-1].x-1==snake.pos[snake.length-2].x)
		origin_direction='d';
	else if(snake.pos[snake.length-1].x+1==snake.pos[snake.length-2].x)
		origin_direction='a';
	else if(snake.pos[snake.length-1].y-1==snake.pos[snake.length-2].y)
		origin_direction='s';
	else 
		origin_direction='w';
	switch(direction){
		case 'w':
			if(origin_direction=='s')
				direction='s';
			break;
		case 'a':
			if(origin_direction=='d')
				direction='d';
			break;
		case 's':
			if(origin_direction=='w')
				direction='w';
			break;
		case 'd':
			if(origin_direction=='a')
				direction='a';
			break;
		default:break;
	}
	switch(direction){
		case 'w':
			if(above(food.pos,snake.pos[snake.length-1])){
				snake.length++;
				snake.pos[snake.length-1]=food.pos;
				FoodGenerate();
			}
			if(snake.pos[snake.length-1].y==2||pixel[snake.pos[snake.length-1].y-1][snake.pos[snake.length-1].x]==BODY){
				printf("you failed!\n");
				return 0;
				
			}
			else {
				for(int i=0;i<snake.length-1;i++){
					snake.pos[i]=snake.pos[i+1];
				}
				snake.pos[snake.length-1].x=snake.pos[snake.length-2].x;
				snake.pos[snake.length-1].y=snake.pos[snake.length-2].y-1;
			}
			break;
		case 's':
			if(below(food.pos,snake.pos[snake.length-1])){
				snake.length++;
				snake.pos[snake.length-1]=food.pos;
				FoodGenerate();
			}
			if(snake.pos[snake.length-1].y==SCREEN_Y-3||pixel[snake.pos[snake.length-1].y+1][snake.pos[snake.length-1].x]==BODY){
				printf("you failed!\n");
				return 0;
			}
			else {
				for(int i=0;i<snake.length-1;i++){
					snake.pos[i]=snake.pos[i+1];
				}
				snake.pos[snake.length-1].x=snake.pos[snake.length-2].x;
				snake.pos[snake.length-1].y=snake.pos[snake.length-2].y+1;
			}
			break;
		case 'a':
			if(left(food.pos,snake.pos[snake.length-1])){
				snake.length++;
				snake.pos[snake.length-1]=food.pos;
				FoodGenerate();
			}
			if(snake.pos[snake.length-1].x==2||pixel[snake.pos[snake.length-1].y][snake.pos[snake.length-1].x-1]==BODY){
				printf("you failed\n");
				return 0;
			}
			else{
				for(int i=0;i<snake.length-1;i++){
					snake.pos[i]=snake.pos[i+1];
				}
				snake.pos[snake.length-1].x=snake.pos[snake.length-2].x-1;
				snake.pos[snake.length-1].y=snake.pos[snake.length-2].y;
			}
			break;
		case 'd':
			if(right(food.pos,snake.pos[snake.length-1])){
				snake.length++;
				snake.pos[snake.length-1]=food.pos;
				FoodGenerate();
			}
			if(snake.pos[snake.length-1].x==SCREEN_X-3||pixel[snake.pos[snake.length-1].y][snake.pos[snake.length-1].x+1]==BODY){
				printf("you failed");
				return 0;
			}
			else {
				for(int i=0;i<snake.length-1;i++){
					snake.pos[i]=snake.pos[i+1];
				}
				snake.pos[snake.length-1].x=snake.pos[snake.length-2].x+1;
				snake.pos[snake.length-1].y=snake.pos[snake.length-2].y;
			}
			break;
		default:break;
	}
	DrawSnake();
	return 1;
}



void FoodGenerate(){
	srand((unsigned) time(NULL));
	DrawSnake();
	int blanksize=MOVEAREA_X*MOVEAREA_Y-snake.length;
	int foodindex=rand()%blanksize;
	int a=0;
	for(int i=2;i<2+MOVEAREA_Y;i++){
		for(int j=2;j<2+MOVEAREA_X;j++){
			if(pixel[i][j]!=HEAD&&pixel[i][j]!=BODY){
				if(a==foodindex){
					food.pos.x=j;
					food.pos.y=i;
					pixel[i][j]=FOOD;
					return;
				}
				a++;
			}
		}
	}
}






























