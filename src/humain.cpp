
#include <iostream>
#include "../include/jeu.h"

int Humain::choisirChoixUtilisateur(int min, int max) {
    int choix;
    //std::cout << "Veuillez entrer un nombre entre " << min << " et " << max << ": ";  à mettre dans Jeu : mécanisme tour par tour
    std::cin >> choix;

    while (choix < min || choix > max) {
        std::cout << "Saisie invalide. Le nombre doit être entre " << min << " et " << max << ".\n";

        std::cout << "Veuillez entrer un nombre entre " << min << " et " << max << ": ";
        std::cin >> choix;
    }
    return choix;
}