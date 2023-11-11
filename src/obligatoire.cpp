#include "../include/obligatoire.h"

void Obligatoire::prendreJeton(Joueur* joueur, ReponseValidationSelection RVS) {
    // Vérifier qu'il y a au moins un jeton sur le plateau
    if (plateau->hasJeton()) {
        // On ajoute les jeton au joueur
        int nb_couleurs[6] = {0, 0, 0, 0, 0, 0};
        for (int i=0; i<RVS.nombre; i++) {
            const Jeton *jeton = RVS.jetons[i];
            switch (jeton->getCouleur()) {
                case Couleur::bleu:
                    nb_couleurs[0] += 1;
                    joueur->setGemmesBonus(0, joueur->getGemmesBonus(0) + 1);
                case Couleur::vert:
                    nb_couleurs[1] += 1;
                    joueur->setGemmesBonus(1, joueur->getGemmesBonus(1) + 1);
                case Couleur::rouge:
                    nb_couleurs[2] += 1;
                    joueur->setGemmesBonus(2, joueur->getGemmesBonus(2) + 1);
                case Couleur::blanc:
                    nb_couleurs[3] += 1;
                    joueur->setGemmesBonus(3, joueur->getGemmesBonus(3) + 1);
                case Couleur::noir:
                    nb_couleurs[4] += 1;
                    joueur->setGemmesBonus(4, joueur->getGemmesBonus(4) + 1);
                case Couleur::rose:
                    nb_couleurs[5] += 1;
                    joueur->setGemmesBonus(5, joueur->getGemmesBonus(5) + 1);
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
            Privilege privilege;
            const Privilege* privilegeptr = nullptr;
            if (adversaire->getNombreDePrivileges() == plateau->getNbPrivilegeMAX()) throw PlateauException("L'adversaire a deja tous les privileges !");
            if (plateau->getNbPrivileges() == 0) {
                privilege = joueur->getPrivilege(0); // Décalage du tableau de privilège à prévoir? Ou suivi de l'index en tant qu'attribut?
                adversaire->ajouterPrivilege(privilege);
            } else {
                privilegeptr = plateau->prendrePrivilege();
                adversaire->ajouterPrivilege(*privilegeptr);
            }
        }
    } else throw PlateauException("Le plateau est vide !");
};

CarteJoaillerie Obligatoire::reserverCarte(Joueur* joueur) {
    // Vérifier qu'il y a au moins un jeton or ou que le joueur n'a pas 3 cartes réservées déjà
    if (!plateau->hasJetonOr()) throw PlateauException("Il n'y a pas de jeton or de disponible sur le plateau !");
    if (joueur->getNbCartesReservees() == 3) throw PlateauException("Le joueur a deja 3 cartes reservees !");


};

CarteJoaillerie Obligatoire::acheterCarte(Joueur* joueur) {

};