#include <iostream>
#include <cstdlib>
#include <ctime>
#include "pioche.h"
//#include "jeu.h"

Pioche::Pioche(int np, int mcr, int mcp):numero_pioche(np),
                                         max_cartes_revelees(mcr), max_cartes_pioche(mcp){
    cartes_dans_pioche = new const CarteJoaillerie*[mcp];
    cartes_dehors = new const CarteJoaillerie*[mcr];

    for (int i = 0; i < mcp; ++i) {
        cartes_dans_pioche[i] = new CarteJoaillerie(i);
    }
    for (int i = 0; i < mcr; ++i) {
        cartes_dehors[i] = nullptr;
    }
}

Pioche::~Pioche(){
    for (int i = 0; i < max_cartes_pioche; i++) {
        delete cartes_dans_pioche[i];
    }
    for (int i = 0; i < max_cartes_revelees; i++) {
        delete cartes_dehors[i];
    }
    delete [] cartes_dans_pioche;
    delete [] cartes_dehors;
}

const CarteJoaillerie * Pioche::joueurPrend(int numero_carte) {
    int i = 0;
    while(cartes_dehors[i]->getID() != numero_carte) {
        std::cout << cartes_dehors[i]->getID() << "\n";
        i++;
    }
    std::cout << "Passe\n";
    const CarteJoaillerie * temp = cartes_dehors[i];
    if (max_cartes_pioche != -1) {
        //std::srand(std::time(0));
        int nombreAleatoire = std::rand() % max_cartes_pioche;
        cartes_dehors[i] = cartes_dans_pioche[nombreAleatoire];
        cartes_dans_pioche[nombreAleatoire] = cartes_dans_pioche[max_cartes_pioche-1];
        max_cartes_pioche--;
    }
    return temp;
}

void Pioche::distribution(){ // ne servira que pour la création de partie
    int i = 0;
    while (i < max_cartes_revelees && max_cartes_pioche != -1) {
        //std::srand(std::time(0));
        int nombreAleatoire = std::rand() % max_cartes_pioche;
        cartes_dehors[i] = cartes_dans_pioche[nombreAleatoire];
        cartes_dans_pioche[nombreAleatoire] = cartes_dans_pioche[max_cartes_pioche-1];
        max_cartes_pioche--;
        i++;
    }
}

const CarteJoaillerie * Pioche::joueurPrendPioche() {
    //std::srand(std::time(0));
    int nombreAleatoire = std::rand() % max_cartes_pioche;
    const CarteJoaillerie * temp = cartes_dans_pioche[nombreAleatoire];
    cartes_dans_pioche[nombreAleatoire] = cartes_dans_pioche[max_cartes_pioche-1];
    max_cartes_pioche--;
    return temp;
}

void Pioche::afficherPioche(std::ostream& f){
    f << "Cartes dans pioche " << numero_pioche << ":\n";
    for (int i = 0; i < max_cartes_pioche; i++)
        f << "Carte : " << cartes_dans_pioche[i]->getID() << "\n";
}

void Pioche::afficherCartesRevelees(std::ostream &f) {
    f << "Cartes sur le plateau de la pioche " << numero_pioche << ":\n";
    for (int i = 0; i < max_cartes_revelees; i++)
        f << "Carte : " << cartes_dehors[i]->getID() << "\n";
}

VuePioche::VuePioche(Pioche * p1, Pioche * p2, Pioche * p3, QWidget * parent): QWidget(parent) {
    layoutPioches = new QVBoxLayout;
    layoutPioche1 = new QHBoxLayout;
    layoutPioche2 = new QHBoxLayout;
    layoutPioche3 = new QHBoxLayout;
    layoutDosPioche = new QVBoxLayout;
    layoutPlateauCarte = new QHBoxLayout;
    carteSelectionnee = nullptr;
    valider = new QPushButton("Valider");
    const std::vector<CarteJoaillerie*> test(0);


    for (size_t row = 0; row < p3->getMaxCartesRevelees(); row++) {
        std::cout << "Test \n";
        const CarteJoaillerie* c = p3->cartes_dehors[row];
        std::cout << "Test2 \n";
        VueCarteJoaillerie * carte = new VueCarteJoaillerie(c, test, nullptr);
        vuecartes3.push_back(carte);
        vuecartes3[row]->setStyleSheet("border: 1px solid black;");  // Ajouter une bordure pour la séparation
        vuecartes3[row]->setFixedSize(150, 200);
        layoutPioche3->addWidget(vuecartes3[row]);
        connect(vuecartes3[row], SIGNAL(carteClickJ(VueCarteJoaillerie*)), this, SLOT(carteClique(VueCarteJoaillerie*)));
    }

    for (size_t row = 0; row < p2->getMaxCartesRevelees(); row++) {
        VueCarteJoaillerie * carte = new VueCarteJoaillerie(p2->cartes_dehors[row], test, nullptr);
        vuecartes2.push_back(carte);
        vuecartes2[row]->setStyleSheet("border: 1px solid black;");  // Ajouter une bordure pour la séparation
        vuecartes2[row]->setFixedSize(150, 200);
        layoutPioche2->addWidget(vuecartes2[row]);
        connect(vuecartes2[row], SIGNAL(carteClickJ(VueCarteJoaillerie*)), this, SLOT(carteClique(VueCarteJoaillerie*)));
    }

    for (size_t row = 0; row < p1->getMaxCartesRevelees(); row++) {
        VueCarteJoaillerie * carte = new VueCarteJoaillerie(p1->cartes_dehors[row], test, nullptr);
        vuecartes1.push_back(carte);
        vuecartes1[row]->setStyleSheet("border: 1px solid black;");  // Ajouter une bordure pour la séparation
        vuecartes1[row]->setFixedSize(150, 200);
        layoutPioche1->addWidget(vuecartes1[row]);
        connect(vuecartes1[row], SIGNAL(carteClickJ(VueCarteJoaillerie*)), this, SLOT(carteClique(VueCarteJoaillerie*)));
    }

    QPushButton * dos1 = new QPushButton("Pioche 1");
    vuedoscartes.push_back(dos1);
    vuedoscartes[0]->setStyleSheet("border: 1px solid black;");
    vuedoscartes[0]->setFixedSize(150, 200);
    layoutDosPioche->addWidget(vuedoscartes[0]);

    QPushButton * dos2 = new QPushButton("Pioche 2");
    vuedoscartes.push_back(dos2);
    vuedoscartes[1]->setStyleSheet("border: 1px solid black;");
    vuedoscartes[1]->setFixedSize(150, 200);
    layoutDosPioche->addWidget(vuedoscartes[1]);

    QPushButton * dos3 = new QPushButton("Pioche 3");
    vuedoscartes.push_back(dos3);
    vuedoscartes[2]->setStyleSheet("border: 1px solid black;");
    vuedoscartes[2]->setFixedSize(150, 200);
    layoutDosPioche->addWidget(vuedoscartes[2]);

    QObject::connect(
            valider, &QPushButton::clicked,
            this,
            &VuePioche::validerCarte);

    layoutPioches->addLayout(layoutPioche3);
    layoutPioches->addLayout(layoutPioche2);
    layoutPioches->addLayout(layoutPioche1);
    layoutPioches->setAlignment(Qt::AlignCenter);
    layoutPlateauCarte->addLayout(layoutDosPioche);
    layoutPlateauCarte->addLayout(layoutPioches);
    layoutPlateauCarte->addWidget(valider);

    setLayout(layoutPlateauCarte);
}

void VuePioche::carteClique(VueCarteJoaillerie * c) {
    carteSelectionnee = c;
}

void VuePioche::validerCarte() {
    if (carteSelectionnee != nullptr){
        std::cout<<"\nCarte sel "<<carteSelectionnee->getCarteJoaillerieId()<<"\n";
        //return carteSelectionnee->getCarteJoaillerieId();
    }
    else
        std::cout<<"\nCarte sel "<<"nullptr"<<"\n";
//        return -1;
}