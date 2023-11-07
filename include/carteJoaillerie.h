#ifndef CARTEJOAILLERIE_H
#define CARTEJOAILLERIE_H

#include <map>
#include <vector>
#include "couleur.h"
#include "carte.h"

class CarteJoaillerie : public Carte { // Inherits from Carte
private:
    int niveau;    // La pioche correspondant à cette carte
    int couronne;  // Le score correspondant à la carte
    bool pierre;   // La couleur que le joueur peut déduire lors de l'achat d'autres cartes à l'avenir.
    Couleur type_pierre;
    std::map<Couleur, int> prix;

public:
    CarteJoaillerie(Plateau* p, Joueur* j, int niv, int cour, bool pier, Couleur couleur, std::map<Couleur, int> prx, const std::string& chemin, int prestige, const Pouvoir& pvr);
    CarteJoaillerie();
    ~CarteJoaillerie();

    // Specific methods for CarteJoaillerie
    std::map<Couleur, int> getPrix() const;
    int getNiveau() const;
    int getCouronne() const;
    bool hasPierre() const;
    Couleur getTypePierre() const;
};

#endif // CARTEJOAILLERIE_H
