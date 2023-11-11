#ifndef SPLENDOR_OBLIGATOIRE_H
#define SPLENDOR_OBLIGATOIRE_H

#include "carte.h"
#include "carteJoaillerie.h"

class Obligatoire {
    public:
        Obligatoire(Plateau* plateau) : plateau(plateau) {};

        void prendreJeton(Joueur* joueur, ReponseValidationSelection RVS);
        CarteJoaillerie reserverCarte(Joueur* joueur, ReponseValidationSelection RVS, CarteJoaillerie* card);
        CarteJoaillerie acheterCarte(Joueur* joueur, ReponseValidationSelection RVS, CarteJoaillerie* card);

    private:
        Plateau* plateau;
};

#endif //SPLENDOR_OBLIGATOIRE_H
