#ifndef JETON_H
#define JETON_H

#include <string>
#include "couleur.h"

enum class JetonType {
    Or,
    Gemme,
};

class Jeton {
private:
    JetonType type;
    Couleur couleur; // Utilisé uniquement lorsque type = Gemme
    std::string chemin_vers_image;

public:
    Jeton(JetonType t, Couleur c = Couleur::rien) : type(t), couleur(c) {}
    ~Jeton() {}

    void afficher() const;
    std::string getCouleurString() const;
    Couleur getCouleur() const;
    JetonType getType() const { return type; }
};

#endif // JETON_H
