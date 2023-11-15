#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <iostream>
//#include "carteJoaillerie.h"
//#include "carteNoble.h"
#include "privilege.h"
#include "couleur.h"
//#include "carteJoaillerie.h"
//#include "carteNoble.h"
#include "carte.h" //-> pas besoin ??
class CarteJoaillerie;
class CarteNoble;


class CarteJoaillerie;
class CarteNoble;

const int MAX_CARTES = 10;
const int MAX_PRIVILEGES = 3;

enum Difficulte {facile, moyen, difficile};

class Joueur {
protected:
    std::string pseudo;
    int nombre_couronnes;
    int points_prestige_total;
    int points_prestige_couleurs[5];
    int nb_cartes_reservees;
    CarteJoaillerie *cartes_reservees[3];
    CarteJoaillerie *cartes_main[MAX_CARTES];
    CarteNoble *cartes_noble[2];
    int gemmes_bonus[6];
    int nb_jeton[7]; // Timo - Temporaire pour actions (a un getter et setter)
    Privilege *privileges[3];
    int nombre_de_privileges;


    Joueur* adversaire; // Pointeur vers le joueur adverse
    bool droitDeRejouer; // Marqueur pour le droit de jouer un tour supplémentaire

public:
    Joueur(const std::string nom);
    ~Joueur();
    Joueur(const Joueur& autre);
    Joueur& operator=(const Joueur& autre);

    int getPointsPrestigeTotal() const;
    std::string getPseudo() const;
    int getNombreCouronnes()const;
    int getPointsPrestigeCouleurs(int index) const;
    CarteJoaillerie getCarteReservee(int index) const;
    CarteJoaillerie getCarteMain(int index) const;
    CarteNoble getCarteNoble(int index) const;
    int getGemmesBonus(int index) const;
    Privilege* getPrivilege(int index) const;
    void ajouterCarteJoaillerie(CarteJoaillerie& carte);
    void ajouterCarteNoble(const CarteNoble& carte);
    void ajouterCarteReservee(CarteJoaillerie *carte);
    void ajouterPrivilege(Privilege *privilege);

    void setPointsPrestigeCouleurs(int index, int valeur);
    void setGemmesBonus(int index, int value);

    // Timo - Temporaire pour action
    int getNbJeton(int index) const;
    void setNbJeton(int index, int value);

    // Définir l'adversaire
    Joueur* getAdversaire();
    void setAdversaire(Joueur* adv);
    bool hasPrivilege();
    Privilege removePrivilege();
    // Méthode pour vérifier si le joueur a le droit de jouer à nouveau.
    bool peutRejouer() const;
    // Réinitialisez le droit de jouer à la fin du tour du joueur.
    void resetRejouer(); // Normalement, on passe au tour de l'adversaire
    void resetRejouer(bool reset); // Si vous obtenez le pouvoir, vous pouvez passer au tour suivant et appeler cette fonction

    // Usefull for Optionnelle and Obligatoire
    int getNombreDePrivileges() const { return nombre_de_privileges; }
    int getNbCartesReservees() const { return nb_cartes_reservees; }
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




