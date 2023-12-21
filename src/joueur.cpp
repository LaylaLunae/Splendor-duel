#include <iostream>
#include <algorithm>
#include <utility>
#include "../include/jeu.h"

Joueur::Joueur(const std::string nom): pseudo(nom), nombre_couronnes(0), points_prestige_total(0), droitDeRejouer(false), adversaire(nullptr){

    // Utilisation de vecteurs au lieu de tableaux statiques
    cartes_reservees.resize(0, nullptr);
    cartes_main.resize(0, nullptr);
    cartes_noble.resize(0, nullptr);
    //gemmes_bonus.resize(0, 0);
    //nb_jeton.resize(0, 0);
    //privileges.resize(0, nullptr);
    points_prestige_couleurs.resize(5,0);
}

// Destructeur
Joueur::~Joueur() {
    for (CarteJoaillerie* carte : cartes_reservees) {
        delete carte;
    }
    cartes_reservees.clear();

    for (CarteJoaillerie* carte : cartes_main) {
        delete carte;
    }
    cartes_main.clear();

    for (const CarteNoble* carte : cartes_noble) {
        delete carte;
    }
    cartes_noble.clear();

    for (Privilege* privilege : privileges) {
        delete privilege;
    }
    privileges.clear();
}

// Constructeur de recopie
Joueur::Joueur(const Joueur& autre)
        : pseudo(autre.pseudo), nombre_couronnes(autre.nombre_couronnes), points_prestige_total(autre.points_prestige_total),
          adversaire(autre.adversaire), droitDeRejouer(autre.droitDeRejouer), points_prestige_couleurs(autre.points_prestige_couleurs),
          gemmes_bonus(autre.gemmes_bonus), nb_jeton(autre.nb_jeton) {

    // Utilisation de la boucle for each pour copier les éléments des vecteurs
    for (const auto& carte : autre.cartes_reservees) {
        cartes_reservees.push_back(new CarteJoaillerie(*carte));
    }

    for (const auto& carte : autre.cartes_main) {
        cartes_main.push_back(new CarteJoaillerie(*carte));
    }

    for (const auto& carte : autre.cartes_noble) {
        cartes_noble.push_back(new CarteNoble(*carte));
    }

    for (const auto& privilege : autre.privileges) {
        privileges.push_back(new Privilege(*privilege));
    }
}

// Opérateur de recopie
Joueur& Joueur::operator=(const Joueur& autre) {
    if (this != &autre) {
        // Utilisation de la méthode clear pour libérer la mémoire des vecteurs
        cartes_reservees.clear();
        cartes_main.clear();
        cartes_noble.clear();
        privileges.clear();

        // Copie des éléments du vecteur
        for (const auto& carte : autre.cartes_reservees) {
            cartes_reservees.push_back(new CarteJoaillerie(*carte));
        }
        for (const auto& carte : autre.cartes_main) {
            cartes_main.push_back(new CarteJoaillerie(*carte));
        }
        for (const auto& carte : autre.cartes_noble) {
            cartes_noble.push_back(new CarteNoble(*carte));
        }
        for (const auto& privilege : autre.privileges) {
            privileges.push_back(new Privilege(*privilege));
        }
    }
    return *this;
}

int Joueur::getPointsPrestigeTotal() const{
    return points_prestige_total;
}

void Joueur::setPointsPrestigeTotal(int pointP) {
    points_prestige_total = pointP;
}

std::string Joueur::getPseudo() const {
    return pseudo;
}

void Joueur::setPseudo(std::string pse) {
    pseudo = std::move(pse);
}

int Joueur::getNombreCouronnes()const {
    return nombre_couronnes;
}

void Joueur::setNombreCouronnes(int nbCour) {
    nombre_couronnes = nbCour;
}

void Joueur::setDifficulte(Difficulte difficulte) {
    diff = difficulte;
}

int Joueur:: getPointsPrestigeCouleurs(int index) const {
    if (index >= 0 && index < 6) {
        return points_prestige_couleurs[index];
    }
    return 0;
}

const CarteJoaillerie * Joueur::getCarteReservee(int index) const {
    if (index >= 0 && index <= 3) {
        return (cartes_reservees[index]);
    }
    return nullptr;
}

CarteJoaillerie * Joueur::getCarteMain(int index) const {
    if (index >= 0 ) {
        return (cartes_main[index]);
    }
    return nullptr;
}

const CarteNoble * Joueur::getCarteNoble(int index) const {
    if (index >= 0 && index < 3) {
        return (cartes_noble[index]);
    }
    return nullptr;
}

int Joueur::getGemmesBonus(int index) const {
    if (index >= 0 && index < 6) {
        return gemmes_bonus[index];
    }
    return 0;
}

int Joueur::getNbJetonTotal() const {
    int totalJetons = 0;
    for (int i = 0; i < nb_jeton.size(); ++i) {
        totalJetons += nb_jeton[i];
    }
    return totalJetons;
}

int Joueur::getNbJetonsParCouleur(int couleur) const {
    int totalJetonsCouleur = 0;
    for (size_t i = 0; i < nb_jeton.size(); ++i) {
        if (gemmes_bonus[i] == couleur) {
            totalJetonsCouleur += nb_jeton[i];
        }
    }
    return totalJetonsCouleur;
}

bool Joueur::getDroitDeRejouer() const { return droitDeRejouer; }

std::vector<CarteJoaillerie*> Joueur::getCartesReservees() const {
    return cartes_reservees;
}

std::vector<CarteJoaillerie*> Joueur::getCartesMain() const {
    return cartes_main;
}

std::vector<const CarteNoble*> Joueur::getCartesNoble() const{
    return cartes_noble;
}

const std::vector<Privilege *>& Joueur::getPrivileges() const {
    return privileges;
}

int Joueur::getNombreDePrivileges() const {
    // Count the number of non-nullptr items using std::count_if and a lambda function
//    std::size_t countNonNullPtrs = std::count_if(privileges.begin(), privileges.end(),
//                                                 [](Privilege* ptr) { return ptr != nullptr; });
//    return countNonNullPtrs;

    return privileges.size();
}

int Joueur::getNbCartesReservees() const {
    return cartes_reservees.size();
}

int Joueur::getNombreCartesNobles() const {
    return cartes_noble.size();
}

int Joueur::getNbJeton(int index) const{
    return nb_jeton[index];
}
void Joueur::setNbJeton(int index, int value){
    nb_jeton[index] = value;
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
    CarteJoaillerie* temp = &carte;
    cartes_main.push_back(const_cast<CarteJoaillerie*>(temp));
}

void Joueur::ajouterCarteNoble(const CarteNoble* carte) {
    int nombreCouronnesCarte = carte->getCouronne();

    // Ajouter le nombre de couronnes à la variable nombre_couronnes
    // Alexandre : NON ! La carte noble ne donne QUE du prestige/pouvoir.
    //nombre_couronnes += nombreCouronnesCarte;
    cartes_noble.push_back(carte);
    // Ajouter les points de prestige de la carte à la variable points_prestige_total
    points_prestige_total += carte->getPointPrestige();
    info->miseAJourInformations();
}

void Joueur::ajouterCarteReservee(CarteJoaillerie *carte) {
    if (cartes_reservees.size() < 3) {
        cartes_reservees.push_back(carte);
    }
    else {
        throw std::runtime_error("Le joueur ne peut pas réserver plus de 3 cartes.");
    }
}

void Joueur::ajouterPrivilege(Privilege *privilege) {
    if (privileges.size() < 3) {
        privileges.push_back(privilege);
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
    return !privileges.empty();
}

Privilege Joueur::removePrivilege() {
    for (int i = 0; i < MAX_PRIVILEGES; i++) {
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
    if (index >= 0 && index < 6) { // Assurez-vous que l'indice est dans la plage valide
        points_prestige_couleurs[index] = valeur;
    } else {
        std::cerr << "L'indice est hors limites." << std::endl;
    }
}

void Joueur::setGemmesBonus(int index, int value) {
    if (index < gemmes_bonus.size())
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

bool Joueur::getIsIA() const {
    return isIA;
}

void Joueur::setIsIA(bool isia) {
    isIA = isia;
}

Difficulte Joueur::getDifficulte() const {
    return diff;
}

void IA::setDifficulte(Difficulte diff) {
    difficulte = diff;
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

// tests
void Joueur::initialiserJoueur() {
    for (int i = 0; i < 10; ++i) {
        CarteJoaillerie* carte = new CarteJoaillerie();
        cartes_main.push_back(carte);
    }
    for (int i = 0; i < 7; ++i) {
        nb_jeton[i] = 10;
    }
}

void FenetreInformations::displayCartes(Joueur* j) {

    while (QLayoutItem *item = layout()->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    const std::vector<CarteJoaillerie *> cartesJoueur = j->getCartesMain();
    for (const CarteJoaillerie *carte: cartesJoueur) {
        //QPushButton *vueCarte = new QPushButton(this);
        VueCarteJoaillerie *vueCarte = new VueCarteJoaillerie(carte, cartesJoueur, this);
        layout()->addWidget(vueCarte);
    }


    while (QLayoutItem *item = layout()->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    const std::vector<const CarteNoble*> cartesNobles = j->getCartesNoble();
    for (const CarteNoble* cn : cartesNobles) {
        VueCarteNoble* vc = new VueCarteNoble(cn->getID(), Jeu::getJeu().getVueJeu()->getVuePlateau(), this);
        layout()->addWidget(vc);
    }
}