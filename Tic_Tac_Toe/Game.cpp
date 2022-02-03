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
bool is_game_finish;
int winner = 0;
int turn_counter = 0;


void turn(int i, int j) {
	COORD move[3][3] = { {{c2_tmp.X + 2,c2_tmp.Y + 2}, {c2_tmp.X + 6,c2_tmp.Y + 2}, {c2_tmp.X + 10,c2_tmp.Y + 2}}, {{c2_tmp.X + 2,c2_tmp.Y + 6}, {c2_tmp.X + 6,c2_tmp.Y + 6}, {c2_tmp.X + 10,c2_tmp.Y + 6}}, {{c2_tmp.X + 2,c2_tmp.Y + 10}, {c2_tmp.X + 6,c2_tmp.Y + 10}, {c2_tmp.X + 10,c2_tmp.Y + 10}} };
	game[i][j] = 2;
	SetConsoleCursorPosition(hout, move[i][j]);
	cout << "O";
	turn_counter++;
	return;
}


void Bot_turn(int priority)
{
	//ход в центр
	if (game[1][1] == 0) {
		turn(1, 1);
		return;
	}

	//Перебор по столбцам и строкам
	for (int i = 0; i < 3; i++)
	{
		if ((game[0][i] == priority && game[1][i] == priority) || (game[1][i] == priority && game[2][i] == priority) || (game[0][i] == priority && game[2][i] == priority)) {
			for (int j = 0; j < 3; j++)
			{
				if (game[j][i] == 0)
				{
					turn(j, i);
					return;
				}
			}
		}
		if ((game[i][0] == priority && game[i][1] == priority) || (game[i][1] == priority && game[i][2] == priority) || (game[i][0] == priority && game[i][2] == priority))
		{
			for (int j = 0; j < 3; j++)
			{
				if (game[i][j] == 0)
				{
					turn(i, j);
					return;
				}
			}
		}
	}
	//перебор двух диагоналей
	if ((game[0][0] == priority && game[1][1] == priority) || (game[1][1] == priority && game[2][2] == priority) || (game[0][0] == priority && game[2][2] == priority))
	{
		for (int i = 0; i < 3; i++)
		{
			if (game[i][i] == 0) {
				turn(i, i);
				return;
			}
		}
	}
	if ((game[2][0] == priority && game[1][1] == priority) || (game[1][1] == priority && game[0][2] == priority) || (game[0][2] == priority && game[2][0] == priority))
	{
		for (int i = 0; i < 3; i++)
		{
			if (game[i][2-i] == 0) {
				turn(i, 2-i);
				return;
			}
		}
	}
	if (priority == 2) Bot_turn(1);
	//ход в первую пустую
	else
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
			{
				if (game[i][j] == 0) {
					turn(i, j);
					return;
				}
			}
		}
	}
}

void Player_turn(int mode)
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
	is_game_finish = true;
	while (is_game_finish)
	{
		Player_turn(mode_menu);
		Check();
		if (is_game_finish == 0) break;
		if (mode_menu == 2)
		{
			Bot_turn(2);
			Check();
		}
	}
	SetConsoleCursorPosition(hout, inf_out);
	cout << "                ";
	SetConsoleCursorPosition(hout, inf_out);
	ci.bVisible = false;
	SetConsoleCursorInfo(hout, &ci);
	if (winner == 1) {
		if (mode_menu == 1) { cout << "Player 1 win!"; _getch(); }
		if (mode_menu == 2) {cout << "Player win!"; _getch();}
	}
	else if (winner == 2) {
		if (mode_menu == 1) { cout << "Player 2 win!"; _getch(); }
		if (mode_menu == 2) { cout << "Computer win!"; _getch();}
	}
	else
	{
		cout << "Tie!";
		_getch();
	}

	return;
}

void Check()
{
	for (int i = 0; i < 3; i++)
	{
		if (game[0][i] == game[1][i] && game[1][i] == game[2][i])
		{
			if (game[0][i] != 0 && game[1][i] != 0 && game[2][i] != 0)
			{
				if (game[0][i] == 1) winner = 1;
				else if (game[0][i] == 2) winner = 2;
				is_game_finish = 0;
				return;
			}
		}
		if (game[i][0] == game[i][1] && game[i][1] == game[i][2])
		{
			if (game[i][0] != 0 && game[i][1] != 0 && game[i][2] != 0)
			{
				if (game[i][0] == 1) winner = 1;
				else if (game[i][0] == 2) winner = 2;
				is_game_finish = 0;
				return;
			}
		}
	}
	if (game[0][0] == game[1][1] && game[1][1] == game[2][2]) //диагональ слева на право
	{
		if (game[0][0] == 1)
		{
			winner = 1;
		}
		else if (game[0][0] == 2)
		{
			winner = 2;
		}
		is_game_finish = 0;
		return;
	}
	if (game[2][0] == game[1][1] && game[1][1] == game[0][2]) //диагональ справа на лево
	{
		if (game[2][0] == 1)
		{
			winner = 1;
			is_game_finish = 0;
		}
		else if (game[2][0] == 2)
		{
			winner = 2;
			is_game_finish = 0;
		}
		return;
	}
	if (turn_counter == 9) is_game_finish = 0; return;
}

