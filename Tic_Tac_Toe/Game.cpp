#pragma once
#include "Header.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>


using namespace std;

HANDLE hout;

COORD c2_tmp = cmain;
COORD inf_out = {c2_tmp.X, c2_tmp.Y+13};
CONSOLE_CURSOR_INFO ci;

int game[3][3] = { 0 };
int curX = 0;
int curY = 0;
bool flag;
int winner = 0;
int turn_counter = 0;


bool turn(int i, int j) {
	COORD move[3][3] = { {{c2_tmp.X + 2,c2_tmp.Y + 2}, {c2_tmp.X + 6,c2_tmp.Y + 2}, {c2_tmp.X + 10,c2_tmp.Y + 2}}, {{c2_tmp.X + 2,c2_tmp.Y + 6}, {c2_tmp.X + 6,c2_tmp.Y + 6}, {c2_tmp.X + 10,c2_tmp.Y + 6}}, {{c2_tmp.X + 2,c2_tmp.Y + 10}, {c2_tmp.X + 6,c2_tmp.Y + 10}, {c2_tmp.X + 10,c2_tmp.Y + 10}} };
	if (game[i][j] == 0) {
		game[i][j] = 2;
		SetConsoleCursorPosition(hout, move[i][j]);
		cout << "O";
		turn_counter++;
		return 1;
	}
}


void Bot_turn(int priority)
{
	//ход в центр
	if (turn(1, 1)) {
		return;
	}

	//Перебор по столбцам и строкам
	for (int i = 0; i < 3; i++)
	{
		if ((game[0][i] == priority && game[1][i] == priority) || (game[1][i] == priority && game[2][i] == priority) || (game[0][i] == priority && game[2][i] == priority)) 
		{
			for (int j = 0; j < 3; j++) {
				if (turn(j, i)) {
					return;
				}
			}
		}
		else if ((game[i][0] == priority && game[i][1] == priority) || (game[i][1] == priority && game[i][2] == priority) || (game[i][0] == priority && game[i][2] == priority)) 
		{
			for (int j = 0; j < 3; j++) {
				if (turn(i, j)) {
					return;
				}
			}
		}
	}
	if ((game[0][0] == priority && game[1][1] == priority) || (game[1][1] == priority && game[2][2] == priority) || (game[0][0] == priority && game[2][2] == priority))
	{
		for (int j = 0; j < 3; j++)
		{
			if (turn(j, j)) {
				return;
			}
		}
	}
	//перебор двух диагоналей
	if ((game[2][0] == priority && game[1][1] == priority) || (game[1][1] == priority && game[0][2] == priority) || (game[0][2] == priority && game[2][0] == priority))
	{
		for (int j = 0; j < 3; j++)
		{
			if (turn(j, 2-j)) {
				return;
			}
		}
	}
	if (priority == 2) Bot_turn(1);
	//ход в первую пустую
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				if (turn(i, j)) {
					return;
				}
			}
	}
}

void Player_turn()
{
	int button_press;
	COORD move[3][3] = { {{c2_tmp.X+2,c2_tmp.Y+2}, {c2_tmp.X + 6,c2_tmp.Y + 2}, {c2_tmp.X + 10,c2_tmp.Y + 2}}, {{c2_tmp.X + 2,c2_tmp.Y + 6}, {c2_tmp.X + 6,c2_tmp.Y + 6}, {c2_tmp.X + 10,c2_tmp.Y + 6}}, {{c2_tmp.X + 2,c2_tmp.Y + 10}, {c2_tmp.X + 6,c2_tmp.Y + 10}, {c2_tmp.X + 10,c2_tmp.Y + 10}} };
	while (true)
	{
		SetConsoleCursorPosition(hout, move[curX][curY]);
		button_press = _getch();
		switch (button_press)
		{
		case 75:
			if (curY - 1 >= 0 && curY - 1 <= 2) curY--;
			break;
		case 77:
			if (curY + 1 >= 0 && curY + 1 <= 2) curY++;
			break;
		case 80:
			if (curX + 1 >= 0 && curX + 1 <= 2) curX++;
			break;
		case 72:
			if (curX - 1 >= 0 && curX - 1 <= 2) curX--;
			break;
		case 32:
			if (game[curX][curY] != 0)
			{
				SetConsoleCursorPosition(hout, inf_out);
				cout << "Wrong move!";
				break;
			}
			else if (mode == 1) 
			{
				if (turn_counter % 2 == 0) 
				{
					cout << "X";
					game[curX][curY] = 1;
					SetConsoleCursorPosition(hout, { (short)(c2_tmp.X),(short) (c2_tmp.Y-1) });
					cout << "Move 2 player";
				}
				else if (turn_counter % 2 != 0) 
				{
					cout << "O";
					game[curX][curY] = 2;
					SetConsoleCursorPosition(hout, { (short)(c2_tmp.X),(short)(c2_tmp.Y - 1) });
					cout << "Move 1 player";
				}
				turn_counter++;
				return;
			}
			else
			{
				cout << "X";
				game[curX][curY] = 1;
				turn_counter++;
				return;
			}
			break;
		}
	}
}

void Game(int mode_menu)
{
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	ci.dwSize = 100;
	ci.bVisible = true;
	SetConsoleCursorInfo(hout, &ci);
	

	//game clean
	curX = 0;
	curY = 0;
	turn_counter = 0;
	winner = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			game[i][j] = 0;
		}
	}


	SetConsoleCursorPosition(hout, { 35,9 });
	flag = true;
	mode = mode_menu;
	while (flag)
	{
		Player_turn();
		Check();
		if (flag == 0) break;
		if (mode == 0)
		{
			Bot_turn(2);
			Check();
		}
	}
	SetConsoleCursorPosition(hout, inf_out);
	cout << "                ";
	SetConsoleCursorPosition(hout, { 33, 6 });
	cout << "                ";
	SetConsoleCursorPosition(hout, inf_out);
	if (winner == 1) {
		if (mode == 0) cout << "Player win!";
		if (mode == 1) cout << "Player 1 win!";
	}
	else if (winner == 2) {

		if (mode == 0) cout << "Computer win!";
		if (mode == 1) cout << "Player 2 win!";
	}
	else
	{
		SetConsoleCursorPosition(hout, inf_out);
		cout << "Tie!";
	}
	ci.bVisible = false;
	SetConsoleCursorInfo(hout, &ci);
	return;
}

void Check()
{
	if (turn_counter == 9) flag = 0; return;
	for (int i = 0; i < 3; i++)
	{
		if ((game[0][i] == game[1][i] and game[0][i] == game[2][i]) and game[0][i] != 0)
		{
			if (game[0][i] == 1) winner = 1;
			else if (game[0][i] == 2) winner = 2;
			flag = 0;
			return;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if ((game[i][0] == game[i][1] && game[i][0] == game[i][2]) and game[i][0] != 0)
		{
			if (game[i][0] == 1) winner = 1;
			else if (game[i][0] == 2) winner = 2;
			flag = 0;
			return;
		}
	}
	if (game[0][0] == game[1][1] && game[0][0] == game[2][2]) //диагональ слева на право
	{
		if (game[0][0] == 1)
		{
			winner = 1;
		}
		else if (game[0][0] == 2)
		{
			winner = 2;
		}
		flag = 0;
		return;
	}
	if (game[2][0] == game[1][1] && game[1][1] == game[0][2]) //диагональ справа на лево
	{
		if (game[2][0] == 1)
		{
			winner = 1;
		}
		else if (game[2][0] == 2)
		{
			winner = 2;
		}
		flag = 0;
		return;
	}
}

