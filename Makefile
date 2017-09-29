test:test.c HappySnake.c HappySnake.h
	gcc -o test test.c HappySnake.c -g -lpthread
.PHONY: clean
clean:
	rm test
