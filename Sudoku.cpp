#include "Sudoku.h"

playerMove currentMove{ 0, 0 }; //Standard starting position of the selected cell / Стандартная начальная позиция выбранной ячейки


int main()
{	
	//The loop runs until the exit of the game is made
	int result = 0;
	while (result == 0)
	{
		result = Menu();
		switch (result)
		{
			case 1:
				result = Game();
				break;
			case 2:
				result = MakeNewGameField();
				break;
		}
	}
}

//The method works while we have a game
//Метод работающий пока у нас проходит игра
int Game()
{
	field gameField;
	blockField blocked;
	field badElements;
	


	int result = LoadGame(gameField, blocked);

	if (result == 1) return 0;

	//If the preparation was successful - start the game
	//Если подготовка прошла успешно - начинаем игру
	if (result == 0)
	{
		while (true)
		{
			CheckGameState(gameField, currentMove, badElements);
			PrintGameFieldToConsole(gameField, currentMove, badElements);	
			//for (int i = 0; i < 9; i++)
			//{
			//	for (int j = 0; j < 9; j++) printf("%c", badElements[i][j]);
			//	printf("\n");
			//}
		
			if (CheckForWin(gameField, badElements))
			{
				result = 1;
				break;
			}

			int move = GetPlayerMove(currentMove);
			
			//If the player wants to put a number in a cell as a move - change the playing field
			//Если в качестве хода игрок пожелал поставить цифру в ячейку - меняем игровое поле
			if (move >= 48 && move <= 57) MakeMove(gameField, blocked, currentMove, move); 

			if (move == 1) //Escape pressed
			{
				result = -1;
				break;
			}
		}
	}
	else
	{
		printf("Error when preparing game. Check output before.");
		getchar();
		return -1;
	}
	if (result == 1) Win();
	if (result == -1) StopGame(gameField, blocked);

	return 0;
}

//The game was won
int Win()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 11);
	printf("Game was won!\n");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
	printf("To continue, press any button on the keyboard");
	_getch();
	return 1;
}

//Escape was pressed. We ask if the player wants to save the game
int StopGame(field gameField, blockField blocked)
{
	clearConsole();

	printf("Do you want to save game?\n(Y/N):");
	int act;
	do
	{
		act = _getch();
		act = toupper(act);
	} while (act != 'Y' && act != 'N');

	if (act == 'N') return 0;
	else
	{
		//Player wants to save game
		SaveGame(gameField, blocked);
		return 0;
	}
}