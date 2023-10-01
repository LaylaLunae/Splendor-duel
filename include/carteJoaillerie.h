#ifndef CARTEJOAILLERIE_H
#define CARTEJOAILLERIE_H

#include <map>
#include "couleur.h"

class CarteJoaillerie {
private:
    int niveau;
    int couronne;
    bool pierre;
    Couleur type_pierre;
    std::map<Couleur, int> prix;

public:
    CarteJoaillerie();
    CarteJoaillerie(int niv, int cour, bool pier, Couleur couleur, std::map<Couleur, int> prx);
    std::map<Couleur, int> getPrix() const;
    int getNiveau() const;
    int getCouronne() const;
    bool hasPierre() const;
    Couleur getTypePierre() const;
};

#endif // CARTEJOAILLERIE_H
