#ifndef COULEUR_H
#define COULEUR_H

#include <map>
#include <string>

enum class Couleur {
    bleu, vert, rouge, blanc, noir, rose, rien, choix_utilisateur
};

inline std::map<std::string, Couleur> couleurMap = {
        {"bleu", Couleur::bleu},
        {"vert", Couleur::vert},
        {"rouge", Couleur::rouge},
        {"blanc", Couleur::blanc},
        {"noir", Couleur::noir},
        {"rose", Couleur::rose},
        {"rien", Couleur::rien},
        {"choix_utilisateur", Couleur::choix_utilisateur}
};

#endif // COULEUR_H
