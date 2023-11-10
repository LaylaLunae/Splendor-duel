#ifndef SPLENDOR_OBLIGATOIRE_H
#define SPLENDOR_OBLIGATOIRE_H

#include "carte.h"

class Obligatoire {
    public:
        Jeton* prendreJeton();
        CarteJoaillerie reserverCarte();
        CarteJoaillerie acheterCarte();
};

#endif //SPLENDOR_OBLIGATOIRE_H
