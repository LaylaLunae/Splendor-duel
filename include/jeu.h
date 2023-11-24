#ifndef JEU_JEU_H
#define JEU_JEU_H
#include <string>
#include <iostream>

#include "carteJoaillerie.h"
#include "carte.h"
#include "carteNoble.h"
#include "privilege.h"
#include "jeton.h"
#include "plateau.h"
#include "optionnelle.h"
#include "pioche.h"
#include "obligatoire.h"
#include "joueur.h"
#include "affichage_joueur.h"


class Jeu{
private:
    /*struct Handler {
        Jeu * instance = nullptr;
        ~Handler() { delete instance; instance = nullptr;}
    };
    static Handler handler;*/

    static Jeu* instance;

    Joueur* joueur_actuel;

    Jeu(){};
    ~Jeu(){};
    Jeu(const Jeu& j) = delete;
    Jeu& operator=(const Jeu& j) = delete;

public:
    static Jeu& getJeu();
    static void libereJeu();

    Joueur* getJoueurActuel() const {return joueur_actuel;}

    void validationAction();

    //pour l'instant dans public
    void nouvellePartie();
    void reprendrePartie(); //faut bdd
    void verifAnciennePartie(); //faut bdd
    void verifGagnant();
    void sauvegarderPartie(); //faut bdd
    Joueur* vainqueur();
    void auSuivant();
    void verifObligationRemplissage();
};

#endif //JEU_JEU_H
