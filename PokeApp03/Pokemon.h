#pragma once
#include <string>

using namespace std;

struct Pokemon {
    string name;
    string type;
    int number;

    Pokemon* next;
    Pokemon* previous;
};

//CRUD
Pokemon* GetPokemonList();
Pokemon* CreateNewPokemon(string name, string type, string number);

void insertNewPokemon(Pokemon* newPokemon);


