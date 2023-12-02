#ifndef SPLENDOR_OBLIGATOIRE_H
#define SPLENDOR_OBLIGATOIRE_H

#include <iostream>
#include <vector>

// Comment vérifier l'obligation de remplir le plateau ?
// Faire des fonctions de vérifications ?
// Vérification anti str

// Il reste à vérifier ajouterJoueur, le blabla dans acheterCarte,, reserver et prendre

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
    void ajouterJetonsJoueur(Joueur* joueur, std::vector<const Jeton*> selection);
    bool achatPiochePossible(Joueur* joueur, Pioche* p);
    bool achatCartePossible(Joueur *joueur, std::vector<int> difference);
    std::vector<bool> achatCartesPossible(Joueur* joueur, Pioche* p1, Pioche* p2, Pioche* p3);
    std::vector<int> calculDifference(Joueur* joueur, std::map<Couleur, int> prix);
};

#endif //SPLENDOR_OBLIGATOIRE_H