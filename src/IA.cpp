#include <iostream>
#include "../include/jeu.h"
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <vector>
#include <algorithm>
#include <random>


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
    ajouterJetonsJoueur();
    return jetonsChoisi;
}




 */