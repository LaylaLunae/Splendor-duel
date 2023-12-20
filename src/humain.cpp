
#include <iostream>
#include "../include/jeu.h"
// cette fonction une définition pour la classe humain, elle est override et permet de savoir si le choiix choisit par l'utilisateur est bien compris entre la borne min et max, elle renvoie le choix.
int Humain::choisirChoix(int min, int max) {
    int choix;
    std::cin >> choix;
    while (choix < min || choix > max) {
        std::cout << "Saisie invalide. Le nombre doit être entre " << min << " et " << max << ".\n";

        std::cout << "Veuillez entrer un nombre entre " << min << " et " << max << ": ";
        std::cin >> choix;
    }
    return choix;
}