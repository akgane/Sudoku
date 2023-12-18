#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <sys/stat.h>
#include <stdbool.h>



#define BACKGROUND_YELLOW 224
#define BACKGROUND_GREEN 160 //current choosen cell color / ���� ��������� ������ �������� ����
#define BACKGROUND_LIGHTGRAY 112
#define BACKGROUND_GRAY 128
#define BACKGROUND_DEFAULT 15 //default black bg color / ����������� ������ ����
#define WRONGCOLOR 64 | 15 //wrong line color / ���� ��� ������������ �����




typedef char field[9][9]; //A new name for a two-dimensional array of type char / ����� ��� ��� ���������� ������� ���� char

typedef char square[3][3];

//A two-dimensional array in which those elements that were originally filled in (they are not allowed to be changed) are marked as false
//��������� ������ � ������� �� ��������, ������� ���������� ���� ��������� (�� ������ �� ���������) �������� ��� false
typedef bool blockField[9][9];
typedef int playerMove[2]; //Position of the currently selected cell / ������� �������� ���������� ��������

typedef char fileList[100][50];


//badI and badJ are the coordinates of the line on which there are two identical digits. filledI and filledJ are 
//the coordinates of the line in which all the digits are filled
//in the method, both cases are checked. A bad line has a higher priority than a filled one. A poorly filled line will be red

//badI � badJ - ���������� ����� �� ������� ����� ��� ���������� �����. filledI � filledJ - ���������� ����� � ������� ��������� ��� �����
//� ������ ����������� ��� ������. ������ ����� ����� ��������� ���� ��� �����������. ����� ����������� ����� ����� �������
void PrintGameFieldToConsole(field gameField, playerMove currentMove, field badElements);

int GetPlayerMove(playerMove currentMove);
int GetPlayerMove(int currentUserAction);
bool CheckMovePosibility(playerMove currentMove, int move);
bool CheckMovePosibility(int currentUserAction, int move);
void MakeMove(field gameField, blockField blocked, playerMove currentMove, int move);
int CheckGameState(field gameField, playerMove currentMove, field badElements);
void CheckLinesForSimilar(field gameField, playerMove currentMove, field badElements);
bool CheckOneLineForSimilar(int line[9]);
void CheckIfLineFilled(field gameField, playerMove currentMove, field badElements);
bool CheckForWin(field gameField, field badElements);
int SaveGame(field gameField, blockField blocked);
int LoadGame(field gameField, blockField blocked);
int MakeNewGameField();
int GenerateFromFile();
int GenerateByPlacing();
int CheckIfSquareWrong(field gameField, field badElements);
bool CheckSquare(int squarePos[], field gameField);


void clearConsole();