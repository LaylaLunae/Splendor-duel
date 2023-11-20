

#include "../include/affichage_joueur.h"
#include <QVBoxLayout>

/*
MainWindow::MainWindow(Joueur *joueur, QWidget *parent)
        : QMainWindow(parent), joueur_(joueur) {
    // Initialisation du QLabel
    labelPrivilges_ = new QLabel("Nombre de privilèges : 0", this);

    // Mise en place du layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(labelPrivilges_);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    // Connexion du signal priviligesChanged au slot updateLabel
    connect(reinterpret_cast<const QObject *>(joueur_), SIGNAL(priviligesChanged()), this, SLOT(updateLabel()));
}

void MainWindow::updateLabel() {
    // Mettez à jour le texte du label avec le nombre actuel de privilèges
    int nombrePrivilges = joueur_->getNombreDePrivileges();
    labelPrivilges_->setText("Nombre de privilèges : " + QString::number(nombrePrivilges));
}

MainWindow::~MainWindow() {
    // Assurez-vous de libérer la mémoire si nécessaire
}

 */
