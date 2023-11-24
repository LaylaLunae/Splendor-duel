//#include "../include/obligatoire.h"
#include "../include/jeu.h"

void Obligatoire::prendreJeton(Joueur* joueur) {
    // Vérifier que le plateau n'est point vide
    if (!plateau->hasJeton()) {
        std::cout << "Plateau vide\n";
        return;
    }

    // Le joueur récupère les jetons
    std::tuple<int, int> jeton_choisi(0, 0);
    const Jeton* jeton_pris = nullptr;
    ReponseValidationSelection *selection = nullptr;
    int cpt = 0, n = 0;
    while (n < 1 or n > 3) {
        std::cout << "Combien de jetons comptez vous prendre ? (MAX 3)   n = ";
        std::cin >> n;
        std::cout << "\n";
        if (n < 0) std::cout << "Vous voulez prendre des jetons, pas en remettre...\n";
        if (n == 0) std::cout << "Attraper de l'air ne va pas vous aider a gagner...\n";
        if (n > 3) std::cout << "Il faut jouer en respectant les regles quand meme...\n";
    }
    while (cpt != n) {
        do { // A MODIFIER AVEC SELECTIONJETON
            jeton_choisi = choisir_jeton();
            jeton_pris = plateau->prendreJeton(get<0>(jeton_choisi), get<1>(jeton_choisi));
            if (jeton_pris->getType() == JetonType::Or) std::cout << "On ne peut pas prendre de jeton or avec cette action !\n";
            // Faudra utiliser la fonction selection modifiée avvec les codes d'erreur
        } while (jeton_pris->getType() == JetonType::Or);
        selection = plateau->validerSelectionEtPrendreJetons();
        cpt++;
    }

    // On ajoute les jetons au joueur
    std::vector<int> nb_couleurs(6, 0);
    // Bleu - Vert - Rouge - Blanc - Noir - Rose(Perle)
    for (int i=0; i<selection->nombre; i++) {
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
        if (adversaire->getNombreDePrivileges() == plateau->getNbPrivilegeMAX()) std::cout << "L'adversaire a deja tous les privileges.\n";
        if (plateau->getNbPrivileges() == 0) {
            privileges = joueur->getPrivilege(); // A CHANGER AVEC LE VECTOR DE PRIVILEGE ENTIER
            adversaire->ajouterPrivilege(privileges);
        } else {
            privileges = const_cast<Privilege*>(plateau->prendrePrivilege());
            adversaire->ajouterPrivilege(privileges);
        }
    }
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