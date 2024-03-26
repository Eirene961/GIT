#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;


bool gameOver = false;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;

enum Direction
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

Direction dir;

void Setup()
{
	srand(time(NULL));
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");

	for (int i = -1; i <= height; i++)
	{
		for (int j = -1; j <= width; j++) {
			if (i == -1 || i == height || j == -1 || j == width)
				cout << "#";
			else if (i == y && j == x)
				cout << "O";
			else if (j == fruitX && i == fruitY)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
		case 'A':
			dir = LEFT;
			break;
		case 'd':
		case 'D':
			dir = RIGHT;
			break;
		case 'w':
		case 'W':
			dir = UP;
			break;
		case 's':
		case 'S':
			dir = DOWN;
			break;
		case 'x':
		case 'X':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0], prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (x < -1 || x > width || y < -1 || y > height)
		gameOver = true;
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}


int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10);
	}

	return 0;
}