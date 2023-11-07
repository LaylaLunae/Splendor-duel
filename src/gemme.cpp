#include "../include/gemme.h"
#include <iostream>
#include <string>

Gemme::Gemme(Couleur c) : couleur(c) {}

void Gemme::afficher() const {
    std::string couleur_str;
    switch (couleur) {
        case Couleur::rouge: couleur_str = "Rouge"; break;
        case Couleur::vert: couleur_str = "Vert"; break;
        case Couleur::bleu: couleur_str = "Bleu"; break;
        case Couleur::noir: couleur_str = "Noir"; break;
        case Couleur::blanc: couleur_str = "Blanc"; break;
    }
    std::cout << "Jeton Gemme de couleur " << couleur_str << std::endl;
}

Couleur Gemme::getCouleur() const {
    return couleur;
}
