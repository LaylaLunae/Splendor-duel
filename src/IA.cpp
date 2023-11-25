
#include <iostream>
#include "../include/jeu.h"

#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()

int IA::choisirChoix(int min, int max) {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int choix = rand() % max + 1;

    if (choix < min || choix > max) {
        choix = choisirChoix(min, max);
    }
    return choix;
}

/*
void IA::prendreJetonsAleatoires(Plateau* plateau) {
    int nombreJetonsAChoisir = rand() % 3 + 1;

    for (int i = 0; i < nombreJetonsAChoisir; ++i) {
        // Générez des coordonnées aléatoires pour choisir un jeton sur le plateau
        int positionX = rand() % 5 + 1;
        int positionY = rand() % 5 + 1;

        try {
            const Jeton* jeton = plateau->prendreJeton(positionX, positionY);
        } catch (PlateauException& e) {.
            std::cout << e.get_info() << std::endl;
        }
    }
}

 */