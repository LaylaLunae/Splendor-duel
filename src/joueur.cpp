#include "../include/joueur.h"
#include <iostream>


Joueur::Joueur(const std::string nom): pseudo(nom), nombre_couronnes(0), points_prestige_total(0) {

    for (int i = 0; i < 6; i++) {
        cartes_reservees[i] = CarteJoaillerie();
        cartes_main[i] = CarteJoaillerie();
        cartes_noble[i] = CarteNoble();
        privileges[i] = Privilege();
    }

    for (int i = 0; i < 5; i++) {
        gemmes_bonus[i] = 0;
        points_prestige_couleurs[i] = 0;
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
}

CarteJoaillerie Joueur::getCarteMain(int index) const {
    if (index >= 0 ) {
        return cartes_main[index];
    }
}


CarteNoble Joueur::getCarteNoble(int index) const {
    if (index >= 0 && index < 3) {
        return cartes_noble[index];
    }
}

int Joueur::getGemmesBonus(int index) const {
    if (index >= 0 && index < 6) {
        return gemmes_bonus[index];
    }
    return 0;
}

Privilege Joueur::getPrivilege(int index) const {
    if (index >= 0 && index < 3) {
        return privileges[index];
    }
}

void Joueur::ajouterCarteJoaillerie(const CarteJoaillerie& carte) {
    int nombrePointsCarte = carte.getPointsPrestige();
    int nombreCouronnesCarte = carte.getNombreCouronnes();

    // Ajouter les points de prestige si la carte en a
    if (nombrePointsCarte > 0) {
        points_prestige_total += nombrePointsCarte;
    }

    // Ajouter les points dans la couleur du bijou si la carte en a
    Couleur couleurBijou = carte.getCouleurBijou();
    if (couleurBijou != Couleur::aucune) {
        points_prestige_couleurs[static_cast<int>(couleurBijou)] += nombrePointsCarte;
    }

    // Ajouter le nombre de couronnes si la carte en a
    if (nombreCouronnesCarte > 0) {
        nombre_couronnes += nombreCouronnesCarte;
    }

    // Ajouter le nombre de bonus (gemme) si la carte en a
    for (const auto& [couleur, nombreGemmes] : carte.getGemmesBonus()) {
        gemmes_bonus[static_cast<int>(couleur)] += nombreGemmes;
    }

void Joueur::ajouterCarteNoble(const CarteNoble& carte) {

    int nombreCouronnesCarte = carteNoble.getNombreCouronnes();

    // Vérifier si le joueur a 3 ou 6 couronnes dans son jeu
    if (nombre_couronnes == 3 || nombre_couronnes == 6) {
        // Ajouter le nombre de couronnes à la variable nombre_couronnes
        nombre_couronnes += nombreCouronnesCarte;

        // Ajouter les points de prestige de la carte à la variable points_prestige_total
        points_prestige_total += carteNoble.getPointsPrestige();
    }
    else{
        throw std::runtime_error("Le joueur doit avoir 3 ou 6 couronnes pour ajouter une carte noble.");
    }
}


void Joueur::ajouterCarteReservee(const CarteJoaillerie& carte) {
    if (compteur_cartes_reservees < 3) {
        compteur_cartes_reservees++;
    }
    else {
        throw std::runtime_error("Le joueur ne peut pas réserver plus de 3 cartes.");
    }
}

void Joueur::ajouterPrivilege(const Privilege& privilege) {
    if (compteur_privileges < 3) {
        compteur_privileges++;
    } else {
        throw std::runtime_error("Le joueur ne peut pas avoir plus de 3 privilèges.");
    }
}

