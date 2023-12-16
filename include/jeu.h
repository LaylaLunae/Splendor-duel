#ifndef JEU_JEU_H
#define JEU_JEU_H
#include <string>

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

#include <sqlite3.h>
#include "query.h"


class Jeu {
private:
    /*struct Handler {
        Jeu * instance = nullptr;
        ~Handler() { delete instance; instance = nullptr;}
    };
    static Handler handler;*/

    static Jeu* instance;

    Joueur* joueur_actuel;
    Joueur* joueur_gagnant;

    Jeu():joueur_actuel(nullptr),joueur_gagnant(nullptr){};
    ~Jeu(){};
    Jeu(const Jeu& j) = delete;
    Jeu& operator=(const Jeu& j) = delete;
    //void verifCarteNoble(Joueur * j, Plateau * p);

public:
    static Jeu& getJeu();
    static void libereJeu();

    Joueur* getJoueurActuel() const {return joueur_actuel;}
    Joueur* getJoueurGagnant() const {return joueur_gagnant;}
    void setJoueurActuel(Joueur* joueur) {joueur_actuel = joueur;}
    void setJoueurGagnant(Joueur* joueur) {joueur_gagnant = joueur;}

    void validationAction();

    //pour l'instant dans public
    void nouvellePartie(); // faut bdd
    //void reprendrePartie(); //faut bdd
    //void verifAnciennePartie(); //faut bdd  Zhenyang: pas necessaire
    //void sauvegarderPartie(); //faut bdd
    void verifGagnant(Joueur * j1, Joueur * j2);
    void vainqueur(Joueur * j);
    void auSuivant(Joueur * j1, Joueur * j2);
    void verifCarteNoble(Joueur * j, Plateau * p);

    void manche(Plateau * p, Pioche * p1, Pioche * p2, Pioche * p3, Joueur * j1, Joueur * j2, Obligatoire * obl, Optionnelle * opt);
    void tour(Plateau * p, Pioche * p1, Pioche * p2, Pioche * p3, Joueur * j, Obligatoire * obl, Optionnelle * opt);
};

/* =============================================== Fonctions avec BDD =============================================== */
void executeSQL(sqlite3* db, const std::string& sql);

void initCarteJoaillerie(sqlite3* db, std::vector<const CarteJoaillerie*>* cartes);
void initCarteNoble(sqlite3* db, std::vector<const CarteNoble*>* cartesNoble);
//void initPrivileges(sqlite3* db, std::vector<const Privilege*>* privileges);

// Interface de fonction pour initialiser toute la base de données du jeu
void clearAndInitializeTables(sqlite3* db);

// Interface fonctionnelle pour stocker l'intégralité du jeu
void sauvegarderPartie(sqlite3* db,
        //const std::vector<CarteJoaillerie>& cartesDansPioche,
        //const std::vector<CarteJoaillerie>& cartesDehors,
                       const Jeu& jeu,
                       const Joueur& joueur1,
                       const Joueur& joueur2,
                       std::vector<Pioche *> pioches,
                       const Plateau& plateau);

// Interface de récupération de données pour continuer le jeu
void continuerLaPartie(sqlite3* db,
                       std::vector<CarteJoaillerie*>& cartesJoaillerie, // Avant de continuer le jeu, vous devez initialiser toutes les cartesJoaillerie
                       std::vector<const CarteNoble*>& cartesNoble, // Avant de continuer le jeu, vous devez initialiser toutes les cartesNoble
                       //std::vector<CarteJoaillerie>& cartesDansPioche,
                       //std::vector<CarteJoaillerie>& cartesDehors,
                       Jeu& jeu, // Avant de continuer le jeu, vous devez initialiser un objet vide pour stocker les données lues.
                       Joueur* joueur1,
                       Joueur* joueur2,
                       std::vector<Pioche*>& pioches,
                       Plateau& plateau,
                       std::vector<Privilege*> privileges);


class VueJeu : public QWidget {
    Q_OBJECT
public:
    VueJeu(Jeu* jeu, QWidget *parent = nullptr);
private:

    Jeu* jeu;
    Joueur* j1;
    Joueur* j2;
    Pioche* pioche1;
    Pioche* pioche2;
    Pioche* pioche3;
    std::vector<Pioche*> pioches;
    std::vector<CarteJoaillerie*> cartesJoaillerie;


    QVBoxLayout* layout_main;
    QHBoxLayout* layout_centre;
    QHBoxLayout *layout_bas;
    VuePlateau* vue_plateau;

    QPushButton*  bouton_sauvegarde;

    sqlite3* db;

   // void sauvegarder();
private slots:
    void boutonSauvegardeClick();
};

#endif //JEU_JEU_H
