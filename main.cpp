#include <iostream>
#include <tuple>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <vector>

#include "./include/jeu.h"


int main(int argc, char *argv[]) {

/*

    Humain joueur("NomDuJoueur");

    joueur.ajouterPrivilege(new Privilege());
    int nombreDePrivileges = joueur.getNombreDePrivileges();


*/

    QApplication app(argc, argv);

    FenetreInformations fenetre;
    fenetre.show();

    return app.exec();

    /* Création Jeton : */



    /* Affichage plateau v0.1*/
     /*
    QApplication app (argc, argv);
    VuePlateau plateau;
    plateau.show();
    return app.exec();
    */
}



