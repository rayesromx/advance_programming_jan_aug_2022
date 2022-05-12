#include "Pokemon.h"

Pokemon* PokeList = NULL;

Pokemon* GetPokemonList()
{
	return PokeList;
}

void insertNewPokemon(Pokemon* newPokemon)
{
    if (GetPokemonList() == NULL)
    {
        PokeList = newPokemon;
    }
    else
    {
        Pokemon* lastPokemon = GetPokemonList();
        while (lastPokemon->next != NULL)
            lastPokemon = lastPokemon->next;

        lastPokemon->next = newPokemon;
        newPokemon->previous = lastPokemon;
    }
}

Pokemon* CreateNewPokemon(string name, string type, string number)
{
    Pokemon* newPokemon = new Pokemon;
    newPokemon->name = name;
    newPokemon->type = type;
    newPokemon->number = atoi(number.c_str());
    newPokemon->next = NULL;
    newPokemon->previous = NULL;
    return newPokemon;
}

void savePkmnFile()
{
    fstream archivo;
    archivo.open("pkmn.bin", ios::out | ios::binary);

    Pokemon* lastPokemon = GetPokemonList();
    while (lastPokemon != NULL)
    {
        archivo.write((char*)lastPokemon, sizeof(Pokemon));
        lastPokemon = lastPokemon->next;
    }
    archivo.close();
}

void openPkmnFile()
{
    fstream archivo;
    archivo.open("pkmn.bin", ios::in | ios::binary | ios::ate);
    int totalSizeInByte = archivo.tellg();//50
    int totalPokemons = totalSizeInByte / sizeof(Pokemon);// 50 / 5 = 10 
    for (int i = 0; i < totalPokemons; i++)
    {
        Pokemon* aux = new Pokemon;
        archivo.seekg(i * sizeof(Pokemon));
        archivo.read((char*)aux, sizeof(Pokemon));
        insertNewPokemon(aux);
    }
    archivo.close();
}