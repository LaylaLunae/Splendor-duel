#include "../include/joueur.h"
#include "../include/carteJoaillerie.h"
#include <iostream>

#include "../include/carteJoaillerie.h"

Joueur::Joueur(const std::string nom): pseudo(nom), nombre_couronnes(0), points_prestige_total(0),droitDeRejouer(false),adversaire(nullptr) {
//
//    for (int i = 0; i < 6; i++) {
//        cartes_reservees[i] = CarteJoaillerie();
//        cartes_main[i] = CarteJoaillerie();
//        cartes_noble[i] = CarteNoble();
//        privileges[i] = Privilege();
//    }
//
//    for (int i = 0; i < 5; i++) {
//        gemmes_bonus[i] = 0;
//        points_prestige_couleurs[i] = 0;
//    }
}
//
int Joueur::getPointsPrestigeTotal() const{
//    return points_prestige_total;
}
//
std::string Joueur::getPseudo() const {
//    return pseudo;
}
//
int Joueur::getNombreCouronnes()const {
//    return nombre_couronnes;
}
//
int Joueur:: getPointsPrestigeCouleurs(int index) const {
//    if (index >= 0 && index < 5) {
//        return points_prestige_couleurs[index];
//    }
//    return 0;
}
//
CarteJoaillerie Joueur::getCarteReservee(int index) const {
//    if (index >= 0 && index <= 3) {
//        return cartes_reservees[index];
//    }
}
//
CarteJoaillerie Joueur::getCarteMain(int index) const {
//    if (index >= 0 ) {
//        return cartes_main[index];
//    }
}


CarteNoble Joueur::getCarteNoble(int index) const {
//    if (index >= 0 && index < 3) {
//        return cartes_noble[index];
//    }
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

void Joueur::ajouterCarteJoaillerie(CarteJoaillerie carte) {
    int nombrePointsCarte = carte.getPointsPrestige();
    int nombreCouronnesCarte = carte.getCourronnes();

    // Ajouter les points de prestige si la carte en a
    if (nombrePointsCarte > 0) {
        points_prestige_total += nombrePointsCarte;
    }
    // Ajouter les points dans la couleur du bijou si la carte en a
    Couleur couleurBijou = carte.getTypePierre();
    if (Couleur::rien!= couleurBijou) {
        points_prestige_couleurs[static_cast<int>(couleurBijou)] += nombrePointsCarte;
    }

    // Ajouter le nombre de couronnes si la carte en a
    if (nombreCouronnesCarte > 0) {
        nombre_couronnes += nombreCouronnesCarte;
    }
    /*
    // Ajouter le nombre de bonus (gemme) si la carte en a
    if(carte.getTypePierre()!=Couleur::rien){
        if(carte.getNombrePierre()==1) {//TO DO: wait for Xu's update and correct
            int i = static_cast<int>(carte.getTypePierre());
            gemmes_bonus[i]+=carte.getNombrePierre();
        }
    }
     */
}

void Joueur::ajouterCarteNoble(const CarteNoble& carte) {

    int nombreCouronnesCarte = carte.getCouronne();

    // Vérifier si le joueur a 3 ou 6 couronnes dans son jeu
    if (nombre_couronnes == 3 || nombre_couronnes == 6) {
        // Ajouter le nombre de couronnes à la variable nombre_couronnes
        nombre_couronnes += nombreCouronnesCarte;

        // Ajouter les points de prestige de la carte à la variable points_prestige_total
        points_prestige_total += carte.getPointPrestige();
    }
    else{
        throw ("Le joueur doit avoir 3 ou 6 couronnes pour ajouter une carte noble.");
    }
}

void Joueur::ajouterCarteReservee(const CarteJoaillerie& carte) {
//    if (nb_cartes_reservees < 3) {
//        cartes_reservees[nb_cartes_reservees] = carte;
//        nb_cartes_reservees++;
//    }
//    else {
//        throw std::runtime_error("Le joueur ne peut pas réserver plus de 3 cartes.");
//    }
}


void Joueur::ajouterPrivilege(const Privilege& privilege) {
    if (nombre_de_privileges < 3) {
        privileges[nombre_de_privileges]=privilege;
        nombre_de_privileges++;
    }
    else {
        throw ("Le joueur ne peut pas avoir plus de 3 privilèges.");
    }
}


// Définir l'adversaire
void Joueur::setAdversaire(Joueur *adv) {
    adversaire = adv;
    if (adv->adversaire == nullptr) { // Assurez-vous que l'adversaire désigne également le joueur actuel comme adversaire
        adv->setAdversaire(this);
    }
}

Joueur* Joueur::getAdversaire() {
    return adversaire;
}

bool Joueur::hasPrivilege() {
    if (this->privileges != nullptr)
        return true;
    return false;
}

Privilege Joueur::removePrivilege() {
    for (int i = 0; i < MAX_PRIVILEGES; ++i) {
        if (privileges[i].getStatus() != PrivilegeStatus::NONE) {
            Privilege tmp = privileges[i];
            privileges[i].setStatus(PrivilegeStatus::NONE);
            return tmp;
        }
    }
    throw std::runtime_error("No privilege to remove");
}

// Ajouter une méthode setter à la classe Joueur
void Joueur::setPointsPrestigeCouleurs(int index, int valeur) {
    if (index >= 0 && index < 5) { // Assurez-vous que l'indice est dans la plage valide
        points_prestige_couleurs[index] = valeur;
    } else {
        std::cerr << "L'indice est hors limites." << std::endl;
    }
}

void Joueur::setGemmesBonus(int index, int value) {
    this->gemmes_bonus[index] = value;
}

// Méthode pour vérifier si le joueur a le droit de jouer à nouveau.
bool Joueur::peutRejouer() const {
    return droitDeRejouer;
}

// Réinitialisez le droit de jouer à la fin du tour du joueur.
void Joueur::resetRejouer() {
    if (droitDeRejouer == true)
        droitDeRejouer = false;
    else
        droitDeRejouer = true;
}

void Joueur::resetRejouer(bool reset) {
    droitDeRejouer = reset;
}
