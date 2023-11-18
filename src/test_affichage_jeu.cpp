
// But de l'affichage pour Joueur :
// faire un rectangle avec les différents compteurs et le nom du joueur en titre
// - compteur de couronnes totale
// - faire un compteur de points prestige dans chaque couleur possible (Rouge, Vert, Bleu, Noir, Blanc)
// - faire un compteur de tous les points prestiges que le joueur a
//

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "../include/test_affichage_joueur.h"


MainWindow::MainWindow(Joueur *joueur, QWidget *parent): QMainWindow(parent), joueur_(joueur) {
    labelPrivilges_ = new QLabel(this);
    updateLabel();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(labelPrivilges_);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    connect(reinterpret_cast<const QObject *>(joueur_), SIGNAL(priviligesChanged()), this, SLOT(updateLabel()));
}

void MainWindow::updateLabel() {
    int nombrePrivilges = joueur_->getNombreDePrivileges();
    labelPrivilges_->setText("Nombre de privilèges : " + QString::number(nombrePrivilges));
}

MainWindow::~MainWindow() {}


