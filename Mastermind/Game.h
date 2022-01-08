#pragma once
#include "Includes.h"
#include "Termocolor.h"

#pragma region Identifiers
void game(int& amount, int& difficulty, bool standardGame);
void setup(int& amount, int& difficulty);
void vectorBuild(vector<int>& numberSelected, vector<int>& numberSelectedTemp, int amount, int difficulty);

void boardPrint(vector<int> numberSelected);
void playerInput(vector<int> numberSelected, vector<int>& playerSelected, vector<vector<int>>& playerTurnSelects, int amount, int difficulty);

void calculateRightInRight(vector<int> numberSelected, vector<int> playerSelected, int& rightInRight, vector<int>& rightInRightVector);
void calculateRightInWrong(vector<int> numberSelected, vector<int>& numberSelectedTemp, vector<int> playerSelected, int& rightInWrong, vector<int>& rightInWrongVector);
void playerProgressionBoard(vector<vector<int>> playerTurnSelects, vector<int> numberSelected, vector<int> rightInRightVector, vector<int> rightInWrongVector, int turn);

void winCondition(vector<int> playerSelected, vector<int> numberSelected, bool& run);
#pragma endregion

void game(int& amount, int& difficulty, bool standardGame) {
	int rightInRight{};
	int rightInWrong{};
	int turn{};

	vector<int> numberSelected{};
	vector<int> numberSelectedTemp{};
	vector<int> playerSelected{};
	vector<vector<int>> playerTurnSelects{};

	vector<int> rightInRightVector{};
	vector<int> rightInWrongVector{};

	bool run{true};

	//Setup the game calls
	if (standardGame == false)
		setup(amount, difficulty);
	vectorBuild(numberSelected, numberSelectedTemp, amount, difficulty);

	while (run)
	{
		turn++;

		playerInput(numberSelected, playerSelected, playerTurnSelects, amount, difficulty);
		calculateRightInRight(numberSelected, playerSelected, rightInRight, rightInRightVector);
		calculateRightInWrong(numberSelected, numberSelectedTemp, playerSelected, rightInWrong, rightInWrongVector);
		playerProgressionBoard(playerTurnSelects, numberSelected, rightInRightVector, rightInWrongVector, turn);

		winCondition(playerSelected, numberSelected, run);
	}
}

void setup(int& amount, int& difficulty) {
	cout << "How large will you make your board? ";
	cin >> amount;
	system("cls");

	cout << "What difficulty do you want to give yourself? ";
	cin >> difficulty;
	system("cls");
}

void vectorBuild(vector<int>& numberSelected, vector<int>& numberSelectedTemp, int amount, int difficulty) {
	
	numberSelected.clear();
	numberSelectedTemp.clear();
	
	int numberMin{1};
	int numberMax{difficulty};
	int randomNumber{};

	for (size_t i = 0; i < amount; i++)
	{
		//RNG
		random_device rd;
		mt19937_64 gen(rd());
		uniform_int_distribution<int> RNG(numberMin, numberMax);
		randomNumber = RNG(gen);

		//Build vector
		numberSelected.push_back(randomNumber);
	}
}

void boardPrint(vector<int> numberSelected) {

	cout << endl;
	cout << "   |  ";
	for (size_t i = 0; i < numberSelected.size(); i++)
		cout << numberSelected[i] << setw(4);
	cout << " | " << endl << endl;
}

void playerInput(vector<int> numberSelected, vector<int>& playerSelected, vector<vector<int>>& playerTurnSelects, int amount, int difficulty) {

	string input{};
	bool correctInput{false};

	playerSelected.clear();

	//Gives the right amount of numbers outputted
	while (correctInput == false)
	{
		//boardPrint(numberSelected); //Remove when finished
		cout << "Input your guess (" << amount << " numbers from 1 - " << difficulty << "):" << endl;
		cin >> input;
		cout << endl << endl;

		if (input.size() == numberSelected.size())
			correctInput = true;
		else if (input.size() < numberSelected.size())
		{
			cout << "Too few inputs" << endl;
			system("pause > 0");
		}
		else if (input.size() > numberSelected.size())
		{
			cout << "Too many inputs" << endl;
			system("pause > 0");
		}
		else
		{
			cout << "Invalid input" << endl;
			system("pause > 0");
		}

		system("cls");
	}

	//Update vector"playerSelected" to match the last player input
	for (size_t i = 0; i < input.size(); i++)
		playerSelected.push_back(input[i] - 48);

	//Update vector"playerTurnSelects" to include the last turn selected
	playerTurnSelects.push_back(playerSelected);
}

void calculateRightInRight(vector<int> numberSelected, vector<int> playerSelected, int& rightInRight, vector<int>& rightInRightVector) {
	
	rightInRight = 0;

	for (size_t i = 0; i < numberSelected.size(); i++)
	{
		if (numberSelected[i] == playerSelected[i])
			rightInRight++;
	}

	rightInRightVector.push_back(rightInRight);
}

void calculateRightInWrong(vector<int> numberSelected, vector<int>& numberSelectedTemp, vector<int> playerSelected, int& rightInWrong, vector<int>& rightInWrongVector) {
	
	vector<int> playerSelectedTemp{};

	rightInWrong = 0;
	numberSelectedTemp = numberSelected;
	playerSelectedTemp = playerSelected;

	//Rouling out what's on the right place
	for (size_t i = 0; i < numberSelected.size(); i++)
	{
		if (numberSelected[i] == playerSelected[i])
		{
			numberSelectedTemp[i] = 0;
			playerSelectedTemp[i] = 0;
		}
	}

	//Find the ringtInWrong amoung the numbers that's not right
	for (size_t i = 0; i < numberSelected.size(); i++)
	{
		for (size_t j = 0; j < numberSelected.size(); j++)
		{
			if (numberSelectedTemp[i] == playerSelectedTemp[j])
			{
				if (numberSelectedTemp[i] != 0 && playerSelectedTemp[j] != 0)
				{
					numberSelectedTemp[i] = 0;
					playerSelectedTemp[j] = 0;
					rightInWrong++;
				}
			}
		}
	}

	rightInWrongVector.push_back(rightInWrong);
}

void playerProgressionBoard(vector<vector<int>> playerTurnSelects, vector<int> numberSelected, vector<int> rightInRightVector, vector<int> rightInWrongVector, int turn) {

	for (size_t i = 0; i < turn; i++)
	{
		cout << " " << termcolor::green << rightInRightVector[i] << termcolor::reset << " |  ";
		for (size_t j = 0; j < numberSelected.size(); j++)
		{
			cout << playerTurnSelects[i][j] << setw(4);
		}
		cout << " | " << termcolor::red << rightInWrongVector[i] << termcolor::reset << endl;
	}
	cout << endl;
}

void winCondition(vector<int> playerSelected, vector<int> numberSelected, bool& run) {

	int winCount{};

	for (size_t i = 0; i < numberSelected.size(); i++)
	{
		if (playerSelected[i] == numberSelected[i])
			winCount++;
	}
	
	if (winCount == numberSelected.size())
	{
		cout << endl;
		cout << "You got it!!!" << endl;
		system("pause > 0");
		run = false;
	}
}