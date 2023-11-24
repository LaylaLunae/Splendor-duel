#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <iostream>
#include <vector>

class CarteNoble;
class CarteJoaillerie;
class Privilege;

const int MAX_CARTES = 500;
const int MAX_PRIVILEGES = 3;

enum Difficulte { facile, moyen, difficile };

class Joueur {
protected:
    std::string pseudo;
    int nombre_couronnes;
    int points_prestige_total;
    std::vector<int> points_prestige_couleurs;
    //int nb_cartes_reservees;
    std::vector<CarteJoaillerie*> cartes_reservees;
    std::vector<CarteJoaillerie*> cartes_main;
    std::vector<CarteNoble*> cartes_noble;
    std::vector<int> gemmes_bonus;
    std::vector<int> nb_jeton; // Timo - Temporaire pour actions (a un getter et setter)
    std::vector<Privilege*> privileges;
    //int nombre_de_privileges;

    Joueur* adversaire; // Pointeur vers le joueur adverse
    bool droitDeRejouer; // Marqueur pour le droit de jouer un tour supplémentaire

    Joueur(const std::string nom);
    ~Joueur();
    Joueur(const Joueur& autre);
    Joueur& operator=(const Joueur& autre);


public:

    int getPointsPrestigeTotal() const;
    std::string getPseudo() const;
    int getNombreCouronnes() const;
    int getPointsPrestigeCouleurs(int index) const;
    const CarteJoaillerie * getCarteReservee(int index) const;
    CarteJoaillerie * getCarteMain(int index) const;
    CarteNoble * getCarteNoble(int index) const;
    int getGemmesBonus(int index) const;
    //Privilege getPrivilege(int index) const;
    const std::vector<Privilege *> getPrivileges() const;
    void ajouterCarteJoaillerie(CarteJoaillerie& carte);
    void ajouterCarteNoble(const CarteNoble& carte);
    void ajouterCarteReservee(CarteJoaillerie* carte);
    void ajouterPrivilege(Privilege* privilege);

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

    // Utile pour Optionnelle et Obligatoire
    int getNombreDePrivileges() const;
    int getNbCartesReservees() const;
    int getNombreCartesNobles() const;

    int getNbJetonTotal() const;
    int getNbJetonsParCouleur(int couleur) const;

    virtual int choisirChoix(int min, int max) = 0;
};

class IA : public Joueur {
protected:
    Difficulte difficulte;


public:
    IA(const std::string& pseudo, Difficulte diff) : Joueur(pseudo), difficulte(diff) {}
    //int choisirChoix(int min, int max);
    virtual int choisirChoix(int min, int max) override;

};

class Humain : public Joueur {
protected:

public:
    Humain(const std::string& pseudo) : Joueur(pseudo) {}
    //int choisirChoixUtilisateur(int min, int max);
    virtual int choisirChoix(int min, int max) override;
};

#endif // JOUEUR_H
