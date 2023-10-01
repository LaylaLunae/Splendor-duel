#include "../include/carteJoaillerie.h"

CarteJoaillerie::CarteJoaillerie() : niveau(0), couronne(0), pierre(false), type_pierre(Couleur::bleu) {}

CarteJoaillerie::CarteJoaillerie(int niv, int cour, bool pier, Couleur couleur, std::map<Couleur, int> prx)
        : niveau(niv), couronne(cour), pierre(pier), type_pierre(couleur), prix(prx) {}

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
