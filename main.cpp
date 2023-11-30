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
#include "affichage/affichage_carte.h"


int main(int argc, char *argv[]) {

/*

    Humain joueur("NomDuJoueur");

    joueur.ajouterPrivilege(new Privilege());
    int nombreDePrivileges = joueur.getNombreDePrivileges();


*/

//    QApplication app(argc, argv);
//
//    FenetreInformations fenetre;
//    fenetre.show();
//
//    return app.exec();

    /* Création Jeton : */



    /* Affichage plateau v0.1*/
     /*
    QApplication app (argc, argv);
    VuePlateau plateau;
    plateau.show();
    return app.exec();
    */

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
    QApplication app(argc, argv);
    AffichageCarte affichageCarte;
    affichageCarte.show();
    return app.exec();
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