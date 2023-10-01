#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <map>
#include "couleur.h"
#include "carteJoaillerie.h"
#include "carteNoble.h"
#include "privilege.h"

const int MAX_CARTES = 10;
const int MAX_PRIVILEGES = 5;

class Joueur {
private:
    std::string pseudo;
    int nombre_couronnes;
    int points_prestige_total;
    std::map<Couleur, int> points_prestige_couleurs;
    CarteJoaillerie cartes_reservees[MAX_CARTES];
    int cartes_reservees_count;
    CarteJoaillerie cartes_main[MAX_CARTES];
    int cartes_main_count;
    CarteNoble cartes_noble[MAX_CARTES];
    int cartes_noble_count;
    std::map<Couleur, int> gemmes_bonus;
    Privilege privileges[MAX_PRIVILEGES];
    int privileges_count;

public:
    Joueur(std::string nom);
    int getPoints() const;
    std::string getPseudo() const;
    void ajouterCarteJoaillerie(const CarteJoaillerie& carte);
    void ajouterCarteNoble(const CarteNoble& carte);
    void ajouterCarteReservee(const CarteJoaillerie& carte);
    void ajouterPrivilege(const Privilege& privilege);
};

#endif // JOUEUR_H
