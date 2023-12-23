#ifndef SPLENDOR_CARTE_H
#define SPLENDOR_CARTE_H

#include <string>
#include <array>
#include <algorithm>

#include "privilege.h"
#include "pouvoir.h"
#include "jeton.h"
#include "joueur.h"
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
    Privilege prendrePrivilege(Plateau* plateau, Joueur* joueur); // prenez 1 privilège. Si aucun n'est disponible, prenez-en 1 à votre adversaire.
    bool volerJeton(int couleurIndex, Joueur* joueur); // prenez 1 jeton Gemme ou Perle à votre adversaire. Si votre adversaire n'a pas de tels jetons, ignorez cet effet. Vous ne pouvez pas prendre un jeton Or à votre adversaire.
    bool prendreJeton(unsigned int position_x, unsigned int position_y, Plateau* plateau, Joueur* joueur); // prenez 1 jeton correspondant à la couleur de cette carte du plateau de jeu. S'il n'y a plus de jetons de ce type, ignorez cet effet.
    void rejouer(Joueur* joueur); // prenez un autre tour immédiatement après la fin de celui-ci.
    void rajouteBonus(int couleurIndex, Joueur* joueur); // placez cette carte de manière à ce qu'elle chevauche une carte Joyau avec un bonus.

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
