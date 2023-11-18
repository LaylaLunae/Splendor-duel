#include <iostream>
#include <tuple>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "./include/jeu.h"
#include "./include/test_affichage_joueur.h"

/*
int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
    testes_pour_plateau();

}

*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Humain *joueur = new Humain("Nom du Joueur");

    MainWindow *mainWindow = new MainWindow(joueur);

    mainWindow->show();

    return app.exec();
}
