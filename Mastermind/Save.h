#pragma once
#include "Includes.h"

void save() {

	system("cls");

	vector<string> usersName{};
	string usersNameTemp{};
	vector<string> usersData{};
	string usersDataTemp{};

	cout << "Name: ";
	cin >> usersNameTemp;

	cout << "Data: ";
	cin >> usersDataTemp;

	usersName.push_back(usersNameTemp);
	usersData.push_back(usersDataTemp);

	fstream Users("Users", ios::in | ios::app | ios::out);

	for (size_t i = 0; i < usersName.size(); i++)
	{
		Users << usersName[i] << endl;
		Users << usersData[i] << endl;
		Users << endl;
	}

	Users.close();
}