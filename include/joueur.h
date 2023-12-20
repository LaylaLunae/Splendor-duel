
#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <iostream>
#include <vector>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPen>
#include <QBrush>
#include <QString>
//#include "affichage_joueur.h"


class CarteNoble;
class CarteJoaillerie;
class Privilege;
class Plateau;
class Pioche;
class Jeton;
class Jeu;
class Carte;
class FenetreInformations;

const int MAX_CARTES = 500;
const int MAX_PRIVILEGES = 3;

enum Difficulte {aleatoire, facile, moyen, difficile };

class Joueur {
    friend class Jeu;
protected:
    std::string pseudo;
    int nombre_couronnes;
    int points_prestige_total;
    std::vector<int> points_prestige_couleurs;
    //int nb_cartes_reservees;
    std::vector<CarteJoaillerie*> cartes_reservees;
    std::vector<CarteJoaillerie*> cartes_main;
    std::vector<CarteNoble*> cartes_noble;
    std::vector<int> gemmes_bonus = std::vector<int>(6, 0);
    std::vector<int> nb_jeton = std::vector<int>(7, 0); // Timo - Temporaire pour actions (a un getter et setter)
    std::vector<Privilege*> privileges;
    //int nombre_de_privileges;

    Joueur* adversaire; // Pointeur vers le joueur adverse
    bool droitDeRejouer; // Marqueur pour le droit de jouer un tour supplémentaire

    FenetreInformations* info;

    bool isIA;
    Difficulte diff;

    Joueur(const std::string nom);
    virtual ~Joueur();
    Joueur(const Joueur& autre);
    Joueur& operator=(const Joueur& autre);




public:

    void setInfo(FenetreInformations* f) {
        info= f;
    }
    FenetreInformations* getInfo() {return info;}
    int getPointsPrestigeTotal() const;
    std::string getPseudo() const;
    int getNombreCouronnes() const;
    int getPointsPrestigeCouleurs(int index) const;
    const CarteJoaillerie * getCarteReservee(int index) const;
    CarteJoaillerie * getCarteMain(int index) const;
    CarteNoble * getCarteNoble(int index) const;
    int getGemmesBonus(int index) const;

    std::vector<CarteJoaillerie*> getCartesReservees() const;
    std::vector<CarteJoaillerie*> getCartesMain() const;
    std::vector<CarteNoble*> getCartesNoble() const;

    //Privilege getPrivilege(int index) const;
    const std::vector<Privilege *>& getPrivileges() const;
    void ajouterCarteJoaillerie(CarteJoaillerie& carte);
    void ajouterCarteNoble(const CarteNoble& carte);
    void ajouterCarteReservee(CarteJoaillerie* carte);
    void ajouterPrivilege(Privilege* privilege);

    //void ajouterGemmeBonus(int index);


    void setPointsPrestigeCouleurs(int index, int valeur);
    void setGemmesBonus(int index, int value);
    void setNombreCouronnes(int nbCour);
    void setPseudo(std::string pse);
    void setPointsPrestigeTotal(int pointP);

    // Timo - Temporaire pour action
    int getNbJeton(int index) const;
    void setNbJeton(int index, int value);

    // Définir l'adversaire
    Joueur* getAdversaire();
    void setAdversaire(Joueur* adv);
    bool hasPrivilege();
    Privilege removePrivilege();
    // Méthode pour vérifier si le joueur a le droit de jouer à nouveau.
    bool peutRejouer() const;
    // Réinitialisez le droit de jouer à la fin du tour du joueur.
    void resetRejouer(); // Normalement, on passe au tour de l'adversaire
    void resetRejouer(bool reset); // Si vous obtenez le pouvoir, vous pouvez passer au tour suivant et appeler cette fonction

    // Utile pour Optionnelle et Obligatoire
    int getNombreDePrivileges() const;
    int getNbCartesReservees() const;
    int getNombreCartesNobles() const;

    int getNbJetonTotal() const;
    int getNbJetonsParCouleur(int couleur) const;

    bool getDroitDeRejouer() const;

    virtual int choisirChoix(int min, int max) = 0;

    // Utilisé pour décider s'il faut initialiser IA ou Hum ai n lors de la poursuite du jeu
    bool getIsIA() const;
    void setIsIA(bool isia);
    Difficulte getDifficulte() const;
    void setDifficulte(Difficulte difficulte);

    // test :
    void initialiserJoueur();
};

class IA : public Joueur {
protected:
    Difficulte difficulte;


public:
    IA(const std::string& pseudo, Difficulte diff) : Joueur(pseudo), difficulte(diff) {}
    ~IA() {}

    virtual int choisirChoix(int min, int max) override;


    virtual std::vector<CarteJoaillerie*> getCartesAchetable(const Pioche& pioche) const ;
//    virtual bool peutAcheterCarte(const CarteJoaillerie& carte) const;
    virtual CarteJoaillerie* melangerEtObtenirDerniereCarte(Pioche& pioche, Joueur& joueur,Plateau& plateau);
    //void activerPouvoir(Joueur& joueur, CarteJoaillerie& carte, Plateau& plateau);

    virtual std::vector<std::pair<const Jeton*, const Jeton*>> genererCombinaisonsDeuxJetons(Plateau* plateau);
    virtual std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> genererCombinaisonsTroisJetons(Plateau *plateau) const;
    //virtual bool verificationCombinaisonDeuxJetons(const Jeton* jeton1, const Jeton* jeton2, const Plateau& plateau) const;
    //virtual bool verificationCombinaisonTroisJetons(const Jeton* jeton1, const Jeton* jeton2, const Jeton* jeton3, const Plateau& plateau) const;
    virtual void choisirJetonSurPlateau(Plateau* plateau);

    virtual void prendreJetons(Plateau* plateau);

    void setDifficulte(Difficulte diff);
};


class Humain : public Joueur {
protected:

public:
    Humain(const std::string& pseudo) : Joueur(pseudo) {}
    ~Humain(){}
    //int choisirChoixUtilisateur(int min, int max);
    virtual int choisirChoix(int min, int max) override;



};




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
        setJoueur(j);
    }

public slots:

    void    miseAJourInformations() {
        if (joueur!=nullptr) {
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
                                joueur->getNbJeton(couleur) )
                );
                std::cout<<labelJetonsParCouleur[couleur]->text().toStdString();
                labelJetonsParCouleur[couleur]->repaint();

                // Ajoutez une feuille de style pour changer la couleur du texte
                labelJetonsParCouleur[couleur]->setStyleSheet(
                        QString("QLabel { background-color: darkblue; color: %1; }").arg(getCouleurTexte(couleur))
                );
            }
        }
         repaint();
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


#endif // JOUEUR_H
