#ifndef JOUEUR_H
#define JOUEUR_H
// tous les include necessaire à la compliation
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
#include "carte.h"
#include "carteJoaillerie.h"

// Les classes ont besoin d'être déclarée afin de pouvoir les utiliser
class CarteNoble;
class CarteJoaillerie;
class Privilege;
class Plateau;
class Pioche;
class Jeton;
class Jeu;
class Carte;
class FenetreInformations;
//class VueCarteJoaillerie;


// initialisation de maximum de privilèges et de cartes possible
const int MAX_CARTES = 500;
const int MAX_PRIVILEGES = 3;
// enum pour le choix pour l'IA
enum Difficulte {aleatoire, facile, moyen, difficile };

class Joueur {
    friend class Jeu;
protected: // protected comme ça les classes filles peuvent utiliser les attributs.
    std::string pseudo;
    int nombre_couronnes;
    int points_prestige_total; // nombre de points total
    std::vector<int> points_prestige_couleurs; // nombre de points par couleurs
    std::vector<CarteJoaillerie*> cartes_reservees;
    std::vector<CarteJoaillerie*> cartes_main;
    std::vector<const CarteNoble*> cartes_noble;
    std::vector<int> gemmes_bonus = std::vector<int>(6, 0); // tous les gemmes (pas les jetons or)
    std::vector<int> nb_jeton = std::vector<int>(7, 0); // jeton or compris
    std::vector<Privilege*> privileges = std::vector<Privilege*>(0);

    Joueur* adversaire; // Pointeur vers le joueur adverse
    bool droitDeRejouer; // Marqueur pour le droit de jouer un tour supplémentaire

    FenetreInformations* info; // l'affichage de joueur compose la classe joueur

    bool isIA; // permet de savoir si c'est un ia ou un humain qui joue
    Difficulte diff;

    // constructeur, destructeur, constructeur de recopie, et opérateur d'affectation en protected car la classe jeu est un singleton.
    Joueur(const std::string nom);
    virtual ~Joueur();
    Joueur(const Joueur& autre);
    Joueur& operator=(const Joueur& autre);

public:
    // necessaire pour la composition avec l'affichage
    void setInfo(FenetreInformations* f) {
        info= f;
    }
    FenetreInformations* getInfo() {
        return info;
    }
    // getters :
    int getPointsPrestigeTotal() const;
    std::string getPseudo() const;
    int getNombreCouronnes() const;
    int getPointsPrestigeCouleurs(int index) const;
    const CarteJoaillerie * getCarteReservee(int index) const;
    CarteJoaillerie * getCarteMain(int index) const;
    const CarteNoble * getCarteNoble(int index) const;
    int getGemmesBonus(int index) const;
    std::vector<CarteJoaillerie*> getCartesReservees() const;
    std::vector<CarteJoaillerie*> getCartesMain() const;
    std::vector<const CarteNoble*> getCartesNoble() const;
    const std::vector<Privilege *>& getPrivileges() const;
    int getNbJeton(int index) const;
    Joueur* getAdversaire();
    int getNombreDePrivileges() const;
    int getNbCartesReservees() const;
    int getNombreCartesNobles() const;
    int getNbJetonTotal() const;
    int getNbJetonsParCouleur(int couleur) const;
    bool getDroitDeRejouer() const;
    // Utilisé pour décider s'il faut initialiser IA ou Hum ai n lors de la poursuite du jeu
    bool getIsIA() const;
    Difficulte getDifficulte() const;

    // setters :
    void setPointsPrestigeCouleurs(int index, int valeur);
    void setGemmesBonus(int index, int value);
    void setNombreCouronnes(int nbCour);
    void setPseudo(std::string pse);
    void setPointsPrestigeTotal(int pointP);
    void setNbJeton(int index, int value);
    void setAdversaire(Joueur* adv);
    void setIsIA(bool isia);
    void setDifficulte(Difficulte difficulte);

    //méthodes d'ajouts :
    void ajouterCarteJoaillerie(CarteJoaillerie* carte);
    void ajouterCarteNoble(const CarteNoble* carte);
    void ajouterCarteReservee(CarteJoaillerie* carte);
    void ajouterPrivilege( Privilege* privilege);

    bool hasPrivilege();
    Privilege  removePrivilege();

    // Méthode pour vérifier si le joueur a le droit de jouer à nouveau.
    bool peutRejouer() const;
    // Réinitialisez le droit de jouer à la fin du tour du joueur.
    void resetRejouer();
    void resetRejouer(bool reset); // Si vous obtenez le pouvoir, vous pouvez passer au tour suivant et appeler cette fonction

    virtual int choisirChoix(int min, int max) = 0;
    // test :
    void initialiserJoueur();
};

class IA : public Joueur {
protected:
    Difficulte difficulte;

public:
    IA(const std::string& pseudo, Difficulte diff) : Joueur(pseudo), difficulte(diff) {}
    ~IA() {}
    void setDifficulte(Difficulte diff);
    virtual int choisirChoix(int min, int max) override;
    // méthodes pour acheter une carte
    virtual std::vector<CarteJoaillerie*> getCartesAchetable(const Pioche& pioche) const ;
    virtual CarteJoaillerie* melangerEtObtenirDerniereCarte(Pioche& pioche, Joueur& joueur,Plateau& plateau);
    // méthodes pour prendre des jetons
    virtual std::vector<std::pair<const Jeton*, const Jeton*>> genererCombinaisonsDeuxJetons(Plateau* plateau);
    virtual std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> genererCombinaisonsTroisJetons(Plateau *plateau) const;
    virtual void choisirJetonSurPlateau(Plateau* plateau);
    virtual void prendreJetons(Plateau* plateau);
};

class Humain : public Joueur {
public:
    Humain(const std::string& pseudo) : Joueur(pseudo) {}
    ~Humain(){}
    virtual int choisirChoix(int min, int max) override;
};

// ----------------------- Visuels du joueur  -----------------------
// Pour joueur, on ne peut pas passer par VueCarteJoaillerie sinon
// nous avons des dépendances cycliques. Donc on va passer par une classe similaire
// qui ne sert qu'à dessiner les cartes.

class ImageCarte : public QPushButton {
Q_OBJECT

public:
    explicit ImageCarte(QWidget *parent = nullptr): QPushButton(parent) {
        setFixedSize(100, 150);
        connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
    }
};

class FenetreInformations : public QWidget {
Q_OBJECT
public:
    FenetreInformations(Joueur *j, QWidget *parent = nullptr) : QWidget(parent), joueur(j) {
        //setFixedSize(400, 400);
        setWindowTitle("Informations du Joueur");

        layout = new QVBoxLayout();
        layout_cartes = new QGridLayout();
        main_layout = new QHBoxLayout(this);
        miseAJourInformations();
// nous voulons afficher les différentes cartes acheter par le joueur
        displayCartes();
        main_layout->addLayout(layout);
        main_layout->addLayout(layout_cartes);

        setLayout(main_layout);
    }
    // fonction pour afficher les cartes du joueur
    // Appelée par VueJeu donc public
    void displayCartes();

public slots:
    // fonction pour mettre à jour tous les compteurs
    void miseAJourInformations() {
        if (joueur != nullptr) {
            std::cout<<"\n\n\n\n"<<joueur->getPseudo()<<"\n";
            while (QLayoutItem *item = layout->takeAt(0)) {
                if (QWidget *widget = item->widget()) {
                    widget->deleteLater();
                }
                delete item;
            }
            // toujours le meme model : un label, un style, et le widget
            labelNom = new QLabel(QString::fromStdString(joueur->getPseudo()), this);
            labelNom->setStyleSheet("QLabel { background-color: white; color: black; }");
            layout->addWidget(labelNom);

            labelPriviliges = new QLabel(QString("Nombre de Privilèges: %1").arg(joueur->getNombreDePrivileges()));
            labelCouronnes = new QLabel(QString("Nombre de Couronnes: %1").arg(joueur->getNombreCouronnes()));
            labelCartesNobles = new QLabel(QString("Nombre de Cartes Nobles: %1").arg(joueur->getNombreCartesNobles()));
            labelCartesReservees = new QLabel(QString("Nombre de Cartes Réservées: %1").arg(joueur->getNbCartesReservees()));
            labelJetons = new QLabel(QString("Nombre de Jetons: %1").arg(joueur->getNbJetonTotal()));
            labelPriviliges->setStyleSheet("QLabel { background-color: grey; color: white; }");
            layout->addWidget(labelPriviliges);

            labelCouronnes->setStyleSheet("QLabel { background-color: grey; color: white; }");
            layout->addWidget(labelCouronnes);

            labelCartesNobles->setStyleSheet("QLabel { background-color: grey; color: white; }");
            layout->addWidget(labelCartesNobles);

            labelCartesReservees->setStyleSheet("QLabel { background-color: grey; color: white; }");
            layout->addWidget(labelCartesReservees);

            labelJetons->setStyleSheet("QLabel { background-color: grey; color: white; }");
            layout->addWidget(labelJetons);

            for (int couleur = 0; couleur < 7; ++couleur) {
                labelJetonsParCouleur[couleur] = new QLabel(QString("Nombre de %1: %2").arg(getNomCouleur(couleur)).arg(joueur->getNbJeton(couleur)));
                labelJetonsParCouleur[couleur] ->setStyleSheet(QString("QLabel { background-color: grey; color: %1; }").arg(getCouleurTexte(couleur)));
                layout->addWidget(labelJetonsParCouleur[couleur]);
            }
// On fait cela pour mettre en rouge le joeur qui joue
        }
        if (joueurCourant != nullptr && joueur == joueurCourant) {
            labelNom->setStyleSheet("QLabel { background-color: white; color: red; }");
        }
        else {
            labelNom->setStyleSheet("QLabel { background-color: white; color: black; }");
        }
        // Il faut repainte pour que les modifications apparaissent
        repaint();
    }
    // fonction pour mettre à jour le joueur
    void setJoueur(Joueur *j) {
        joueur = j;
        //miseAJourInformations();
    }
    // fonction pour savoir qui est le joueur courant
    void setJoueurCourrant(Joueur *courant) {
        joueurCourant = courant;
        miseAJourInformations();
    }
private:
    QLayout* layout;
    QGridLayout* layout_cartes;
    QHBoxLayout* main_layout;
    QLabel *labelNom;
    QLabel *labelPriviliges;
    QLabel *labelCouronnes;
    QLabel *labelCartesNobles;
    QLabel *labelCartesReservees;
    QLabel *labelJetons;
    QLabel *labelJetonsParCouleur[7];
    Joueur *joueur;
    Joueur *joueurCourant;

// fonction pour créer tout les labels
    void setupLabels(Joueur *j, QVBoxLayout *layout) {
        labelNom = createLabel(QString::fromStdString(j->getPseudo()), "white", "black");
        labelPriviliges = createLabel("Nombre de Privilèges: 0", "grey", "white");
        labelCouronnes = createLabel("Nombre de Couronnes: 0", "grey", "white");
        labelCartesNobles = createLabel("Nombre de Cartes Nobles: 0", "grey", "white");
        labelCartesReservees = createLabel("Nombre de Cartes Réservées: 0", "grey", "white");
        labelJetons = createLabel("Nombre de Jetons: 0", "grey", "white");

        layout->addWidget(labelNom);
        layout->addWidget(labelPriviliges);
        layout->addWidget(labelCouronnes);
        layout->addWidget(labelCartesNobles);
        layout->addWidget(labelCartesReservees);
        layout->addWidget(labelJetons);

        for (int couleur = 0; couleur < 7; couleur++) {
            labelJetonsParCouleur[couleur] = createLabel(QString("Nombre de %1 : 0").arg(getNomCouleur(couleur)),
                                                         "grey", "white");
            layout->addWidget(labelJetonsParCouleur[couleur]);
        }
    }

// méthode pour les compteurs
    QLabel *createLabel(const QString &text, const QString &backgroundColor, const QString &textColor) {
        QLabel *label = new QLabel(text, this);
        label->setStyleSheet(QString("QLabel { background-color: %1; color: %2; }").arg(backgroundColor, textColor));
        label->show();
        return label;
    }

// méthode pour avoir le nom de la pierre précieuse
    QString getNomCouleur(int couleur) const {
        switch (couleur) {
            case 0:
                return "Saphir";
            case 1:
                return "Emeraude";
            case 2:
                return "Ruby";
            case 3:
                return "Diamant";
            case 4:
                return "Onix";
            case 5:
                return "Perle";
            case 6:
                return "Or";
            default:
                return "Inconnue";
        }
    }

// la couleur associée à la pierre précisieuse
    QString getCouleurTexte(int couleur) const {
        switch (couleur) {
            case 0:
                return "blue";
            case 1:
                return "green";
            case 2:
                return "red";
            case 3:
                return "white";
            case 4:
                return "black";
            case 5:
                return "pink";
            case 6:
                return "gold";
            default:
                return "white";
        }
    }

};

#endif // JOUEUR_H