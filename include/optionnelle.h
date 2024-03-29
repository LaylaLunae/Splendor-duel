#ifndef SPLENDOR_OPTIONNELLE_H
#define SPLENDOR_OPTIONNELLE_H

//#include "plateau.h"
//#include "joueur.h"
#include <vector>

class Optionnelle {
    friend class Jeu;

public:
    Optionnelle() = default;
    ~Optionnelle() = default;
    Optionnelle(const Optionnelle& optionnelle) = delete;
    Optionnelle& operator=(const Optionnelle& optionnelle) = delete;

    static bool depenserPrivilege(Joueur* joueur, Plateau* plateau);
    static bool remplissagePlateau(Joueur* joueur, Plateau* plateau);
};

#endif //SPLENDOR_OPTIONNELLE_H
