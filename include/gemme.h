//
// Created by Pacino on 05/11/2023.
//

#ifndef SPLENDOR_GEMME_H
#define SPLENDOR_GEMME_H

#include "jeton.h"
#include "couleur.h"

class Gemme : public Jeton {
private:
    Couleur couleur;

public:
    Gemme(Couleur c);
    void afficher() const;

    Couleur getCouleur() const;
};


#endif //SPLENDOR_GEMME_H
