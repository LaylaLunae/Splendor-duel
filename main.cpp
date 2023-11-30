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



