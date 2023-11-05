#include "../include/carteJoaillerie.h"

CarteJoaillerie::CarteJoaillerie(int niv, int cour, bool pier, Couleur couleur, std::map<Couleur, int> prx, const std::string& chemin, int prestige, const Pouvoir& pvr)
        : Carte(chemin, prestige, cour, pvr), niveau(niv), couronne(cour), pierre(pier), type_pierre(couleur), prix(prx) {
    // Constructor implementation
}

CarteJoaillerie::~CarteJoaillerie() {
    // Destructor implementation, if needed
}

std::map<Couleur, int> CarteJoaillerie::getPrix() const {
    return prix;
}

int CarteJoaillerie::getNiveau() const {
    return niveau;
}

int CarteJoaillerie::getCouronne() const {
    return couronne;
}

bool CarteJoaillerie::hasPierre() const {
    return pierre;
}

Couleur CarteJoaillerie::getTypePierre() const {
    return type_pierre;
}
