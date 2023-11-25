//#include "../include/obligatoire.h"
#include "../include/jeu.h"

// L28 + L110

void Obligatoire::prendreJeton(Joueur* joueur, Plateau* plateau) {
    // Vérifier que le plateau n'est point vide
    if (!plateau->hasJeton()) {
        std::cout << "Plateau vide\n";
        return;
    }

    // Le joueur récupère les jetons
    std::tuple<int, int> jeton_choisi(0, 0);
    ReponseValidationSelection *selection = nullptr;
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
    for (int i = 0; i < selection->nombre; i++) {
        const Jeton *jeton = selection->jetons[i];
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

void Obligatoire::reserverCarte(Joueur* joueur, Plateau* plateau, Pioche* pioche) {
    // Vérifier que le plateau a au moins 1 jeton or et que le joueur n'a pas 3 cartes réservées déjà
    if (!plateau->hasJetonOr()) {
        std::cout << "Aucun jeton or de disponible sur le plateau !\n";
        return;
    }
    if (joueur->getNbCartesReservees() == 3) std::cout << "Le joueur a deja 3 cartes reservees !";

    // On récupère un jeton or
    std::tuple<int, int> jeton_choisi(0, 0);
    ReponseValidationSelection *selection = nullptr;
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
        std::cout << "Prendre 1 carte Joaillerie de votre choix dans la pyramide ? (1)\n";
        std::cout << "Piocher la premiere carte de l’un des 3 paquets ? (2)";
        std::cout << "Choix (1 ou 2) : ";
        std::cin >> choix;
        std::cout << "\n";
    } while (choix != 1 and choix != 2);

    // Il choisi alors une carte en fonction de son choix
    int n_carte, n_pioche, n;
    CarteJoaillerie* card;
    do {
        std::cout << "Dans quelle pioche souhaitez vous piocher - (1, 2, 3) ? Pioche = ";
        std::cin >> n_pioche;
        std::cout << "\n";
        if (n_pioche < 1 or n_pioche > 3) std::cout << "Numero de pioche invalide !\n";
    } while (n_pioche < 1 or n_pioche > 3);
    if (choix == 1) {
        do {
            std::cout << "Quelle carte de cette pioche voulez vous prendre - (La plus a gauche etant la premiere, soit 1) ? Carte = ";
            std::cin >> n_carte;
            std::cout << "\n";
            if (n_carte < 1 or n_carte > 12) std::cout << "Numero de carte invalide !\n";
        } while (n_carte < 1 or n_carte > 12);
        switch (n_pioche) {
            case 0: n = -1;
            case 1: n = 3;
            case 2: n = 7;
            default: std::cout << "Numero de pioche invalide !\n";
        }
        n += n_carte;
        card = const_cast<CarteJoaillerie*>(pioche->joueurPrend(n));
    } else {
        return; // Pas de fonctions pour piocher direct ?
    }

    // On ajoute la carte réservée
    joueur->ajouterCarteReservee(card);
};

void Obligatoire::acheterCarte(Joueur* joueur, Plateau* plateau, Pioche* pioche) {
    CarteJoaillerie* card;

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