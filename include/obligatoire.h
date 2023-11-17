#ifndef SPLENDOR_OBLIGATOIRE_H
#define SPLENDOR_OBLIGATOIRE_H


//#include "carte.h"
//#include "carteJoaillerie.h"

class Obligatoire {
    private:
        Obligatoire(Plateau* plateau) : plateau(plateau) {};

        void prendreJeton(Joueur* joueur, ReponseValidationSelection RVS);
        void reserverCarte(Joueur* joueur, ReponseValidationSelection RVS, CarteJoaillerie* card);
        void acheterCarte(Joueur* joueur, ReponseValidationSelection RVS, CarteJoaillerie* card);

    private:
        Plateau* plateau;
};

#endif //SPLENDOR_OBLIGATOIRE_H
