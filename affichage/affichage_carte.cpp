// CardViewer.cpp
#include "affichage_carte.h"

AffichageCarte::AffichageCarte(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    auto *pile1Button = new QPushButton("Pile 1", this);
    auto *pile2Button = new QPushButton("Pile 2", this);
    auto *pile3Button = new QPushButton("Pile 3", this);
    cardLabel = new QLabel(this);
    cardLabel->setFixedSize(200, 300); // Set to card image size

    layout->addWidget(pile1Button);
    layout->addWidget(pile2Button);
    layout->addWidget(pile3Button);
    layout->addWidget(cardLabel);

    connect(pile1Button, &QPushButton::clicked, this, [this]{ showTopCard(1); });
    connect(pile2Button, &QPushButton::clicked, this, [this]{ showTopCard(2); });
    connect(pile3Button, &QPushButton::clicked, this, [this]{ showTopCard(3); });
}

void AffichageCarte::showTopCard(int pile) {
    QString imagePath = getTopCardImagePath(pile);
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        cardLabel->setPixmap(pixmap.scaled(cardLabel->size(), Qt::KeepAspectRatio));
    } else {
        QMessageBox::warning(this, "Warning", "Failed to load card image.");
    }
}

QString AffichageCarte::getTopCardImagePath(int pile) {
    // Replace with actual logic to get the top card image path from the database
    switch (pile) {
        case 1: return "../images/01.png";
        case 2: return "../images/31.png";
        case 3: return "../images/55.png";
        default: return QString();
    }
}
