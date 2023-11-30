#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "pioche.h"
#include "jeu.h"

Pioche::Pioche(int np, int mcr, int mcp):numero_pioche(np),
                                         max_cartes_revelees(mcr), max_cartes_pioche(mcp){
    cartes_dans_pioche = new const CarteJoaillerie*[mcp];
    cartes_dehors = new const CarteJoaillerie*[mcr];

    for (int i = 0; i < mcp; ++i) {
        cartes_dans_pioche[i] = nullptr;
    }
    for (int i = 0; i < mcr; ++i) {
        cartes_dehors[i] = nullptr;
    }
}

Pioche::~Pioche(){
    for (int i = 0; i < max_cartes_pioche; i++) {
        delete cartes_dans_pioche[i];
    }
    for (int i = 0; i < max_cartes_revelees; i++) {
        delete cartes_dehors[i];
    }
    delete [] cartes_dans_pioche;
    delete [] cartes_dehors;
}

const CarteJoaillerie * Pioche::joueurPrend(int numero_carte) {
    int i = 0;
    while(cartes_dehors[i]->getID() != numero_carte) {
        std::cout << cartes_dehors[i]->getID() << "\n";
        i++;
    }
    std::cout << "Passe\n";
    const CarteJoaillerie * temp = cartes_dehors[i];
    if (max_cartes_pioche != -1) {
        std::srand(std::time(0));
        int nombreAleatoire = std::rand() % max_cartes_pioche;
        cartes_dehors[i] = cartes_dans_pioche[nombreAleatoire];
        cartes_dans_pioche[nombreAleatoire] = cartes_dans_pioche[max_cartes_pioche-1];
        max_cartes_pioche--;
    }
    return temp;
}

void Pioche::distribution(){ // ne servira que pour la création de partie
    int i = 0;
    while (i < max_cartes_revelees && max_cartes_pioche != -1) {
        std::srand(std::time(0));
        int nombreAleatoire = std::rand() % max_cartes_pioche;
        cartes_dehors[i] = cartes_dans_pioche[nombreAleatoire];
        cartes_dans_pioche[nombreAleatoire] = cartes_dans_pioche[max_cartes_pioche-1];
        max_cartes_pioche--;
        i++;
    }
}

const CarteJoaillerie * Pioche::joueurPrendPioche() {
    std::srand(std::time(0));
    int nombreAleatoire = std::rand() % max_cartes_pioche;
    const CarteJoaillerie * temp = cartes_dans_pioche[nombreAleatoire];
    cartes_dans_pioche[nombreAleatoire] = cartes_dans_pioche[max_cartes_pioche-1];
    max_cartes_pioche--;
    return temp;
}

void Pioche::afficherPioche(std::ostream& f){
    f << "Cartes dans pioche " << numero_pioche << ":\n";
    for (int i = 0; i < max_cartes_pioche; i++)
        f << "Carte : " << cartes_dans_pioche[i]->getID() << "\n";
    f << "\n";
}

void Pioche::afficherCartesRevelees(std::ostream &f) {
    f << "Cartes sur le plateau de la pioche " << numero_pioche << ":\n";
    for (int i = 0; i < max_cartes_revelees; i++)
        f << "Carte : " << cartes_dehors[i]->getID() << "\n";
    f << "\n";
}