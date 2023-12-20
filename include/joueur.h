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
    std::vector<CarteNoble*> cartes_noble;
    std::vector<int> gemmes_bonus = std::vector<int>(6, 0); // tous les gemmes (pas les jetons or)
    std::vector<int> nb_jeton = std::vector<int>(7, 0); // jeton or compris
    std::vector<Privilege*> privileges;

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
    CarteNoble * getCarteNoble(int index) const;
    int getGemmesBonus(int index) const;
    std::vector<CarteJoaillerie*> getCartesReservees() const;
    std::vector<CarteJoaillerie*> getCartesMain() const;
    std::vector<CarteNoble*> getCartesNoble() const;
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
    void ajouterCarteJoaillerie(CarteJoaillerie& carte);
    void ajouterCarteNoble(const CarteNoble& carte);
    void ajouterCarteReservee(CarteJoaillerie* carte);
    void ajouterPrivilege(Privilege* privilege);

    bool hasPrivilege();
    Privilege removePrivilege();

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

class FenetreInformations : public QWidget {
Q_OBJECT
public:
    // constructeur
    // initialisaition de tous les labels necessaire pour l'afficahge des différents compteurs :
    FenetreInformations(Joueur* j, QWidget *parent = nullptr) : QWidget(parent), joueur(nullptr) {
        setFixedSize(400, 400);
        setWindowTitle("Informations du Joueur");

        QVBoxLayout *layout = new QVBoxLayout(this);
// toujours le meme model : un label, un style, et le widget
        labelNom = new QLabel(QString::fromStdString(j->getPseudo()), this);
        labelNom->setStyleSheet("QLabel { background-color: white; color: black; }");
        layout->addWidget(labelNom);

        labelPriviliges = new QLabel("Nombre de Privilèges: 0", this);
        labelPriviliges->setStyleSheet("QLabel { background-color: grey; color: white; }");
        layout->addWidget(labelPriviliges);

        labelCouronnes = new QLabel("Nombre de Couronnes: 0", this);
        labelCouronnes->setStyleSheet("QLabel { background-color: grey; color: white; }");
        layout->addWidget(labelCouronnes);

        labelCartesNobles = new QLabel("Nombre de Cartes Nobles: 0", this);
        labelCartesNobles->setStyleSheet("QLabel { background-color: grey; color: white; }");
        layout->addWidget(labelCartesNobles);

        labelCartesReservees = new QLabel("Nombre de Cartes Réservées: 0", this);
        labelCartesReservees->setStyleSheet("QLabel { background-color: grey; color: white; }");
        layout->addWidget(labelCartesReservees);

        labelJetons = new QLabel("Nombre de Jetons: 0", this);
        labelJetons->setStyleSheet("QLabel { background-color: grey; color: white; }");
        layout->addWidget(labelJetons);

        // Labels pour le nombre de jetons par couleur
        for (int couleur = 0; couleur < 7; couleur++) {
            labelJetonsParCouleur[couleur] = new QLabel(QString("Nombre de %1 : 0").arg(getNomCouleur(couleur)), this);
            labelJetonsParCouleur[couleur]->setStyleSheet("QLabel { background-color: grey; color: white; }");
            layout->addWidget(labelJetonsParCouleur[couleur]);
        }
        // permet de faire cela pour le joueur
        setJoueur(j);
    }

public slots:
    // fonction qui va mettre à jour les informations sans utiliser de sinaux seulement les getters.
    void miseAJourInformations() {
        if (joueur!=nullptr) {
            labelPriviliges->setText(QString("Nombre de Privilèges: %1").arg(joueur->getNombreDePrivileges()));
            labelCouronnes->setText(QString("Nombre de Couronnes: %1").arg(joueur->getNombreCouronnes()));
            labelCartesNobles->setText(QString("Nombre de Cartes Nobles: %1").arg(joueur->getNombreCartesNobles()));
            labelCartesReservees->setText(QString("Nombre de Cartes Réservées: %1").arg(joueur->getNbCartesReservees()));
            labelJetons->setText(QString("Nombre de Jetons: %1").arg(joueur->getNbJetonTotal()));

            for (int couleur = 0; couleur < 7; ++couleur) {
                labelJetonsParCouleur[couleur]->setText(QString("Nombre de %1: %2").arg(getNomCouleur(couleur)).arg(joueur->getNbJeton(couleur)));
                std::cout<<labelJetonsParCouleur[couleur]->text().toStdString();
                labelJetonsParCouleur[couleur]->repaint();

                labelJetonsParCouleur[couleur]->setStyleSheet(QString("QLabel { background-color: grey; color: %1; }").arg(getCouleurTexte(couleur)));
            }
        }
        // il faut faire repaint pour pouvoir mettre à jour
         repaint();
    }
    // permet de mettre à jour le joueur
    void setJoueur(Joueur* j) {
        joueur = j;
        miseAJourInformations();
    }

private:
    // tous les attributs pour les labels
    QLabel *labelNom;
    QLabel *labelPriviliges;
    QLabel *labelCouronnes;
    QLabel *labelCartesNobles;
    QLabel *labelCartesReservees;
    QLabel *labelJetons;
    QLabel *labelJetonsParCouleur[7];
    Joueur *joueur;
    // permet d'avoir les noms de pierre précieuses
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
    // permet de mettre le texte en couleur
    QString getCouleurTexte(int couleur) const {
        switch (couleur) {
            case 0: return "blue";
            case 1: return "green";
            case 2: return "red";
            case 3: return "white";
            case 4: return "black";
            case 5: return "pink";
            case 6: return "gold";
            default: return "white";
        }
    }
};
#endif // JOUEUR_H
