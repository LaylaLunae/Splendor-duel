//#include "../include/joueur.h"
//#include "../include/carteJoaillerie.h"
#include <iostream>
#include "../include/jeu.h"
//#include "../include/carteJoaillerie.h"

Joueur::Joueur(const std::string nom): pseudo(nom), nombre_couronnes(0), points_prestige_total(0),droitDeRejouer(false),adversaire(nullptr),nb_cartes_reservees(0),nombre_de_privileges(0) {

    for (int i = 0; i < 3; i++) {
        cartes_reservees[i] = nullptr;
        privileges[i] = nullptr;
    }
    for(int i=0; i<MAX_CARTES;i++){
        cartes_main[i] = nullptr;
    }
    for (int i=0; i<2;i++){
        cartes_noble[i] = nullptr;
    }
    for (int i = 0; i < 5; i++) {
        gemmes_bonus[i] = 0;
        points_prestige_couleurs[i] = 0;
    }
    for(int i=0; i<7;i++){
        nb_jeton[i]=0;
    }
}

// Destructeur
Joueur::~Joueur() {

    for (int i = 0; i < nb_cartes_reservees; ++i) {
        delete cartes_reservees[i];
    }

    for (int i = 0; i < MAX_CARTES; ++i) {
        delete cartes_main[i];
    }

    for (int i = 0; i < 2; ++i) {
        delete cartes_noble[i];
    }

    for (int i = 0; i < nombre_de_privileges; ++i) {
        delete privileges[i];
    }
}

// Constructeur de recopie
Joueur::Joueur(const Joueur& autre) {
    pseudo = autre.pseudo;
    nombre_couronnes = autre.nombre_couronnes;
    points_prestige_total = autre.points_prestige_total;
    nb_cartes_reservees = autre.nb_cartes_reservees;
    nombre_de_privileges = autre.nombre_de_privileges;
    adversaire = autre.adversaire;
    droitDeRejouer = autre.droitDeRejouer;

    for (int i = 0; i < 5; ++i) {
        points_prestige_couleurs[i] = autre.points_prestige_couleurs[i];
    }
    for (int i = 0; i < 6; ++i) {
        gemmes_bonus[i] = autre.gemmes_bonus[i];
        nb_jeton[i] = autre.nb_jeton[i];
    }

    for (int i = 0; i < 3; ++i) {
        cartes_reservees[i] = new CarteJoaillerie(*(autre.cartes_reservees[i]));
    }
    for (int i = 0; i < MAX_CARTES; ++i) {
        cartes_main[i] = new CarteJoaillerie(*(autre.cartes_main[i]));
    }
    for (int i = 0; i < 2; ++i) {
        cartes_noble[i] = new CarteNoble(*(autre.cartes_noble[i]));
    }

    for (int i = 0; i < 3; ++i) {
        privileges[i] = new Privilege(*(autre.privileges[i]));
    }
}

// Opérateur de recopie
Joueur& Joueur::operator=(const Joueur& autre) {
    if (this != &autre) {

        this->~Joueur();

        new (this) Joueur(autre);
    }
    return *this;
}


int Joueur::getPointsPrestigeTotal() const{
    return points_prestige_total;
}

std::string Joueur::getPseudo() const {
    return pseudo;
}

int Joueur::getNombreCouronnes()const {
    return nombre_couronnes;
}

int Joueur:: getPointsPrestigeCouleurs(int index) const {
    if (index >= 0 && index < 5) {
        return points_prestige_couleurs[index];
    }
    return 0;
}

CarteJoaillerie Joueur::getCarteReservee(int index) const {
    if (index >= 0 && index <= 3) {
        return reinterpret_cast<const CarteJoaillerie &>(cartes_reservees[index]);
    }
    return CarteJoaillerie();
}

CarteJoaillerie Joueur::getCarteMain(int index) const {
    if (index >= 0 ) {
        return reinterpret_cast<const CarteJoaillerie &>(cartes_main[index]);
    }
    return CarteJoaillerie();
}

CarteNoble Joueur::getCarteNoble(int index) const {
    if (index >= 0 && index < 3) {
        return reinterpret_cast<const CarteNoble &>(cartes_noble[index]);
    }
    return CarteNoble();
}

int Joueur::getGemmesBonus(int index) const {
    if (index >= 0 && index < 6) {
        return gemmes_bonus[index];
    }
    return 0;
}

Privilege* Joueur::getPrivilege(int index) const {
    if (index >= 0 && index < 3) {
        return privileges[index];
    }
    return nullptr;
}

void Joueur::ajouterCarteJoaillerie(CarteJoaillerie& carte) {
    int nombrePointsCarte = carte.getPointsPrestige();
    int nombreCouronnesCarte = carte.getCourronnes();

    // Ajouter les points de prestige si la carte en a
    if (nombrePointsCarte > 0) {
        points_prestige_total += nombrePointsCarte;
    }
    // Ajouter les points dans la couleur du bijou si la carte en a
    Couleur couleurBijou = carte.getTypePierre();
    if (Couleur::rien!= couleurBijou) {
        points_prestige_couleurs[static_cast<int>(couleurBijou)] += nombrePointsCarte;
    }

    // Ajouter le nombre de couronnes si la carte en a
    if (nombreCouronnesCarte > 0) {
        nombre_couronnes += nombreCouronnesCarte;
    }

    if(carte.getTypePierre()!=Couleur::choix_utilisateur){
        int j = static_cast<int>(carte.getTypePierre());
        gemmes_bonus[j]++;
    }

    // Ajouter le nombre de bonus (gemme) si la carte en a
    if(carte.getTypePierre()!=Couleur::rien){
        if(carte.getNombrePierre()==1) {
            int i = static_cast<int>(carte.getTypePierre());
            gemmes_bonus[i]+=carte.getNombrePierre();
        }
    }
}

void Joueur::ajouterCarteNoble(const CarteNoble& carte) {

    int nombreCouronnesCarte = carte.getCouronne();

    // Vérifier si le joueur a 3 ou 6 couronnes dans son jeu
    if (nombre_couronnes == 3 || nombre_couronnes == 6) {
        // Ajouter le nombre de couronnes à la variable nombre_couronnes
        nombre_couronnes += nombreCouronnesCarte;

        // Ajouter les points de prestige de la carte à la variable points_prestige_total
        points_prestige_total += carte.getPointPrestige();
    }
    else{
        throw ("Le joueur doit avoir 3 ou 6 couronnes pour ajouter une carte noble.");
    }
}

void Joueur::ajouterCarteReservee(CarteJoaillerie *carte) {
    if (nb_cartes_reservees < 3) {
        cartes_reservees[nb_cartes_reservees] = carte;
        nb_cartes_reservees++;
    }
    else {
        throw std::runtime_error("Le joueur ne peut pas réserver plus de 3 cartes.");
    }
}

void Joueur::ajouterPrivilege(Privilege *privilege) {
    if (nombre_de_privileges < 3) {
        privileges[nombre_de_privileges]=privilege;
        nombre_de_privileges++;
    }
    else {
        throw std::runtime_error("Le joueur ne peut pas avoir plus de 3 privilèges.");
    }
}


// Définir l'adversaire
void Joueur::setAdversaire(Joueur *adv) {
    adversaire = adv;
    if (adv->adversaire == nullptr) { // Assurez-vous que l'adversaire désigne également le joueur actuel comme adversaire
        adv->setAdversaire(this);
    }
}

Joueur* Joueur::getAdversaire() {
    return adversaire;
}

bool Joueur::hasPrivilege() {
    if (this->privileges != nullptr)
        return true;
    return false;
}

Privilege Joueur::removePrivilege() {
    for (int i = 0; i < MAX_PRIVILEGES; ++i) {
        if (privileges[i]->getStatus() != PrivilegeStatus::NONE) {
            Privilege* tmp = privileges[i];
            privileges[i]->setStatus(PrivilegeStatus::NONE);
            return *tmp;
        }
    }
    throw std::runtime_error("No privilege to remove");
}

// Ajouter une méthode setter à la classe Joueur
void Joueur::setPointsPrestigeCouleurs(int index, int valeur) {
    if (index >= 0 && index < 5) { // Assurez-vous que l'indice est dans la plage valide
        points_prestige_couleurs[index] = valeur;
    } else {
        std::cerr << "L'indice est hors limites." << std::endl;
    }
}

void Joueur::setGemmesBonus(int index, int value) {
    this->gemmes_bonus[index] = value;
}

// Méthode pour vérifier si le joueur a le droit de jouer à nouveau.
bool Joueur::peutRejouer() const {
    return droitDeRejouer;
}

// Réinitialisez le droit de jouer à la fin du tour du joueur.
void Joueur::resetRejouer() {
    if (droitDeRejouer == true)
        droitDeRejouer = false;
    else
        droitDeRejouer = true;
}

void Joueur::resetRejouer(bool reset) {
    droitDeRejouer = reset;
}





// Flux ostream
std::ostream& operator<<(std::ostream& os, const Joueur& joueur) {
    os << "Pseudo: " << joueur.getPseudo() << "\n";
    os << "Nombre de couronnes: " << joueur.getNombreCouronnes() << "\n";
    os << "Points de prestige total: " << joueur.getPointsPrestigeTotal() << "\n";

    os << "Points de prestige par couleur: ";
    for (int i = 0; i < 5; ++i) {
        os << joueur.getPointsPrestigeCouleurs(i) << " ";
    }
    os << "\n";

    os << "Gemmes bonus: ";
    for (int i = 0; i < 6; ++i) {
        os << joueur.getGemmesBonus(i) << " ";
    }
    os << "\n";

    os << "Nombre de jetons: ";
    for (int i = 0; i < 6; ++i) {
        os << joueur.getNbJeton(i) << " ";
    }
    os << "\n";
    return os;
}

