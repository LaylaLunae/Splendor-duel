#include "../include/joueur.h"
#include <iostream>


Joueur::Joueur(const std::string nom)
        : pseudo(nom), nombre_couronnes(0), points_prestige_total(0) {

    for (int i = 0; i < 6; i++) {
        cartes_reservees[i] = CarteJoaillerie();  // Initialisez avec des valeurs par défaut
        cartes_main[i] = CarteJoaillerie();       // Initialisez avec des valeurs par défaut
        cartes_noble[i] = CarteNoble();            // Initialisez avec des valeurs par défaut
        privileges[i] = Privilege();               // Initialisez avec des valeurs par défaut
    }

    for (int i = 0; i < 5; i++) {
        gemmes_bonus[i] = 0;                      // Initialisez avec des valeurs par défaut
        points_prestige_couleurs[i] = 0;          // Initialisez avec des valeurs par défaut
    }
}


int Joueur::getPointsPrestigeTotal() const{
    return points_prestige_total;
}

std::string Joueur::getPseudo() const {
    return pseudo;
}

int Joueur::getNombreCouronnes()const {
    return nombre_couronnes;
}

int Joueur:: getPointsPrestigeCouleurs(int index) const {
    if (index >= 0 && index < 5) {
        return points_prestige_couleurs[index];
    }
    return 0;
}

CarteJoaillerie Joueur::getCarteReservee(int index) const {
    if (index >= 0 && index < 6) {
        return cartes_reservees[index];
    }
    return CarteJoaillerie(); // Retourne une carte vide par défaut
}

CarteJoaillerie Joueur::getCarteMain(int index) const {
    if (index >= 0 && index < 6) {
        return cartes_main[index];
    }
    return CarteJoaillerie();
}


CarteNoble Joueur::getCarteNoble(int index) const {
    if (index >= 0 && index < 6) {
        return cartes_noble[index];
    }
    return CarteNoble();
}

int Joueur::getGemmesBonus(int index) const {
    if (index >= 0 && index < 5) {
        return gemmes_bonus[index];
    }
    return 0;
}


Privilege Joueur::getPrivilege(int index) const {
    if (index >= 0 && index < 6) {
        return privileges[index];
    }
    return Privilege();
}


void Joueur::ajouterCarteJoaillerie(const CarteJoaillerie& carte) {

    /* si ya des couronnes on rajoute le nombre de couronnes dans le compteur
     * pareil pour point de pestiges
     * point dans une couleur en particullier
     *


}


void Joueur::ajouterCarteNoble(const CarteNoble& carte) {

}

void Joueur::ajouterCarteReservee(const CarteJoaillerie& carte) {

}

void Joueur::ajouterPrivilege(const Privilege& privilege) {

}

