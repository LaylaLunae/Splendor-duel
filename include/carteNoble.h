#ifndef CARTENOBLE_H
#define CARTENOBLE_H

#include <map>

#include "couleur.h" // safe
#include "carte.h"

class CarteNoble : public Carte{
private:
    int couronne;
    int pointPrestige;
    const int id;


public:
    CarteNoble();
    CarteNoble(Plateau* p, Joueur* j, const std::string& chemin,
               int prestige,
               int cour, int pointPrestige, const Pouvoir& pvr1, const Pouvoir& pvr2,
               const int id);

    int getCouronne() const;
    int getPointPrestige()const;
    const int getID() const;
};

#endif // CARTENOBLE_H
