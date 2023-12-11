#include <iostream>
#include <tuple>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDir>
#include <vector>

#include "./include/jeu.h"
#include "./include/plateau.h"
#include "affichage/affichage_carte.h"
#include "./include/affichage_joueur.h"

class Plateau;
class Pioche;
class Joueur;


int main(int argc, char *argv[]) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Plateau * plateau_jeu = new Plateau();
    std::string sortie = plateau_jeu->etatPlateau();
    std::cout << sortie << "\n";

    Pioche * pioche1 = new Pioche(1,5,30);
    Pioche * pioche2 = new Pioche(2,4,24);
    Pioche * pioche3 = new Pioche(3,3,13);

    IA ia("IA1", Difficulte::aleatoire);
    ia.initialiserJoueur();

    Optionnelle * act_opt = new Optionnelle();
    Obligatoire * act_obl = new Obligatoire();

    act_opt->remplissagePlateau(&ia, plateau_jeu);


    int choixIA = ia.choisirChoix(1, 3);
    std::cout << "Choix de l'IA : " << choixIA << std::endl;

/*
    //tester pour prendre des cartes avec l'IA

    std::vector<CarteJoaillerie*> cartesAchetable = ia.getCartesAchetable(reinterpret_cast<Pioche &>(pioche1));

    std::cout<<"jfjzflj";

    for (const auto& carte : cartesAchetable) {
        //std::cout << "Prix de la carte : " << carte->getPrix() << std::endl;
        std::cout << "prix : \n  " ;
    }


    Carte carte;
    CarteJoaillerie* derniereCarte = ia.melangerEtObtenirDerniereCarte(reinterpret_cast<Pioche &>(pioche1), ia, reinterpret_cast<Plateau &>(plateau_jeu), carte);

    //std::cout << "Dernière carte obtenue - Prix : " << derniereCarte->getPrix() << std::endl;

*/

// test pour prendre des jetons à l'IA :

// pour 2 jetons
/*
    std::vector<std::pair<const Jeton*, const Jeton*>> combinaisons = ia.genererCombinaisonsDeuxJetons(plateau_jeu);

    std::cout << "Combinaisons générées :\n";
    for (const auto& combinaison : combinaisons) {
        std::cout << "Jeton 1 : " << combinaison.first->getCouleurString() << ", Jeton 2 : " << combinaison.second->getCouleurString() << std::endl;
    }
*/
/*
// pour 3 jetons
    std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisons3 = ia.genererCombinaisonsTroisJetons(reinterpret_cast<Plateau *>(&plateau_jeu));

    // Affichez les combinaisons générées
    std::cout << "Combinaisons générées :\n";
    for (const auto& combinaison3 : combinaisons3) {
        const Jeton* jeton1 = std::get<0>(combinaison3);
        const Jeton* jeton2 = std::get<1>(combinaison3);
        const Jeton* jeton3 = std::get<2>(combinaison3);

        //std::cout << "Jeton 1 : " << jeton1->getCouleur() << ", Jeton 2 : " << jeton2->getCouleur() << ", Jeton 3 : " << jeton3->getCouleur() << std::endl;
        std::cout<<"jslkdfj\n";
    }

*/
    // prendre 1 jeton

    //ia.choisirJetonSurPlateau(plateau_jeu);


    // tous choix jetons confondus :
    // ia.prendreJetons(reinterpret_cast<Plateau *>(&plateau_jeu));


    /* Création Jeton : */


    /* Affichage plateau v0.1*/
    //QApplication app (argc, argv);
    //VuePlateau plateau;
    //plateau.show();
    //return app.exec();


    /* Affichage cartes v0.1 */
//     QApplication app(argc, argv);
//     QLabel label;
//     QPixmap pixmap("../images/01.png");
//    if (pixmap.isNull()) {
//        qDebug() << "Failed to load the image. Check the path:";
//        qDebug() << QDir::current().absoluteFilePath("images/01.png");
//    } else {
//        label.setPixmap(pixmap);
//        label.setScaledContents(true); // This ensures the image scales with the label size.
//        label.show();
//    }
//    return app.exec();

    /* Affichage piles de carte */
    /*
    QApplication app(argc, argv);
    AffichageCarte affichageCarte;
    affichageCarte.show();
    return app.exec();
     */
}

/*
void menu(Jeu& j) {
    int choix;
    std::cout << "##### MENU #####\n";
    do {
        std::cout << "Nouvelle partie (1)\nReprendre partie (2)\nChoix = ";
        std::cin >> choix;
        std::cout << "\n";
        if (choix != 1 and choix != 2) std::cout << "Choix incorrect !\n";
    } while (choix != 1 and choix != 2);
    system("cls");
    switch (choix) {
        case 1: j.nouvellePartie();
        case 2: j.reprendrePartie();
        default: std::cout << "Probleme au niveau du menu !\n";
    }
}
 */