#ifndef CARTENOBLE_H
#define CARTENOBLE_H

#include <map>
#include <QPushButton>
#include <QWidget>
#include <QPen>

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
    explicit VueCarteNoble (unsigned int n, QWidget* parent= nullptr):
            QPushButton(parent), parent(parent), numero(n) {
        //carte = c;
        setFixedSize(50,50);
        connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
        //update();
    };

    //const CarteNoble* getCarte() const {return carte;}
    unsigned int getNumero() const {return numero;}

    //void setCarte(const CarteNoble* c) {carte = c;}


protected:
    void paintEvent(QPaintEvent *event) override;
private:
    //const CarteNoble* carte = nullptr;
    unsigned int numero;
    QWidget* parent;
    signals:
            void carteClick(VueCarteNoble*);
public slots:
private slots:
    void clickedEvent() { emit carteClick(this); }
};
#endif // CARTENOBLE_H
