#ifndef SPLENDOR_OBLIGATOIRE_H
#define SPLENDOR_OBLIGATOIRE_H

#include <iostream>
#include <vector>

// Comment vérifier l'obligation de remplir le plateau ?
// Faire des fonctions de vérifications ?

class Obligatoire {
    friend Jeu;

    public:
        Obligatoire() = default;
        ~Obligatoire() = default;
        Obligatoire(const Obligatoire& obligatoire) = delete;
        Obligatoire& operator=(const Obligatoire& obligatoire) = delete;

        void prendreJeton(Joueur* joueur, Plateau* plateau);
        void reserverCarte(Joueur* joueur, Plateau* plateau, Pioche* pioche);
        void acheterCarte(Joueur* joueur, Plateau* plateau, Pioche* pioche);
};

#endif //SPLENDOR_OBLIGATOIRE_H
