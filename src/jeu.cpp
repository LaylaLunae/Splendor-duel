#include <iostream>
#include <string.h>
#include "../include/jeu.h"

/* Jeu& Jeu::getJeu(){
    if (handler.instance == nullptr)
        handler.instance = new Jeu();
    return * handler.instance;
}

void Jeu::libereJeu() {
    delete handler.instance;
    handler.instance = nullptr;
}*/

Jeu * Jeu::instance = nullptr;

Jeu& Jeu::getJeu(){
    if (instance == nullptr)
        instance = new Jeu;
    return * instance;
}

void Jeu::libereJeu() {
    delete instance;
    instance = nullptr;
}

void Jeu::nouvellePartie() {
    Plateau * plateau_jeu = new Plateau();
    std::string sortie = plateau_jeu->etatPlateau();
    std::cout << sortie << "\n";

    Pioche * pioche1 = new Pioche(1,5,30);
    Pioche * pioche2 = new Pioche(2,4,24);
    Pioche * pioche3 = new Pioche(3,3,13);

    /*pioche1->distribution();
    pioche2->distribution();
    pioche3->distribution();*/

    Optionnelle * act_opt = new Optionnelle(plateau_jeu);
    Obligatoire * act_obl = new Obligatoire();

    std::cout << "Choix des joueurs :\n" << "0 - Joueur vs joueur\n";
    std::cout << "1 - Joueur vs IA\n" << "2 - IA vs IA\n";
    int choix;
    std::cout << "Choix : ";
    std::cin >> choix;

    switch (choix) {
        case 0: {
            std::cout << "Nom du joueur 1 : ";
            std::string nom1;
            std::cin >> nom1;
            Humain *joueur1 = new Humain(nom1);

            std::cout << "Nom du joueur 2 : ";
            std::string nom2;
            std::cin >> nom2;
            Humain *joueur2 = new Humain(nom2);

            joueur_actuel = joueur1;

            manche(plateau_jeu, pioche1, pioche2, pioche3, joueur1, joueur2, act_obl, act_opt);

            break;
        }

        case 1: {
            std::cout << "Nom du joueur : ";
            std::string nom4;
            std::cin >> nom4;
            Humain *humain = new Humain(nom4);

            std::cout << "Nom de l'IA : ";
            std::string nom3;
            std::cin >> nom3;
            IA *ia = new IA(nom3, facile);

            joueur_actuel = humain;

            manche(plateau_jeu, pioche1, pioche2, pioche3, humain, ia, act_obl, act_opt);

            break;
        }

        case 2: {
            std::cout << "Nom de l'IA 1 : ";
            std::string nom5;
            std::cin >> nom5;
            IA *ia1 = new IA(nom5, facile);

            std::cout << "Nom de l'IA 2 : ";
            std::string nom6;
            std::cin >> nom6;
            IA *ia2 = new IA(nom6, facile);

            joueur_actuel = ia1;

            manche(plateau_jeu, pioche1, pioche2, pioche3, ia1, ia2, act_obl, act_opt);

            break;
        }

        default:
            std::cout << "Il fait rien\n";
            break;
    }
}

void Jeu::manche(Plateau * p, Pioche * p1, Pioche * p2, Pioche * p3, Joueur * j1, Joueur * j2, Obligatoire * obl, Optionnelle * opt) {
   while(joueur_gagnant == nullptr) {
        tour(p, p1, p2, p3, joueur_actuel, obl, opt);
        verifGagnant(j1, j2);
    }
    std::cout << "Bravo " << joueur_gagnant->getPseudo() << " ! Tu as gagne !\n";
    std::cout << "Fin de la partie\n";
}

void Jeu::tour(Plateau * p, Pioche * p1, Pioche * p2, Pioche * p3, Joueur * j, Obligatoire * obl, Optionnelle * opt){
    int choix_opt = -1;
    int stop = 0;
    IA * test_ia = dynamic_cast<IA *>(j);
    while (choix_opt != 0 && stop != 10){
        if (!(p->hasJeton())){
            std::cout << "Vous devez remplir le plateau.\n";
            opt->remplissagePlateau(j);
        }
        else {
            std::cout << "Actions optionnelles :\n" << "0 - Aucune action\n";
            std::cout << "1 - Remplir le plateau\n" << "2 - Utiliser un privilege\n";

            if (test_ia) {
                choix_opt = j->choisirChoix(0,2);
                std::cout << "l'IA choisit l'action" << choix_opt << "\n";
                stop++;
            }
            else {
                std::cout << "Votre choix : ";
                std::cin >> choix_opt;
            }

            switch (choix_opt) {
                case 1: {
                    //opt->remplissagePlateau(j);
                    std::cout << "Remplissage du plateau.\n";
                    break;
                }

                case 2: {
                    //p->depenserPrivilege(j,p); //Je peux pas passer le deuxième paramètre
                    std::cout << "Dépense d'un privilege.\n";
                    break;
                }

                default: {
                    if (choix_opt != 0)
                            std::cout << "Tu t'es trompe de chiffre banane !\n";
                    break;
                }
            }
        }
    }

    int choix_obl;
    std::cout << "Actions obligatoires :\n" << "0 - Prendre des jetons\n";
    std::cout << "1 - Acheter une carte\n" << "2 - Reserver une carte\n";

    if (test_ia) {
        choix_obl = j->choisirChoix(0,2);
        std::cout << "l'IA choisit l'action" << choix_obl << "\n";
    }
    else {
        std::cout << "Votre choix : ";
        std::cin >> choix_obl;
    }
    switch(choix_obl){
        case 0:
            //obl->prendreJeton(j,p);
            std::cout << "Prend un jeton.\n";
            break;

        case 1:
            //obl->acheterCarte(j,p);
            std::cout << "Achete une carte.\n";
            break;

        case 2:
            //obl->reserverCarte(j,p);
            std::cout << "Reserve une carte.\n";
            break;

        default:
            std::cout << "Eh ben voila, t'as plus la possibilite de prendre une action banane !\n";
            break;
    }
}

void Jeu::vainqueur(Joueur * j){
    joueur_gagnant = j;
}

void Jeu::auSuivant(Joueur * j1, Joueur * j2){
    if (joueur_actuel->getPseudo() == j1->getPseudo()) {
        std::cout << joueur_actuel->getPseudo() << " passe la main a " << j2->getPseudo() << "\n";
        joueur_actuel = j2;
    }
    else {
        std::cout << joueur_actuel->getPseudo() << " passe la main a " << j1->getPseudo() << "\n";
        joueur_actuel = j1;
    }
}

void Jeu::verifGagnant(Joueur * j1, Joueur * j2) {
    /*if (joueur_actuel->getNombreCouronnes() >= 10)
        vainqueur(joueur_actuel);
    else if (joueur_actuel->getPointsPrestigeTotal() >= 20)
        vainqueur(joueur_actuel);
    else {
        bool gagnant = false;
        for (int i = 0; i<5; i++)
            if (joueur_actuel->getPointsPrestigeCouleurs(i) >= 10)
                gagnant = true;
        if (gagnant)
            vainqueur(joueur_actuel);
        else
            auSuivant();
    }*/
    int choix = -1;
    std::cout << "On continue ? 1 - oui, 0 - non :";
    std::cin >> choix;
    if (choix == 0) {
        vainqueur(joueur_actuel);
    }
    else {
        auSuivant(j1, j2);
    }
}

void Jeu::validationAction() {
    // si bouton pressé
        // recueillir variable qui contient bouton choisi
        // si variable vide -> peut pas presser bouton ?
        // appeler action correspondante
}
