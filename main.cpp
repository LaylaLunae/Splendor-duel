#include <iostream>
#include <tuple>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "./include/jeu.h"
#include "./include/affichage_joueur.h"


// main.cpp

#include <QApplication>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FenetreInformations fenetre;
    fenetre.show();

    return app.exec();
}

#include "main.moc"