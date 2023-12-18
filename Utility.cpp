#include "Utility.h"

//Метод выводящий на консоль игровое поле. Вместо нулей вставляет пробел
//The method that outputs the playing field to the console. Inserts a space instead of zeros
void PrintGameFieldToConsole(field gameField, playerMove currentMove, field badElements)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	clearConsole(); //Clear console before printing / Очистить консоль перед выводом

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((currentMove[0] == i) && (currentMove[1] == j))
			{
				SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN);
				if (gameField[i][j] == '0') printf("%c", ' ');
				else printf("%c", gameField[i][j]);
				SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
				if ((j == 2) || (j == 5)) printf("%c", '|');
				continue;
			}
			if (badElements[i][j] == '1')
			{
				SetConsoleTextAttribute(hStdOut, WRONGCOLOR);
				if (gameField[i][j] == '0') printf("%c", ' ');
				else printf("%c", gameField[i][j]);
				SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
				if ((j == 2) || (j == 5)) printf("%c", '|');
			}
			else
			{
				if (i > 2 && i < 6)
				{
					if (j > 2 && j < 6)
					{
						SetConsoleTextAttribute(hStdOut, BACKGROUND_LIGHTGRAY);
						if (gameField[i][j] == '0') printf("%c", ' ');
						else printf("%c", gameField[i][j]);
						SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
					}
					else
					{
						if (gameField[i][j] == '0') printf("%c", ' ');
						else printf("%c", gameField[i][j]);
					}
					if (j == 2 || j == 5) printf("%c", '|');
				}
				else
				{
					if (j < 3 || j > 5)
					{
						SetConsoleTextAttribute(hStdOut, BACKGROUND_LIGHTGRAY);
						if (gameField[i][j] == '0') printf("%c", ' ');
						else printf("%c", gameField[i][j]);	
						SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
					}
					else
					{
						if (gameField[i][j] == '0') printf("%c", ' ');
						else printf("%c", gameField[i][j]);
					}
					if (j == 2 || j == 5) printf("%c", '|');
				}
			}
		}
		printf("%c", '\n');
	}
	//Return the color output to the console to the standard value
	//Возвращаем выводимый на консоль цвет в стандартное значение
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
}

//A method that processes the player's actions
//Метод обрабатывающий действия игрока
int GetPlayerMove(playerMove currentMove)
{
	int userInput = _getch();
	//Processing empty moves / Обрабатываем пустые ходы
	if (userInput == 0 || userInput == 224) userInput = _getch(); 
	//Return userInput as indicator that player want to place number /Возвращает пользовательский ввод в качестве индикатора того, что игрок хочет разместить цифру
	if (userInput >= 48 && userInput <= 57) return userInput; 

	//Processing other various actions
	//Проверяем другие различные действия
	switch (userInput)
	{
		case 27:
			//Escape was pressed. Stop game, return 1 as result to catch
			return 1;
		case 72:
			//Up button
			if (CheckMovePosibility(currentMove, userInput)) currentMove[0] -= 1;
			else currentMove[0] = 8;
			return 0;
		case 80:
			//Down button
			if (CheckMovePosibility(currentMove, userInput)) currentMove[0] += 1;
			else currentMove[0] = 0;
			return 0;
		case 77:
			//Right button
			if (CheckMovePosibility(currentMove, userInput)) currentMove[1] += 1;
			else currentMove[1] = 0;
			return 0;
		case 75:
			//Left button
			if (CheckMovePosibility(currentMove, userInput)) currentMove[1] -= 1;
			else currentMove[1] = 8;
			return 0;
	}	
	//printf("%d", userInput);
}

//GetPlayerMove method overload. To get input for Menu
int GetPlayerMove(int currentUserAction)
{
	int userInput = _getch();
	
	if (userInput == 0 || userInput == 224) userInput = _getch();
	switch (userInput)
	{
		case 72:
			if (CheckMovePosibility(currentUserAction, userInput)) return 1;
			else return 2;
		case 80:
			if (CheckMovePosibility(currentUserAction, userInput)) return -1;
			else return -2;
		case 13: //Enter
			return 13;
	}
}

//A method that checks whether a player can go in the desired direction. If it is on the edge of the playing field, 
//then the move is not allowed - we skip it
//Метод проверяющий может ли игрок пойти в желаемую сторону. Если находится на краю игрового поля то ход не разрешен - пропускаем его
bool CheckMovePosibility(playerMove currentMove, int move)
{
	switch (move)
	{
		case 72:
			if (currentMove[0] > 0) return true;
			break;
		case 80:
			if (currentMove[0] < 8) return true;
			break;
		case 77:
			if (currentMove[1] < 8) return true;
			break;
		case 75:
			if (currentMove[1] > 0) return true;
			break;
	}
	return false;
}

//CheckMovePosibility methode overload. To check move for Menu
bool CheckMovePosibility(int currentUserAction, int move)
{
	switch (move)
	{
		case 72:
			if (currentUserAction > 0) return true;
			return false;
		case 80:
			if (currentUserAction < 3) return true;
			return false;
	}
}

//A method that changes the playing field depending on the player's move
//Метод меняющий игровое поле в зависимости от хода игрока
void MakeMove(field gameField, blockField blocked, playerMove currentMove, int move)
{
	//Check: is the player allowed to change this playing field. 
	//Проверка: разрешено ли игроку менять данное игровое поле. 
	if (blocked[currentMove[0]][currentMove[1]]) 
	{
		if (gameField[currentMove[0]][currentMove[1]] == (char)move) gameField[currentMove[0]][currentMove[1]] = '0';
		else gameField[currentMove[0]][currentMove[1]] = (char)move;
	}
	return;
}

//Check current game state
int CheckGameState(field gameField, playerMove currentMove, field badElements)
{
	//Check all lines if they completely filled. This does not mean that the line is filled in correctly
	//CheckIfLineFilled(gameField, currentMove);

	//Check all lines for similar numbers
	CheckLinesForSimilar(gameField, currentMove, badElements);
	CheckIfSquareWrong(gameField, badElements);

	return 0;
}

//Check all lines if they filled
//void CheckIfLineFilled(field gameField, playerMove currentMove, field badElements)
//{
//	int hTemp = -1;
//	int vTemp = -1;
//	//Horizontal
//	for (int i = 0; i < 9; i++)
//	{
//		for (int j = 0; j < 9; j++)
//		{
//			if (gameField[i][j] == '0') j = 9;
//			else if (j == 8) hTemp = i;
//		}
//	}
//
//	//Vertical
//	for (int i = 0; i < 9; i++)
//	{
//		for (int j = 0; j < 9; j++)
//		{
//			if (gameField[j][i] == '0') j = 9;
//			else if (j == 8) vTemp = i;
//		}
//	}
//	PrintGameFieldToConsole(gameField, currentMove, badElements);	
//}

//Check all lines for similar numbers
void CheckLinesForSimilar(field gameField, playerMove currentMove, field badElements)
{
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) badElements[i][j] = '0';
	//Check all horizontal lines
	for (int i = 0; i < 9; i++)
	{
		int line[9];
		for (int j = 0; j < 9; j++) line[j] = gameField[i][j];
	
		
		if (CheckOneLineForSimilar(line))
		{
			for (int j = 0; j < 9; j++) badElements[i][j] = '1';
		}
	}

	//Check all vertical lines
	for (int i = 0; i < 9; i++)
	{
		int line[9];
		for (int j = 0; j < 9; j++) line[j] = gameField[j][i];
	
		if (CheckOneLineForSimilar(line))
		{
			for (int j = 0; j < 9; j++) badElements[j][i] = '1';
		}

	}
}
//Check one line for two similar numbers. Return true if similar numbers was found - bad line
bool CheckOneLineForSimilar(int line[9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = i + 1; j < 9; j++)
		{
			if (line[i] != '0' && (line[i] == line[j])) return true; 
		}
	}
	return false;
}

bool CheckForWin(field gameField, field badElements)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (gameField[i][j] == '0') return false;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (badElements[i][j] == '1') return false;
		}
	}
	//If the whole playing field is filled with numbers, and there are no lines with repeating numbers - the player wins
	return true;
}

int CheckIfSquareWrong(field gameField, field badElements) 
{
	for (int i = 0; i <= 6; i = i + 3)
	{
		for (int j = 0; j <= 6; j = j + 3)
		{
			int squarePos[2] = { i, j };
			if (CheckSquare(squarePos, gameField))
			{
				for (int ix = i; ix < (i + 3); ix++)
				{
					for (int jx = j; jx < (j + 3); jx++)
					{
						badElements[ix][jx] = '1';
					}
				}
			}
		}
	}
	return 1;
}

bool CheckSquare(int squarePos[], field gameField)
{
	int countOfEachNumber[9];

	for (int i = 0; i < 9; i++) countOfEachNumber[i] = 1;

	for (int i = squarePos[0]; i < (squarePos[0] + 3); i++)
	{
		for (int j = squarePos[1]; j < (squarePos[1] + 3); j++)
		{
			if (gameField[i][j] == '0') return false;
			countOfEachNumber[gameField[i][j] - 49]--;
		}
	}

	for (int i = 0; i < 9; i++) if (countOfEachNumber[i] < 0) return true;
	return false;
}


//Method for saving the game
int SaveGame(field gameField, blockField blocked) 
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	FILE* mainFile;
	FILE* blockFile;
	char mainName[40] = "Fields\\";
	char blockName[47] = "Fields\\";

	//Temporary variable for getting a string from the console
	char temp[20];
	printf("\nPrint 'esc' if you want to exit.\n");
	printf("\nName the game save (max length 20 characters): ");
	scanf_s("%s", temp, 20);
	if (strcmp(temp, "esc") == 0) return 1;
	//Converting the names to the correct file names
	strcat_s(mainName, temp);
	strcat_s(mainName, ".txt");

	strcat_s(blockName, temp);
	strcat_s(blockName, "BLOCKED.txt");

	errno_t errMain = fopen_s(&mainFile, mainName, "w");
	errno_t errBlock = fopen_s(&blockFile, blockName, "w");

	if (errMain != 0 || errBlock != 0)
	{
		printf("Error with creating save file");
		return 1;
	}
	//Writing data to the appropriate files
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fprintf(mainFile, "%c", gameField[i][j]);
			fprintf(blockFile, "%d", blocked[i][j]);
		}
		fprintf(mainFile, "%c", '\n');
		fprintf(blockFile, "%c", '\n');
	}
	SetConsoleTextAttribute(hStdOut, 10);
	printf("Game was succesfully saved.");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
	_getch();

	fclose(mainFile);
	fclose(blockFile);

	return 0;

}

//Method for loading a game from text files
int LoadGame(field gameField, blockField blocked)
{
	clearConsole();
	
	FILE* mainFile;
	FILE* blockFile;
	errno_t errMain;

	char mainName[40] = "Fields\\";
	char blockName[47] = "Fields\\";
	char temp[20];

	//Requesting a save name until the correct name is entered
	do
	{
		printf("Print 'esc' if you want to exit.\n");
		printf("Write the name of the save, without extencion '.txt' \n(There is a standard playing field in the folder 'default'): ");
		scanf_s("%s", temp, 20);
		//if player wants to exit
		if (strcmp(temp, "esc") == 0) return 1;

		strcat_s(mainName, temp);
		strcat_s(mainName, ".txt");
		errMain = fopen_s(&mainFile, mainName, "r");
		if (errMain != 0)
		{
			printf("\nThe save file was not found\n");
			strcpy_s(mainName, "Fields\\");
		}
	} while (errMain != 0);

	strcat_s(blockName, temp);
	strcat_s(blockName, "BLOCKED.txt");

	errno_t errBlock = fopen_s(&blockFile, blockName, "r");
	if (errBlock != 0)
	{
		printf("Error with opening 'BLOCKED' file");
		printf("Try 'Make new field' menu button");
		return -1;
	}

	//Write data from files to variables
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			char m = fgetc(mainFile);
			char b = fgetc(blockFile);
			gameField[i][j] = (char)m;
			if (b == '1') blocked[i][j] = true;
			else if (b == '0') blocked[i][j] = false;
			else
			{
				clearConsole();
				printf("Error when reading 'BLOCKED' file");
				return -1;
			}
		}
		fgetc(mainFile);
		fgetc(blockFile);
	}

	fclose(mainFile);
	fclose(blockFile);
	return 0;
}

//Managing the game field creation menu
int MakeNewGameField()
{
	clearConsole();

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 10);
	printf("[EN]\n");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);

	printf("The Make new field method is needed in order to generate a new playing field. \nThere are three methods in total for generating the playing field:\n\n");
	printf("1) Paste a text file into the Fields folder. \nAnd run the algorithm that generates a new playing field from the file.\n");
	SetConsoleTextAttribute(hStdOut, 12);
	printf("(Note: Just inserting a text file is not enough. Before the game, be sure to run this algorithm)\n\n");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
	printf("2) Create the playing field yourself by placing the numbers \nthat will be forbidden to change yourself\n\n\n\n");



	SetConsoleTextAttribute(hStdOut, 10);
	printf("[CZ]\n");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);

	printf("Make new field metoda je nutna k vygenerovani noveho herniho planu. \nExistuji celkem tri metody pro generovani hraciho pole:\n\n");
	printf("1) Vlozit textovy soubor do slozky pole. \nA spustit algoritmus ktery generuje ze souboru nove herni pole.\n");
	SetConsoleTextAttribute(hStdOut, 12);
	printf("(Pozor: pouhe vlozeni textoveho souboru nestaci. Pred hranim nezapomente spustit tento algoritmus)\n\n");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
	printf("2) Vytvorte si hriste sami usporadanim cisel, ktera budou zakazana menit sami.\n\n\n\n");


	printf("Choose methode: ");
	int action;
	do
	{
		action = _getch();
	} while (action != '1' && action != '2' && action != 27);

	switch (action)
	{
		case '1':
			GenerateFromFile();
			break;
		case '2':
			GenerateByPlacing();
			break;
		case 27: //escape
			return 0;
	}



	return 0;
}

//Method for generating a playing field from a text files
int GenerateFromFile() 
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	clearConsole();
	printf("Print 'esc' if you want to exit.");
	printf("The method with inserting a text file into the Fields folder is selected.\nMake sure that you have inserted the text file into the folder. \nIt should contain a 9x9 field of digits 0-9, where 0 is an empty cell.\nThe maximum length of the file name is 20 characters\n");
	printf("After you have inserted the file, write its name here (without extension.txt): ");

	FILE* mainFile;
	FILE* blockFile;

	char tempName[20];
	char mainName[40] = "Fields\\";
	char blockName[47] = "Fields\\";

	errno_t errMain;
	do
	{
		scanf_s("%s", tempName, 20);

		if (strcmp(tempName, "esc") == 0) return 1;
		

		strcat_s(mainName, tempName);
		strcat_s(mainName, ".txt");
		errMain = fopen_s(&mainFile, mainName, "r");

		if (errMain != 0)
		{
			printf("File not found. Try again\n");
			strcpy_s(mainName, "Fields\\"); 
		}
	} while (errMain != 0);

	strcat_s(blockName, tempName);
	strcat_s(blockName, "BLOCKED.txt");

	errno_t errBlock = fopen_s(&blockFile, blockName, "w");
	if (errBlock != 0)
	{
		printf("Error with creating 'BLOCKED' file");
		return -1;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			char c = fgetc(mainFile);
			if (c != '0') fprintf(blockFile, "%d", 0);
			else fprintf(blockFile, "%d", 1);
		}
		fprintf(blockFile, "%c", '\n');
		fgetc(mainFile);
	}

	fclose(mainFile);
	fclose(blockFile);

	
	SetConsoleTextAttribute(hStdOut, 10);
	printf("\nGame field was succesfully generated");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);

	_getch();
	return 0;
}

//A method for creating a game save by setting the cells yourself
int GenerateByPlacing()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	field badElements;
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) badElements[i][j] = '0';

	field gameField;
	blockField blocked;
	playerMove currentMove{ 0, 0 };

	FILE* mainFile;
	FILE* blockFile;

	char tempName[20];
	char mainName[40] = "Fields\\";
	char blockName[47] = "Fields\\";

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			gameField[i][j] = '0';
			blocked[i][j] = true;
		}
	}

	int action;
	do
	{
		PrintGameFieldToConsole(gameField, currentMove, badElements);
		action = GetPlayerMove(currentMove);
		if (action >= 48 && action <= 57) MakeMove(gameField, blocked, currentMove, action);
	} while (action != 1);

	clearConsole();
	

	errno_t errMain;
	do
	{
		printf("Write the name of the save (without extencion '.txt' ):");
		scanf_s("%s", tempName, 20);
		strcat_s(mainName, tempName);
		strcat_s(mainName, ".txt");

		errMain = fopen_s(&mainFile, mainName, "w");
		if (errMain != 0)
		{
			printf("Error with creating file. Try again.\n");
			strcpy_s(mainName, "Fields\\");
		}
	} while (errMain != 0);

	strcat_s(blockName, tempName);
	strcat_s(blockName, "BLOCKED.txt");

	errno_t errBlock = fopen_s(&blockFile, blockName, "w");
	if (errBlock != 0)
	{
		printf("Error with creating 'BLOCKED' file");
		return 1;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (gameField[i][j] != '0') blocked[i][j] = false;
			fprintf(mainFile, "%c", gameField[i][j]);
			fprintf(blockFile, "%d", blocked[i][j]);
		}
		fprintf(mainFile, "%c", '\n');
		fprintf(blockFile, "%c", '\n');
	}
	fclose(mainFile);
	fclose(blockFile);

	SetConsoleTextAttribute(hStdOut, 10);
	printf("\nFile was succesfully saved");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
	_getch();
	return 0;
}

//Just clear console methode
void clearConsole() { system("@cls||clear"); }