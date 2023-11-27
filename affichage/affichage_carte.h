#ifndef AFFICHAGECARTE_H
#define AFFICHAGECARTE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>

class AffichageCarte : public QWidget {
Q_OBJECT
public:
    AffichageCarte(QWidget *parent = nullptr);

private slots:
    void showTopCard(int pile);

private:
    QLabel *cardLabel;
    QString getTopCardImagePath(int pile);
};

#endif // AFFICHAGECARTE_H
