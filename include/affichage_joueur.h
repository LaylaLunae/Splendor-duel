

#ifndef SPLENDOR_AFFICHAGE_JOUEUR_H
#define SPLENDOR_AFFICHAGE_JOUEUR_H
#include "joueur.h"
class Joueur;


#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class FenetreInformations : public QWidget {
Q_OBJECT
public:
    FenetreInformations(QWidget *parent = nullptr) : QWidget(parent), joueur(nullptr) {
        setFixedSize(300, 300);
        setWindowTitle("Informations du Joueur");

        QVBoxLayout *layout = new QVBoxLayout(this);

        labelPriviliges = new QLabel("Nombre de Privilèges: 0", this);
        labelPriviliges->setStyleSheet("QLabel { background-color: darkblue; color: white; }");
        layout->addWidget(labelPriviliges);

        labelCouronnes = new QLabel("Nombre de Couronnes: 0", this);
        labelCouronnes->setStyleSheet("QLabel { background-color: darkblue; color: white; }");
        layout->addWidget(labelCouronnes);

        labelCartesNobles = new QLabel("Nombre de Cartes Nobles: 0", this);
        labelCartesNobles->setStyleSheet("QLabel { background-color: darkblue; color: white; }");
        layout->addWidget(labelCartesNobles);

        labelCartesReservees = new QLabel("Nombre de Cartes Réservées: 0", this);
        labelCartesReservees->setStyleSheet("QLabel { background-color: darkblue; color: white; }");
        layout->addWidget(labelCartesReservees);

        // Mise en place du joueur initial
        setJoueur(nullptr);
    }

public slots:
    // Fonction pour mettre à jour les informations du joueur
    void miseAJourInformations() {
        if (joueur) {
            labelPriviliges->setText(QString("Nombre de Privilèges: %1").arg(joueur->getNombreDePrivileges()));
            labelCouronnes->setText(QString("Nombre de Couronnes: %1").arg(joueur->getNombreCouronnes()));
            labelCartesNobles->setText(QString("Nombre de Cartes Nobles: %1").arg(joueur->getNombreCartesNobles()));
            labelCartesReservees->setText(QString("Nombre de Cartes Réservées: %1").arg(joueur->getNbCartesReservees()));
        }
    }

    // Fonction pour définir le joueur actuel
    void setJoueur(Joueur* j) {
        joueur = j;
        miseAJourInformations();  // Mettez à jour l'affichage lorsque le joueur change
    }

private:
    QLabel *labelPriviliges;
    QLabel *labelCouronnes;
    QLabel *labelCartesNobles;
    QLabel *labelCartesReservees;
    Joueur *joueur;
};


#endif //SPLENDOR_AFFICHAGE_JOUEUR_H
