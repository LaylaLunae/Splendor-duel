//#include "../include/obligatoire.h"
#include "../include/jeu.h"

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
            jeton_selec = plateau->selectionJeton(std::get<0>(jeton_choisi), std::get<1>(jeton_choisi));
            // Renvoie un int "code d'erreur" - 0 OK - 1 CASE VIDE - 2 JETON OR - 3 2 OR SELEC - 4 MAUVAISES POSITIONS
            switch (jeton_selec) {
                case 0: std::cout << "Selection autorise\n"; break;
                case 1: std::cout << "Case vide\n"; break;
                case 2:
                    std::cout << "Vous ne pouvez selectionner de jeton or lors de cette action !\n";
                    // Désélection
                    plateau->selectionJeton(std::get<0>(jeton_choisi), std::get<1>(jeton_choisi));
                    break;
                case 3: std::cout << "Vous ne pouvez selectionner de jeton or lors de cette action, encore moins 2 !\n"; //théoriquement impossible
                case 4: std::cout << "Ce jeton ne peut etre selectionne !\n"; break;
                default: std::cout << "Pour une raison ou une autre, il y a eu un probleme...\n";
            }
        } while (jeton_selec != 0);
        cpt++;
    }
    selection = plateau->validerSelectionEtPrendreJetons();

    // On ajoute les jetons au joueur
    std::vector<int> nb_couleurs;
    nb_couleurs = ajouterJetonsJoueur(joueur, selection);

    // On donne un privilège à l'adversaire si 2 perles ou 3 identiques
    bool give_privilege = false;
    for (int i=0; i<5; i++) {
        if (nb_couleurs[i] == 3) give_privilege = true;
    }
    if (nb_couleurs[5] >= 2) give_privilege = true;
    if (give_privilege) {
        donnerPrivilegeAdversaire(joueur, plateau);
    }
}

void Obligatoire::demanderCarteAReserver(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3) {
    // Vérifier que le plateau a au moins 1 jeton or et que le joueur n'a pas 3 cartes réservées déjà
    if (!plateau->hasJetonOr()) {
        std::cout << "Aucun jeton or de disponible sur le plateau !\n";
        return;
    }
    if (joueur->getNbCartesReservees() == 3) {
        std::cout << "Le joueur a deja 3 cartes reservees !";
        return;
    }

    // On récupère un jeton or
    std::tuple<int, int> jeton_choisi(0, 0);
    std::vector<const Jeton*> selection;
    int jeton_selec;
    do {
        jeton_choisi = choisir_jeton();
        jeton_selec = plateau->selectionJeton(std::get<0>(jeton_choisi), std::get<1>(jeton_choisi));
        // Renvoie un int "code d'erreur" - 0 OK - 1 CASE VIDE - 2 JETON OR - 3 2 OR SELEC - 4 MAUVAISES POSITIONS
        switch (jeton_selec) {
            case 0:
                std::cout << "Ce n'est pas un jeton or !\n";
                // Désélection
                plateau->selectionJeton(std::get<0>(jeton_choisi), std::get<1>(jeton_choisi));
                break;
            case 1: std::cout << "Case vide\n"; break;
            case 2:
                std::cout << "Selection autorise\n";
                break;
                // case 3 théoriquement impossible
            case 4: std::cout << "Ce jeton ne peut etre selectionne !\n"; break;
            default: std::cout << "Pour une raison ou une autre, il y a eu un probleme...\n";
        }
    } while (jeton_selec != 0);
    selection = plateau->validerSelectionEtPrendreJetons();

    // On ajoute le jeton or au joueur
    ajouterJetonsJoueur(joueur, selection);

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
    bool carte_revelee = true;
    if (choix == 2)  carte_revelee = false;

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
        case 1: pioche = p1; break;
        case 2: pioche = p2; break;
        case 3: pioche = p3; break;
        default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
    }
    if (carte_revelee) {
        do {
            std::cout << "Quelle carte revelee voulez vous prendre - (La plus a gauche etant la premiere, soit 1) ? Carte = ";
            std::cin >> n_carte;
            std::cout << "\n";
            if (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees()) std::cout << "Numero de carte invalide !\n";
        } while (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees());
    } else {
        std::cout << "Vous reservez la premiere carte de cette pioche.\n";
    }

    reserverCarte(joueur, plateau, p1, p2, p3, n_pioche, n_carte, carte_revelee);
}

void Obligatoire::reserverCarte(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3, int n_pioche, int n_carte, bool carte_revelee) {
    // Vérifier que le plateau a au moins 1 jeton or et que le joueur n'a pas 3 cartes réservées déjà
    if (!plateau->hasJetonOr()) {
        std::cout << "Aucun jeton or de disponible sur le plateau !\n";
        return;
    }
    if (joueur->getNbCartesReservees() == 3) {
        std::cout << "Le joueur a deja 3 cartes reservees !";
        return;
    }

    Pioche* pioche;
    CarteJoaillerie* card;
    switch (n_pioche) {
        case 1: pioche = p1; break;
        case 2: pioche = p2; break;
        case 3: pioche = p3; break;
        default: {
            std::cout << "Numero de pioche invalide !\n";
            return;
        }
    }
    if (carte_revelee) {
        if (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees()) {
            std::cout << "Numero de carte invalide !\n";
            return;
        }
        int id = pioche->getCartesDehors(n_carte-1)->getID();
        card = const_cast<CarteJoaillerie*>(pioche->joueurPrend(id));
    } else {
        card = const_cast<CarteJoaillerie*>(pioche->joueurPrendPioche());
    }
    joueur->ajouterCarteReservee(card);
}

void Obligatoire::acheterCarte(Joueur* joueur, Plateau* plateau, Pioche* p1, Pioche* p2, Pioche* p3) {
    // Vérifier où le joueur peut acheter une carte
    // Pioche1?
    bool achat_pioche1_possible = achatPiochePossible(joueur, p1);
    // Pioche2?
    bool achat_pioche2_possible = achatPiochePossible(joueur, p2);
    // Pioche3?
    bool achat_pioche3_possible = achatPiochePossible(joueur, p3);
    // Cartes réservées?
    bool achat_carte_reservees_possible = false;
    const CarteJoaillerie* carte;
    std::map<Couleur, int> prix;
    for (int i = 0; i < joueur->getNbCartesReservees(); i++) {
        carte = joueur->getCarteReservee(i);
        if (carte != nullptr) {
            prix = carte->getPrix();
            std::vector<int> difference = calculDifference(joueur, prix);
            if (achatCartePossible(joueur, difference)) achat_carte_reservees_possible = true;
        }
    }

    // Le joueur choisit ce qu'il veut faire en fonction de ce qu'il peut faire
    int n_carte, n_pioche, choix;
    Pioche* pioche;
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
                        case 1: pioche = p1; break;
                        case 2: pioche = p2; break;
                        case 3: pioche = p3; break;
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
                        case 1: pioche = p1; break;
                        case 2: pioche = p2; break;
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
                        case 1: pioche = p1; break;
                        case 3: pioche = p2; break;
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
                        case 2: pioche = p1; break;
                        case 3: pioche = p2; break;
                        default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                    }
                } else if (achat_pioche1_possible) {
                    std::cout << "Vous devez acheter votre carte dans la pioche 1 obligatoirement.\n";
                    pioche = p1;
                } else if (achat_pioche2_possible) {
                    std::cout << "Vous devez acheter votre carte dans la pioche 2 obligatoirement.\n";
                    pioche = p2;
                } else if (achat_pioche3_possible) {
                    std::cout << "Vous devez acheter votre carte dans la pioche 3 obligatoirement.\n";
                    pioche = p3;
                }
                do {
                    std::cout << "Quelle carte revelee voulez vous prendre - (La plus a gauche etant la premiere, soit 1) ? Carte = ";
                    std::cin >> n_carte;
                    std::cout << "\n";
                    if (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees()) std::cout << "Numero de carte invalide !\n";
                } while (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees());
                int id = pioche->getCartesDehors(n_carte-1)->getID();
                carte = pioche->joueurPrend(id);
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
                    case 1: pioche = p1; break;
                    case 2: pioche = p2; break;
                    case 3: pioche = p3; break;
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
                    case 1: pioche = p1; break;
                    case 2: pioche = p2; break;
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
                    case 1: pioche = p1; break;
                    case 3: pioche = p2; break;
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
                    case 2: pioche = p1; break;
                    case 3: pioche = p2; break;
                    default: std::cout << "Numero de pioche invalide ! Théoriquement impossible...\n";
                }
            } else if (achat_pioche1_possible) {
                std::cout << "Vous devez acheter votre carte dans la pioche 1 obligatoirement.\n";
                pioche = p1;
            } else if (achat_pioche2_possible) {
                std::cout << "Vous devez acheter votre carte dans la pioche 2 obligatoirement.\n";
                pioche = p2;
            } else if (achat_pioche3_possible) {
                std::cout << "Vous devez acheter votre carte dans la pioche 3 obligatoirement.\n";
                pioche = p3;
            }
            do {
                std::cout << "Quelle carte revelee voulez vous prendre - (La plus a gauche etant la premiere, soit 1) ? Carte = ";
                std::cin >> n_carte;
                std::cout << "\n";
                if (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees()) std::cout << "Numero de carte invalide !\n";
            } while (n_carte < 1 or n_carte > pioche->getMaxCartesRevelees());
            int id = pioche->getCartesDehors(n_carte-1)->getID();
            carte = pioche->joueurPrend(id);
        } else {
            std::cout << "Achat impossible!";
            return;
        }
        // Vérifier achat possible de la carte
        prix = carte->getPrix();
        difference = calculDifference(joueur, prix);
        if (!achatCartePossible(joueur, difference)) std::cout << "Vous ne pouvez pas acheter cette carte !\n";
    } while (!achatCartePossible(joueur, difference));

    // On ajoute la carte au joueur
    joueur->ajouterCarteJoaillerie(*(const_cast<CarteJoaillerie*>(carte)));

    // On retire les jetons au joueur et les remet dans le sac
    for (auto elem = prix.begin(); elem != prix.end(); elem++) {
        int prix_elem = elem->second;
        switch (elem->first) {
            case Couleur::bleu: remettreJetonSac(joueur, plateau, Couleur::bleu, difference[0], prix_elem, 0); break;
            case Couleur::vert: remettreJetonSac(joueur, plateau, Couleur::vert, difference[1], prix_elem, 1); break;
            case Couleur::rouge: remettreJetonSac(joueur, plateau, Couleur::rouge, difference[2], prix_elem, 2); break;
            case Couleur::blanc: remettreJetonSac(joueur, plateau, Couleur::blanc, difference[3], prix_elem, 3); break;
            case Couleur::noir: remettreJetonSac(joueur, plateau, Couleur::noir, difference[4], prix_elem, 4); break;
            case Couleur::rose: remettreJetonSac(joueur, plateau, Couleur::rose, difference[5], prix_elem, 5); break;
            default: std::cout << "Il y a un probleme avec le jeton pris au joueur !\n";
        }
    }
}

void Obligatoire::remettreJetonSac(Joueur* joueur, Plateau* plateau, Couleur c, int difference, int prix_elem, int index) {
    if (difference > 0) {
        // Le joueur n'a pas assez, il comble avec de l'or
        for (int i = 0; i < joueur->getNbJeton(index); i++) {
            const Jeton* j = new Jeton(JetonType::Gemme, c);
            plateau->ajouterSac(j);
        }
        for (int i = 0; i < difference; i++) {
            const Jeton* j = new Jeton(JetonType::Or);
            plateau->ajouterSac(j);
        }
        joueur->setNbJeton(index, 0);
        joueur->setNbJeton(6, joueur->getNbJeton(6) - difference);
    } else {
        // Le joueur a assez
        for (int i = 0; i < prix_elem; i++) {
            const Jeton* j = new Jeton(JetonType::Gemme, c);
            plateau->ajouterSac(j);
        }
        joueur->setNbJeton(index, joueur->getNbJeton(index) - prix_elem);
    }
}

std::vector<int> Obligatoire::ajouterJetonsJoueur(Joueur* joueur, std::vector<const Jeton*> selection) {
    // On ajoute les jetons au joueur
    std::vector<int> nb_couleurs(7, 0);
    // Bleu - Vert - Rouge - Blanc - Noir - Rose(Perle) - Or
    for (int i = 0; i < selection.size(); i++) {
        const Jeton *jeton = selection[i];
        if (jeton->getType() == JetonType::Or) {
            joueur->setNbJeton(6, joueur->getNbJeton(6) + 1);
        } else {
            switch (jeton->getCouleur()) {
                case Couleur::bleu:
                    nb_couleurs[0]++;
                    joueur->setNbJeton(0, joueur->getNbJeton(0) + 1);
                    break;
                case Couleur::vert:
                    nb_couleurs[1]++;
                    joueur->setNbJeton(1, joueur->getNbJeton(1) + 1);
                    break;
                case Couleur::rouge:
                    nb_couleurs[2]++;
                    joueur->setNbJeton(2, joueur->getNbJeton(2) + 1);
                    break;
                case Couleur::blanc:
                    nb_couleurs[3]++;
                    joueur->setNbJeton(3, joueur->getNbJeton(3) + 1);
                    break;
                case Couleur::noir:
                    nb_couleurs[4]++;
                    joueur->setNbJeton(4, joueur->getNbJeton(4) + 1);
                    break;
                case Couleur::rose:
                    nb_couleurs[5]++;
                    joueur->setNbJeton(5, joueur->getNbJeton(5) + 1);
                    break;
                default: std::cout << "Il y a definitivement un probleme avec la selection...\n";
            }
        }
    }
    return nb_couleurs;
}

bool Obligatoire::achatPiochePossible(Joueur* joueur, Pioche* p) {
    const CarteJoaillerie* carte;
    std::map<Couleur, int> prix;
    for (int i = 0; i < p->getMaxCartesRevelees(); i++) {
        carte = p->getCartesDehors(i);
        if (carte != nullptr) {
            prix = carte->getPrix();
            std::vector<int> difference = calculDifference(joueur, prix);
            if (achatCartePossible(joueur, difference)) return true;
        }
    }
    return false;
}

bool Obligatoire::achatCartePossible(Joueur *joueur, std::vector<int> difference) {
    // On teste si le joueur peut acheter sans or
    bool achat_possible = true;
    for (int j = 0; j < difference.size(); j++) {
        if (difference[j] > 0) achat_possible = false;
    }
    // On teste si le joueur peut acheter avec or
    if (!achat_possible) {
        int somme = 0;
        for (int j = 0; j < difference.size(); j++) {
            if (difference[j] > 0) somme += difference[j];
        }
        if (somme <= joueur->getNbJeton(6)) achat_possible = true;
    }
    return achat_possible;
}

std::vector<int> Obligatoire::calculDifference(Joueur* joueur, std::map<Couleur, int> prix) {
    std::vector<int> difference(6, 0);
    for (auto elem = prix.begin(); elem != prix.end(); elem++) {
        int prix_elem = elem->second;
        switch (elem->first) {
            case Couleur::bleu: difference[0] = prix_elem - joueur->getGemmesBonus(0) - joueur->getNbJeton(0); break;
            case Couleur::vert: difference[1] = prix_elem - joueur->getGemmesBonus(1) - joueur->getNbJeton(1); break;
            case Couleur::rouge: difference[2] = prix_elem - joueur->getGemmesBonus(2) - joueur->getNbJeton(2); break;
            case Couleur::blanc: difference[3] = prix_elem - joueur->getGemmesBonus(3) - joueur->getNbJeton(3); break;
            case Couleur::noir: difference[4] = prix_elem - joueur->getGemmesBonus(4) - joueur->getNbJeton(4); break;
            case Couleur::rose: difference[5] = prix_elem - joueur->getGemmesBonus(5) - joueur->getNbJeton(5); break;
            default: std::cout << "Il y a un probleme avec le prix de la carte !\n";
        }
    }
    return difference;
}

void Obligatoire::donnerPrivilegeAdversaire(Joueur* joueur, Plateau* plateau) {
    Joueur* adversaire = joueur->getAdversaire();
    std::vector<Privilege*> privileges;
    Privilege* privilege;
    if (adversaire->getNombreDePrivileges() == plateau->getNbPrivilegeMAX()) {
        std::cout << "L'adversaire a deja tous les privileges.\n";
        return;
    }
    if (plateau->getNbPrivileges() == 0) {
        const std::vector<Privilege*>& constPrivileges = joueur->getPrivileges();
        auto& privileges = const_cast<std::vector<Privilege*>&>(constPrivileges);
        adversaire->ajouterPrivilege(privileges.back());
        privileges.pop_back();
    } else {
        privilege = const_cast<Privilege*>(plateau->prendrePrivilege());
        adversaire->ajouterPrivilege(privilege);
    }
}