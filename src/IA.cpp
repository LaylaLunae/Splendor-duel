
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

/*
void IA::prendreJetonsAleatoires(Plateau* plateau) {
    int nombreJetonsAChoisir = rand() % 3 + 1;

    for (int i = 0; i < nombreJetonsAChoisir; ++i) {
        int positionX = rand() % 5 + 1;
        int positionY = rand() % 5 + 1;

        if (plateau->selectionJeton(positionX, positionY)==0) {  // selection valide
            ajouterJetons();
        }
    }
    // ATTENTION : VA SE TRANSFORMER EN vector<const Jeton*>
    ReponseValidationSelection* rvs = plateau->validerSelectionEtPrendreJetons();
}

std::vector<jetonsChoisi*> IA::ajouterJetons(std::vector<jetonsChoisi*> jetonsChoisi, int positionX, int positionY){
    // transformer les coordeonne en jetons
    jetonsChoisi.pushback(jeton);
    AjouterMainJoueur(jeton);
    return jetonsChoisi;
}
 */

void IA::AjouterMainJoueur(Joueur* joueur, Plateau* plateau, int positionX, int positionY){

    // faire une fonction qui ajoute les jetons dans la main du joueur
}




// pas sûre de faire la différence entre cartemaxrevelee et cartedehors
std::vector<CarteJoaillerie*> IA::getCartesAchetable(const Pioche& pioche) const {
    std::vector<CarteJoaillerie*> cartesAchetable;

    for (int i = 0; i < pioche.getMaxCartesRevelees(); ++i) {
        const CarteJoaillerie* carte = pioche.getCartesDehors(i);

        if (carte && carte->getNiveau() <= getNbJeton(0)) {
            if (IA::peutAcheterCarte(this, *carte)) {
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


// a changer avec la fonction dans action obligatoire car prendre pas enc ompte que l'or est un joker
bool IA::peutAcheterCarte(const IA *joueur, const CarteJoaillerie& carte) const {

    std::map<Couleur, int> prix = carte.getPrix();
    bool achat_possible = true;
    for (auto elem = prix.begin(); elem != prix.end(); elem++) {
        int price = elem->second;
        switch (elem->first) {
            case Couleur::bleu: if (price - joueur->getGemmesBonus(0) > joueur->getNbJeton(0)) achat_possible = false;
            case Couleur::vert: if (price - joueur->getGemmesBonus(1) > joueur->getNbJeton(1)) achat_possible = false;
            case Couleur::rouge: if (price - joueur->getGemmesBonus(2) > joueur->getNbJeton(2)) achat_possible = false;
            case Couleur::blanc: if (price - joueur->getGemmesBonus(3) > joueur->getNbJeton(3)) achat_possible = false;
            case Couleur::noir: if (price - joueur->getGemmesBonus(4) > joueur->getNbJeton(4)) achat_possible = false;
            case Couleur::rose: if (price - joueur->getGemmesBonus(5) > joueur->getNbJeton(5)) achat_possible = false;
        }
    }
    return achat_possible;
}
