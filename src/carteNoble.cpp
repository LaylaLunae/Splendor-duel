#include "../include/carteNoble.h"

CarteNoble::CarteNoble() : couronne(0) {}

CarteNoble::CarteNoble(int cour, std::map<Couleur, int> exg) : couronne(cour), exigences(exg) {}

int CarteNoble::getCouronne() const {
    return couronne;
}

int CarteNoble::getPointPrestige() const {
    return pointPrestige;
}

std::map<Couleur, int> CarteNoble::getExigences() const {
    return exigences;
}
