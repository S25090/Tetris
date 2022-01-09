#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include "PressedKey.h"
#include "Rotation.h"

typedef char block_t[4][4];
const int GAME_FIELD_HEIGHT = 18;
const int GAME_FIELD_WIDTH = 12;
const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 30;
const int LEFT_ARROW = 0x25;
const int RIGHT_ARROW = 0x27;
const int DOWN_ARROW = 0x28;

typedef char block_t[4][4];


class Game
{
private:
	char gameField[GAME_FIELD_WIDTH][GAME_FIELD_HEIGHT];
	wchar_t* screen = new wchar_t[SCREEN_WIDTH * SCREEN_HEIGHT];
	Rotation rotation;
	block_t blocks[7];
	void drawBlockInGameField(int blockPosX, int blockPosY, block_t block, int angle);
	void drawBlock(int blockPosX, int blockPosY, block_t block, int angle);
	bool canMoveBlock(int blockPosX, int blockPosY, block_t block, int angle);
	PressedKey getKeyPressed();
	void cleanScreen();
	void drawGameField();
	void drawBorder();

public:
	void play();
	Game();

};

#endif