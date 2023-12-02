//#include "../include/obligatoire.h"
#include "../include/jeu.h"

// L28 + L110  //  L152->154 +

void Obligatoire::prendreJeton(Joueur* joueur, Plateau* plateau) {
    // Vérifier que le plateau n'est point vide
    if (!plateau->hasJeton()) {
        std::cout << "Plateau vide\n";
        return;
    }

    // Le joueur récupère les jetons
    std::tuple<int, int> jeton_choisi(0, 0);
    std::vector<const Jeton*> selection;
    int cpt = 0, n = 0, jeton_selec;
    while (n < 1 or n > 3) {
        std::cout << "Combien de jetons comptez vous prendre ? (MAX 3)   n = ";
        std::cin >> n;
        std::cout << "\n";
        if (n < 0) std::cout << "Vous voulez prendre des jetons, pas en remettre...\n";
        if (n == 0) std::cout << "Attraper de l'air ne va pas vous aider a gagner...\n";
        if (n > 3) std::cout << "Il faut jouer en respectant les regles quand meme...\n";
    }
    while (cpt != n) {
        do {
            jeton_choisi = choisir_jeton();
            //jeton_selec = plateau->selectionJeton(std::get<0>(jeton_choisi), std::get<1>(jeton_choisi));
            // Renvoie un int "code d'erreur" - 0 OK - 1 CASE VIDE - 2 JETON OR - 3 2 OR SELEC - 4 MAUVAISES POSITIONS
            switch (jeton_selec) {
                case 0: std::cout << "Selection autorise\n";
                case 1: std::cout << "Case vide\n";
                case 2:
                    std::cout << "Vous ne pouvez selectionner de jeton or lors de cette action !\n";
                    // Désélection
                    plateau->selectionJeton(std::get<0>(jeton_choisi), std::get<1>(jeton_choisi));
                    // case 3 théoriquement impossible
                case 4: std::cout << "Ce jeton ne peut etre selectionne !\n";
                default: std::cout << "Pour une raison ou une autre, il y a eu un probleme...\n";
            }
        } while (jeton_selec != 0);
        cpt++;
    }
    selection = plateau->validerSelectionEtPrendreJetons();

    // On ajoute les jetons au joueur
    std::vector<int> nb_couleurs(6, 0);
    // Bleu - Vert - Rouge - Blanc - Noir - Rose(Perle)
    for (int i = 0; i < selection.size(); i++) {
        const Jeton *jeton = selection[i];
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
            default: std::cout << "Il y a definitivement un probleme avec la selection...\n";
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
        std::vector<Privilege*> privileges;
        Privilege* privilege;
        if (adversaire->getNombreDePrivileges() == plateau->getNbPrivilegeMAX()) std::cout << "L'adversaire a deja tous les privileges.\n";
        if (plateau->getNbPrivileges() == 0) {
            privileges = joueur->getPrivileges();
            adversaire->ajouterPrivilege(privileges.back());
            privileges.pop_back();
        } else {
            privilege = const_cast<Privilege*>(plateau->prendrePrivilege());
            adversaire->ajouterPrivilege(privilege);
        }
    }
};

void Obligatoire::reserverCarte(Joueur* joueur, Plateau* plateau) {
    // Vérifier que le plateau a au moins 1 jeton or et que le joueur n'a pas 3 cartes réservées déjà
    if (!plateau->hasJetonOr()) {
        std::cout << "Aucun jeton or de disponible sur le plateau !\n";
        return;
    }
    if (joueur->getNbCartesReservees() == 3) std::cout << "Le joueur a deja 3 cartes reservees !";

    // On récupère un jeton or
    std::tuple<int, int> jeton_choisi(0, 0);
    std::vector<const Jeton*> selection;
    int jeton_selec;
    do {
        jeton_choisi = choisir_jeton();
        //jeton_selec = plateau->selectionJeton(std::get<0>(jeton_choisi), std::get<1>(jeton_choisi));
        // Renvoie un int "code d'erreur" - 0 OK - 1 CASE VIDE - 2 JETON OR - 3 2 OR SELEC - 4 MAUVAISES POSITIONS
        switch (jeton_selec) {
            case 0:
                std::cout << "Ce n'est pas un jeton or !\n";
                // Désélection
                plateau->selectionJeton(std::get<0>(jeton_choisi), std::get<1>(jeton_choisi));
            case 1: std::cout << "Case vide\n";
            case 2:
                std::cout << "Selection autorise\n";
                // case 3 théoriquement impossible
            case 4: std::cout << "Ce jeton ne peut etre selectionne !\n";
            default: std::cout << "Pour une raison ou une autre, il y a eu un probleme...\n";
        }
    } while (jeton_selec != 0);
    selection = plateau->validerSelectionEtPrendreJetons();

    // On ajoute le jeton or au joueur
    joueur->setNbJeton(6, joueur->getNbJeton(6) + 1);

    // Le joueur choisi quoi faire exactement
    int choix;
    do {
        std::cout << "Que voulez vous faire ?\n";
        std::cout << "Reserver 1 carte Joaillerie de votre choix dans la pyramide ? (1)\n";
        std::cout << "Reserver la premiere carte de l’un des 3 paquets ? (2)";
        std::cout << "Choix (1 ou 2) : ";
        std::cin >> choix;
        std::cout << "\n";
    } while (choix != 1 and choix != 2);

    // Il choisi alors une carte en fonction de son choix
    int n_carte, n_pioche;
    Pioche* pioche;
    CarteJoaillerie* card;
    do {
        std::cout << "Dans quelle pioche souhaitez vous piocher - (1, 2, 3) ? Pioche = ";
        std::cin >> n_pioche;
        std::cout << "\n";
        if (n_pioche < 1 or n_pioche > 3) std::cout << "Numero de pioche invalide !\n";
    } while (n_pioche < 1 or n_pioche > 3);
    switch (n_pioche) {
        //case 1: pioche = Jeu::getPioche1();
        //case 2: pioche = Jeu::getPioche2();
        //case 3: pioche = Jeu::getPioche3();
        default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
    }
    if (choix == 1) {
        do {
            std::cout << "Quelle carte revelee voulez vous prendre - (La plus a gauche etant la premiere, soit 1) ? Carte = ";
            std::cin >> n_carte;
            std::cout << "\n";
            if (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees()) std::cout << "Numero de carte invalide !\n";
        } while (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees());
        card = const_cast<CarteJoaillerie*>(pioche->joueurPrend(n_carte));
    } else {
        std::cout << "Vous reservez la premiere carte de cette pioche.\n";
        card = const_cast<CarteJoaillerie*>(pioche->joueurPrendPioche());
    }

    // On ajoute la carte réservée
    joueur->ajouterCarteReservee(card);
};

void Obligatoire::acheterCarte(Joueur* joueur, Plateau* plateau) {
    // Vérifier où le joueur peut acheter une carte
    bool achat_pioche1_possible = false;
    bool achat_pioche2_possible = false;
    bool achat_pioche3_possible = false;
    bool achat_carte_reservees_possible = false;
    // TEMPORAIRE
    Pioche* pioche1;
    Pioche* pioche2;
    Pioche* pioche3;
    //pioche1 = Jeu::getPioche1();
    //pioche2 = Jeu::getPioche2();
    //pioche3 = Jeu::getPioche3();
    const CarteJoaillerie* carte;
    std::map<Couleur, int> prix;
    // Pioche1?
    for (int i = 0; i < pioche1->getMaxCartesRevelees(); i++) {
        carte = pioche1->getCartesDehors(i);
        if (carte != nullptr) {
            prix = carte->getPrix();
            std::vector<int> difference(6);
            for (auto elem = prix.begin(); elem != prix.end(); elem++) {
                int prix_elem = elem->second;
                switch (elem->first) {
                    case Couleur::bleu: difference[0] = prix_elem - joueur->getGemmesBonus(0) - joueur->getNbJeton(0);
                    case Couleur::vert: difference[1] = prix_elem - joueur->getGemmesBonus(1) - joueur->getNbJeton(1);
                    case Couleur::rouge: difference[2] = prix_elem - joueur->getGemmesBonus(2) - joueur->getNbJeton(2);
                    case Couleur::blanc: difference[3] = prix_elem - joueur->getGemmesBonus(3) - joueur->getNbJeton(3);
                    case Couleur::noir: difference[4] = prix_elem - joueur->getGemmesBonus(4) - joueur->getNbJeton(4);
                    case Couleur::rose: difference[5] = prix_elem - joueur->getGemmesBonus(5) - joueur->getNbJeton(5);
                }
            }
            bool achat_possible = true;
            for (int j = 0; j < difference.size(); j++) {
                if (difference[i] > 0) achat_possible = false;
            }
            if (!achat_possible) {
                int somme = 0;
                for (int j = 0; j < difference.size(); j++) {
                    if (difference[i] > 0) somme += difference[i];
                }
                if (somme < joueur->getNbJeton(6)) achat_possible = true;
            }
            if (achat_possible) achat_pioche1_possible = true;
        }
    }
    // Pioche2?
    for (int i = 0; i < pioche2->getMaxCartesRevelees(); i++) {
        carte = pioche2->getCartesDehors(i);
        if (carte != nullptr) {
            prix = carte->getPrix();
            std::vector<int> difference(6);
            for (auto elem = prix.begin(); elem != prix.end(); elem++) {
                int prix_elem = elem->second;
                switch (elem->first) {
                    case Couleur::bleu: difference[0] = prix_elem - joueur->getGemmesBonus(0) - joueur->getNbJeton(0);
                    case Couleur::vert: difference[1] = prix_elem - joueur->getGemmesBonus(1) - joueur->getNbJeton(1);
                    case Couleur::rouge: difference[2] = prix_elem - joueur->getGemmesBonus(2) - joueur->getNbJeton(2);
                    case Couleur::blanc: difference[3] = prix_elem - joueur->getGemmesBonus(3) - joueur->getNbJeton(3);
                    case Couleur::noir: difference[4] = prix_elem - joueur->getGemmesBonus(4) - joueur->getNbJeton(4);
                    case Couleur::rose: difference[5] = prix_elem - joueur->getGemmesBonus(5) - joueur->getNbJeton(5);
                }
            }
            bool achat_possible = true;
            for (int j = 0; j < difference.size(); j++) {
                if (difference[i] > 0) achat_possible = false;
            }
            if (!achat_possible) {
                int somme = 0;
                for (int j = 0; j < difference.size(); j++) {
                    if (difference[i] > 0) somme += difference[i];
                }
                if (somme < joueur->getNbJeton(6)) achat_possible = true;
            }
            if (achat_possible) achat_pioche2_possible = true;
        }
    }
    // Pioche3?
    for (int i = 0; i < pioche3->getMaxCartesRevelees(); i++) {
        carte = pioche3->getCartesDehors(i);
        if (carte != nullptr) {
            prix = carte->getPrix();
            std::vector<int> difference(6);
            for (auto elem = prix.begin(); elem != prix.end(); elem++) {
                int prix_elem = elem->second;
                switch (elem->first) {
                    case Couleur::bleu: difference[0] = prix_elem - joueur->getGemmesBonus(0) - joueur->getNbJeton(0);
                    case Couleur::vert: difference[1] = prix_elem - joueur->getGemmesBonus(1) - joueur->getNbJeton(1);
                    case Couleur::rouge: difference[2] = prix_elem - joueur->getGemmesBonus(2) - joueur->getNbJeton(2);
                    case Couleur::blanc: difference[3] = prix_elem - joueur->getGemmesBonus(3) - joueur->getNbJeton(3);
                    case Couleur::noir: difference[4] = prix_elem - joueur->getGemmesBonus(4) - joueur->getNbJeton(4);
                    case Couleur::rose: difference[5] = prix_elem - joueur->getGemmesBonus(5) - joueur->getNbJeton(5);
                }
            }
            bool achat_possible = true;
            for (int j = 0; j < difference.size(); j++) {
                if (difference[i] > 0) achat_possible = false;
            }
            if (!achat_possible) {
                int somme = 0;
                for (int j = 0; j < difference.size(); j++) {
                    if (difference[i] > 0) somme += difference[i];
                }
                if (somme < joueur->getNbJeton(6)) achat_possible = true;
            }
            if (achat_possible) achat_pioche3_possible = true;
        }
    }
    // Cartes réservées?
    for (int i = 0; i < joueur->getNbCartesReservees(); i++) {
        carte = joueur->getCarteReservee(i);
        if (carte != nullptr) {
            prix = carte->getPrix();
            std::vector<int> difference(6);
            for (auto elem = prix.begin(); elem != prix.end(); elem++) {
                int prix_elem = elem->second;
                switch (elem->first) {
                    case Couleur::bleu: difference[0] = prix_elem - joueur->getGemmesBonus(0) - joueur->getNbJeton(0);
                    case Couleur::vert: difference[1] = prix_elem - joueur->getGemmesBonus(1) - joueur->getNbJeton(1);
                    case Couleur::rouge: difference[2] = prix_elem - joueur->getGemmesBonus(2) - joueur->getNbJeton(2);
                    case Couleur::blanc: difference[3] = prix_elem - joueur->getGemmesBonus(3) - joueur->getNbJeton(3);
                    case Couleur::noir: difference[4] = prix_elem - joueur->getGemmesBonus(4) - joueur->getNbJeton(4);
                    case Couleur::rose: difference[5] = prix_elem - joueur->getGemmesBonus(5) - joueur->getNbJeton(5);
                }
            }
            bool achat_possible = true;
            for (int j = 0; j < difference.size(); j++) {
                if (difference[j] > 0) achat_possible = false;
            }
            if (!achat_possible) {
                int somme = 0;
                for (int j = 0; j < difference.size(); j++) {
                    if (difference[j] > 0) somme += difference[j];
                }
                if (somme < joueur->getNbJeton(6)) achat_possible = true;
            }
            if (achat_possible) achat_carte_reservees_possible = true;
        }
    }

    // Le joueur choisit ce qu'il veut faire en fonction de ce qu'il peut faire
    int n_carte, n_pioche, choix;
    Pioche* pioche;
    bool achat_possible = true;
    prix = carte->getPrix();
    std::vector<int> difference(6);
    do {
        if (achat_carte_reservees_possible and (achat_pioche1_possible or achat_pioche2_possible or achat_pioche3_possible)) {
            std::cout << "Souhaitez vous acheter une carte reservee (1) ou une carte revelee (2) ? Choix = ";
            std::cin >> choix;
            std::cout << "\n";
            if (choix == 1) {
                do {
                    std::cout << "Quelle carte reservee voulez vous prendre ? Carte = ";
                    std::cin >> n_carte;
                    std::cout << "\n";
                    if (n_carte < 1 or n_carte > joueur->getNbCartesReservees()) std::cout << "Numero de carte invalide !\n";
                } while (n_carte < 1 or n_carte > joueur->getNbCartesReservees());
                carte = joueur->getCarteReservee(n_carte-1);
            } else if (choix == 2) {
                if (achat_pioche1_possible and achat_pioche2_possible and achat_pioche3_possible) {
                    do {
                        std::cout << "Dans quelle pioche souhaitez vous piocher - (1, 2, 3) ? Pioche = ";
                        std::cin >> n_pioche;
                        std::cout << "\n";
                        if (n_pioche < 1 or n_pioche > 3) std::cout << "Numero de pioche invalide !\n";
                    } while (n_pioche < 1 or n_pioche > 3);
                    switch (n_pioche) {
                        case 1: pioche = pioche1;
                        case 2: pioche = pioche2;
                        case 3: pioche = pioche3;
                        default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                    }
                } else if (achat_pioche1_possible and achat_pioche2_possible) {
                    do {
                        std::cout << "Dans quelle pioche souhaitez vous piocher - (1, 2) ? Pioche = ";
                        std::cin >> n_pioche;
                        std::cout << "\n";
                        if (n_pioche != 1 and n_pioche != 2) std::cout << "Numero de pioche invalide !\n";
                    } while (n_pioche != 1 and n_pioche != 2);
                    switch (n_pioche) {
                        case 1: pioche = pioche1;
                        case 2: pioche = pioche2;
                        default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                    }
                } else if (achat_pioche1_possible and achat_pioche3_possible) {
                    do {
                        std::cout << "Dans quelle pioche souhaitez vous piocher - (1, 3) ? Pioche = ";
                        std::cin >> n_pioche;
                        std::cout << "\n";
                        if (n_pioche != 1 and n_pioche != 3) std::cout << "Numero de pioche invalide !\n";
                    } while (n_pioche != 1 and n_pioche != 3);
                    switch (n_pioche) {
                        case 1: pioche = pioche1;
                        case 3: pioche = pioche2;
                        default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                    }
                } else if (achat_pioche2_possible and achat_pioche3_possible) {
                    do {
                        std::cout << "Dans quelle pioche souhaitez vous piocher - (2, 3) ? Pioche = ";
                        std::cin >> n_pioche;
                        std::cout << "\n";
                        if (n_pioche != 2 and n_pioche != 3) std::cout << "Numero de pioche invalide !\n";
                    } while (n_pioche != 2 and n_pioche != 3);
                    switch (n_pioche) {
                        case 2: pioche = pioche1;
                        case 3: pioche = pioche2;
                        default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                    }
                } else if (achat_pioche1_possible) {
                    std::cout << "Vous devez acheter votre carte dans la pioche 1 obligatoirement.\n";
                    pioche = pioche1;
                } else if (achat_pioche2_possible) {
                    std::cout << "Vous devez acheter votre carte dans la pioche 2 obligatoirement.\n";
                    pioche = pioche2;
                } else if (achat_pioche3_possible) {
                    std::cout << "Vous devez acheter votre carte dans la pioche 3 obligatoirement.\n";
                    pioche = pioche3;
                }
                do {
                    std::cout << "Quelle carte revelee voulez vous prendre - (La plus a gauche etant la premiere, soit 1) ? Carte = ";
                    std::cin >> n_carte;
                    std::cout << "\n";
                    if (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees()) std::cout << "Numero de carte invalide !\n";
                } while (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees());
                carte = pioche->joueurPrend(n_carte);
            }
        } else if (achat_carte_reservees_possible) {
            do {
                std::cout << "Quelle carte reservee voulez vous prendre ? Carte = ";
                std::cin >> n_carte;
                std::cout << "\n";
                if (n_carte < 1 or n_carte > joueur->getNbCartesReservees()) std::cout << "Numero de carte invalide !\n";
            } while (n_carte < 1 or n_carte > joueur->getNbCartesReservees());
            carte = joueur->getCarteReservee(n_carte-1);
        } else if (achat_pioche1_possible or achat_pioche2_possible or achat_pioche3_possible) {
            if (achat_pioche1_possible and achat_pioche2_possible and achat_pioche3_possible) {
                do {
                    std::cout << "Dans quelle pioche souhaitez vous piocher - (1, 2, 3) ? Pioche = ";
                    std::cin >> n_pioche;
                    std::cout << "\n";
                    if (n_pioche < 1 or n_pioche > 3) std::cout << "Numero de pioche invalide !\n";
                } while (n_pioche < 1 or n_pioche > 3);
                switch (n_pioche) {
                    case 1: pioche = pioche1;
                    case 2: pioche = pioche2;
                    case 3: pioche = pioche3;
                    default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                }
            } else if (achat_pioche1_possible and achat_pioche2_possible) {
                do {
                    std::cout << "Dans quelle pioche souhaitez vous piocher - (1, 2) ? Pioche = ";
                    std::cin >> n_pioche;
                    std::cout << "\n";
                    if (n_pioche != 1 and n_pioche != 2) std::cout << "Numero de pioche invalide !\n";
                } while (n_pioche != 1 and n_pioche != 2);
                switch (n_pioche) {
                    case 1: pioche = pioche1;
                    case 2: pioche = pioche2;
                    default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                }
            } else if (achat_pioche1_possible and achat_pioche3_possible) {
                do {
                    std::cout << "Dans quelle pioche souhaitez vous piocher - (1, 3) ? Pioche = ";
                    std::cin >> n_pioche;
                    std::cout << "\n";
                    if (n_pioche != 1 and n_pioche != 3) std::cout << "Numero de pioche invalide !\n";
                } while (n_pioche != 1 and n_pioche != 3);
                switch (n_pioche) {
                    case 1: pioche = pioche1;
                    case 3: pioche = pioche2;
                    default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                }
            } else if (achat_pioche2_possible and achat_pioche3_possible) {
                do {
                    std::cout << "Dans quelle pioche souhaitez vous piocher - (2, 3) ? Pioche = ";
                    std::cin >> n_pioche;
                    std::cout << "\n";
                    if (n_pioche != 2 and n_pioche != 3) std::cout << "Numero de pioche invalide !\n";
                } while (n_pioche != 2 and n_pioche != 3);
                switch (n_pioche) {
                    case 2: pioche = pioche1;
                    case 3: pioche = pioche2;
                    default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                }
            } else if (achat_pioche1_possible) {
                std::cout << "Vous devez acheter votre carte dans la pioche 1 obligatoirement.\n";
                pioche = pioche1;
            } else if (achat_pioche2_possible) {
                std::cout << "Vous devez acheter votre carte dans la pioche 2 obligatoirement.\n";
                pioche = pioche2;
            } else if (achat_pioche3_possible) {
                std::cout << "Vous devez acheter votre carte dans la pioche 3 obligatoirement.\n";
                pioche = pioche3;
            }
            do {
                std::cout << "Quelle carte revelee voulez vous prendre - (La plus a gauche etant la premiere, soit 1) ? Carte = ";
                std::cin >> n_carte;
                std::cout << "\n";
                if (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees()) std::cout << "Numero de carte invalide !\n";
            } while (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees());
            carte = pioche->joueurPrend(n_carte);
        } else {
            std::cout << "Achat impossible!";
            return;
        }
        // Vérifier achat possible de la carte
        for (auto elem = prix.begin(); elem != prix.end(); elem++) {
            int prix_elem = elem->second;
            switch (elem->first) {
                case Couleur::bleu: difference[0] = prix_elem - joueur->getGemmesBonus(0) - joueur->getNbJeton(0);
                case Couleur::vert: difference[1] = prix_elem - joueur->getGemmesBonus(1) - joueur->getNbJeton(1);
                case Couleur::rouge: difference[2] = prix_elem - joueur->getGemmesBonus(2) - joueur->getNbJeton(2);
                case Couleur::blanc: difference[3] = prix_elem - joueur->getGemmesBonus(3) - joueur->getNbJeton(3);
                case Couleur::noir: difference[4] = prix_elem - joueur->getGemmesBonus(4) - joueur->getNbJeton(4);
                case Couleur::rose: difference[5] = prix_elem - joueur->getGemmesBonus(5) - joueur->getNbJeton(5);
            }
        }
        bool achat_possible = true;
        for (int j = 0; j < difference.size(); j++) {
            if (difference[j] > 0) achat_possible = false;
        }
        if (!achat_possible) {
            int somme = 0;
            for (int j = 0; j < difference.size(); j++) {
                if (difference[j] > 0) somme += difference[j];
            }
            if (somme < joueur->getNbJeton(6)) achat_possible = true;
        }
        if (achat_possible) achat_carte_reservees_possible = true;
        if (!achat_possible) std::cout << "Vous ne pouvez pas acheter cette carte !\n";
    } while (!achat_possible);

    // On ajoute la carte au joueur
    joueur->ajouterCarteJoaillerie(*(const_cast<CarteJoaillerie*>(carte)));

    // On retire les jetons au joueur et les remet dans le sac
    for (auto elem = prix.begin(); elem != prix.end(); elem++) {
        int prix_elem = elem->second;
        switch (elem->first) {
            case Couleur::bleu: remettreJetonSac(joueur, plateau, Couleur::bleu, difference[0], prix_elem, 0);
            case Couleur::vert: remettreJetonSac(joueur, plateau, Couleur::bleu, difference[1], prix_elem, 1);
            case Couleur::rouge: remettreJetonSac(joueur, plateau, Couleur::bleu, difference[2], prix_elem, 2);
            case Couleur::blanc: remettreJetonSac(joueur, plateau, Couleur::bleu, difference[3], prix_elem, 3);
            case Couleur::noir: remettreJetonSac(joueur, plateau, Couleur::bleu, difference[4], prix_elem, 4);
            case Couleur::rose: remettreJetonSac(joueur, plateau, Couleur::bleu, difference[5], prix_elem, 5);
        }
    }
};

void Obligatoire::remettreJetonSac(Joueur* joueur, Plateau* plateau, Couleur c, int difference, int prix_elem, int index) {
    if (difference > 0) {
        for (int i = 0; i < joueur->getNbJeton(index); i++) {
            const Jeton* j = new Jeton(JetonType::Gemme, Couleur::bleu);
            plateau->ajouterSac(j);
        }
        for (int i = 0; i < difference; i++) {
            const Jeton* j = new Jeton(JetonType::Or);
            plateau->ajouterSac(j);
        }
        joueur->setNbJeton(index, 0);
        joueur->setNbJeton(6, joueur->getNbJeton(6) - difference);
    } else {
        for (int i = 0; i < prix_elem; i++) {
            const Jeton* j = new Jeton(JetonType::Gemme, Couleur::bleu);
            plateau->ajouterSac(j);
        }
        joueur->setNbJeton(index, joueur->getNbJeton(index) - prix_elem);
    }
}

void Obligatoire::ajouterJetonsJoueur(Joueur* joueur, ReponseValidationSelection* selection) {
    // On ajoute les jetons au joueur
    //std::vector<int> nb_couleurs(7, 0);
    // Bleu - Vert - Rouge - Blanc - Noir - Rose(Perle) - Or
    for (int i = 0; i < selection->nombre; i++) {
        const Jeton *jeton = selection->jetons[i];
        if (jeton->getType() == JetonType::Or) {
            joueur->setNbJeton(7, joueur->getNbJeton(7) + 1);
        } else {
            switch (jeton->getCouleur()) {
                case Couleur::bleu:
                    //nb_couleurs[0] += 1;
                    joueur->setNbJeton(0, joueur->getNbJeton(0) + 1);
                case Couleur::vert:
                    //nb_couleurs[1] += 1;
                    joueur->setNbJeton(1, joueur->getNbJeton(1) + 1);
                case Couleur::rouge:
                    //nb_couleurs[2] += 1;
                    joueur->setNbJeton(2, joueur->getNbJeton(2) + 1);
                case Couleur::blanc:
                    //nb_couleurs[3] += 1;
                    joueur->setNbJeton(3, joueur->getNbJeton(3) + 1);
                case Couleur::noir:
                    //nb_couleurs[4] += 1;
                    joueur->setNbJeton(4, joueur->getNbJeton(4) + 1);
                case Couleur::rose:
                    //nb_couleurs[5] += 1;
                    joueur->setNbJeton(5, joueur->getNbJeton(5) + 1);
                default: std::cout << "Il y a definitivement un probleme avec la selection...\n";
            }
        }
    }
}