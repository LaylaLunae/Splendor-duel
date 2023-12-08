//#include "../include/optionnelle.h"
#include "../include/jeu.h"

void Optionnelle::depenserPrivilege(Joueur* joueur, Plateau* plateau) {
    // Vérifier si le privilège est disponible et qu'il y a au moins un jeton sur le plateau
    if (!joueur->hasPrivilege() or !plateau->hasJeton()) {
        std::cout << "Le joueur ne peut pas depenser de privileges !\n";
        return;
    }

    // Le joueur choisit un jeton non or
    std::tuple<int, int> jeton_choisi(0, 0);
    std::vector<const Jeton*> selection;
    int jeton_selec;
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
            // case 3 théoriquement impossible
            case 4: std::cout << "Ce jeton ne peut etre selectionne !\n"; break;
            default: std::cout << "Pour une raison ou une autre, il y a eu un probleme...\n";
        }
    } while (jeton_selec != 0);
    selection = plateau->validerSelectionEtPrendreJetons();

    // On ajoute le jeton au joueur
    Obligatoire::ajouterJetonsJoueur(joueur, selection);

    // On remet le privilège sur le plateau
    const std::vector<Privilege*>& constPrivileges = joueur->getPrivileges();
    auto& privileges = const_cast<std::vector<Privilege*>&>(constPrivileges);
    plateau->donnePrivilege(privileges.back());
    privileges.pop_back();
}

void Optionnelle::remplissagePlateau(Joueur* joueur, Plateau* plateau) {
    // Remplir les cases vides du plateau avec des jetons aléatoires tirés du sac

    // Vérifier qu'au moins une case est vide et qu'il y a au moins un jeton dans le sac
    if (plateau->getNbJetonsPlateau() == plateau->getNbJetonsPlateauMAX()) {
        std::cout << "Plateau deja rempli !\n";
        return;
    }
    if (plateau->getNbJetonsSac() == 0) {
        std::cout << "Sac vide !\n";
        return;
    }

    // On remplit alors le plateau
    plateau->remplissagePlateau(false);

    // Et on donne un privilège à l'adversaire
    Obligatoire::donnerPrivilegeAdversaire(joueur, plateau);
}