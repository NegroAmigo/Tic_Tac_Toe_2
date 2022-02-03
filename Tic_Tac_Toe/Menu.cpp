#ifndef HEADER_H
#define HEADER_H

#include "Header.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

CONSOLE_CURSOR_INFO ci1;

COORD c1;
COORD c_letters = cmain;
HANDLE hout_menu;
int curY_menu = 0;
int arrLetter[5][5] = {0};
vector<vector<COORD>> drops;

void Letter_Draw(int sleep_time_let) {
    void (*letters[6])() = {letter_T, letter_E, letter_T, letter_R, letter_I, letter_S};

    COORD c_tmp = c_letters;
    for (int let_count = 0; let_count < 6; let_count++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                arrLetter[i][j] = 255;
            }
        }
        letters[let_count]();
        for (int i = 0; i < 5; i++) {
            SetConsoleCursorPosition(hout_menu, c_tmp);
            for (int j = 0; j < 5; j++) {
                cout << (char) arrLetter[i][j];
                Sleep(sleep_time_let);
            }
            c_tmp.Y++;
        }
        c_tmp.Y -= 5;
        c_tmp.X += 7;
    }

}

void letter_T() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 0) arrLetter[i][j] = 220;
            if (j == 2 && i != 0) arrLetter[i][j] = 219;
        }
    }
}

void letter_E() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i % 2 == 0) arrLetter[i][j] = 220;
            if (j == 0 && i != 0) arrLetter[i][j] = 219;
        }
    }
}

void letter_R() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == 0 && i != 0) arrLetter[i][j] = 219;
            if (i == 0) arrLetter[i][j] = 220;
            if (j == 4 && i != 0 && i != 3) arrLetter[i][j] = 219;
            if (i != 0 && i == 2 && j != 0 && j != 4) arrLetter[i][j] = 220;
        }
    }
    arrLetter[3][3] = 219;
}

void letter_I() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 0 || i == 4) arrLetter[i][j] = 220;
            if (j == 2 && i != 0) arrLetter[i][j] = 219;
        }
    }
}

void letter_S() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((j == 0 && (i == 1 || i == 2)) || (j == 4 && (i == 3 || i == 4))) arrLetter[i][j] = 219;
            if (i == 0) arrLetter[i][j] = 220;
            if (i == 2 && j != 0) arrLetter[i][j] = 220;
            if (i == 4 && j != 4) arrLetter[i][j] = 220;
        }
    }
}

void Welcome_screen() {
    int arr[11][46] = {0};
    c1 = cmain;
    c_letters = cmain;
    int sleep_time_let = 0;//10
    int sleep_time = 0;//15
    curY_menu = 0;

    //отрисовка большой рамки
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 46; j++) {
            if (j == 0 || j == 45) arr[i][j] = 219;
            if (i == 0) arr[i][j] = 220;
            if (i == 10) arr[i][j] = 223;
            if (i != 0 && i != 10 && j != 0 && j != 45) arr[i][j] = 255;

        }
    }


    COORD c_tmp = c1;
    for (int i = 0; i < 11; i++) {
        SetConsoleCursorPosition(hout_menu, c_tmp);
        for (int j = 0; j < 46; j++) {
            if (i == 0 || i == 10 || j == 0 || j == 45) {
                cout << (char) arr[i][j];
                Sleep(sleep_time);
            } else cout << (char) arr[i][j];
        }
        c_tmp.Y++;
    }
    c_letters.Y += 2;
    c_letters.X += 3;
    Letter_Draw(sleep_time_let);
    c1.X += 15;
    c1.Y += 8;
    SetConsoleCursorPosition(hout_menu, c1);
    cout << "by Blue Warriors";
    sleep_time = 0;
    sleep_time_let = 0;
    c1.Y += 4;
}

void Draw_Butt(bool is_frame, int phrase_id, COORD coords) {
    if (!is_frame) {}

    int butt[3][20];

    if (is_frame) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 20; j++) {
                if (i == 0 || i == 2) {
                    butt[i][j] = 205;
                    continue;
                }//═
                if ((j == 0 && i == 1) || (j == 19 && i == 1)) {
                    butt[i][j] = 186;
                    continue;
                }//║
                else butt[i][j] = ' ';
            }
        }
        butt[0][0] = 201; // ╔
        butt[0][19] = 187; // ╗
        butt[2][0] = 200; // ╚
        butt[2][19] = 188; // ╝ 
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 20; j++) {
                butt[i][j] = ' ';
            }
        }
    }


    string phrases[5] = {"Play vs Computer", "Play vs Player 2", "Options", "Credits", "Exit"};
    short str_len = phrases[phrase_id].size();
    for (int i = 0; i < str_len; i++) {
        int space = i + (ceil(20 - str_len) / 2);
        butt[1][space] = (int) phrases[phrase_id][i];
    }

    SetConsoleCursorPosition(hout_menu, coords);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 20; j++) {
            cout << (char) butt[i][j];
        }
        coords.Y++;
        SetConsoleCursorPosition(hout_menu, coords);
    }

}

void Create_field() {
    int field[13][13];
    system("cls");
    SetConsoleCursorPosition(hout_menu, c1);
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            if (i == 0 && j % 4 == 0) field[i][j] = 203; // ╦
            else if (i == 12 && j % 4 == 0) field[i][j] = 202; // ╩
            else if (i % 4 == 0 && j % 4 != 0) field[i][j] = 205; // ═
            else if (i % 4 != 0 && j % 4 == 0) field[i][j] = 186; // ║
            else if (i % 4 == 0 && j % 4 == 0 && i != 0 && j != 0 && j != 12 && i != 12) field[i][j] = 206; // ╬
            else if (i % 4 == 0 && j == 0) field[i][j] = 204; // ╠
            else if (i % 4 == 0 && j == 12) field[i][j] = 185; // ╣
            else if (i % 4 != 0 && j % 4 != 0) field[i][j] = 255; //space
        }
    }

    field[0][0] = 201; // ╔
    field[0][12] = 187; // ╗
    field[12][0] = 200; // ╚
    field[12][12] = 188; // ╝

    //Draw_field
    c1 = cmain;
    system("cls");

    for (int i = 0; i < 13; i++) {
        SetConsoleCursorPosition(hout_menu, c1);
        for (int j = 0; j < 13; j++) {
            cout << (char) field[i][j];
        }
        c1.Y++;
    }
}

void Main_menu() {
    int curY_menu = 0;
    COORD frame[5] = {{c1.X - 1, c1.Y},
                      {c1.X - 1, c1.Y + 3},
                      {c1.X - 1, c1.Y + 6},
                      {c1.X - 1, c1.Y + 9},
                      {c1.X - 1, c1.Y + 12}};
    SetConsoleCursorPosition(hout_menu, frame[curY_menu]);
    Draw_Butt(true, 0, frame[0]);
    for (int but_draw = 1; but_draw < 5; but_draw++) {
        Draw_Butt(false, but_draw, frame[but_draw]);
    }

    while (true) {
        Drops();
        if (_kbhit())
        {
            int y = _getch();
            switch (y)
            {
            case 72:
                Draw_Butt(false, curY_menu, frame[curY_menu]);
                if (curY_menu - 1 < 0) curY_menu = 4;
                else if (curY_menu - 1 >= 0 && curY_menu - 1 <= 4) curY_menu--;
                Draw_Butt(true, curY_menu, frame[curY_menu]);
                break;
            case 80:
                Draw_Butt(false, curY_menu, frame[curY_menu]);
                if (curY_menu + 1 > 4) curY_menu = 0;
                else if (curY_menu + 1 <= 4 && curY_menu + 1 >= 0) curY_menu++;
                Draw_Butt(true, curY_menu, frame[curY_menu]);
                break;
            case 13:
                if (curY_menu == 0) {
                    Create_field();
                    Game(2);
                    return;
                }
                else if (curY_menu == 1) {
                    Create_field();
                    Game(1);
                    return;
                }
                else if (curY_menu == 2) {
                    /* do some
                    option shit*/
                }
                else if (curY_menu == 3) {
                    /* do some
                    credits shit*/
                }
                else if (curY_menu == 4) {
                    system("cls");
                    exit(0);
                }
                break;
            }
        }
        
        
        
        
    }
}


void Drops() {

    drops.push_back(vector<COORD>());

    //создание новой сопли
    short x = rand() % 210;
    for (short now_use_element = -6; now_use_element < 0; now_use_element++) {
        COORD tmp = {x, now_use_element};
        drops[drops.size()-1].push_back(tmp);
    }
    //передвижение сопли от конца в начало
    for (int now_use_drop = 0; now_use_drop < drops.size(); now_use_drop++)
    {

        short min = drops[now_use_drop][0].Y;
        int min_index = 0;
        int now_use_element=0;
        //Нахождение максимального значения капли
        for (now_use_element = 0; now_use_element < drops[now_use_drop].size(); now_use_element++)
        {
            if (drops[now_use_drop][now_use_element].Y < min)
            {
                min = drops[now_use_drop][now_use_element].Y;
                min_index = now_use_element;
            }
        }
        //Перемещение минимального элемента вниз

        drops[now_use_drop][min_index].Y += 6;

        //Удаление сопли или елементов выходящих за область отрисовки
        bool what_the_fuck_is_this = false;
        for (int now_use_element = 0; now_use_element < drops[now_use_drop].size(); now_use_element++)
        {
            COORD tmp = drops[now_use_drop][now_use_element];
            if (tmp.Y >= 54)
            {
                if (drops[now_use_drop].size() > 1)
                {
                    drops[now_use_drop].erase(drops[now_use_drop].begin() + now_use_element);
                }
                if (drops[now_use_drop].size() == 1)
                {
                    drops.erase(drops.begin() + now_use_drop);
                    what_the_fuck_is_this = true;
                    break;
                }
            }
        }
        if(what_the_fuck_is_this)
        {
            continue;
        }
        for (int now_use_element = 0; now_use_element < drops[now_use_drop].size(); now_use_element++){
            COORD tmp = drops[now_use_drop][now_use_element];
            if (tmp.X >= 96 && tmp.X < 116 && tmp.Y >= 10 && tmp.Y <= 36) { continue; }
            else if (tmp.X >= 82 && tmp.X <= 95 && tmp.Y >= 10 && tmp.Y < 21) { continue; }
            else if (tmp.X >= 115 && tmp.X <= 128 && tmp.Y >= 10 && tmp.Y < 21) { continue; }
            else{
                if (now_use_element+1==drops[now_use_drop].size()){
                    SetConsoleCursorPosition(hout_menu, { drops[now_use_drop][min_index].X, drops[now_use_drop][min_index].Y-  6 });
                    cout << " ";
                }
                SetConsoleCursorPosition(hout_menu, {drops[now_use_drop][now_use_element].X, drops[now_use_drop][now_use_element].Y});
                if (now_use_element % 2 == 0) cout << "X";
                else cout << "O";
            }
        }
    }
    Sleep(20);
}

int main() {
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    system("mode con cols=210 lines=54");//~1680*864 НО ЭТО ПОЛНЫЙ ЭКРАН
    hout_menu = GetStdHandle(STD_OUTPUT_HANDLE);
    ci1.dwSize = 100;
    ci1.bVisible = false;
    SetConsoleCursorInfo(hout_menu, &ci1);
    srand((unsigned int) time(NULL));


    while (true) {
        system("cls");
        Welcome_screen();

        Main_menu();
    }

    return 0;
}

#endif