#ifndef JETON_H
#define JETON_H

#include <string>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include <iostream>
#include <QLabel>
#include <QString>
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

    void setX (unsigned int x) {positionX=x;}
    void setY (unsigned int y) {positionY=y;}

};


class VueJeton : public QPushButton {
Q_OBJECT
public:
    VueJeton(const Jeton* j, unsigned int x, unsigned int y, QWidget *parent = nullptr):
    jeton(j),pos_x(x),pos_y(y),is_selected(false),
    QPushButton(parent), parent(parent) {
        setFixedSize(50,50);
        connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
        //setCheckable(false);
    };
    explicit VueJeton(QWidget *parent = nullptr):QPushButton(parent){
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
        jeton = j;
    }

    unsigned int getX() {return pos_x;}
    unsigned int getY() {return pos_y;}
    void setSelected(bool s);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    const Jeton* jeton = nullptr;
    QWidget* parent;
    QPen pen;
    QBrush brush;
    unsigned  int pos_x;
    unsigned int pos_y;
    bool is_selected;
    void setButtonColors(const QColor &backgroundColor, const QColor &textColor);
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void jetonClick(VueJeton*);
public slots:
private slots:
    void clickedEvent() { emit jetonClick(this); }


};


#endif // JETON_H
