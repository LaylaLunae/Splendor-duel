#include <iostream>
#include <tuple>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "./include/jeu.h"


int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
    testes_pour_plateau();


    QApplication app(argc, argv);

    FenetreInformations fenetre;
    fenetre.show();

    return app.exec();

}

