#include "HappySnake.h"
#include <pthread.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int kbhit();
char input='a';
void ReadKey(){
	system("stty raw -echo");
	while(1){
		if(kbhit()){
			input=getchar();
			fflush(stdout);
		}
	}
}
int main(){
	/*
	pthread_t t;
	if(pthread_create(&t,NULL,ReadKey,NULL)){
		printf("fail to creat pthread");
		return 0;
	}
	while(1){
		usleep(1000*1000);
		printf("%c",input);
		fflush(stdout);
		if(input=='q')
			break;
	}
	system("stty cooked echo");
	return 0;
	*/
	pthread_t t;
	if(pthread_create(&t,NULL,ReadKey,NULL)){
		printf("fail to creat pthread");
		return 0;
	}

	food.pos.x=2;
	food.pos.y=2;
	SnakeInit();
	FreshenScreen();
	FoodGenerate();
	while(1){
		usleep(1000*500);
		if(!SnakeMove(input))
			return 0;
		FreshenScreen();
	}
	return 0;
}
int kbhit(){
	int i;
	ioctl(0,FIONREAD,&i);
	return i;
}
