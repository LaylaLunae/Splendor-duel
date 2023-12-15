#ifndef PIOCHE_H_INCLUDED
#define PIOCHE_H_INCLUDED
#include <iostream>

//#include "carteJoaillerie.h"

class CarteJoaillerie;
class Jeu;

class Pioche {
    friend Jeu;
private:
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

    const CarteJoaillerie * setCartesDansPioche(const CarteJoaillerie * c, int i) {cartes_dans_pioche[i] = c; return cartes_dans_pioche[i];}
    const CarteJoaillerie * setCartesDehors(const CarteJoaillerie * c, int i) {cartes_dehors[i] = c; return cartes_dehors[i];}

    Pioche(const int np, const int mcr, int mcp);
    ~Pioche();

    const CarteJoaillerie * joueurPrend(int numero_carte);
    void distribution();
    const CarteJoaillerie * joueurPrendPioche();
    void afficherPioche(std::ostream& f = std::cout);
    void afficherCartesRevelees(std::ostream& f = std::cout);

};

#endif // PIOCHE_H_INCLUDED
