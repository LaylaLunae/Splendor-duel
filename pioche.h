#ifndef PIOCHE_H_INCLUDED
#define PIOCHE_H_INCLUDED
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <vector>
#include "carteJoaillerie.h"

/*class CarteJoaillerie {
    const int id;
public:
    CarteJoaillerie(int i):id(i) {};
    ~CarteJoaillerie() = default;
    const int getID() const {return id;}
};*/
class VuePioche;

class Pioche {
private:
    //friend class Jeu;
    friend class VuePioche;

    const int numero_pioche;
    const CarteJoaillerie ** cartes_dans_pioche; // à revoir
    const CarteJoaillerie ** cartes_dehors; // à revoir
    const int max_cartes_revelees;
    int max_cartes_pioche; // pour l'initialisation du tableau cartes_dans_pioche

    Pioche(const Pioche& p) = delete; //pas de recopie
    Pioche& operator=(const Pioche& p) = delete;



public:
    const int getNumeroPioche() const {return numero_pioche;}
    const CarteJoaillerie * getCartesDansPioche(int i) const {return cartes_dans_pioche[i];}
    const CarteJoaillerie * getCartesDehors(int i) const {return cartes_dehors[i];}
    const int getMaxCartesRevelees() const {return max_cartes_revelees;}
    int getMaxCartesPioche() const {return max_cartes_pioche;}

    Pioche(const int np, const int mcr, int mcp);
    ~Pioche(); //à revoir

    const CarteJoaillerie * joueurPrend(int numero_carte);
    void distribution();
    const CarteJoaillerie * joueurPrendPioche();
    void afficherPioche(std::ostream& f = std::cout);
    void afficherCartesRevelees(std::ostream& f = std::cout);

};

class VuePioche : public QWidget {
Q_OBJECT
private:
    std::vector<VueCarteJoaillerie*> vuecartes1;
    std::vector<VueCarteJoaillerie*> vuecartes2;
    std::vector<VueCarteJoaillerie*> vuecartes3;
    std::vector<QPushButton*> vuedoscartes;
    QVBoxLayout * layoutPioches;
    QHBoxLayout * layoutPioche1;
    QHBoxLayout * layoutPioche2;
    QHBoxLayout * layoutPioche3;
    QHBoxLayout * layoutDosPioche;
    QHBoxLayout * layoutPlateauCarte;
    Pioche * p1;
    Pioche * p2;
    Pioche * p3;
private slots:
    int carteClique(VueCarteJoaillerie * c);

public:
    VuePioche(QWidget * parent = nullptr);

};

#endif // PIOCHE_H_INCLUDED
