
#include <iostream>
#include "../include/jeu.h"
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <vector>
#include <algorithm>
#include <random>


int IA::choisirChoix(int min, int max) {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int choix = rand() % max + 1;

    if (choix < min || choix > max) {
        choix = choisirChoix(min, max);
    }
    return choix;
}


void IA::prendreJetonsAleatoires(Plateau* plateau) {
    int nombreJetonsAChoisir = rand() % 3 + 1;

    for (int i = 0; i < nombreJetonsAChoisir; ++i) {
        int positionX = rand() % 5 + 1;
        int positionY = rand() % 5 + 1;

        try {
            const Jeton* jeton = plateau->prendreJeton(positionX, positionY);
        } catch (PlateauException& e) {
            std::cout << e.get_info() << std::endl;
        }
    }
}

std::vector<CarteJoaillerie*> IA::getCartesAchetable(const Pioche& pioche) const {
    std::vector<CarteJoaillerie*> cartesAchetable;

    for (int i = 0; i < pioche.getMaxCartesRevelees(); ++i) {
        const CarteJoaillerie* carte = pioche.getCartesDehors(i);

        if (carte && carte->getNiveau() <= getNbJeton(0)) {
            if (IA::peutAcheterCarte(*carte)) {
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

    std::vector<CarteJoaillerie*> cartesAchetable;

    for (int i = 0; i < pioche.getMaxCartesRevelees(); ++i) {
        const CarteJoaillerie* carte = pioche.getCartesDehors(i);
        if (carte) {
            cartesAchetable.push_back(const_cast<CarteJoaillerie*>(carte));
        }
    }
    std::default_random_engine generator;
    std::shuffle(cartesAchetable.begin(), cartesAchetable.end(), generator);

    CarteJoaillerie* derniereCarte = cartesAchetable.back();

    joueur.ajouterCarteJoaillerie(*derniereCarte);

    return derniereCarte;
}

// a changer avec la fonction dans action obligatoire
bool IA::peutAcheterCarte(const CarteJoaillerie& carte) const {

    std::map<Couleur, int> prixCarte = carte.getPrix();
    for (const auto& it : prixCarte) {
        Couleur couleur = it.first;
        int quantite = it.second;

        if (getNbJeton(static_cast<int>(couleur)) < quantite) {
            return false;
        }
    }
    return true;
}
