#pragma once
#include "Includes.h"
#include "Game.h"
#include "Save.h"
#include "Load.h"

void menu() {

	int amount{};
	int difficulty{};
	bool standardGame{};

	int select{};
	string selectIcon{"->"};

	bool menuRun{true};

	vector<string> options{"Easy", "Medium", "Hard", "Creative", "Save", "Load"};

	while (menuRun)
	{
		for (size_t i = 0; i < options.size(); i++)
		{
			if (select == i)
				cout << selectIcon << " | " << options[i] << endl;
			else
				cout << " | " << options[i] << endl;
		}

		char menuSelect = tolower(_getch());
		switch (menuSelect)
		{
		case 'w':
			select -= 1;
			break;
		case 's':
			select += 1;
			break;
		case 13:
			if (select == 0) //Easy
			{
				amount = 3;
				difficulty = 3;
				standardGame = true;
				system("cls");
				game(amount, difficulty, standardGame);
			}
			else if (select == 1) //Medium
			{
				amount = 4;
				difficulty = 4;
				standardGame = true;
				system("cls");
				game(amount, difficulty, standardGame);
			}
			else if (select == 2) //Hard
			{
				amount = 5;
				difficulty = 5;
				standardGame = true;
				system("cls");
				game(amount, difficulty, standardGame);
			}
			else if (select == 3) //Creative
			{
				standardGame = false;
				system("cls");
				game(amount, difficulty, standardGame);
			}
			else if (select == 4) //Save
				save();
			else if (select == 5) //Load
				load();
			break;
		case 8:
			menuRun = false;
			break;
		default:
			break;
		}

		if (select < 0)
			select = options.size() - 1;
		if (select == options.size())
			select = 0;

		system("cls");
	}
}