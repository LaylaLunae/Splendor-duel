
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
