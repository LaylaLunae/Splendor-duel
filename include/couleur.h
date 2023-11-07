#ifndef COULEUR_H
#define COULEUR_H

enum class Couleur {
    bleu, vert, rouge, blanc, noir, rose, rien
};

std::map<std::string, Couleur> couleurMap = {
        {"bleu", Couleur::bleu},
        {"vert", Couleur::vert},
        {"rouge", Couleur::rouge},
        {"blanc", Couleur::blanc},
        {"noir", Couleur::noir},
        {"rose", Couleur::rose},
        {"rien", Couleur::rien}
};

#endif // COULEUR_H
