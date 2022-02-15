// console_app_class_practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include<iostream>
#include<string>

using namespace std;

const int MAX_PLAYERS = 2;

struct Player {
	char playerNickname[6];
	char characterName[6];
	int score;
	int level;
};

Player newPlayer[10];
int playerCounter = 0;

void displayMainMission();
void displayLeaderBoard();
void displayMultiplayer();
void capturePlayerGameInfo();
void displayPlayerGameInfo(int currentPlayer);
void Menugame();
void Missiongame();

int main()
{
	int opc = 0;
	Menugame();
}

void displayLeaderBoard()
{
	cout << "****LEADERBOARD****" << endl << endl;
	cout << "PLAYER\tSCORE" << endl;
	for (int i = 0; i < playerCounter; i++)
	{
		cout << newPlayer[i].playerNickname << "\t" << newPlayer[i].score << endl;
	}
}

void displayMainMission()
{
	Missiongame();
}

void displayMultiplayer()
{
	system("cls");
	//cout << "Mission 1....The island of the...." << endl;
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		cout << "Player" << i + 1 << " choose a character: " << endl;
		cout << "1. Marco" << endl;
		cout << "2. Tarma" << endl;
		cout << "3. Eris" << endl;
		cout << "4. Chris" << endl;

		int opc = 0;
		cout << "Select an option: " << endl;
		cin >> opc;

		switch (opc)
		{
		case 1:
			strcpy_s(newPlayer[playerCounter].characterName, "Marco");
			capturePlayerGameInfo();
			break;
		case 2:
			strcpy_s(newPlayer[playerCounter].characterName, "Tarma");
			capturePlayerGameInfo();
			break;
		case 3:
			strcpy_s(newPlayer[playerCounter].characterName, "Eris");
			capturePlayerGameInfo();
			break;
		case 4:
			strcpy_s(newPlayer[playerCounter].characterName, "Chris");
			capturePlayerGameInfo();
			break;
		default:
			cout << "Invalid option. Select an option within a range [1-4]" << endl;
			break;
		}
		playerCounter++;
	}
	displayPlayerGameInfo(playerCounter - 2);
	displayPlayerGameInfo(playerCounter - 1);
	return;
}

void capturePlayerGameInfo()
{
	cout << "Insert your score: " << endl;
	cin >> newPlayer[playerCounter].score;
	newPlayer[playerCounter].level = newPlayer[playerCounter].score / 1000;

	cout << "What is your name? " << endl;
	cin.ignore();
	cin.getline(newPlayer[playerCounter].playerNickname, 6);
}

void displayPlayerGameInfo(int currentPlayer)
{
	cout << newPlayer[currentPlayer].playerNickname << " played with "
		<< newPlayer[currentPlayer].characterName << " and has a score of "
		<< newPlayer[currentPlayer].score << " and reached to the "
		<< newPlayer[currentPlayer].level << " level." << endl;
}

void Menugame()
{
	int opc = 0;
	do {
		system("cls");
		cout << "METAL SLUG 3" << endl << endl;
		cout << "1. Main mission" << endl;
		cout << "2. Multiplayer" << endl;
		cout << "3. Leaderboards" << endl;
		cout << "4. Quit game" << endl;
		cout << "Select an option: " << endl;
		cin >> opc;

		switch (opc)
		{
		case 1:
			displayMainMission();
			system("pause");
			break;
		case 2:
			displayMultiplayer();
			system("pause");
			break;
		case 3:
			system("cls");
			displayLeaderBoard();
			system("pause");
			break;
		case 4:
			system("cls");
			cout << "Thanks for playing Metal Slug 3 :)" << endl;
			break;
		default:
			cout << "Invalid option. Select an option within a range [1-4]" << endl;
		}
	} while (opc != 4);
}
void Missiongame()
{
	system("cls");
	//cout << "Mission 1....The island of the...." << endl;
	cout << "Choose a character: " << endl;
	cout << "1. Marco" << endl;
	cout << "2. Tarma" << endl;
	cout << "3. Eris" << endl;
	cout << "4. Chris" << endl;

	int opc = 0;
	cout << "Select an option: " << endl;
	cin >> opc;

	switch (opc)
	{
	case 1:
		strcpy_s(newPlayer[playerCounter].characterName, "Marco");
		capturePlayerGameInfo();
		break;
	case 2:
		strcpy_s(newPlayer[playerCounter].characterName, "Tarma");
		capturePlayerGameInfo();
		break;
	case 3:
		strcpy_s(newPlayer[playerCounter].characterName, "Eris");
		capturePlayerGameInfo();
		break;
	case 4:
		strcpy_s(newPlayer[playerCounter].characterName, "Chris");
		capturePlayerGameInfo();
		break;
	default:
		cout << "Invalid option. Select an option within a range [1-4]" << endl;
		break;
	}

	displayPlayerGameInfo(playerCounter);
	playerCounter++;

	return;
}