//#include "../include/carteNoble.h"
#include "../include/jeu.h"
CarteNoble::CarteNoble() : couronne(0) {}

CarteNoble::CarteNoble(int cour,int pointPres, std::map<Couleur, int> exg) : couronne(cour), pointPrestige(pointPres), exigences(exg) {}

int CarteNoble::getCouronne() const {
    return couronne;
}

int CarteNoble::getPointPrestige() const {
    return pointPrestige;
}

std::map<Couleur, int> CarteNoble::getExigences() const {
    return exigences;
}
