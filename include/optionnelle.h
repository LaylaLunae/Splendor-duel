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

    void depenserPrivilege(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3);
    void remplissagePlateau(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3);
};

#endif //SPLENDOR_OPTIONNELLE_H
