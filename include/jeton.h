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
};


class VueJeton :public QPushButton {
Q_OBJECT
public:
    VueJeton(const QString& text, const Jeton* j, QWidget *parent = nullptr):
    jeton(j),
    QPushButton(text, parent), parent(parent) {
        //setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(50,50);
        connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
        setButtonColor(QColor(173, 216, 230));

        //std::string texte = std::to_string(j->getX());
        //texte.append(std::to_string(j->getY()));
        //std::cout<<texte<<"\n";
        //QString buttonText = QString::fromStdString(texte);
        //this->setText(buttonText);
        //update();
        //show();

        //setCheckable(false);
    };
    explicit VueJeton(QWidget *parent = nullptr):QPushButton(parent) {
        std::cout<<"Explicit\n";
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
        std::string texte = std::to_string(j->getX());
        texte.append(std::to_string(j->getY()));
        //setText(QString::fromStdString( texte));
        //show();
        update();
    }
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    const Jeton* jeton = nullptr;
    QWidget* parent;
    QLabel* label = nullptr;
    QPen pen;
    QBrush brush;
    void setButtonColor(const QColor &color) {
        // Get the default palette
        QPalette palette = this->palette();

        // Set the background color for buttons to the specified color
        palette.setColor(QPalette::Button, color);

        // Apply the modified palette to the button
        setPalette(palette);
    }
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void jetonClick(VueJeton*);
public slots:
private slots:
    void clickedEvent() { emit jetonClick(this); }


};


#endif // JETON_H
