#pragma once
#include <Windows.h>

static int mode;
static const COORD cmain = { 82,10 };

void Letter_Draw(int sleep_time_let);
void letter_T();
void letter_E();
void letter_R();
void letter_I();
void letter_S();
void Drops();
void Game(int mode_menu);
void Check();
void Create_field();
void Player_turn(int mode);
void Bot_turn(int priority);
void Main_menu();
