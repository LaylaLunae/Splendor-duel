#include "carteJoaillerie.h"

CarteJoaillerie::CarteJoaillerie(Plateau* p, Joueur* j, int niv, int cour, const std::array<Couleur, 2>& pierres, std::map<Couleur, int> prx, const std::string& chemin, int prestige, const Pouvoir& pvr1, const Pouvoir& pvr2, const int id)
        : Carte(chemin, prestige, cour, pvr1, pvr2, p, j), niveau(niv), couronne(cour), pierres(pierres), prix(prx), id(id) {
    // Constructor implementation
}

CarteJoaillerie::CarteJoaillerie()
        : Carte(), niveau(0), couronne(0), pierres({Couleur::rien, Couleur::rien}), prix(), id(0) {}

CarteJoaillerie::CarteJoaillerie(int i)
        : Carte(), niveau(0), couronne(0), pierres({Couleur::rien, Couleur::rien}), prix(), id(i) {}


CarteJoaillerie::~CarteJoaillerie() {
    // Destructor implementation, if needed
}

std::map<Couleur, int> CarteJoaillerie::getPrix() const {
    return prix;
}

int CarteJoaillerie::getNiveau() const {
    return niveau;
}

int CarteJoaillerie::getCouronne() const {
    return couronne;
}

const int CarteJoaillerie::getID() const {
    return id;
}

bool CarteJoaillerie::hasPierre() const {
    for (const auto& pierre : pierres) {
        if (pierre != Couleur::rien) {
            return true;  // Au moins il y a une pierre sans rien dessus
        }
    }
    return false;
}

// 如果您想返回第一个非rien的pierre的类型
Couleur CarteJoaillerie::getTypePierre() const {
    for (const auto& pierre : pierres) {
        if (pierre != Couleur::rien) {
            return pierre;  // Au moins il y a une pierre sans rien dessus
        }
    }
    return Couleur::rien;
}


void CarteJoaillerie::setPierreColor(int index, Couleur couleur) {
    if (index >= 0 && index < pierres.size()) {
        pierres[index] = couleur;
    }
}

std::array<Couleur, 2> CarteJoaillerie::getPierres() const {
    return pierres;
}

int CarteJoaillerie::getNombrePierre() const {
    int count = 0;
    for (const auto& pierre : pierres) {
        if (pierre != Couleur::rien) {
            count++;
        }
    }
    return count;
}

