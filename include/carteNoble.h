#ifndef CARTENOBLE_H
#define CARTENOBLE_H

#include <map>
#include <QPushButton>
#include <QWidget>
#include <QPen>
#include <QIcon>

#include "couleur.h" // safe
#include "carte.h"


class CarteNoble : public Carte{
private:
    int couronne;
    int pointPrestige;
    const int id;


public:
    CarteNoble();
    CarteNoble(Plateau* p, Joueur* j, const std::string& chemin,
               int prestige,
               int cour, int pointPrestige, const Pouvoir& pvr1, const Pouvoir& pvr2,
               const int id);

    int getCouronne() const;
    int getPointPrestige()const;
    const int getID() const;
};


class VueCarteNoble : public QPushButton {
    Q_OBJECT
public:
    explicit VueCarteNoble (unsigned int n, VuePlateau* vp, QWidget* parent= nullptr):
            QPushButton(parent), parent(parent), numero(n) {
        /*
         * L'attribut numéro sert également pour l'ID bdd.
         */
        setFixedSize(100,150);
        vue_plateau = vp;
        QString chemin_image = QString::fromStdString("../images/" + std::to_string(numero+68) + ".png");
        setStyleSheet("QPushButton { border-image: url(" + chemin_image + "); }");
        connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
        QPixmap pixmap(chemin_image);
        pixmap.scaled(50, 50);
        QIcon icon (pixmap);
        this->setIcon(icon);
        this->setIconSize(this->size());
        setEnabled(true);
        //setIconSize(pixmap.rect().size());
        //setFixedSize(pixmap.rect().size());
    };

    //const CarteNoble* getCarte() const {return carte;}
    unsigned int getNumero() const {return numero;}

    //void setCarte(const CarteNoble* c) {carte = c;}



protected:
//    void paintEvent(QPaintEvent *event) override;
private:
    VuePlateau* vue_plateau;
    const CarteNoble* carte = nullptr;
    unsigned int numero; // est utilisé comme id bdd.
    QWidget* parent;
    signals:
            void carteClick(VueCarteNoble*);
public slots:
private slots:
    void clickedEvent() { emit carteClick(this); }

};
#endif // CARTENOBLE_H
