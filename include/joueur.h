#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <map>
#include <iostream>
#include "couleur.h"
#include "carteJoaillerie.h"
#include "carteNoble.h"
#include "privilege.h"

const int MAX_CARTES = 10;
const int MAX_PRIVILEGES = 3;

enum Difficulte {facile, moyen, difficile};

class Joueur {
private:
    std::string pseudo;
    int nombre_couronnes;
    int points_prestige_total;
    int points_prestige_couleurs[5];
    CarteJoaillerie cartes_reservees[6];
    CarteJoaillerie cartes_main[6];
    CarteNoble cartes_noble[6];
    int gemmes_bonus[5];
    Privilege privileges[6];


    Joueur* adversaire; // Pointeur vers le joueur adverse
    bool droitDeRejouer; // Marqueur pour le droit de jouer un tour supplémentaire

public:
    Joueur(const std::string nom);
    int getPointsPrestigeTotal() const;
    std::string getPseudo() const;
    int getNombreCouronnes()const;
    int getPointsPrestigeCouleurs(int index) const;
    CarteJoaillerie getCarteReservee(int index) const;
    CarteJoaillerie getCarteMain(int index) const;
    CarteNoble getCarteNoble(int index) const;
    int getGemmesBonus(int index) const;
    Privilege getPrivilege(int index) const;
    void ajouterCarteJoaillerie(const CarteJoaillerie& carte);
    void ajouterCarteNoble(const CarteNoble& carte);
    void ajouterCarteReservee(const CarteJoaillerie& carte);
    void ajouterPrivilege(const Privilege& privilege);


    // Définir l'adversaire
    Joueur* getAdversaire();
    void setAdversaire(Joueur* adv);
    bool hasPrivilege();
    Privilege removePrivilege();
    // Méthode pour vérifier si le joueur a le droit de jouer à nouveau.
    bool peutRejouer() const;
    // Réinitialisez le droit de jouer à la fin du tour du joueur.
    void resetRejouer();
    void resetRejouer(bool reset);
};


class IA : public Joueur {
private:
    Difficulte difficulte;

public:
    IA(const std::string& pseudo, Difficulte diff) : Joueur(pseudo),difficulte(diff) {

    }
};

class Humain : public Joueur {
public:
    Humain(const std::string& pseudo) : Joueur(pseudo) {

    }

};



#endif // JOUEUR_H




