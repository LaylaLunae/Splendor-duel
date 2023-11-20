#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <iostream>
#include <vector>

class CarteNoble;
class CarteJoaillerie;
class Privilege;

const int MAX_CARTES = 500;
const int MAX_PRIVILEGES = 3;

enum Difficulte { facile, moyen, difficile };

class Joueur {
protected:
    std::string pseudo;
    int nombre_couronnes;
    int points_prestige_total;
    std::vector<int> points_prestige_couleurs;
    //int nb_cartes_reservees;
    std::vector<CarteJoaillerie*> cartes_reservees;
    std::vector<CarteJoaillerie*> cartes_main;
    std::vector<CarteNoble*> cartes_noble;
    std::vector<int> gemmes_bonus;
    std::vector<int> nb_jeton; // Timo - Temporaire pour actions (a un getter et setter)
    std::vector<Privilege*> privileges;
    //int nombre_de_privileges;

    Joueur* adversaire; // Pointeur vers le joueur adverse
    bool droitDeRejouer; // Marqueur pour le droit de jouer un tour supplémentaire

    Joueur(const std::string nom);
    ~Joueur();
    Joueur(const Joueur& autre);
    Joueur& operator=(const Joueur& autre);

public:

    int getPointsPrestigeTotal() const;
    std::string getPseudo() const;
    int getNombreCouronnes() const;
    int getPointsPrestigeCouleurs(int index) const;
    const CarteJoaillerie * getCarteReservee(int index) const;
    CarteJoaillerie * getCarteMain(int index) const;
    CarteNoble * getCarteNoble(int index) const;
    int getGemmesBonus(int index) const;
    Privilege* getPrivilege(int index) const;
    void ajouterCarteJoaillerie(CarteJoaillerie& carte);
    void ajouterCarteNoble(const CarteNoble& carte);
    void ajouterCarteReservee(CarteJoaillerie* carte);
    void ajouterPrivilege(Privilege* privilege);

    void setPointsPrestigeCouleurs(int index, int valeur);
    void setGemmesBonus(int index, int value);

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
    int getNombreDePrivileges() const { return privileges.size(); }
    int getNbCartesReservees() const { return cartes_reservees.size(); }
};

class IA : public Joueur {
private:
    Difficulte difficulte;

public:
    IA(const std::string& pseudo, Difficulte diff) : Joueur(pseudo), difficulte(diff) {}
    int choisirChoix(int min, int max);
};

class Humain : public Joueur {
public:
    Humain(const std::string& pseudo) : Joueur(pseudo) {}
    int choisirChoixUtilisateur(int min, int max);
};


#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>  // Ajout de l'en-tête pour QLineEdit
#include <QLabel>
#include <QLineEdit>

class FenetreInformations : public QWidget {
Q_OBJECT
public:
    FenetreInformations(QWidget *parent = nullptr) : QWidget(parent), joueur(nullptr) {
        // Initialisation de la fenêtre
        setFixedSize(300, 150);
        setWindowTitle("Informations du Joueur");

        // Création de l'étiquette pour afficher le nombre de privilèges
        labelPriviliges = new QLabel("Nombre de Privilèges: 0", this);
        labelPriviliges->setGeometry(10, 10, 200, 30);

        // Zone de texte pour afficher le nombre de privilèges
        textePriviliges = new QLineEdit(this);
        textePriviliges->setReadOnly(true);
        textePriviliges->setGeometry(10, 40, 100, 30);

        // Étiquette pour le nombre de couronnes
        labelCouronnes = new QLabel("Nombre de Couronnes: 0", this);
        labelCouronnes->setGeometry(10, 80, 200, 30);

        // Zone de texte pour afficher le nombre de couronnes
        texteCouronnes = new QLineEdit(this);
        texteCouronnes->setReadOnly(true);
        texteCouronnes->setGeometry(10, 110, 100, 30);

        // Mise en place du joueur initial
        setJoueur(nullptr);
    }

public slots:
    // Fonction pour mettre à jour les informations du joueur
    void miseAJourInformations() {
        if (joueur) {
            // Mettez à jour le texte de l'étiquette et de la zone de texte avec les informations du joueur
            labelPriviliges->setText(QString("Nombre de Privilèges: %1").arg(joueur->getNombreDePrivileges()));
            textePriviliges->setText(QString::number(joueur->getNombreDePrivileges()));

            labelCouronnes->setText(QString("Nombre de Couronnes: %1").arg(joueur->getNombreCouronnes()));
            texteCouronnes->setText(QString::number(joueur->getNombreCouronnes()));
        }
    }

    // Fonction pour définir le joueur actuel
    void setJoueur(Joueur* j) {
        joueur = j;
        miseAJourInformations();  // Mettez à jour l'affichage lorsque le joueur change
    }

private:
    QLabel *labelPriviliges;
    QLineEdit *textePriviliges;
    QLabel *labelCouronnes;
    QLineEdit *texteCouronnes;
    Joueur *joueur;
};





#endif // JOUEUR_H
