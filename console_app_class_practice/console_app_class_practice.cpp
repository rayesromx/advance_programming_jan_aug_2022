
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//int score = 0;
//int option2 = 0;
//char playerName[5];

//int player1character1 = 0;
//int player1score1 = 0;
//char player1name1[5];
//
//int player2character2 = 0;
//int player2score2 = 0;
//char player2name2[5];

const int MAX_PLAYERS_ALLOWED = 4;

struct Player {
    int level;
    char name[10];
    int score;
    char characterName[10];
};

Player players[10];
int playerCounter = 0;

void inputPlayerData(int currentPlayer, int playerNumber);
void displayCharacterList();

int main()
{
    fstream playerFileToRead;
    playerFileToRead.open("playerData.bin", ios::in | ios::binary | ios::ate);
    int totalFileSize = playerFileToRead.tellg();

    for (int i = 0; i < (totalFileSize / sizeof(Player)); i++, playerCounter++)
    {
        playerFileToRead.seekg(i * sizeof(Player));
        playerFileToRead.read((char*)&players[i], sizeof(Player));
    }
    
    playerFileToRead.close();
    

    int option = 0;
    do {
        system("cls");
        //Print the 4 main options
        cout << "METAL SLUG 3" << endl << endl;
        cout << "1. Main Mission" << endl;
        cout << "2. Multiplayer" << endl;
        cout << "3. Leaderboard" << endl;
        cout << "4. Delete a player" << endl;
        cout << "5. Edit a player" << endl;
        cout << "6. Find a player" << endl;
        cout << "10. Quit game" << endl;

        cout << "Select an option: " << endl;
        cin >> option;

        switch (option)
        {
        case 1:
        {
            system("cls");
            int option2 = 0;
            cout << "Main Mission" << endl << endl;
            displayCharacterList();
            inputPlayerData(playerCounter, 1);
            playerCounter++;
        }
        break;
        case 2:
        {
            cout << "Multiplayer" << endl << endl;
            displayCharacterList();
            for (int i = 0; i < MAX_PLAYERS_ALLOWED; i++)
            {
                inputPlayerData(playerCounter + i, i + 1);
            }
            system("pause");
            playerCounter += 4;
        }
        break;
        case 3:
        {
            system("cls");
            cout << "********LEADERBOARD********" << endl << endl;
            cout << "PLAYER --- SCORE -- LEVEL" << endl;
            for (int i = 0; i < playerCounter; i++)
            {
                cout << players[i].name << " --- "
                    << players[i].score << " --- "
                    << players[i].level << endl;
            }
            system("pause");
        }
        break;
        case 4:
        {
            cout << "Delete a player" << endl << endl;
            char playerToBeDeleted[10];

            cout << "Enter the name of the player to be deleted: ";
            cin >> playerToBeDeleted;

            bool isPlayerDeleted = true;

            for (int i = 0; i < playerCounter; i++)
            {
                if (strcmp(players[i].name,playerToBeDeleted) == 0)
                {
                    //en este bloque de codigo vamos a eliminar el elemento del arreglo
                    strcpy_s(players[i].name, "");
                    strcpy_s(players[i].characterName, "");
                    players[i].score = 0;
                    players[i].level = 0;

                    for (int j = i + 1; j < playerCounter; j++)
                    {
                        players[j - 1] = players[j];
                    }
                    playerCounter--;
                    isPlayerDeleted = false;
                }
            }

            if(isPlayerDeleted)
                cout << "Player " << playerToBeDeleted << " does not exists";
            system("pause");
        }
        break;
        case 5:
        {
            char playerToBeEdited[10];
            cout << "Edit a player" << endl << endl;

            cout << "Enter the name of the player to be edited: ";
            cin >> playerToBeEdited;
            for (int i = 0; i < playerCounter; i++)
            {
                if (strcmp(players[i].name, playerToBeEdited) == 0)
                {
                    //en este bloque de codigo vamos a editar el elemento del arreglo
                    inputPlayerData(i, i + 1);
                }
            }
        }
            break;
        case 6:
        {
            //Player Fulanito chose "Charactername" and scored "score", reached to the level "level"!!!!
            char playerToBeFound[10];
            cout << "Find a player" << endl << endl;

            cout << "Enter the name of the player to be found: ";
            cin >> playerToBeFound;
            for (int i = 0; i < playerCounter; i++)
            {
                if (strcmp(players[i].name, playerToBeFound) == 0)
                {
                    //en este bloque de codigo vamos a mostrar el elemento del arreglo encontrado
                    cout << "Player " << players[i].name
                        << " chose " << players[i].characterName
                        << " and scored " << players[i].score
                        << ", reched to the level " << players[i].level
                        << "!!!!!!!" << endl;
                }
            }
            system("pause");
        }
        break;
        case 10:
            cout << "Thanks for playing Metal slug 3." << endl;
            system("pause");
            break;
        default:
            cout << "That option is not available...Select a valid option." << endl;
            system("pause");

        }
    } while (option != 10);

    fstream playerFileToWrite;
    playerFileToWrite.open("playerData.bin", ios::out | ios::binary);
    //ios::trunc -> elimina el contenido del archivo
    //ios::app -> app = append / agrega contenido al archivo
    for (int i = 0; i < playerCounter; i++)
    {
        playerFileToWrite.write((char*)&players[i], sizeof(Player));
    }
    
    playerFileToWrite.close();
}


void inputPlayerData(int currentPlayer, int playerNumber)
{
    int player1character1 = 0;
    cout << "Player " << playerNumber << " choose your character: " << endl;
    cin >> player1character1;
    cout << "Player " << playerNumber << ", what is your score? " << endl;
    cin >> players[currentPlayer].score;
    cout << "Player " << playerNumber << ", enter your name: ";
    cin.ignore();
    cin.getline(players[currentPlayer].name, 5);

    players[currentPlayer].level = players[currentPlayer].score / 1000;

    switch (player1character1)
    {
    case 1: strcpy_s(players[currentPlayer].characterName, "Fio"); break;
    case 2: strcpy_s(players[currentPlayer].characterName, "Pancho"); break;
    case 3: strcpy_s(players[currentPlayer].characterName, "Kirby"); break;
    case 4: strcpy_s(players[currentPlayer].characterName, "Zelda"); break;
    }
}

void displayCharacterList()
{
    cout << "1. Fio" << endl;
    cout << "2. Pancho" << endl;
    cout << "3. Kirby" << endl;
    cout << "4. Zelda" << endl;
}
