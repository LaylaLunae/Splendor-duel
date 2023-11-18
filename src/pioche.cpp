#include <iostream>
//#include "../include/pioche.h"
#include "../include/jeu.h"
/*

Pioche::Pioche(int np, int mcr, int mcp):numero_pioche(np),
                                         max_cartes_revelees(mcr), max_cartes_pioche(mcp){
    cartes_dans_pioche = new const CarteJoaillerie*[mcp];
    cartes_dehors = new const CarteJoaillerie*[mcr];

    for (int i = 0; i < mcp; ++i) {
        cartes_dans_pioche[i] = new CarteJoaillerie(i); // A modifier avec CarteJoaillerie
    }
}

Pioche::~Pioche(){
    for (int i = 0; i < max_cartes_pioche; ++i) {
        delete cartes_dans_pioche[i];
    }
    for (int i = 0; i < max_cartes_revelees; ++i) {
        delete cartes_dehors[i];
    }
    delete [] cartes_dans_pioche;
    delete [] cartes_dehors;
}

const CarteJoaillerie * Pioche::joueurPrend(int numero_carte) {
    int i = 0;
    while(cartes_dehors[i]->carte != numero_carte)
        i++;
    const CarteJoaillerie * temp = cartes_dehors[i];
    if (max_cartes_pioche != -1) {
        cartes_dehors[i] = cartes_dans_pioche[max_cartes_pioche-1];
        max_cartes_pioche--;
    }
    return temp;
}

void Pioche::distribution(){ // ne servira que pour la création de partie
    int i = 0;
    while (i < max_cartes_revelees && max_cartes_pioche != -1) {
        cartes_dehors[i] = cartes_dans_pioche[max_cartes_pioche-1];
        max_cartes_pioche--;
        i++;
    }
}

 */