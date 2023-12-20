//#include "../include/jeton.h"
#include <iostream>
#include <string>
#include <QPainter>
#include <QRegion>
#include "../include/jeu.h"

void VueJeton::paintEvent(QPaintEvent*  event) {
    QPainter painter(this);

    // On choisit la couleur de fond à afficher
    Qt::GlobalColor bg_color_tmp;
    Couleur couleur = jeton->getCouleur();
    switch (jeton->getType()) {
        case JetonType::Or: {
            bg_color_tmp = Qt::yellow;
            break;
        }
        case JetonType::Gemme: {
            switch (couleur) {
                case Couleur::rouge:
                    bg_color_tmp = Qt::red;
                    break;
                case Couleur::vert:
                    bg_color_tmp = Qt::green;
                    break;
                case Couleur::bleu:
                    bg_color_tmp = Qt::blue;
                    break;
                case Couleur::noir:
                    bg_color_tmp = Qt::gray;
                    break;
                case Couleur::blanc:
                    bg_color_tmp = Qt::white;
                    break;
                case Couleur::rose:
                    bg_color_tmp = Qt::magenta;
                    break;
                case Couleur::rien:
                    bg_color_tmp = Qt::gray;
                    break;
            }
            break;
        }
    }
    QColor bg_color(bg_color_tmp);
    if (!is_selected) {
        bg_color.setAlpha(128);
    }
    // Texte contenant la position du bouton à afficher
//    std::string texte = std::to_string(pos_x);
//    texte.append(",");
//    texte.append(std::to_string(pos_y));
//    QString buttonText = QString::fromStdString(texte);
//    this->setText(buttonText);
//    painter.drawText(0, 0, buttonText);

    setButtonColors(bg_color,Qt::black);
    int h, s, v;
    bg_color.getHsv(&h, &s, &v);
    setStyleSheet(QString("QPushButton {"
                          "    border-radius: 25px;"
                          "    background-color: %1;" // Set background color dynamically
                          "    color: white;" // Set text color
                          "}"
                          "QPushButton:hover {"
                          "    background-color:%2;" // Change color on hover
                          "}").arg(bg_color.name(), QColor::fromHsv(h, s, qMin(255, v + 20)).name()));
    setFixedSize(70,70);
    QRect rect(0,0,40,40);
    QRegion region(rect, QRegion::Ellipse);
    setMask(region);
    QPushButton::paintEvent(event);
}

void VueJeton::setSelected(bool s) {
    is_selected=s;
    QPalette p = this->palette();
    QColor current = p.color(QPalette::Button);
    if (!s)
        current.setAlpha(128);
    p.setColor(QPalette::Button, current);
    setPalette(p);
    update();
}

void VueJeton::setButtonColors(const QColor &backgroundColor, const QColor &textColor) {
    // Get the default palette
    QPalette palette = this->palette();

    // Set the background color for buttons to the specified color
    palette.setColor(QPalette::Button, backgroundColor);

    // Set the text color for buttons to the specified color
    palette.setColor(QPalette::ButtonText, textColor);

    // Apply the modified palette to the button
    setPalette(palette);

    QFont font = this->font();
    font.setPointSize(12);
    setFont(font);
}

void Jeton::afficher() const {
    std::string type_str;
    switch (type) {
        case JetonType::Or: {
            type_str = "Or";
            std::cout << "Jeton " << type_str << std::endl;
            break;
        }
        case JetonType::Gemme: {
            type_str = "Gemme";
            std::string couleur_str;
            switch (couleur) {
                case Couleur::rouge:
                    couleur_str = "Rouge";
                    break;
                case Couleur::vert:
                    couleur_str = "Vert";
                    break;
                case Couleur::bleu:
                    couleur_str = "Bleu";
                    break;
                case Couleur::noir:
                    couleur_str = "Noir";
                    break;
                case Couleur::blanc:
                    couleur_str = "Blanc";
                    break;
                case Couleur::rose:
                    couleur_str = "Rose";
                    break;
                case Couleur::rien:
                    couleur_str = "Rien";
                    break;
                case Couleur::choix_utilisateur:
                    couleur_str = "Choix_Utilisateur";
                    break;
            }
            std::cout << "Jeton " << type_str << " de couleur " << couleur_str << std::endl;
            break;
        }
        default:
            std::cout << "Jeton Inconnu" << std::endl;
            break;
    }
}

Couleur Jeton::getCouleur() const {
    if (type == JetonType::Gemme) {
        return couleur;
    }
    return Couleur::rien;
}

std::string Jeton::getCouleurString() const {
    std::string type_str;
    switch (type) {
        case JetonType::Or: {
            type_str = "Or";
            return type_str;
        }
        case JetonType::Gemme: {
            switch (couleur) {
                case Couleur::rouge:
                    type_str = "Rouge";
                    break;
                case Couleur::vert:
                    type_str = "Vert";
                    break;
                case Couleur::bleu:
                    type_str = "Bleu";
                    break;
                case Couleur::noir:
                    type_str = "Noir";
                    break;
                case Couleur::blanc:
                    type_str = "Blanc";
                    break;
                case Couleur::rose:
                    type_str = "Rose";
                    break;
                case Couleur::rien:
                    type_str = "Rien";
                    break;
            }
            return type_str;
        }
    }
    return "";
}