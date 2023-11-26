#ifndef SPLENDOR_OBLIGATOIRE_H
#define SPLENDOR_OBLIGATOIRE_H

#include <iostream>
#include <vector>

// Comment vérifier l'obligation de remplir le plateau ?
// Faire des fonctions de vérifications ?
// Vérification anti str
// Vérifier la récupération des pioches quand ce sera implémenté dans Jeu

class Obligatoire {
    friend class Jeu;

public:
    Obligatoire() = default;
    ~Obligatoire() = default;
    Obligatoire(const Obligatoire& obligatoire) = delete;
    Obligatoire& operator=(const Obligatoire& obligatoire) = delete;

    void prendreJeton(Joueur* joueur, Plateau* plateau);
    void reserverCarte(Joueur* joueur, Plateau* plateau);
    void acheterCarte(Joueur* joueur, Plateau* plateau);
};

#endif //SPLENDOR_OBLIGATOIRE_H