//#include "../include/obligatoire.h"
#include "../include/jeu.h"



void Obligatoire::prendreJeton(Joueur* joueur, ReponseValidationSelection RVS) {
    // Vérifier qu'il y a au moins un jeton sur le plateau
    if (plateau->hasJeton()) {
        // On ajoute les jetons au joueur
        int nb_couleurs[6] = {0, 0, 0, 0, 0, 0};
        for (int i=0; i<RVS.nombre; i++) {
            const Jeton *jeton = RVS.jetons[i];
            switch (jeton->getCouleur()) {
                case Couleur::bleu:
                    nb_couleurs[0] += 1;
                    joueur->setNbJeton(0, joueur->getNbJeton(0) + 1);
                case Couleur::vert:
                    nb_couleurs[1] += 1;
                    joueur->setNbJeton(1, joueur->getNbJeton(1) + 1);
                case Couleur::rouge:
                    nb_couleurs[2] += 1;
                    joueur->setNbJeton(2, joueur->getNbJeton(2) + 1);
                case Couleur::blanc:
                    nb_couleurs[3] += 1;
                    joueur->setNbJeton(3, joueur->getNbJeton(3) + 1);
                case Couleur::noir:
                    nb_couleurs[4] += 1;
                    joueur->setNbJeton(4, joueur->getNbJeton(4) + 1);
                case Couleur::rose:
                    nb_couleurs[5] += 1;
                    joueur->setNbJeton(5, joueur->getNbJeton(5) + 1);
                default: throw PlateauException("Impossible de recuperer ce jeton lors de cette action !");
            }
        }

        // On donne un privilège à l'adversaire si 2 perles ou 3 identiques
        bool give_privilege = false;
        for (int i=0; i<5; i++) {
            if (nb_couleurs[i] == 3) give_privilege = true;
        }
        if (nb_couleurs[5] == 2) give_privilege = true;
        if (give_privilege) {
            Joueur* adversaire = joueur->getAdversaire();
            Privilege* privilege;
            if (adversaire->getNombreDePrivileges() == plateau->getNbPrivilegeMAX()) throw PlateauException("L'adversaire a deja tous les privileges !");
            if (plateau->getNbPrivileges() == 0) {
                privilege = joueur->getPrivilege(0); // Décalage du tableau de privilège à prévoir? Ou suivi de l'index en tant qu'attribut?
                adversaire->ajouterPrivilege(privilege);
            } else {
                privilege = const_cast<Privilege*>(plateau->prendrePrivilege());
                adversaire->ajouterPrivilege(privilege);
            }
        }
    } else throw PlateauException("Le plateau est vide !");
};

void Obligatoire::reserverCarte(Joueur* joueur, ReponseValidationSelection RVS, CarteJoaillerie* card) {
    // Vérifier que la sélection est un jeton or et que le joueur n'a pas 3 cartes réservées déjà
    if (joueur->getNbCartesReservees() == 3) throw PlateauException("Le joueur a deja 3 cartes reservees !");
    if (RVS.nombre != 1) throw PlateauException("La selection n'est pas valide !");
    if (RVS.jetons[0]->getType() != JetonType::Or) throw PlateauException("Ce n'est pas un jeton or !");

    // Ajouter jeton or / Attribute missing?

    // On ajoute la carte réservée
    joueur->ajouterCarteReservee(card);
};

void Obligatoire::acheterCarte(Joueur* joueur, ReponseValidationSelection RVS, CarteJoaillerie* card) {
    // Vérifier achat possible
    std::map<Couleur, int> prix = card->getPrix();
    bool achat_possible = true;
    for (auto elem = prix.begin(); elem != prix.end(); elem++) {
        int price = elem->second;
        switch (elem->first) {
            case Couleur::bleu: if (price - joueur->getGemmesBonus(0) > joueur->getNbJeton(0)) achat_possible = false;
            case Couleur::vert: if (price - joueur->getGemmesBonus(1) > joueur->getNbJeton(1)) achat_possible = false;
            case Couleur::rouge: if (price - joueur->getGemmesBonus(2) > joueur->getNbJeton(2)) achat_possible = false;
            case Couleur::blanc: if (price - joueur->getGemmesBonus(3) > joueur->getNbJeton(3)) achat_possible = false;
            case Couleur::noir: if (price - joueur->getGemmesBonus(4) > joueur->getNbJeton(4)) achat_possible = false;
            case Couleur::rose: if (price - joueur->getGemmesBonus(5) > joueur->getNbJeton(5)) achat_possible = false;
        }
    }

    // Ajouter la carte
    if (!achat_possible) throw PlateauException("Achat non possible !");
    joueur->ajouterCarteJoaillerie(*card);
};


