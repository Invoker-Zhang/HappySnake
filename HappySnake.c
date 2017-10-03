#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "HappySnake.h"

#define above(a,b) ((a.x==b.x&&a.y+1==b.y)?1:0)
#define below(a,b) ((a.x==b.x&&a.y-1==b.y)?1:0)
#define left(a,b) ((a.y==b.y&&a.x+1==b.x)?1:0)
#define right(a,b) ((a.y==b.y&&a.x-1==b.x)?1:0)
#define IsOpsite(a,b) (((a=='w'&&b=='s')||(a=='a'&&b=='d')||(a=='s'&&b=='w'||a=='d'&&b=='a'))?1:0)
#define snakehead (snake.pos[snake.length-1])


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
	WritePixel();
}

void WritePixel(){
	for(int i=2;i<2+MOVEAREA_Y;i++){
		for(int j=2;j<2+MOVEAREA_X;j++)
			pixel[i][j]=BLANK;
	}
	int i=0;
	pixel[food.pos.y][food.pos.x]=FOOD;
	pixel[snakehead.y][snakehead.x]=HEAD;
	for(i=0;i<snake.length-1;i++){
		pixel[snake.pos[i].y][snake.pos[i].x]=BODY; 
	}
}
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

int SnakeMove(char direction){
	char origin_direction='w';
	if(snakehead.x-1==snake.pos[snake.length-2].x)
		origin_direction='d';
	else if(snakehead.x+1==snake.pos[snake.length-2].x)
		origin_direction='a';
	else if(snakehead.y-1==snake.pos[snake.length-2].y)
		origin_direction='s';
	else 
		origin_direction='w';
	if(IsOpsite(origin_direction,direction)){
		direction=origin_direction;
	}
	Pos newhead=snakehead;
	switch(direction){
		case 'w':
			newhead.y=snakehead.y-1;
			break;
		case 'a':
			newhead.x=snakehead.x-1;
			break;
		case 's':
			newhead.y=snakehead.y+1;
			break;
		case 'd':
			newhead.x=snakehead.x+1;
			break;
		default:break;
	}
	if(IsCrash(newhead))
		return 0;
	if(newhead.x==food.pos.x&&newhead.y==food.pos.y){
		snake.length++;
		snakehead=food.pos;
		FoodGenerate();
	}
	else{
		for(int i=0;i<snake.length-1;i++){
			snake.pos[i]=snake.pos[i+1];
		}
		snakehead=newhead;
	}
	WritePixel();
	return 1;
}



void FoodGenerate(){
	srand((unsigned) time(NULL));
	WritePixel();
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

int IsCrash(Pos newhead){
	if(pixel[newhead.y][newhead.x]==BODY)
		return 1;
	if(pixel[newhead.y][newhead.x]==FRAME)
		return 1;
	return 0;
}




























