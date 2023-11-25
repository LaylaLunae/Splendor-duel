
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
        // Générez des coordonnées aléatoires pour choisir un jeton sur le plateau
        int positionX = rand() % 5 + 1;
        int positionY = rand() % 5 + 1;

        try {
            const Jeton* jeton = plateau->prendreJeton(positionX, positionY);
        } catch (PlateauException& e) {
            std::cout << e.get_info() << std::endl;
        }
    }
}



std::vector<CarteJoaillerie*> IA::getCartesAchetable(const Plateau& plateau) const {

    std::vector<CarteJoaillerie*> cartesAchetable;

    // Parcourir les cartes joaillerie du plateau
    for (unsigned int i = 0; i < plateau.getNbJetonsPlateau(); ++i) {
        const CarteJoaillerie* carte = dynamic_cast<const CarteJoaillerie*>(plateau.getCartePlateau(i));

        // Vérifier si la carte est de niveau inférieur ou égal au nombre de gemmes disponibles
        if (carte && carte->getNiveau() <= getNbJeton(0)) {
            // Vérifier si l'IA peut acheter la carte (en fonction de ses ressources)
            if (IA::peutAcheterCarte(*carte)) {
                cartesAchetable.push_back(const_cast<CarteJoaillerie*>(carte));
            }
        }
    }

    return cartesAchetable;
}


// Fonction pour mélanger le vecteur et retourner la dernière carte

CarteJoaillerie* IA::melangerEtObtenirDerniereCarte(std::vector<CarteJoaillerie*>& cartesAchetable, Joueur& joueur) {
    // Vérifier si le vecteur n'est pas vide
    if (cartesAchetable.empty()) {
        return nullptr;
    }

// Mélanger le vecteur avec le générateur par défaut
    std::default_random_engine generator;
    std::shuffle(cartesAchetable.begin(), cartesAchetable.end(), generator);

    CarteJoaillerie* derniereCarte = cartesAchetable.back();

    joueur.ajouterCarteJoaillerie(*derniereCarte);

    return derniereCarte;
}



bool IA::peutAcheterCarte(const CarteJoaillerie& carte) const {
    // Vérifier si l'IA a les ressources nécessaires pour acheter la carte
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
*/