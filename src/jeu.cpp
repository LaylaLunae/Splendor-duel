#include <iostream>
#include "jeu.h"

/* Jeu& Jeu::getJeu(){
    if (handler.instance == nullptr)
        handler.instance = new Jeu();
    return * handler.instance;
}

void Jeu::libereJeu() {
    delete handler.instance;
    handler.instance = nullptr;
}*/

Jeu * Jeu::instance = nullptr;

Jeu& Jeu::getJeu(){
    if (instance == nullptr)
        instance = new Jeu;
    return * instance;
}

void Jeu::libereJeu() {
    delete instance;
    instance = nullptr;
}

void Jeu::nouvellePartie() {
    /*Pioche pioche1 = Pioche(1,5,30);
    Pioche pioche2 = Pioche(2,4,24);
    Pioche pioche3 = Pioche(3,3,13);

    pioche1.distribution();
    pioche2.distribution();
    pioche3.distribution();*/

    //choisir IA ou Joueur : interface ?
}

Joueur* Jeu::vainqueur(){
    return joueur_actuel;
}

void Jeu::auSuivant(){
    joueur_actuel = joueur_actuel->getAdversaire();
}

void Jeu::verifGagnant() {
    if (joueur_actuel->getNombreCouronnes() >= 10)
        vainqueur();
    else if (joueur_actuel->getPointsPrestigeTotal() >= 20)
        vainqueur();
    else {
        bool gagnant = false;
        for (int i = 0; i<5; i++)
            if (joueur_actuel->getPointsPrestigeCouleurs(i) >= 10)
                gagnant = true;
        if (gagnant)
            vainqueur();
        else
            auSuivant();
    }
}

void Jeu::verifObligationRemplissage(){

}

void Jeu::validationAction() {
    // si bouton pressé
        // recueillir variable qui contient bouton choisi
        // si variable vide -> peut pas presser bouton ?
        // appeler action correspondante
}
