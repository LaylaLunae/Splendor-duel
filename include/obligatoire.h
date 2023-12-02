#ifndef SPLENDOR_OBLIGATOIRE_H
#define SPLENDOR_OBLIGATOIRE_H

#include <iostream>
#include <vector>

// Comment vérifier l'obligation de remplir le plateau ?
// Faire des fonctions de vérifications ?
// Vérification anti str

class Obligatoire {
    friend class Jeu;

public:
    Obligatoire() = default;
    ~Obligatoire() = default;
    Obligatoire(const Obligatoire& obligatoire) = delete;
    Obligatoire& operator=(const Obligatoire& obligatoire) = delete;

    void prendreJeton(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3);
    void reserverCarte(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3);
    void acheterCarte(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3);

    void remettreJetonSac(Joueur* joueur, Plateau* plateau, Couleur c, int difference, int prix_elem, int index);
    void ajouterJetonsJoueur(Joueur* joueur, ReponseValidationSelection* selection);
};

#endif //SPLENDOR_OBLIGATOIRE_H