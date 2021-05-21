#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <cstdlib> 
#include <ctime> 

#include "board.h"

const int DELTA_SLEEP = 50;
const int LOG_LEFT = 80;

const int BOARD_HEIGHT = 30;
const int BOARD_WIDTH = 10;

const int ITEM_COUNT = 6;

int board_x = BOARD_WIDTH/2;
int board_y = 0;

int TemplateBox [ITEM_COUNT][5][3] = {
	{
		/*
			XXXXX
		*/
		{board_x-2, 0, 1},
		{board_x-1, 0, 1},
		{board_x, 0, 1},
		{board_x+1, 0, 1},
		{board_x+2, 0, 1},
	},
	{
		/*
			XX
			XX
		*/
		{board_x-1, 0, 1},
		{board_x, 0, 1},
		{board_x-1, 1, 1},
		{board_x, 1, 1},
		{board_x+2, 0, 0},
	},{
		/*
			X
			X
			X
			X
			X
		*/
		{board_x, 0, 1},
		{board_x, 1, 1},
		{board_x, 2, 1},
		{board_x, 3, 1},
		{board_x, 4, 1},
	},{
		/*
			XXX
			 X
		*/
		{board_x-1, 0, 1},
		{board_x , 0, 1},
		{board_x+1,0, 1},
		{board_x , 1, 1},
		{board_x+1,1, 0}
	}, {
		/*
			XXX
			  X
		*/
		{board_x-1, 0, 1},
		{board_x , 0, 1},
		{board_x+1,0, 1},
		{board_x , 1, 0},
		{board_x+1,1, 1}
	},{
		/*
			XXX
			X
		*/
		{board_x-1, 0, 1},
		{board_x , 0, 1},
		{board_x+1,0, 1},
		{board_x , 1, 0},
		{board_x-1,1, 1}
	}
};


void sleep(int millis) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void pause() {

	int key = 0;

	move(0, 0);
	printw("game paused");

	while(true) {
		key = getch();
		if(key == int(' ')) {
			break;
		}

		if(key == 27) {
			endwin();
			exit(0);
		}

	}

	move(0, 0);
	printw("           ");
}

void pickRandom(int item[5][3], int random){

	for(int i=0; i<5; i++){
		for(int j=0; j<3; j++){
			item[i][j] = TemplateBox[random][i][j];
		}
	}

}

int main() {

	initscr();
	cbreak();
	noecho();

	nodelay(stdscr, true);

	keypad(stdscr, true);
	curs_set(0);

	std::srand(static_cast<unsigned int>(std::time(nullptr))); 

	Board board = Board(BOARD_HEIGHT, BOARD_HEIGHT);

	int board_x = board.getWidth()/2;
	int board_y = board.getHeight()/2;
	int randBox = 0;

	int i = 0;
	int key = -1;
	bool canMove = true;

	int sleep_time = 0;
	int remaining = 0;
	int item[5][3];
	int random;


	while (true) {

		board.draw();
		random = std::rand()%ITEM_COUNT;
		pickRandom(item, random);

		board.addItem(item);
		canMove = true;
		key = -1;

		while(canMove) {

			while(board.clearGround()){
				sleep(500);
			}

			sleep_time = 0;
			key = getch();

			auto start = std::chrono::high_resolution_clock::now();

			while(key == -1 && sleep_time < 500){

				move(2, LOG_LEFT);
				printw("sleep time : %dms", sleep_time);

				key = getch();
				sleep_time += DELTA_SLEEP;

				sleep(DELTA_SLEEP);
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = duration_cast<std::chrono::microseconds>(end - start);

			move(1, LOG_LEFT);
			printw("key %d", key);

			move(4, LOG_LEFT);
			printw("                              ");
			move(4, LOG_LEFT);
			printw("Duration : %dms", duration.count()/1000);

			switch(key){

				case KEY_LEFT:
					board.moveLeft();
					break;
				
				case KEY_RIGHT:
					board.moveRight();
					break;

				case KEY_DOWN:
					board.drop();
					break;

				case int(' '):
					pause();
					break;

				case int('f'):
					board.fill();
					break;

				case 27:
					endwin();
					exit(0);

			}

			board.drop();
			board.draw();
			canMove = board.canMove;

			remaining = DELTA_SLEEP - duration.count()/1000;

			move(0, LOG_LEFT);
			printw("can move : %d", canMove);

			move(5, LOG_LEFT);
			printw("Remaining : %dms", remaining);

			if(remaining > 0){
				sleep(remaining);
			}

		}


	}

	endwin();
	return 0;
}


