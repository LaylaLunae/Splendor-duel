#include <iostream>
#include "../include/jeu.h"
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <vector>
#include <algorithm>
#include <random>

class Plateau;

int IA::choisirChoix(int min, int max) {

    //std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int choix = rand() % max + 1;

    if (choix < min || choix > max) {
        choix = choisirChoix(min, max);
    }
    return choix;
}

/* acheter une carte : probleme le type de retour dans obligatoire
std::vector<CarteJoaillerie*> IA::getCartesAchetable(const Pioche& pioche) const {
    std::vector<CarteJoaillerie*> cartesAchetable;

    for (int i = 0; i < pioche.getMaxCartesRevelees(); ++i) {
        const CarteJoaillerie* carte = pioche.getCartesDehors(i);

        if (carte) {
            std::vector<int> difference = Obligatoire::calculDifference((Joueur *) this, carte->getPrix());
            if (Obligatoire::achatPiochePossible((Joueur *) this, difference)) {
                cartesAchetable.push_back(const_cast<CarteJoaillerie*>(carte));
            }
        }
    }
    return cartesAchetable;
}


CarteJoaillerie* IA::melangerEtObtenirDerniereCarte(Pioche& pioche, Joueur& joueur) {
    if (pioche.getMaxCartesRevelees() == 0) {
        return nullptr;
    }

    std::vector<CarteJoaillerie*> cartesAchetable = getCartesAchetable(pioche);

    std::default_random_engine generator;
    std::shuffle(cartesAchetable.begin(), cartesAchetable.end(), generator);

    CarteJoaillerie* derniereCarte = cartesAchetable.back();

    joueur.ajouterCarteJoaillerie(*derniereCarte);

    return derniereCarte;
}
*/


std::vector<std::pair<const Jeton*, const Jeton*>> IA::genererCombinaisonsDeuxJetons(const Plateau& plateau) const {
    std::vector<std::pair<const Jeton*, const Jeton*>> combinaisons;

    for (unsigned int i = 0; i < 5; i++) {
        for (unsigned int j = 0; j < 5; j++) {
            const Jeton* jeton1 = plateau.getJeton(i * 5 + j);

            for (unsigned int k = i; k < 5; k++) {
                for (unsigned int l = (k == i) ? j + 1 : 0; l < 5; l++) {
                    const Jeton* jeton2 = plateau.getJeton(k * 5 + l);
                    if (verificationCombinaisonDeuxJetons(jeton1, jeton2, const_cast<Plateau &>(plateau))) {
                        combinaisons.push_back(std::make_pair(jeton1, jeton2));
                    }
                }
            }
        }
    }

    return combinaisons;
}

std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> IA::genererCombinaisonsTroisJetons(const Plateau& plateau) const{
    std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisons;

    for (unsigned int i = 0; i < 5; i++) {
        for (unsigned int j = 0; j < 5; j++) {
            const Jeton* jeton1 = plateau.getJeton(i * 5 + j);

            for (unsigned int k = i; k < 5; k++) {
                for (unsigned int l = (k == i) ? j + 1 : 0; l < 5; l++) {
                    const Jeton* jeton2 = plateau.getJeton(k * 5 + l);

                    for (unsigned int m = k; m < 5; m++) {
                        for (unsigned int n = (m == k) ? l + 1 : 0; n < 5; n++) {
                            const Jeton* jeton3 = plateau.getJeton(m * 5 + n);
                            if (verificationCombinaisonTroisJetons(jeton1, jeton2, jeton3, plateau)) {
                                combinaisons.push_back(std::make_tuple(jeton1, jeton2, jeton3));
                            }
                        }
                    }
                }
            }
        }
    }

    return combinaisons;
}

bool IA::verificationCombinaisonDeuxJetons(const Jeton* jeton1, const Jeton* jeton2, const Plateau& plateau) const {
    // Création d'un tableau temporaire pour stocker les positions des deux jetons
    int positions_temp[4] = {
            0, 0, // Position du jeton 1
            0, 0  // Position du jeton 2
    };

    // Vérification si les jetons sont nuls
    if (jeton1 == nullptr || jeton2 == nullptr) {
        return false;
    }

    // Obtention des positions des jetons dans le tableau temporaire
    for (unsigned int i = 0; i < 5; ++i) {
        for (unsigned int j = 0; j < 5; ++j) {
            const Jeton* jeton = plateau.getJeton(i * 5 + j);
            if (jeton == jeton1) {
                positions_temp[0] = i + 1;  // position x
                positions_temp[1] = j + 1;  // position y
            } else if (jeton == jeton2) {
                positions_temp[2] = i + 1;  // position x
                positions_temp[3] = j + 1;  // position y
            }
        }
    }

    //return plateau.verificationSelectionPositions(positions_temp, 2);
}

bool IA::verificationCombinaisonTroisJetons(const Jeton* jeton1, const Jeton* jeton2, const Jeton* jeton3, const Plateau& plateau) const {
    // Création d'un tableau temporaire pour stocker les positions des trois jetons
    int positions_temp[6] = {
            0, 0, // Position du jeton 1
            0, 0, // Position du jeton 2
            0, 0  // Position du jeton 3
    };

    // Vérification si les jetons sont nuls (non présents)
    if (jeton1 == nullptr || jeton2 == nullptr || jeton3 == nullptr) {
        return false;
    }

    // Obtention des positions des jetons dans le tableau temporaire
    for (unsigned int i = 0; i < 5; ++i) {
        for (unsigned int j = 0; j < 5; ++j) {
            const Jeton* jeton = plateau.getJeton(i * 5 + j);
            if (jeton == jeton1) {
                positions_temp[0] = i + 1;  // position x
                positions_temp[1] = j + 1;  // position y
            } else if (jeton == jeton2) {
                positions_temp[2] = i + 1;  // position x
                positions_temp[3] = j + 1;  // position y
            } else if (jeton == jeton3) {
                positions_temp[4] = i + 1;  // position x
                positions_temp[5] = j + 1;  // position y
            }
        }
    }
    //return plateau.verificationSelectionPositions(positions_temp, 3);
}



void IA::prendreJetons(Plateau* plateau) {
    // Vérifier si le plateau est vide, le remplir si nécessaire
    if (!plateau->hasJeton()) {
        Optionnelle::remplissagePlateau(this, plateau);
    }

    int choix = choisirChoix(1, 3);

    if (choix == 1) {
        // Choix 1 : Choisir un jeton sur le plateau (non or)
        choisirJetonSurPlateau(plateau);
    }
    else if (choix == 2) {
        // Choix 2 : Vérifier le vecteur de combinaisons de deux jetons
        std::vector<std::pair<const Jeton*, const Jeton*>> combinaisonsDeux = genererCombinaisonsDeuxJetons(*plateau);

        std::random_shuffle(combinaisonsDeux.begin(), combinaisonsDeux.end());
        auto derniereCombinaisonDeux = combinaisonsDeux.back();
        std::vector<int> resultatsAjout = Obligatoire::ajouterJetonsJoueur(this, {derniereCombinaisonDeux.first, derniereCombinaisonDeux.second});
        combinaisonsDeux.pop_back();
    }
    else if (choix == 3) {
        std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisonsTrois = genererCombinaisonsTroisJetons(*plateau);

        std::random_shuffle(combinaisonsTrois.begin(), combinaisonsTrois.end());

        auto derniereCombinaisonTrois = combinaisonsTrois.back();

         std::vector<int> resultatsAjout = Obligatoire::ajouterJetonsJoueur(this, {std::get<0>(derniereCombinaisonTrois), std::get<1>(derniereCombinaisonTrois), std::get<2>(derniereCombinaisonTrois)});

        combinaisonsTrois.pop_back();
    }
    else {
        // Autre choix, rappeler la fonction
        prendreJetons(plateau);
    }
}


void IA::choisirJetonSurPlateau(Plateau* plateau) {

    int positionX = rand() % 5 + 1;
    int positionY = rand() % 5 + 1;

    if (plateau->selectionJeton(positionX, positionY) == 0) {  // sélection valide
        const Jeton* jetonSelectionne = plateau->getJeton(positionX * 5 + positionY);

        std::vector<const Jeton*> jetonsSelectionnes = {jetonSelectionne};
        std::vector<int> resultatsAjout = Obligatoire::ajouterJetonsJoueur(this, jetonsSelectionnes);
    }
    std::vector<const Jeton*> jetonsSelectionnes = plateau->validerSelectionEtPrendreJetons();
}


