//#include "../include/carteNoble.h"
#include "../include/jeu.h"
CarteNoble::CarteNoble() : couronne(0), id(0) {}

CarteNoble::CarteNoble(Plateau* p, Joueur* j, const std::string& chemin,
                       int prestige,
                       int cour, int pointPrestige, const Pouvoir& pvr1, const Pouvoir& pvr2,
                       const int id):
        Carte(chemin, prestige, cour, pvr1, pvr2, p, j), couronne(cour), pointPrestige(pointPrestige),
        id(id){}

int CarteNoble::getCouronne() const {
    return couronne;
}

int CarteNoble::getPointPrestige() const {
    return pointPrestige;
}

const int CarteNoble::getID() const {
    return id;
}
