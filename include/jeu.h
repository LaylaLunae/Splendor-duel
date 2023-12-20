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
#include "affichage_joueur.h"

#include <sqlite3.h>
#include "query.h"


class VueJeu;

class Jeu {
private:
    /*struct Handler {
        Jeu * instance = nullptr;
        ~Handler() { delete instance; instance = nullptr;}
    };
    static Handler handler;*/

    static Jeu* instance;
    VueJeu* vue_jeu;

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

    VueJeu* getVueJeu() {return vue_jeu;}
    Joueur* getJoueurActuel() const {return joueur_actuel;}
    Joueur* getJoueurGagnant() const {return joueur_gagnant;}
    void setJoueurActuel(Joueur* joueur) {joueur_actuel = joueur;}
    void setJoueurGagnant(Joueur* joueur) {joueur_gagnant = joueur;}
    void setVueJeu(VueJeu* vj) {vue_jeu=vj;}

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
Jeton* queryJetonById(sqlite3* db, int jetonId);

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
                       Jeu* jeu, // Avant de continuer le jeu, vous devez initialiser un objet vide pour stocker les données lues.
                       Joueur* joueur1,
                       Joueur* joueur2,
                       std::vector<Pioche*>& pioches,
                       Plateau& plateau,
                       std::vector<Privilege*> privileges);


class VueJeu : public QWidget {
    Q_OBJECT
public:
    VueJeu(Jeu* jeu, QWidget *parent = nullptr);

    void finiAction(int action);

    void message(const char title[], const char texte[]);

private:


    int compteur_action_optionelles= 2;
    bool a_fini_optionnelles = false;
    bool a_fini_obligatoires = false;

    Jeu* jeu;
    Joueur* j1;
    Joueur* j2;
    Pioche* pioche1;
    Pioche* pioche2;
    Pioche* pioche3;
    std::vector<Pioche*> pioches;
    std::vector<CarteJoaillerie*> cartesJoaillerie;


    QVBoxLayout* layout_main;
    QVBoxLayout* layout_menu;
    QVBoxLayout* layout_jeu;
    QHBoxLayout* layout_centre;
    QHBoxLayout* layout_top;
    QHBoxLayout *layout_bas;
    VuePlateau* vue_plateau;
    FenetreInformations* vueJoueur1;
    FenetreInformations* vueJoueur2;
    std::vector<VueCarteNoble*> vuesCartesNobles;

    QPushButton* bouton_nouvelle_partie;
    QPushButton* bouton_charger_partie;
    QPushButton*  bouton_sauvegarde;

    // ---------- Choix actions ---------------
    QPushButton* bouton_depenser_privilege;
    QPushButton* bouton_prendre_jeton;
    QPushButton* bouton_acheter_carte;
    QPushButton* bouton_reserver_carte;
    QPushButton* bouton_remplir_plateau;

    sqlite3* db;

   // void sauvegarder();
   void dessinerPartie();
   void deleteLayout(QLayout* layout);
   void afficherChoix();
    void desactiverOuActiverBouton(bool etat);
    void setEtatBoutonPrivilege();

   // Ecrit un message console si le plateau n'est pas définie
   bool checkPlateau() {
       bool b =  vue_plateau== nullptr ||
                  (vue_plateau != nullptr && vue_plateau->getPlateau()== nullptr);
       if (b) {
           std::cerr<<"Plateau ou VuePlateau non définie dans VueJeu !";
       }
       return b;
   }

private slots:
    void boutonSauvegardeClick();
    void boutonNouvellePartie();
    void boutonChargerPartie();
    void boutonActionPrivilege();
    void boutonPrendreJeton();
    void boutonRemplirPlateau();
    void boutonAcheterCarte();
    void boutonReserverCarte();
};

#endif //JEU_JEU_H
