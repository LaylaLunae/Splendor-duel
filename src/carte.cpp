//#include "../include/jeu.h"
//#include "../include/carte.h"
#include "../include/jeu.h"
//#include <bits/stdc++.h>

Carte::Carte(const std::string& chemin, int prestige, int cour, Pouvoir pvr1, Pouvoir pvr2, Plateau* p, Joueur* j)
        : chemin_vers_image(chemin), point_prestige(prestige), courronnes(cour), pouvoirs({pvr1, pvr2}), plateau(p), joueur(j) {
}

Carte::Carte(){}

int Carte::getPointsPrestige() {
    return point_prestige;
}

int Carte::getCourronnes() {
    return courronnes;
}

void Carte::actionPouvoir() {
    for (const auto& pouvoir : pouvoirs) {
        std::string couleurChoisie;
        Couleur couleur;

        if (pouvoir == Pouvoir::rien) continue; // 跳过没有的pouvoir

        switch (pouvoir) {
            case Pouvoir::nouveau_tour:
                rejouer();
                break;
            case Pouvoir::bonus_pierre:
                while (true) {
                    std::cout << "Quel bonus de couleur souhaitez-vous ? bleu, vert, rouge, blanc, noir, rose?" << std::endl;
                    std::cin >> couleurChoisie;

                    std::transform(couleurChoisie.begin(), couleurChoisie.end(), couleurChoisie.begin(), ::tolower);

                    auto it = couleurMap.find(couleurChoisie);
                    if (it != couleurMap.end()) {
                        couleur = it->second;
                        break;
                    } else {
                        std::cout << "Couleur invalide. Veuillez réessayer." << std::endl;
                    }
                }
                rajouteBonus(static_cast<int>(couleur));
                break;
            case Pouvoir::pierre_en_plus:
                std::cout << "Quelle couleur de jeton voulez-vous voler? Sélectionner l'abscisse x et l'ordonnée y du plateau" << std::endl;
                int x,y;
                std::cin >> x;
                std::cin >> y;
                prendreJeton(x,y);
                break;
            case Pouvoir::privilege_en_plus:
                prendrePrivilege();
                break;
            case Pouvoir::vol_pierre:
                while (true) {
                    std::cout << "Quel bonus de jeton voulez-vous voler ? bleu, vert, rouge, blanc, noir, rose?" << std::endl;
                    std::cin >> couleurChoisie;

                    std::transform(couleurChoisie.begin(), couleurChoisie.end(), couleurChoisie.begin(), ::tolower);

                    auto it = couleurMap.find(couleurChoisie);
                    if (it != couleurMap.end()) {
                        couleur = it->second;
                        break;
                    } else {
                        std::cout << "Couleur invalide. Veuillez réessayer." << std::endl;
                    }
                }
                volerJeton(static_cast<int>(static_cast<int>(couleur)));
                break;
            case Pouvoir::rien:
            default:
                break;
        }
    }
}

std::array<Pouvoir, 2> Carte::existancePouvoir() {
    return this->pouvoirs;
}

Privilege Carte::prendrePrivilege() {
    // Essayez d'obtenir le privilège du Plateau.
    // 1. Si le Plateau a un Privilège disponible, le Joueur actuel appelle ajouterPrivilege() pour l'ajouter à sa propre liste de privilèges.
    // 2. S'il n'y a pas de Privilège disponible sur le Plateau, le Joueur actuel doit en prendre un au Privilège de l'adversaire (si celui-ci en a un).
    const Privilege* privilegeDuPlateau = plateau->prendrePrivilege();
    if (privilegeDuPlateau != nullptr) {
        // Copie du privilège retourné par le plateau
        Privilege privilegeTemp = *privilegeDuPlateau;

        // Ajout du privilège temporaire au joueur
        joueur->ajouterPrivilege(&privilegeTemp);

        // Retour du privilège temporaire pour une utilisation future si nécessaire
        return privilegeTemp;
    } else {
        // Il n'y a aucun privilege sur le plateau, essayez d'en prendre un à adversaire
        if (this->joueur->getAdversaire()->hasPrivilege()) { // 检查对手是否有特权
            Privilege oppPrivilege = this->joueur->getAdversaire()->removePrivilege();
            this->joueur->ajouterPrivilege(&oppPrivilege);
        }
    }
}


// Implémentation de la méthode volerJeton dans la classe Carte
bool Carte::volerJeton(int couleurIndex) {
    // Vérifiez que le joueur et son adversaire sont bien définis
    if (this->joueur == nullptr || this->joueur->getAdversaire() == nullptr) {
        std::cerr << "Les joueurs ne sont pas initialisés ou n'existent pas." << std::endl;
        return false;
    }

    Joueur* adversaire = this->joueur->getAdversaire();

    // Vérifiez que l'adversaire a des ressources de la couleur spécifiée
    if (adversaire->getPointsPrestigeCouleurs(couleurIndex) > 0) {
        // Soustraire une ressource de l'adversaire
        adversaire->setPointsPrestigeCouleurs(couleurIndex, adversaire->getPointsPrestigeCouleurs(couleurIndex) - 1);
        // Ajouter une ressource au joueur actuel
        this->joueur->setPointsPrestigeCouleurs(couleurIndex, this->joueur->getPointsPrestigeCouleurs(couleurIndex) + 1);

        return true;
    }

    // Si l'adversaire n'a pas de ressource de la couleur spécifiée ou si l'opération échoue
    return false;
}


bool Carte::prendreJeton(unsigned int position_x, unsigned int position_y) {
    if (plateau->hasJeton()) {
        const Jeton* j = plateau->prendreJeton(position_x, position_y);
        int couleurIndex = static_cast<int>(j->getCouleur());
        joueur->setPointsPrestigeCouleurs(couleurIndex, this->joueur->getPointsPrestigeCouleurs(couleurIndex) + 1); // Add one token of the specified color to the player's inventory
            return true;
    }
    return false;
}

void Carte::rejouer() {
    this->joueur->resetRejouer(true);
    this->joueur->getAdversaire()->resetRejouer(false);
}

void Carte::rajouteBonus(int couleurIndex) {
    this->joueur->setGemmesBonus(couleurIndex,this->joueur->getGemmesBonus(couleurIndex) + 1);
}
