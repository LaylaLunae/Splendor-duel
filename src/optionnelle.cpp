//#include "../include/optionnelle.h"
#include "../include/jeu.h"

void Optionnelle::depenserPrivilege(Joueur* joueur, ReponseValidationSelection RVS) {
    // Vérifier si le privilège est disponible et qu'il y a au moins un jeton sur le plateau
    if (joueur->hasPrivilege() && plateau->hasJeton()) {
        // On vérifie qu'il n'y a qu'un seul jeton
        if (RVS.nombre > 1) throw PlateauException("On ne peut recuperer qu'un seul jeton en depensant un privilege !");

        // On ajoute le jeton au joueur
        const Jeton* jeton = RVS.jetons[0];
        switch (jeton->getCouleur()) {
            case Couleur::bleu: joueur->setNbJeton(0, joueur->getNbJeton(0)+1);
            case Couleur::vert: joueur->setNbJeton(1, joueur->getNbJeton(1)+1);
            case Couleur::rouge: joueur->setNbJeton(2, joueur->getNbJeton(2)+1);
            case Couleur::blanc: joueur->setNbJeton(3, joueur->getNbJeton(3)+1);
            case Couleur::noir: joueur->setNbJeton(4, joueur->getNbJeton(4)+1);
            case Couleur::rose: joueur->setNbJeton(5, joueur->getNbJeton(5)+1);
            default: throw PlateauException("Impossible de recuperer ce jeton avec un privilege !");
        }

        // On remet le privilège sur le plateau
        Privilege* privilege = nullptr;
        /*
        privilege = joueur->getPrivilege(0); // Décalage du tableau de privilège à prévoir? Ou suivi de l'index en tant qu'attribut?
        plateau->donnePrivilege(privilege);
        */
    } else throw PlateauException("Le joueur ne peut depenser de privilege !");
}

void Optionnelle::remplissagePlateau(Joueur* joueur) {
    // Remplir les cases vides du plateau avec des jetons aléatoires tirés du sac

    // Vérifier qu'au moins une case est vide et qu'il y a au moins un jeton dans le sac
    if (plateau->getNbJetonsPlateau() == plateau->getNbJetonsPlateauMAX()) throw PlateauException("Plateau deja rempli !");
    if (plateau->getNbJetonsSac() == 0) throw PlateauException("Sac vide !");

    // On remplit alors le plateau
    plateau->remplissagePlateau(false);

    // Et on donne un privilège à l'adversaire
    Joueur* adversaire = joueur->getAdversaire();
    const Privilege* privilege;
    if (adversaire->getNombreDePrivileges() == plateau->getNbPrivilegeMAX()) throw PlateauException("L'adversaire a deja tous les privileges !");
    if (plateau->getNbPrivileges() == 0) {
        std::cout << "qqch";
        /*
        privilege = joueur->getPrivilege(0); // Décalage du tableau de privilège à prévoir? Ou suivi de l'index en tant qu'attribut?
        adversaire->ajouterPrivilege(const_cast<Privilege*>(privilege));
        */
    } else {
        privilege = plateau->prendrePrivilege();
        adversaire->ajouterPrivilege(const_cast<Privilege*>(privilege));
    }
}