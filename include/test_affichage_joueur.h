
#ifndef SPLENDOR_TEST_AFFICHAGE_JOUEUR_H
#define SPLENDOR_TEST_AFFICHAGE_JOUEUR_H


#include <QMainWindow>
#include <QLabel>
#include "Joueur.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(Joueur *joueur, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateLabel();

private:
    Joueur *joueur_;
    QLabel *labelPrivilges_;
};


#endif //SPLENDOR_TEST_AFFICHAGE_JOUEUR_H
