//
// Created by Pacino on 05/11/2023.
//

#ifndef SPLENDOR_CARTE_H
#define SPLENDOR_CARTE_H

#include <string>
#include "../include/jeton.h"
#include "../include/privilege.h"
#include "../include/pouvoir.h"
#include "../include/joueur.h"
#include "../include/plateau.h"

class Carte {
protected:
    std::string chemin_vers_image;
    int point_prestige;
    int courronnes;
    Pouvoir pouvoir;
    Plateau* plateau;
    Joueur* joueur;

public:
    Carte(const std::string& chemin, int prestige, int cour, const Pouvoir& pvr, Plateau* p, Joueur* j);
    Carte();
    virtual ~Carte() {}

    void actionPouvoir();
    int getPointsPrestige();
    int getCourronnes();
    Pouvoir existancePouvoir();
    Privilege prendrePrivilege(); // take 1 privilege. If none are available, take 1 from your opponent.
    bool volerJeton(int couleurIndex); // take 1 Gem or Pearl token from your opponent. If your opponent has no such tokens, ignore this effect. You can't take a Gold token from your opponent.
    bool prendreJeton(unsigned int position_x, unsigned int position_y); // take 1 Token matching the color of this card from the board. If tere are no such tokens left, ignore this effect.
    void rejouer(); // take antorher turn immediately after ths one ends.
    void rajouteBonus(int couleurIndex); // Place this card so that it overlaps a Jewel card with a bonus.
};

#endif //SPLENDOR_CARTE_H
