#ifndef CARTENOBLE_H
#define CARTENOBLE_H

#include <map>
#include "couleur.h"
#include "carte.h"

class CarteNoble {
private:
    int couronne;
    int pointPrestige;
    std::map<Couleur, int> exigences;

public:
    CarteNoble();
    CarteNoble(int cour, int pointPrestige, std::map<Couleur, int> exg);
    int getCouronne() const;
    int getPointPrestige()const;
    std::map<Couleur, int> getExigences() const;
};

#endif // CARTENOBLE_H
