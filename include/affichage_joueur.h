#ifndef SPLENDOR_AFFICHAGE_JOUEUR_H
#define SPLENDOR_AFFICHAGE_JOUEUR_H

#include "joueur.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
//#include <vector>

class Joueur;

class FenetreInformations : public QWidget {
Q_OBJECT

public:
    FenetreInformations(QWidget *parent = nullptr) : QWidget(parent), joueur(nullptr) {
        setFixedSize(400, 400);
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

        labelJetons = new QLabel("Nombre de Jetons: 0", this);
        labelJetons->setStyleSheet("QLabel { background-color: darkblue; color: white; }");
        layout->addWidget(labelJetons);

        // Labels pour le nombre de jetons par couleur
        for (int couleur = 0; couleur < 5; ++couleur) {
            labelJetonsParCouleur[couleur] = new QLabel(QString("Nombre de Jetons (Couleur %1): 0").arg(couleur + 1), this);
            labelJetonsParCouleur[couleur]->setStyleSheet("QLabel { background-color: darkblue; color: white; }");
            layout->addWidget(labelJetonsParCouleur[couleur]);
        }

        // Mise en place du joueur initial
        setJoueur(nullptr);
    }

public slots:
    void miseAJourInformations() {
        if (joueur) {
            labelPriviliges->setText(QString("Nombre de Privilèges: %1").arg(joueur->getNombreDePrivileges()));
            labelCouronnes->setText(QString("Nombre de Couronnes: %1").arg(joueur->getNombreCouronnes()));
            labelCartesNobles->setText(QString("Nombre de Cartes Nobles: %1").arg(joueur->getNombreCartesNobles()));
            labelCartesReservees->setText(QString("Nombre de Cartes Réservées: %1").arg(joueur->getNbCartesReservees()));
            labelJetons->setText(QString("Nombre de Jetons: %1").arg(joueur->getNbJetonTotal()));

            // Mettez à jour le nombre de jetons par couleur
            for (int couleur = 0; couleur < 5; ++couleur) {
                labelJetonsParCouleur[couleur]->setText(
                        QString("Nombre de Jetons (Couleur %1): %2").arg(couleur + 1).arg(joueur->getNbJetonsParCouleur(couleur))
                );
            }
        }
    }

    void setJoueur(Joueur* j) {
        joueur = j;
        miseAJourInformations();
    }

private:
    QLabel *labelPriviliges;
    QLabel *labelCouronnes;
    QLabel *labelCartesNobles;
    QLabel *labelCartesReservees;
    QLabel *labelJetons;
    QLabel *labelJetonsParCouleur[5]; // Labels pour le nombre de jetons par couleur
    Joueur *joueur;
};

#endif //SPLENDOR_AFFICHAGE_JOUEUR_H
