#ifndef CARTENOBLE_H
#define CARTENOBLE_H

#include <map>
#include "couleur.h"

class CarteNoble {
private:
    int couronne;
    std::map<Couleur, int> exigences;

public:
    CarteNoble();
    CarteNoble(int cour, std::map<Couleur, int> exg);
    int getCouronne() const;
    std::map<Couleur, int> getExigences() const;
};

#endif // CARTENOBLE_H
