#include "../include/jeton.h"
#include <iostream>
#include <string>

void Jeton::afficher() const {
    std::string type_str;
    switch (type) {
        case JetonType::Or: {
            type_str = "Or";
            std::cout << "Jeton " << type_str << std::endl;
            break;
        }
        case JetonType::Gemme: {
            type_str = "Gemme";
            std::string couleur_str;
            switch (couleur) {
                case Couleur::rouge:
                    couleur_str = "Rouge";
                    break;
                case Couleur::vert:
                    couleur_str = "Vert";
                    break;
                case Couleur::bleu:
                    couleur_str = "Bleu";
                    break;
                case Couleur::noir:
                    couleur_str = "Noir";
                    break;
                case Couleur::blanc:
                    couleur_str = "Blanc";
                    break;
                case Couleur::rose:
                    couleur_str = "Rose";
                    break;
                case Couleur::rien:
                    couleur_str = "Rien";
                    break;
            }
            std::cout << "Jeton " << type_str << " de couleur " << couleur_str << std::endl;
            break;
        }
        default:
            std::cout << "Jeton Inconnu" << std::endl;
            break;
    }
}

Couleur Jeton::getCouleur() const {
    if (type == JetonType::Gemme) {
        return couleur;
    }
    return Couleur::rien;
}
