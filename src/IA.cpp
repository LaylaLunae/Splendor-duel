
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




// Fonction auxiliaire pour trouver les combinaisons de jetons à partir d'une position donnée
std::vector<const Jeton*> trouverCombinaisons(Plateau plateau, unsigned int x, unsigned int y, unsigned int dx, unsigned int dy, unsigned int nombreDeJetons) {
    std::vector<const Jeton*> combinaisons;

    for (unsigned int i = 0; i < nombreDeJetons; ++i) {
        unsigned int posX = x + i * dx;
        unsigned int posY = y + i * dy;

        // Vérifier que les coordonnées sont valides
        if (posX >= plateau.getNombreJetonsParCoteDePlateau() || posY >= plateau.getNombreJetonsParCoteDePlateau()) {
            break;
        }

        const Jeton* jeton = plateau.getJetons()[posY * plateau.getNombreJetonsParCoteDePlateau() + posX];

        // Vérifier s'il y a un jeton à cette position
        if (jeton != nullptr) {
            combinaisons.push_back(jeton);
        } else {
            // S'il y a une case vide, la combinaison est invalide
            combinaisons.clear();
            break;
        }
    }

    return combinaisons;
}

// Fonction pour vérifier la présence d'une combinaison de jetons de 2
std::vector<std::vector<const Jeton*>> trouverCombinaisonsDeDeux(Plateau plateau) {

    std::vector<std::vector<const Jeton*>> combinaisonsDeDeux;

    // Parcours de toutes les positions du plateau
    for (unsigned int y = 0; y < plateau.getNombreJetonsParCoteDePlateau(); ++y) {
        for (unsigned int x = 0; x < plateau.getNombreJetonsParCoteDePlateau(); ++x) {
            // Trouver les combinaisons horizontales
            std::vector<const Jeton*> combinaisonsHorizontales = trouverCombinaisons(plateau, x, y, 1, 0, 2);
            if (!combinaisonsHorizontales.empty()) {
                combinaisonsDeDeux.push_back(combinaisonsHorizontales);
            }

            // Trouver les combinaisons verticales
            std::vector<const Jeton*> combinaisonsVerticales = trouverCombinaisons(plateau, x, y, 0, 1, 2);
            if (!combinaisonsVerticales.empty()) {
                combinaisonsDeDeux.push_back(combinaisonsVerticales);
            }

            // Trouver les combinaisons diagonales
            std::vector<const Jeton*> combinaisonsDiagonales1 = trouverCombinaisons(plateau, x, y, 1, 1, 2);
            if (!combinaisonsDiagonales1.empty()) {
                combinaisonsDeDeux.push_back(combinaisonsDiagonales1);
            }

            std::vector<const Jeton*> combinaisonsDiagonales2 = trouverCombinaisons(plateau, x, y, 1, -1, 2);
            if (!combinaisonsDiagonales2.empty()) {
                combinaisonsDeDeux.push_back(combinaisonsDiagonales2);
            }
        }
    }

    return combinaisonsDeDeux;
}

// Fonction pour vérifier la présence d'une combinaison de jetons de 3
std::vector<std::vector<const Jeton*>> trouverCombinaisonsDeTrois(const Plateau& plateau) {
    std::vector<std::vector<const Jeton*>> combinaisonsDeTrois;

    // Parcours de toutes les positions du plateau
    for (unsigned int y = 0; y < plateau.getNombreJetonsParCoteDePlateau(); ++y) {
        for (unsigned int x = 0; x < plateau.getNombreJetonsParCoteDePlateau(); ++x) {
            // Trouver les combinaisons horizontales
            std::vector<const Jeton*> combinaisonsHorizontales = trouverCombinaisons(plateau, x, y, 1, 0, 3);
            if (!combinaisonsHorizontales.empty()) {
                combinaisonsDeTrois.push_back(combinaisonsHorizontales);
            }

            // Trouver les combinaisons verticales
            std::vector<const Jeton*> combinaisonsVerticales = trouverCombinaisons(plateau, x, y, 0, 1, 3);
            if (!combinaisonsVerticales.empty()) {
                combinaisonsDeTrois.push_back(combinaisonsVerticales);
            }

            // Trouver les combinaisons diagonales
            std::vector<const Jeton*> combinaisonsDiagonales1 = trouverCombinaisons(plateau, x, y, 1, 1, 3);
            if (!combinaisonsDiagonales1.empty()) {
                combinaisonsDeTrois.push_back(combinaisonsDiagonales1);
            }

            std::vector<const Jeton*> combinaisonsDiagonales2 = trouverCombinaisons(plateau, x, y, 1, -1, 3);
            if (!combinaisonsDiagonales2.empty()) {
                combinaisonsDeTrois.push_back(combinaisonsDiagonales2);
            }
        }
    }

    return combinaisonsDeTrois;
}

/*

combien de jetons ?
si 1 : est ce que la combinaisons de 1 existe si oui : piocher de maniere random sur le plateau
si 2 : est ce que le vector combinaisaiosn de deux est vide
        alors si combinaisons de 1 vide
            remplir le plateau
            et chosir de manire random 1, 2, ou 3
Si 3 : si le vecotd de conmbinaisaon de 3 est vide verifer dans 3 si deux vide verifier dans 1 si 1 vide remplir le tableau
    sinon suffle et pop la denrier combinainson.
*/

