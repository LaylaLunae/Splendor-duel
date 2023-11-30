#ifndef JETON_H
#define JETON_H

#include <string>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include <iostream>
#include "couleur.h"

enum class JetonType {
    Or,
    Gemme,
};

class Jeton {
private:
    JetonType type;
    Couleur couleur; // Utilisé uniquement lorsque type = Gemme
    std::string chemin_vers_image;
    unsigned int positionX, positionY;
public:
    Jeton(JetonType t, Couleur c = Couleur::rien,
          unsigned int x=0,
          unsigned int y=0) :
          type(t), couleur(c), positionX(x), positionY(y) {}
    ~Jeton() {}

    void afficher() const;
    std::string getCouleurString() const;
    Couleur getCouleur() const;
    JetonType getType() const { return type; }
    unsigned int getX() const {return positionX;}
    unsigned int getY() const {return positionY;}
};


class VueJeton :public QPushButton {
Q_OBJECT
public:
    VueJeton(const Jeton* j, QWidget *parent = nullptr):jeton(j),QPushButton(parent) {
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(50,50);
        connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
        setCheckable(false);
    };
    explicit VueJeton(QWidget *parent = nullptr):QPushButton(parent) {
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(50, 50);
        connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
        setCheckable(false);
    };

    const Jeton* getJeton() const {
        return jeton;
    }

    void setJeton(const Jeton* j) {
        setCheckable(true);
        setChecked(false);
        jeton=j;
        update();
    }
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    const Jeton* jeton = nullptr;
    QPen pen;
    QBrush brush;
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void jetonClick(VueJeton*);
public slots:
private slots:
    void clickedEvent() { emit jetonClick(this); }


};


#endif // JETON_H
