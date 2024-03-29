#ifndef CARTEJOAILLERIE_H
#define CARTEJOAILLERIE_H

#include <map>
#include <vector>
#include <array>

#include "carte.h"

enum class Couleur;
class Joueur;

class CarteJoaillerie : public Carte { // Héritage de Carte
private:
    int niveau;    // La pioche correspondant à cette carte
    int couronne;  // Le score correspondant à la carte
    std::array<Couleur, 2> pierres; // La couleur que le joueur peut déduire lors de l'achat d'autres cartes à l'avenir.
    std::map<Couleur, int> prix;
    const int id;

public:
    CarteJoaillerie(Plateau* p, Joueur* j, int niv, int cour, const std::array<Couleur, 2>& pierres, std::map<Couleur, int> prx, const std::string& chemin, int prestige, const Pouvoir& pvr1, const Pouvoir& pvr2, const int id);
    CarteJoaillerie();
    ~CarteJoaillerie();

    // Specific methods for CarteJoaillerie
    std::map<Couleur, int> getPrix() const;
    int getNiveau() const;
    int getCouronne() const;
    int getID() const;
    bool hasPierre() const;
    Couleur getTypePierre() const;
    void setPierreColor(int index, Couleur couleur);
    std::array<Couleur, 2> getPierres() const;
    int getNombrePierre() const;
};

class VueCarteJoaillerie : public QPushButton {
Q_OBJECT

public:
    explicit VueCarteJoaillerie(unsigned int id, const std::vector<const CarteJoaillerie*> cartes, QWidget* parent = nullptr)
            : QPushButton(parent), carteJoaillerieId(id) {
        setFixedSize(100, 150);
        const CarteJoaillerie* carte = findCarteById(id, cartes);
        if (carte) {
            carte_rep = carte;
            QString cheminImage = QString::fromStdString(carte->getCheminVersImage());
            setStyleSheet("QPushButton { border-image: url(" + cheminImage + "); }");
        }
        connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
    }

    VueCarteJoaillerie(const CarteJoaillerie* c, const std::vector<CarteJoaillerie*> cartes, QWidget* parent = nullptr)
            : QPushButton(parent) {
        /*
         * Constructeur défini pour passer une carte en paramètre.
         * L'id est pris de cette carte.
         */
        unsigned int id = c->getID();
        carteJoaillerieId = id;
        setFixedSize(100, 150);
        const CarteJoaillerie *carte = findCarteById(id, cartes);
        if (carte) {
            carte_rep = carte;
            QString cheminImage = QString::fromStdString(carte->getCheminVersImage());
            setStyleSheet("QPushButton { border-image: url(" + cheminImage + "); }");
            QPixmap pixmap(cheminImage);
            pixmap.scaled(100, 150);
            QIcon icon (pixmap);
            this->setIcon(icon);
            this->setIconSize(this->size());
        }
        connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
    }

    unsigned int getCarteJoaillerieId() const {
        return carteJoaillerieId;
    }

    std::map<Couleur, int> getPrix() {
        if (carte_rep != nullptr) {
            return carte_rep->getPrix();
        }
        return std::map<Couleur, int>();
    }

    Couleur getCouleur() {
    if (carte_rep != nullptr && carte_rep->hasPierre()) return carte_rep->getTypePierre();
    return Couleur::rien;
}

    const CarteJoaillerie* getCarte() {return carte_rep;}

signals:
    void carteClickJ(VueCarteJoaillerie *);


private slots:
    void clickedEvent() {
        emit carteClickJ(this);
    }

private:
    unsigned int carteJoaillerieId;
    const CarteJoaillerie* carte_rep;

    const CarteJoaillerie* findCarteById(unsigned int id, const std::vector<const CarteJoaillerie*>& cartes) const {
        for (const auto& carte : cartes) {
            if (carte && carte->getID() == id) {
                return carte;
            }
        }
        return nullptr;
    }

    const CarteJoaillerie* findCarteById(unsigned int id, const std::vector< CarteJoaillerie*>& cartes) const {
        for (const auto& carte : cartes) {
            if (carte && carte->getID() == id) {
                return carte;
            }
        }
        return nullptr;
    }
};

#endif // CARTEJOAILLERIE_H
