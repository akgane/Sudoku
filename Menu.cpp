#include "Menu.h"


int Menu()
{
	int result = 0;
	int currentUserAction = 0;
	//Until player dont switch to another menu
	while (result == 0)
	{
		clearConsole();
		for (int i = 0; i < 5; i++)
		{
			if (i == currentUserAction) printf(">");
			PrintMenuToConsole(i);
			if (i == currentUserAction) printf("<");
			printf("\n");
		}
		int action = GetPlayerMove(currentUserAction);
		if (action == 1 || action == 2 || action == -1 || action == -2)
		{
			switch (action)
			{
				case 1:
					currentUserAction--;
					break;
				case 2:
					currentUserAction = 3;
					break;
				case -1:
					currentUserAction++;
					break;
				case -2:
					currentUserAction = 0;
					break;
			}
		}
		else if (action == 13)
		{
			switch (currentUserAction)
			{
				case 0:
					result = 1;
					break;
				case 1:
					result = 2;
					break;
				case 2:
					result = HelpAbout();
					break;
				case 3:
					result = Exit();
					break;
				default:
					printf("Invalid value in switch from Menu methode");
					return -1;
			}
		}
	}	
	if (result == 1) return 1;
	if (result == 2) return 2;
}

int HelpAbout()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	clearConsole();
	SetConsoleTextAttribute(hStdOut, 10);
	printf("[EN]\n");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
	printf("The playing field is stored in memory in two files.\nA regular file in which the entire playing field is saved. \nAnd the second file with the ending 'BLOCKED'.\nIt is needed so that the program knows which cells are forbidden to change the player\n(which cells were installed initially).\n");
	printf("Due to the peculiarities of the output of the playing field to the console, \nproblems may begin to appear when moving too fast. So please don't click on the arrows too fast\n\n\n");

	SetConsoleTextAttribute(hStdOut, 10);
	printf("[CZ]\n");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
	printf("Hraci pole je ulozeno v pameti ve dvou souborech. \nNormalni soubor, ktery uklada cele hraci pole. \nA druhy soubor s koncem 'BLOCKED'. Je nutne, aby program vedel, \nktere bunky je zakazano menit hrace (ktere bunky byly puvodne nainstalovany).\n");
	printf("Vzhledem k vlastnostem vystupu herniho planu na konzoli \nse mohou pri prilis rychlem pohybu zacit objevovat problemy. Proto prosim neklikejte na sipky prilis rychle\n\n\n");

	SetConsoleTextAttribute(hStdOut, BACKGROUND_LIGHTGRAY);
	printf("The project was made by Orazgali Akhan and Miniailenko Vladyslav, VUT FEKT, BPC-TLI4, 2022\n\n");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);

	printf("To continue, press any button on the keyboard");
	_getch();
	return 0;
}

int Exit()
{
	clearConsole();
	
	printf("Are you sure you want to quit the game?\n(Y/N):");
	int action;
	do
	{
		action = _getch();
		action = toupper(action);
	} while (action != 'Y' && action != 'N');

	if (action == 'N') return 0;

	clearConsole();
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 11);
	printf("Thanks for playing. See you soon!\nDiky za hrani. Uvidime se brzy!");
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
	return 5;
}

void PrintMenuToConsole(int currentLine)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 11);
	switch (currentLine)
	{
		default:
			break;
		case 0:
			
			printf("Start game");
			break;
		case 1:
			printf("Make new field");
			break;
		case 2:
			printf("Help / About");
			break;
		case 3:
			printf("Exit");
			break;
	}
	SetConsoleTextAttribute(hStdOut, BACKGROUND_DEFAULT);
}