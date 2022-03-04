// console_app_class_practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string characterNames[5] = {
	{"Fio"},
	{"Mario"},
	{"Arthemys"},
	{"Zeus"},
	{"Kirby"}
};

struct PlayerInfo {
	string playerName;
	string characterName;
	int score;
	int level;

	PlayerInfo* previous;
	PlayerInfo* next;
};

const int EXIT_OPTION = 10;
//arreglo de jugadores
//PlayerInfo players[10];
//lista doble de jugadores

PlayerInfo* INICIO_LISTA;

//int playerCounter = 0;

void displayCharacterNames();
void displayPlayerInfo(int currentPlayer);
void displayPlayerInfo(PlayerInfo* player);

PlayerInfo* createNewPlayer(string playerName, string characterName, int score);
void insertNewPlayerToTheList(PlayerInfo* player);
void enterNewPlayer(string title);
PlayerInfo* searchPlayerByName(string playerName);
void printPlayerList();

int main()
{
	/*PlayerInfo* newPlayer1 = createNewPlayer("ray", "fox", 1000);
	PlayerInfo* newPlayer2 = createNewPlayer("angy", "peach", 1230);
	PlayerInfo* newPlayer3 = createNewPlayer("robert", "pichu", 12309);

	insertNewPlayerToTheList(newPlayer1);
	insertNewPlayerToTheList(newPlayer2);
	insertNewPlayerToTheList(newPlayer3);*/

	fstream readStream;
	readStream.open("playersData.bin", ios::in | ios::binary | ios::ate);
	int totalSizeInByte = readStream.tellg();
	for (int i = 0; i < (totalSizeInByte / sizeof(PlayerInfo)); i++)
	{
		PlayerInfo* tempPlayerFromFile = new PlayerInfo;
		readStream.seekg(i * sizeof(PlayerInfo));
		readStream.read((char*)tempPlayerFromFile, sizeof(PlayerInfo));
		insertNewPlayerToTheList(tempPlayerFromFile);
		//playerCounter++;
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
			enterNewPlayer("Player 1");
			//playerCounter++;
			system("pause");
		}
		break;
		case 2:
		{
			/*int characterP1 = 0;
			int characterP2 = 0;*/

			system("cls");
			cout << "Multiplayer" << endl << endl;
			//displayCharacterNames();

			////Input data from player 1
			//cout << "Player 1, choose your character: ";
			//cin >> characterP1;
			//players[playerCounter].characterName = characterNames[characterP1 - 1];

			//cout << "What is your name?" << endl;
			//cin.ignore();
			//getline(cin,players[playerCounter].playerName);

			//cout << "Enter your score: " << endl;
			//cin >> players[playerCounter].score;

			//cout << "Player 2, choose your character: ";
			//cin >> characterP2;
			//players[playerCounter + 1].characterName = characterNames[characterP2 - 1];

			//cout << "What is your name?" << endl;
			////cin.ignore();
			//getline(cin, players[playerCounter + 1].playerName);

			//cout << "Enter your score: " << endl;
			//cin >> players[playerCounter + 1].score;

			//players[playerCounter].level = players[playerCounter].score / 1000;
			//players[playerCounter + 1].level = players[playerCounter + 1].score / 1000;

			////Print message for player 1
			//displayPlayerInfo(playerCounter);
			////Print message for player 2
			//displayPlayerInfo(playerCounter + 1);
			//playerCounter += 2;
			for (int i = 0; i < 2; i++)
			{
				string title = "Player ";
				title.append(to_string(i + 1));
				enterNewPlayer(title);
			}

			system("pause");
		}
		break;
		case 3:
		{
			system("cls");
			cout << "****LEADERBOARD****" << endl << endl;
			if (INICIO_LISTA == NULL)
			{
				cout << "NO RECORDS" << endl << endl;
				system("pause");
				system("cls");
				break;
			}
			
			cout << "PLAYER \t SCORE" << endl;
			PlayerInfo* aux = INICIO_LISTA;


			while (aux != NULL)
			{
				cout << aux->playerName << "\t" << aux->score << endl;
				aux = aux->next;
			}

			/*for (int i = 0; i < playerCounter; i++)
			{
				cout << players[i].playerName << "\t"
					<< players[i].score << endl;
			}*/

			system("pause");
		}
		break;
		case 4:
		{
			system("cls");
			cout << "****Find a player****" << endl << endl;
			
			printPlayerList();
			string playerToBeFound;
			cout << "Which player do you want to find? ";
			cin.ignore();
			getline(cin,playerToBeFound);

			PlayerInfo* foundPlayer = searchPlayerByName(playerToBeFound);
			if (foundPlayer == NULL)
			{
				cout << "NO PLAYER EXISTS WITH NAME = " << playerToBeFound;
			}
			else {
				displayPlayerInfo(foundPlayer);
			}
			//aux = INICIO_LISTA;
			//while (aux != NULL)
			////for (int i = 0; i < playerCounter; i++)
			//{
			//	if (playerToBeFound == aux->playerName)
			//	{
			//		displayPlayerInfo(aux);
			//	}
			//	aux = aux->next;
			//}
			system("pause");
		}
			break;
		case 5:
		{
			system("cls");
			cout << "**** Edit a player ****" << endl << endl;
			printPlayerList();

			string playerToBeFound;
			cout << "Which player do you want to edit? ";
			cin >> playerToBeFound;

			PlayerInfo* foundPlayer = searchPlayerByName(playerToBeFound);
			if (foundPlayer == NULL)
			{
				cout << "NO PLAYER EXISTS WITH NAME = " << playerToBeFound;
			}
			else {
				cout << "Enter your score: " << endl;
				cin >> foundPlayer->score;
				foundPlayer->level = foundPlayer->score / 1000;
			}

			/*for (int i = 0; i < playerCounter; i++)
			{
				if (playerToBeFound == players[i].playerName)
				{
					cout << "Enter your score: " << endl;
					cin >> players[i].score;
					players[i].level = players[i].score / 1000;
				}
			}*/
			system("pause");
		}
			break;
		case 6:
		{
			system("cls");
			cout << "****Delete a player****" << endl << endl;
			/*cout << "List of players" << endl;
			for (int i = 0; i < playerCounter; i++)
			{
				cout << players[i].playerName << endl;
			}*/
			printPlayerList();

			string playerToBeDeleted;
			cout << "Which player do you want to edit? ";
			cin >> playerToBeDeleted;

			PlayerInfo* foundPlayer = searchPlayerByName(playerToBeDeleted);
			if (foundPlayer == NULL)
			{
				cout << "NO PLAYER EXISTS WITH NAME = " << playerToBeDeleted;
			}
			else {
				PlayerInfo* aux = INICIO_LISTA;
				//Eliminar un nodo que esta al inicio de la lista
				if (foundPlayer == INICIO_LISTA)
				{
					INICIO_LISTA = INICIO_LISTA->next;
					INICIO_LISTA->previous = NULL;
				}				
				//eliminar el nodo que esta al final de la lista
				else if (foundPlayer->next == NULL)
				{
					aux = foundPlayer->previous;
					aux->next = NULL;
				}
				//eliminar el nodo que esta en medio de la lista
				else {
					PlayerInfo* previousNode = foundPlayer->previous;
					PlayerInfo* nextNode = foundPlayer->next;

					previousNode->next = nextNode;
					nextNode->previous = previousNode;
				}
				delete foundPlayer;
			}

			/*for (int i = 0; i < playerCounter; i++)
			{
				if (playerToBeDeleted == players[i].playerName)
				{
					players[i].playerName = "";
					players[i].characterName = "";
					players[i].score = 0;
					players[i].level = 0;

					for (int j = i + 1; j < playerCounter; j++)
					{
						players[j - 1] = players[j];
					}
					playerCounter--;
				}
			}*/
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
	PlayerInfo* tempAux = INICIO_LISTA;
	while (tempAux != NULL)
	{
		archivo.write((char*)tempAux, sizeof(PlayerInfo));
		tempAux = tempAux->next;
	}
	
	/*for (int i = 0; i < playerCounter; i++)
	{
		archivo.write((char*)&players[i], sizeof(PlayerInfo));
	}*/
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
	/*cout << "Player " << players[currentPlayer].playerName << " chose ";
	cout << players[currentPlayer].characterName;
	cout << ", scored " << players[currentPlayer].score
		<< " points and reached to " << players[currentPlayer].level
		<< " level." << endl;*/
}

void displayPlayerInfo(PlayerInfo* player)
{
	cout << "Player " << player->playerName << " chose ";
	cout << player->characterName;
	cout << ", scored " << player->score
		<< " points and reached to " << player->level
		<< " level." << endl;
}

PlayerInfo* createNewPlayer(string playerName, string characterName, int score)
{
	//reservar memoria para un nuevo nodo
	PlayerInfo* newPlayer = new PlayerInfo;
	//guardar datos en los miembros del nodo
	newPlayer->playerName = playerName;
	newPlayer->characterName = characterName;
	newPlayer->score = score;
	newPlayer->level = newPlayer->score / 1000;

	newPlayer->next = NULL;
	newPlayer->previous = NULL;

	return newPlayer;
}

void insertNewPlayerToTheList(PlayerInfo* player)
{
	//insertar cuando la lista esta vacia
	if (INICIO_LISTA == NULL)
	{
		INICIO_LISTA = player;
	}
	//insertar cuando la lista ya tiene datos
	else {
		//insertamos un nuevo nodo al final de la lista
		PlayerInfo* aux = INICIO_LISTA;
		while(aux->next != NULL)
			aux = aux->next;

		aux->next = player;
		player->previous = aux;
	}
}


void enterNewPlayer(string title)
{
	//reservando memoria para almacenar datos en un nodo tipo PlayerInfo
		//PlayerInfo* newPlayer = new PlayerInfo;
	
	int character = 0;
	string tempPlayerName;
	int tempScore;

	cout << title << endl;

	displayCharacterNames();
	cout << "Choose a character: ";
	cin >> character;
	//players[playerCounter].characterName = characterNames[character - 1];
	//newPlayer->characterName = characterNames[character - 1];


	cout << "What is your name?" << endl;
	cin.ignore();
	//getline(cin, players[playerCounter].playerName);
	//getline(cin, newPlayer->playerName);
	getline(cin, tempPlayerName);

	cout << "Enter your score: " << endl;
	//cin >> players[playerCounter].score;
	//cin >> newPlayer->score;
	cin >> tempScore;

	//players[playerCounter].level = players[playerCounter].score / 1000;
	//newPlayer->level = newPlayer->score / 1000;

	PlayerInfo* newPlayer =
		createNewPlayer(
			tempPlayerName,
			characterNames[character - 1],
			tempScore);
	//agregando un nodo a la lista
	//INICIO_LISTA = newPlayer;
	insertNewPlayerToTheList(newPlayer);
	//displayPlayerInfo(playerCounter);
	displayPlayerInfo(newPlayer);
}

PlayerInfo* searchPlayerByName(string playerToBeFound)
{
	PlayerInfo* aux = INICIO_LISTA;
	while (aux != NULL)
	{
		if (playerToBeFound == aux->playerName)
		{
			return aux;
		}
		aux = aux->next;
	}
	return NULL;
}

void printPlayerList()
{
	cout << "List of players" << endl;
	PlayerInfo* aux = INICIO_LISTA;
	while (aux != NULL)
	{
		cout << aux->playerName << endl;
		aux = aux->next;
	}
}