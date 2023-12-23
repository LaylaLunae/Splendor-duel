#ifndef PIOCHE_H_INCLUDED
#define PIOCHE_H_INCLUDED
#include <iostream>

//#include "carteJoaillerie.h"

class CarteJoaillerie;
class Jeu;

class Pioche {
    friend Jeu;
    friend class VuePioche;
private:
    const int numero_pioche; //le numéro de la pioche
    const CarteJoaillerie ** cartes_dans_pioche; // les cartes de la pioche
    const CarteJoaillerie ** cartes_dehors; // les cartes révélées sur le plateau
    const int max_cartes_revelees; // le nombre max de cartes révélées
    int max_cartes_pioche; // pour l'initialisation du tableau cartes_dans_pioche

    Pioche(const Pioche& p) = delete; //pas de recopie
    Pioche& operator=(const Pioche& p) = delete;



public:
    const int getNumeroPioche() const {return numero_pioche;}
    const CarteJoaillerie * getCartesDansPioche(int i) const {return cartes_dans_pioche[i];}
    const CarteJoaillerie * getCartesDehors(int i) const {return cartes_dehors[i];}
    const int getMaxCartesRevelees() const {return max_cartes_revelees;}
    int getMaxCartesPioche() const {return max_cartes_pioche;}

    const CarteJoaillerie * setCartesDansPioche(const CarteJoaillerie * c, int i) {
        cartes_dans_pioche[i] = c;
        std::cout<<"\n              Carte numero  "<<i <<" Elle est nullptr : ";
        if (c== nullptr)
            std::cout<<"VRAI";
        return cartes_dans_pioche[i];
    }
    const CarteJoaillerie * setCartesDehors(const CarteJoaillerie * c, int i) {cartes_dehors[i] = c; return cartes_dehors[i];}
    //change la carte du tas de cartes révélées

    Pioche(const int np, const int mcr, int mcp); // constructeur
    ~Pioche(); // destructeur

    const CarteJoaillerie * joueurPrend(int numero_carte); //prend une carte parmi les cartes révélées
    void distribution(); //distribue les cartes au début de la partie
    const CarteJoaillerie * joueurPrendPioche(); //prend une carte au hasard dans la pioche
    void afficherPioche(std::ostream& f = std::cout); //pour l'affichage en console
    void afficherCartesRevelees(std::ostream& f = std::cout); //pour l'affichage en console

};

class VuePioche : public QWidget {
Q_OBJECT
private:
    std::vector<VueCarteJoaillerie*> vuecartes1;
    std::vector<VueCarteJoaillerie*> vuecartes2;
    std::vector<VueCarteJoaillerie*> vuecartes3;
    std::vector<std::vector<VueCarteJoaillerie*>*> vuescartes_tot;
    std::vector<QPushButton*> vuedoscartes;
    QVBoxLayout * layoutPioches;
    QHBoxLayout * layoutPioche1;
    QHBoxLayout * layoutPioche2;
    QHBoxLayout * layoutPioche3;
    std::vector<QHBoxLayout*> layout_pioches;
    QVBoxLayout * layoutDosPioche;
    QHBoxLayout * layoutPlateauCarte;
    VueCarteJoaillerie * carteSelectionnee;
    QPushButton * valider;
    std::vector<Pioche*> pioches;
    std::vector<CarteJoaillerie*> tot_cartes_jo;

    bool est_en_action_achat = false;

    void mettreAJour(int index_to_update, int index_carte);

public slots:
    void carteClique(VueCarteJoaillerie *);
    void validerCarte();

public:
    VuePioche(Pioche * p1, Pioche * p2, Pioche * p3, std::vector<CarteJoaillerie*> tot_cartes_jo, QWidget * parent = nullptr);

    void setStatutActif(bool nouvel_etat = false);

};


#endif // PIOCHE_H_INCLUDED
