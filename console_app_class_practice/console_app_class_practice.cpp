// console_app_class_practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;
char characterNames[5][10] = {
	{"Fio"},
	{"Mario"},
	{"Arthemys"},
	{"Zeus"},
	{"Kirby"}
};

struct PlayerInfo {
	char playerName[5];
	char characterName[10];
	int score;
	int level;
};
const int EXIT_OPTION = 10;
PlayerInfo players[10];
int playerCounter = 0;

void displayCharacterNames();
void displayPlayerInfo(int currentPlayer);

int main()
{
	fstream readStream;
	readStream.open("playersData.bin", ios::in | ios::binary | ios::ate);
	int totalSizeInByte = readStream.tellg();
	for (int i = 0; i < (totalSizeInByte / sizeof(PlayerInfo)); i++)
	{
		readStream.seekg(i * sizeof(PlayerInfo));
		readStream.read((char*)&players[i], sizeof(PlayerInfo));
		playerCounter++;
	}
	readStream.close();

	

	int option = 0;

	do {
		cout << "METAL SLUG 3" << endl << endl;
		cout << "1. Main Mission" << endl;
		cout << "2. Multiplayer" << endl;
		cout << "3. Leaderboard" << endl;
		cout << "4. Find a player" << endl;
		cout << "5. Edit a player" << endl;
		cout << "6. Delete a player" << endl;
		cout << EXIT_OPTION << ". Quit game" << endl;
		cout << "Select an option:" << endl;
		cin >> option;

		switch (option)
		{
		case 1:
		{
			system("cls");
			int character = 0;

			cout << "Main mission" << endl << endl;

			displayCharacterNames();

			cout << "Choose a character: ";
			cin >> character;
			strcpy_s(players[playerCounter].characterName, characterNames[character - 1]);

			cout << "What is your name?" << endl;
			cin.ignore();
			cin.getline(players[playerCounter].playerName, 5);

			cout << "Enter your score: " << endl;
			cin >> players[playerCounter].score;

			players[playerCounter].level = players[playerCounter].score / 1000;

			displayPlayerInfo(playerCounter);

			playerCounter++;
			system("pause");
		}
		break;
		case 2:
		{
			int characterP1 = 0;
			int characterP2 = 0;

			system("cls");
			cout << "Multiplayer" << endl << endl;
			displayCharacterNames();

			//Input data from player 1
			cout << "Player 1, choose your character: ";
			cin >> characterP1;
			strcpy_s(players[playerCounter].characterName, characterNames[characterP1 - 1]);

			cout << "What is your name?" << endl;
			cin.ignore();
			cin.getline(players[playerCounter].playerName, 5);

			cout << "Enter your score: " << endl;
			cin >> players[playerCounter].score;

			cout << "Player 2, choose your character: ";
			cin >> characterP2;
			strcpy_s(players[playerCounter + 1].characterName, characterNames[characterP2 - 1]);

			cout << "What is your name?" << endl;
			cin.ignore();
			cin.getline(players[playerCounter + 1].playerName, 5);

			cout << "Enter your score: " << endl;
			cin >> players[playerCounter + 1].score;

			players[playerCounter].level = players[playerCounter].score / 1000;
			players[playerCounter + 1].level = players[playerCounter + 1].score / 1000;

			//Print message for player 1
			displayPlayerInfo(playerCounter);
			//Print message for player 2
			displayPlayerInfo(playerCounter + 1);
			playerCounter += 2;
			system("pause");
		}
		break;
		case 3:
		{
			system("cls");
			cout << "****LEADERBOARD****" << endl << endl;
			cout << "PLAYER \t SCORE" << endl;
			for (int i = 0; i < playerCounter; i++)
			{
				cout << players[i].playerName << "\t"
					<< players[i].score << endl;
			}
			system("pause");
		}
		break;
		case 4:
		{
			system("cls");
			cout << "****Find a player****" << endl << endl;
			cout << "List of players" << endl;
			for (int i = 0; i < playerCounter; i++)
			{
				cout << players[i].playerName<< endl;
			}

			char playerToBeFound[10];
			cout << "Which player do you want to find? ";
			cin >> playerToBeFound;

			for (int i = 0; i < playerCounter; i++)
			{
				if (strcmp(playerToBeFound, players[i].playerName) == 0)
				{
					displayPlayerInfo(i);
				}
			}
			system("pause");
		}
			break;
		case 5:
		{
			system("cls");
			cout << "****Edit a player****" << endl << endl;
			cout << "List of players" << endl;
			for (int i = 0; i < playerCounter; i++)
			{
				cout << players[i].playerName << endl;
			}

			char playerToBeFound[10];
			cout << "Which player do you want to edit? ";
			cin >> playerToBeFound;

			for (int i = 0; i < playerCounter; i++)
			{
				if (strcmp(playerToBeFound, players[i].playerName) == 0)
				{
					cout << "Enter your score: " << endl;
					cin >> players[i].score;
					players[i].level = players[i].score / 1000;
				}
			}
			system("pause");
		}
			break;
		case 6:
		{
			system("cls");
			cout << "****Delete a player****" << endl << endl;
			cout << "List of players" << endl;
			for (int i = 0; i < playerCounter; i++)
			{
				cout << players[i].playerName << endl;
			}

			char playerToBeDeleted[10];
			cout << "Which player do you want to edit? ";
			cin >> playerToBeDeleted;

			for (int i = 0; i < playerCounter; i++)
			{
				if (strcmp(playerToBeDeleted, players[i].playerName) == 0)
				{
					strcpy_s(players[i].playerName, "");
					strcpy_s(players[i].characterName, "");
					players[i].score = 0;
					players[i].level = 0;

					for (int j = i + 1; j < playerCounter; j++)
					{
						players[j - 1] = players[j];
					}
					playerCounter--;
				}
			}
			system("pause");

			system("pause");
		}
			break;
		case EXIT_OPTION:
		{
			cout << "Thanks for playing Metal slug 3" << endl;
			system("pause");
		}
		break;
		default:
			cout << "The selection option is not valid." << endl;
			system("pause");
			break;
		}//end switch

	} while (option != EXIT_OPTION);

	fstream archivo;
	archivo.open("playersData.bin", ios::out | ios::binary);
	for (int i = 0; i < playerCounter; i++)
	{
		archivo.write((char*)&players[i], sizeof(PlayerInfo));
	}
	archivo.close();

}

void displayCharacterNames()
{
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ". " << characterNames[i] << endl;
	}
}

void displayPlayerInfo(int currentPlayer)
{
	cout << "Player " << players[currentPlayer].playerName << " chose ";
	cout << players[currentPlayer].characterName;
	cout << ", scored " << players[currentPlayer].score
		<< " points and reached to " << players[currentPlayer].level
		<< " level." << endl;
}