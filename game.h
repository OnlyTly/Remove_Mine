#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include<windows.h>

//埋雷的范围
#define ROW 9
#define COL 9
//整个雷场的范围
#define ROWS ROW+2
#define COLS COL+2
//雷的个数--游戏难易
#define EASY_COUNT 10

void InitBoard(char board[ROWS][COLS], int rows, int cols,char set);

void DisplayBoard(char board[ROWS][COLS], int row, int col);

void SetMine(char board[ROWS][COLS], int row, int col);

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);