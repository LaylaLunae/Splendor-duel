#ifndef CARTEJOAILLERIE_H
#define CARTEJOAILLERIE_H

#include <map>
#include <vector>
#include <array>

#include "carte.h"
//#include "joueur.h"
//#include "plateau.h"

enum class Couleur;
class Joueur;

class CarteJoaillerie : public Carte { // Inherits from Carte
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
    const int getID() const;
    bool hasPierre() const;
    Couleur getTypePierre() const;
    void setPierreColor(int index, Couleur couleur);
    std::array<Couleur, 2> getPierres() const;
    int getNombrePierre() const;
};

class VueCarteJoaillerie : public QPushButton {
Q_OBJECT

public:
    explicit VueCarteJoaillerie(unsigned int id, const std::vector<const CarteJoaillerie*>& cartes, QWidget* parent = nullptr)
            : QPushButton(parent), carteJoaillerieId(id) {
        setFixedSize(100, 150);
        const CarteJoaillerie* carte = findCarteById(id, cartes);
        if (carte) {
            QString cheminImage = QString::fromStdString(carte->getCheminVersImage());
            setStyleSheet("QPushButton { border-image: url(" + cheminImage + "); }");
        }
        connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
    }

    unsigned int getCarteJoaillerieId() const {
        return carteJoaillerieId;
    }

private slots:
    void clickedEvent() {
        // Implémenter la fonction lorsque le bouton est cliqué
        // Les fonctions mises en œuvre par les membres de l'équipe pourront être ajoutées ici à l'avenir.
    }

private:
    unsigned int carteJoaillerieId;

    const CarteJoaillerie* findCarteById(unsigned int id, const std::vector<const CarteJoaillerie*>& cartes) const {
        for (const auto& carte : cartes) {
            if (carte && carte->getID() == id) {
                return carte;
            }
        }
        return nullptr;
    }
};

// code pour tester QT de CarteJoaillerie
/*
int main(int argc, char *argv[]) {

    sqlite3* db;
    if (sqlite3_open("../base.db", &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    QApplication app(argc, argv);

    std::vector<const CarteJoaillerie*> cartesJoaillerie;
    initCarteJoaillerie(db, &cartesJoaillerie);

    QWidget window;
    window.setWindowTitle("Test VueCarteJoaillerie");

    VueCarteJoaillerie* vueCarte = new VueCarteJoaillerie(1, cartesJoaillerie, &window);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(vueCarte);

    window.setLayout(layout);
    window.show();
    return app.exec();
}
 */

#endif // CARTEJOAILLERIE_H
