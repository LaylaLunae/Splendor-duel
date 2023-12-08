#ifndef SPLENDOR_OBLIGATOIRE_H
#define SPLENDOR_OBLIGATOIRE_H

#include <iostream>
#include <vector>

class Obligatoire {
    friend class Jeu;

public:
    Obligatoire() = default;
    ~Obligatoire() = default;
    Obligatoire(const Obligatoire& obligatoire) = delete;
    Obligatoire& operator=(const Obligatoire& obligatoire) = delete;

    static void prendreJeton(Joueur* joueur, Plateau* plateau);
    static void reserverCarte(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3);
    static void reserverCarteIA(IA* ia, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3, int n_pioche, int n_carte, bool carte_revelee = true);
    static void acheterCarte(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3);

    static void remettreJetonSac(Joueur* joueur, Plateau* plateau, Couleur c, int difference, int prix_elem, int index);
    static std::vector<int> ajouterJetonsJoueur(Joueur* joueur, std::vector<const Jeton*> selection);
    static bool achatPiochePossible(Joueur* joueur, Pioche* p);
    static bool achatCartePossible(Joueur *joueur, std::vector<int> difference);
    static std::vector<int> calculDifference(Joueur* joueur, std::map<Couleur, int> prix);
    static void donnerPrivilegeAdversaire(Joueur* joueur, Plateau* plateau);
};

#endif //SPLENDOR_OBLIGATOIRE_H