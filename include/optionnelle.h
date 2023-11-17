#ifndef SPLENDOR_OPTIONNELLE_H
#define SPLENDOR_OPTIONNELLE_H

//#include "plateau.h"
//#include "joueur.h"


class Optionnelle {
    private:
        Optionnelle(Plateau* plateau) : plateau(plateau) {};

        void depenserPrivilege(Joueur* joueur, ReponseValidationSelection RVS);
        void remplissagePlateau(Joueur* joueur);

    private:
        Plateau* plateau;
};

#endif //SPLENDOR_OPTIONNELLE_H
