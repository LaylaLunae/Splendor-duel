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
    FenetreInformations(Joueur* j, QWidget *parent = nullptr) : QWidget(parent), joueur(nullptr) {
        setFixedSize(400, 400);
        setWindowTitle("Informations du Joueur");

        QVBoxLayout *layout = new QVBoxLayout(this);

        labelNom = new QLabel(QString::fromStdString(j->getPseudo()), this);
        labelNom->setStyleSheet("QLabel { background-color: white; color: black; }");
        layout->addWidget(labelNom);

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
        for (int couleur = 0; couleur < 7; couleur++) {
            labelJetonsParCouleur[couleur] = new QLabel(QString("Nombre de %1 : 0").arg(getNomCouleur(couleur)), this);
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
            labelCartesReservees->setText(
                    QString("Nombre de Cartes Réservées: %1").arg(joueur->getNbCartesReservees()));
            labelJetons->setText(QString("Nombre de Jetons: %1").arg(joueur->getNbJetonTotal()));

            // Mettez à jour le nombre de jetons par couleur
            for (int couleur = 0; couleur < 7; ++couleur) {
                labelJetonsParCouleur[couleur]->setText(
                        QString("Nombre de %1: %2").arg(getNomCouleur(couleur)).arg(
                                joueur->getNbJetonsParCouleur(couleur))
                );

                // Ajoutez une feuille de style pour changer la couleur du texte
                labelJetonsParCouleur[couleur]->setStyleSheet(
                        QString("QLabel { background-color: darkblue; color: %1; }").arg(getCouleurTexte(couleur))
                );
            }
        }
    }




    void setJoueur(Joueur* j) {
        joueur = j;
        miseAJourInformations();
    }

private:
    QLabel *labelNom;
    QLabel *labelPriviliges;
    QLabel *labelCouronnes;
    QLabel *labelCartesNobles;
    QLabel *labelCartesReservees;
    QLabel *labelJetons;
    QLabel *labelJetonsParCouleur[7]; // Labels pour le nombre de jetons par couleur
    Joueur *joueur;

    QString getNomCouleur(int couleur) const {
        switch (couleur) {
            case 0: return "Saphir";
            case 1: return "Emeraude";
            case 2: return "Ruby";
            case 3: return "Diamant";
            case 4: return "Onix";
            case 5: return "Perle";
            case 6: return "Or";
            default: return "Inconnue";
        }
    }
    QString getCouleurTexte(int couleur) const {
        switch (couleur) {
            case 0: return "blue";
            case 1: return "green";
            case 2: return "red";
            case 3: return "white";
            case 4: return "black";
            case 5: return "silver";
            case 6: return "gold";
            default: return "white";
        }
    }
};

#endif //SPLENDOR_AFFICHAGE_JOUEUR_H
