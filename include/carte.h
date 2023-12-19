//
// Created by Pacino on 05/11/2023.
//

#ifndef SPLENDOR_CARTE_H
#define SPLENDOR_CARTE_H

#include <string>
#include <array>
#include <algorithm>

#include "privilege.h"
#include "pouvoir.h" // safe
#include "jeton.h" // safe
#include "joueur.h" //
#include "plateau.h"


class CarteNoble;
class CarteJoaillerie;
class Plateau;

class Carte {
protected:
    std::string chemin_vers_image;
    int point_prestige;
    int courronnes;
    std::array<Pouvoir, 2> pouvoirs;
//    Plateau* plateau;
//    Joueur* joueur;
    Privilege prendrePrivilege(Plateau* plateau, Joueur* joueur); // take 1 privilege. If none are available, take 1 from your opponent.
    bool volerJeton(int couleurIndex, Joueur* joueur); // take 1 Gem or Pearl token from your opponent. If your opponent has no such tokens, ignore this effect. You can't take a Gold token from your opponent.
    bool prendreJeton(unsigned int position_x, unsigned int position_y, Plateau* plateau, Joueur* joueur); // take 1 Token matching the color of this card from the board. If tere are no such tokens left, ignore this effect.
    void rejouer(Joueur* joueur); // take antorher turn immediately after ths one ends.
    void rajouteBonus(int couleurIndex, Joueur* joueur); // Place this card so that it overlaps a Jewel card with a bonus.

public:
    Carte(const std::string& chemin, int prestige, int cour, Pouvoir pvr1, Pouvoir pvr2, Plateau* p, Joueur* j);
    Carte();
    virtual ~Carte() {}

    void actionPouvoir(Plateau* plateau, Joueur* joueur);
    int getPointsPrestige();
    int getCourronnes();
    std::string getCheminVersImage() const;
    std::array<Pouvoir, 2> existancePouvoir();

};

#endif //SPLENDOR_CARTE_H
