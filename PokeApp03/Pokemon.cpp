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