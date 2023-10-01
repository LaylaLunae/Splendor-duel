#include "../include/joueur.h"
#include <iostream>

Joueur::Joueur(std::string nom)
        : pseudo(nom), nombre_couronnes(0), points_prestige_total(0),
          cartes_reservees_count(0), cartes_main_count(0), cartes_noble_count(0), privileges_count(0) {}

int Joueur::getPoints() {
    return points_prestige_total;
}

std::string Joueur::getPseudo() {
    return pseudo;
}

void Joueur::ajouterCarteJoaillerie(CarteJoaillerie carte) {
    if (cartes_main_count < MAX_CARTES) {
        cartes_main[cartes_main_count++] = carte;
        points_prestige_total += carte.couronne;
    } else {
        std::cerr << "Erreur: Le joueur a atteint la limite maximale de cartes." << std::endl;
    }
}

void Joueur::ajouterCarteNoble(CarteNoble carte) {
    if (cartes_noble_count < MAX_CARTES) {
        cartes_noble[cartes_noble_count++] = carte;
        points_prestige_total += carte.couronne;
    } else {
        std::cerr << "Erreur: Le joueur a atteint la limite maximale de cartes nobles." << std::endl;
    }
}

void Joueur::ajouterCarteReservee(CarteJoaillerie carte) {
    if (cartes_reservees_count < MAX_CARTES) {
        cartes_reservees[cartes_reservees_count++] = carte;
    } else {
        std::cerr << "Erreur: Le joueur a atteint la limite maximale de cartes réservées." << std::endl;
    }
}

void Joueur::ajouterPrivilege(Privilege privilege) {
    if (privileges_count < MAX_PRIVILEGES) {
        privileges[privileges_count++] = privilege;
    } else {
        std::cerr << "Erreur: Le joueur a atteint la limite maximale de privilèges." << std::endl;
    }
}
