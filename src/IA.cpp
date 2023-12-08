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


std::vector<CarteJoaillerie*> IA::getCartesAchetable(const Pioche& pioche) const {
    std::vector<CarteJoaillerie*> cartesAchetable;

    for (int i = 0; i < pioche.getMaxCartesRevelees(); ++i) {
        const CarteJoaillerie* carte = pioche.getCartesDehors(i);

        if (carte) {
            std::vector<int> difference = Obligatoire::calculDifference((Joueur *) this, carte->getPrix());

            if (Obligatoire::achatPiochePossible((Joueur *) this, const_cast<Pioche*>(&pioche))) {
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


std::vector<std::pair<const Jeton*, const Jeton*>> IA::genererCombinaisonsDeuxJetons(Plateau plateau) const {
    std::vector<std::pair<const Jeton*, const Jeton*>> combinaisons;

    // Parcourir le plateau de jetons
    for (unsigned int i = 0; i < plateau.getNbJetonsPlateauMAX(); ++i) {
        const Jeton* jeton1 = plateau.getJeton(i);

        // Obtenir les positions possibles pour le jeton1
        unsigned int x = i / 5;
        unsigned int y = i % 5;
        std::vector<std::vector<unsigned int>> positionsPossibles = plateau.donnePositionsPossiblesAPartirDe(x, y);

        // Insérer les positions possibles dans un vecteur global
        std::vector<std::pair<unsigned int, unsigned int>> positions;
        for (const auto& pos : positionsPossibles) {
            for (unsigned int j = 0; j < pos.size(); j += 2) {
                positions.push_back({pos[j], pos[j + 1]});
            }
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(positions.begin(), positions.end(), g);

        // Parcourir le vecteur de positions et sélectionner deux jetons
        for (unsigned int k = 0; k < positions.size() && combinaisons.size() < 2; ++k) {
            unsigned int posX = positions[k].first;
            unsigned int posY = positions[k].second;
            const Jeton* jeton2 = plateau.getJeton(posX * 5 + posY);

            plateau.selectionJeton(posX, posY);

            // Ajouter la paire de jetons
            combinaisons.push_back({jeton1, jeton2});
        }
    }
    plateau.validerSelectionEtPrendreJetons();

    return combinaisons;
}

std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> IA::genererCombinaisonsTroisJetons(Plateau plateau) const {
    std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisons;

    // Parcourir le plateau de jetons
    for (unsigned int i = 0; i < plateau.getNbJetonsPlateauMAX(); ++i) {
        const Jeton* jeton1 = plateau.getJeton(i);

        // Obtenir les positions possibles pour le jeton1
        unsigned int x = i / 5;
        unsigned int y = i % 5;
        std::vector<std::vector<unsigned int>> positionsPossibles = plateau.donnePositionsPossiblesAPartirDe(x, y);

        // Insérer les positions possibles dans un vecteur global
        std::vector<std::tuple<unsigned int, unsigned int, const Jeton*>> positions;
        for (const auto& pos : positionsPossibles) {
            for (unsigned int j = 0; j < pos.size(); j += 2) {
                unsigned int posX = pos[j];
                unsigned int posY = pos[j + 1];
                const Jeton* jeton2 = plateau.getJeton(posX * 5 + posY);
                positions.emplace_back(posX, posY, jeton2);
            }
        }

        // Mélanger le vecteur de positions avec std::shuffle
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(positions.begin(), positions.end(), g);

        // Parcourir le vecteur de positions et sélectionner trois jetons
        for (unsigned int k = 0; k < positions.size() && combinaisons.size() < 3; ++k) {
            unsigned int posX2, posY2;
            const Jeton* jeton2;
            std::tie(posX2, posY2, jeton2) = positions[k];

            plateau.selectionJeton(posX2, posY2);

            // Ajouter la triple paire de jetons
            combinaisons.emplace_back(jeton1, jeton2, plateau.getJeton(posX2 * 5 + posY2));
        }
    }

    // Valider la sélection après avoir parcouru toutes les positions possibles
    plateau.validerSelectionEtPrendreJetons();

    return combinaisons;
}



void IA::prendreJetons(Plateau* plateau) {
    // Vérifier si le plateau est vide, le remplir si nécessaire
    if (!plateau->hasJeton()) {
        Optionnelle::remplissagePlateau(this, plateau);
    }
    int choix = choisirChoix(1, 3);

    if (choix == 1) {
        choisirJetonSurPlateau(plateau);
    }
    else if (choix == 2) {
        std::vector<std::pair<const Jeton*, const Jeton*>> combinaisonsDeux = genererCombinaisonsDeuxJetons(*plateau);

    }
    else if (choix == 3) {
        std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisonsTrois = genererCombinaisonsTroisJetons(*plateau);
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
