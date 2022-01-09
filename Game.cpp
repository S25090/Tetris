#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include "Point.h"
#include "Rotation.h"
#include "PressedKey.h"

using namespace std::chrono_literals;

Game::Game() : blocks{
	{
		{' ',' ',' ',' '},
		{' ',' ',' ',' '},
		{'A','A','A','A'},
		{' ',' ',' ',' '}
	},
	{
		{' ',' ',' ',' '},
		{' ',' ','B',' '},
		{'B','B','B',' '},
		{' ',' ',' ',' '}
	},
	{
		{' ',' ',' ',' '},
		{'G','G','G',' '},
		{' ',' ','G',' '},
		{' ',' ',' ',' '}
	},
	{
		{' ',' ','C','C'},
		{' ',' ','C','C'},
		{' ',' ',' ',' '},
		{' ',' ',' ',' '}
	},
	{
		{' ','D',' ',' '},
		{' ','D','D',' '},
		{' ',' ','D',' '},
		{' ',' ',' ',' '}
	},
	{
		{' ',' ','F',' '},
		{' ','F','F',' '},
		{' ','F',' ',' '},
		{' ',' ',' ',' '}
	},
	{
		{' ',' ',' ',' '},
		{'E','E','E',' '},
		{' ','E',' ',' '},
		{' ',' ',' ',' '}
	},
}
{
	rotation = Rotation();
}

void Game::play()
{
	drawGameField();
	drawBorder();

	cleanScreen();

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;


	int blockPosX = GAME_FIELD_WIDTH / 2;
	int blockPosY = 0;
	int angle = 0;
	bool isRotationAvailable = false;
	int currentBlockIndex = 5;

	while (true)
	{
		std::this_thread::sleep_for(50ms);
		PressedKey klawisz = getKeyPressed();


		if (klawisz == PressedKey::R_KEY)
		{
			if (isRotationAvailable)
			{
				int newAngle = angle + 90;
				if (newAngle >= 360)
				{
					newAngle = 0;
				}

				if (canMoveBlock(blockPosX, blockPosY, blocks[currentBlockIndex], newAngle))
				{
					angle = newAngle;
				}


			}
			isRotationAvailable = false;
		}
		else
		{
			isRotationAvailable = true;
		}

		switch (klawisz)
		{
		case PressedKey::LEFT_ARROW:
			if (canMoveBlock(blockPosX - 1, blockPosY, blocks[currentBlockIndex], angle))
			{
				--blockPosX;
			}
			break;
		case PressedKey::RIGHT_ARROW:
			if (canMoveBlock(blockPosX + 1, blockPosY, blocks[currentBlockIndex], angle))
			{
				++blockPosX;
			}
			break;
		case PressedKey::DOWN_ARROW:
			if (canMoveBlock(blockPosX, blockPosY + 1, blocks[currentBlockIndex], angle))
			{
				++blockPosY;
			}
			break;
		}

		drawGameField();

		drawBlock(blockPosX, blockPosY, blocks[currentBlockIndex], angle);

		drawBlockInGameField(4, 10, blocks[0], angle);
		drawBlockInGameField(6, 14, blocks[2], angle);
		WriteConsoleOutputCharacter(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, { 0,0 }, &dwBytesWritten);
	}
}


void Game::drawBorder()
{
	for (int y = 0; y < GAME_FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < GAME_FIELD_WIDTH; x++)
		{
			if ((x == 0 || x == GAME_FIELD_WIDTH - 1 || y == GAME_FIELD_HEIGHT - 1))
			{
				gameField[x][y] = '#';
			}
			else
			{
				gameField[x][y] = ' ';
			}

		}
	}
}



bool Game::canMoveBlock(int blockPosX, int blockPosY, block_t block, int angle)
{
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			Point point = rotation.rotate(Point(x, y), angle);
			if (block[point.getY()][point.getX()] != ' ')
			{
				if (gameField[blockPosX + x][blockPosY + y] != ' ')
				{
					return false;
				}
			}
		}
	}
	return true;
}


void Game::drawBlock(int blockPosX, int blockPosY, block_t block, int angle)
{
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			Point point = rotation.rotate(Point(x, y), angle);
			if (block[point.getY()][point.getX()] != ' ')
			{
				screen[(blockPosY + y + 2) * SCREEN_WIDTH + (blockPosX + x + 2)] = block[point.getY()][point.getX()];
			}
		}
		std::cout << std::endl;
	}
}


void Game::drawBlockInGameField(int blockPosX, int blockPosY, block_t block, int angle)
{
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			Point point = rotation.rotate(Point(x, y), angle);
			if (block[point.getX()][point.getY()] != ' ')
			{
				gameField[blockPosX + point.getX()][blockPosY + point.getY()] = block[point.getX()][point.getY()];
			}
		}
		std::cout << std::endl;
	}
}

PressedKey Game::getKeyPressed()
{
	if ((0x8000 & GetAsyncKeyState(LEFT_ARROW)) != 0)
	{
		return PressedKey::LEFT_ARROW;
	}
	else if ((0x8000 & GetAsyncKeyState(RIGHT_ARROW)) != 0)
	{
		return PressedKey::RIGHT_ARROW;
	}
	else if ((0x8000 & GetAsyncKeyState(DOWN_ARROW)) != 0)
	{
		return PressedKey::DOWN_ARROW;
	}
	else if ((0x8000 & GetAsyncKeyState('R')) != 0)
	{
		return PressedKey::R_KEY;
	}
	else
	{
		return PressedKey::OTHER;
	}
}

void Game::cleanScreen()
{
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		screen[i] = ' ';
	}
}


void Game::drawGameField()
{
	for (int y = 0; y < GAME_FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < GAME_FIELD_WIDTH; x++)
		{
			screen[(y + 2) * SCREEN_WIDTH + (x + 2)] = gameField[x][y];
		}
	}
}


