#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "pioche.h"

#include "../include/jeu.h"
enum class Couleur;

//initialisation de pioche
Pioche::Pioche(int np, int mcr, int mcp):numero_pioche(np),
                                         max_cartes_revelees(mcr), max_cartes_pioche(mcp){
    cartes_dans_pioche = new const CarteJoaillerie*[mcp];
    cartes_dehors = new const CarteJoaillerie*[mcr];

    for (int i = 0; i < mcp; ++i) {
        cartes_dans_pioche[i] = nullptr;
    }
    for (int i = 0; i < mcr; ++i) {
        cartes_dehors[i] = nullptr;
    }
}

//destructeur de pioche
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

// prendre une carte dans les cartes révélées
const CarteJoaillerie * Pioche::joueurPrend(int numero_carte) {
    int i = 0;
    while(cartes_dehors[i]->getID() != numero_carte) { //cherche la carte en question
        std::cout << cartes_dehors[i]->getID() << "\n";
        i++;
    }
    const CarteJoaillerie * temp = cartes_dehors[i]; //pour retourner la carte
    if (max_cartes_pioche != -1) { //si la pioche est pas vide, on remplace le trou par une carte
        int nombreAleatoire = std::rand() % max_cartes_pioche; //choix d'une carte au hasard
        cartes_dehors[i] = cartes_dans_pioche[nombreAleatoire];
        cartes_dans_pioche[nombreAleatoire] = cartes_dans_pioche[max_cartes_pioche-1];
        max_cartes_pioche--;
    }
    return temp;
}

void Pioche::distribution(){ // ne servira que pour la création de partie
    int i = 0;
    while (i < max_cartes_revelees && max_cartes_pioche != -1) {
        int nombreAleatoire = std::rand() % max_cartes_pioche; //choix d'une carte au hasard
        cartes_dehors[i] = cartes_dans_pioche[nombreAleatoire];
        cartes_dans_pioche[nombreAleatoire] = cartes_dans_pioche[max_cartes_pioche-1];
        max_cartes_pioche--;
        i++;
    }
}

//cas où on prend dans la pioche
const CarteJoaillerie * Pioche::joueurPrendPioche() {
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
    f << "\n";
}

std::string couleurToString(Couleur couleur) {
    switch (couleur) {
        case Couleur::rouge:
            return "rouge";
            break;
        case Couleur::vert:
            return "vert";
            break;
        case Couleur::bleu:
            return "bleu";
            break;
        case Couleur::noir:
            return "noir";
            break;
        case Couleur::blanc:
            return "blanc";
            break;
        case Couleur::rose:
            return "rose";
            break;
        default:
            return "rien";
    }
}

void Pioche::afficherCartesRevelees(std::ostream &f) {
    f << "Cartes sur le plateau de la pioche " << numero_pioche << ":\n";
    for (int i = 0; i < max_cartes_revelees; i++) {
        f << "Carte : " << cartes_dehors[i]->getID() << ", prix : (";
        std::map<Couleur, int> prix = cartes_dehors[i]->getPrix();
        for (const auto& paire : prix) {
            f << couleurToString(paire.first) << " - " << paire.second << ", ";
        }
        f << "), produit : (";
        std::array<Couleur, 2> pierre = cartes_dehors[i]->getPierres();
        for (const auto& element : pierre) {
            f << couleurToString(element) << " - ";
        }
        f << ")\n";
    }
    f << "\n";
}


VuePioche::VuePioche(Pioche * p1, Pioche * p2, Pioche * p3, std::vector<CarteJoaillerie*> tot_cartes_jo_, QWidget * parent): QWidget(parent) {
    layoutPioches = new QVBoxLayout;
    layoutPioche1 = new QHBoxLayout;
    layoutPioche2 = new QHBoxLayout;
    layoutPioche3 = new QHBoxLayout;
    layoutDosPioche = new QVBoxLayout;
    layoutPlateauCarte = new QHBoxLayout;
    carteSelectionnee = nullptr;
    valider = new QPushButton("Valider");
    vuecartes1 = std::vector<VueCarteJoaillerie*>(0);
    vuecartes2 = std::vector<VueCarteJoaillerie*>(0);
    vuecartes3 = std::vector<VueCarteJoaillerie*>(0);
    //const std::vector<CarteJoaillerie*> test(0);
    pioches = std::vector<Pioche*>();
    pioches.push_back(p1);
    pioches.push_back(p2);
    pioches.push_back(p3);
    tot_cartes_jo = std::vector<CarteJoaillerie*>();
    for (auto vc : tot_cartes_jo_) {tot_cartes_jo.push_back(vc); }
    vuescartes_tot =    std::vector<std::vector<VueCarteJoaillerie*>>();
    vuescartes_tot.push_back(vuecartes1);
    vuescartes_tot.push_back(vuecartes2);
    vuescartes_tot.push_back(vuecartes3);

    int card_width = 100;
    int card_height = 150;
    for (size_t row = 0; row < p3->getMaxCartesRevelees(); row++) {
        const CarteJoaillerie* c = p3->cartes_dehors[row];
        VueCarteJoaillerie * carte = new VueCarteJoaillerie(c, tot_cartes_jo, this);
        carte->setStyleSheet("border: 1px solid black;");  // Ajouter une bordure pour la séparation
        carte->setFixedSize(card_width, card_height);
        vuecartes3.push_back(carte);
        layoutPioche3->addWidget(vuecartes3[row]);
        connect(vuecartes3[row], SIGNAL(carteClickJ(VueCarteJoaillerie*)), this, SLOT(carteClique(VueCarteJoaillerie*)));
    }

    for (size_t row = 0; row < p2->getMaxCartesRevelees(); row++) {
        VueCarteJoaillerie * carte = new VueCarteJoaillerie(p2->cartes_dehors[row], tot_cartes_jo, this);
        carte->setStyleSheet("border: 1px solid black;");  // Ajouter une bordure pour la séparation
        carte->setFixedSize(card_width, card_height);
        vuecartes2.push_back(carte);
        layoutPioche2->addWidget(vuecartes2[row]);
        connect(vuecartes2[row], SIGNAL(carteClickJ(VueCarteJoaillerie*)), this, SLOT(carteClique(VueCarteJoaillerie*)));
    }

    for (size_t row = 0; row < p1->getMaxCartesRevelees(); row++) {
        VueCarteJoaillerie * carte = new VueCarteJoaillerie(p1->cartes_dehors[row], tot_cartes_jo, this);
        carte->setStyleSheet("border: 1px solid black;");  // Ajouter une bordure pour la séparation
        carte->setFixedSize(card_width, card_height);
        vuecartes1.push_back(carte);
        layoutPioche1->addWidget(vuecartes1[row]);
        connect(vuecartes1[row], SIGNAL(carteClickJ(VueCarteJoaillerie*)), this, SLOT(carteClique(VueCarteJoaillerie*)));
    }

    QPushButton * dos1 = new QPushButton("Pioche 1");
    vuedoscartes.push_back(dos1);
    vuedoscartes[0]->setStyleSheet("border: 1px solid black;");
    vuedoscartes[0]->setFixedSize(card_width, card_height);
    layoutDosPioche->addWidget(vuedoscartes[0]);

    QPushButton * dos2 = new QPushButton("Pioche 2");
    vuedoscartes.push_back(dos2);
    vuedoscartes[1]->setStyleSheet("border: 1px solid black;");
    vuedoscartes[1]->setFixedSize(card_width, card_height);
    layoutDosPioche->addWidget(vuedoscartes[1]);

    QPushButton * dos3 = new QPushButton("Pioche 3");
    vuedoscartes.push_back(dos3);
    vuedoscartes[2]->setStyleSheet("border: 1px solid black;");
    vuedoscartes[2]->setFixedSize(card_width, card_height);
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

    layout_pioches = std::vector<QHBoxLayout*>();
    layout_pioches.push_back(layoutPioche1);
    layout_pioches.push_back(layoutPioche2);
    layout_pioches.push_back(layoutPioche3);

    setLayout(layoutPlateauCarte);
}

void VuePioche::carteClique(VueCarteJoaillerie * c) {
    carteSelectionnee = c;
    std::cout<<"Got it! \n";
}

void VuePioche::validerCarte() {
    if (carteSelectionnee != nullptr){
        std::cout<<"\nCarte sel "<<carteSelectionnee->getCarteJoaillerieId()<<"\n";
        //const CarteJoaillerie* carte_sel_carte = carteSelectionnee->getCarte();
        const CarteJoaillerie* carte_sel_carte = nullptr;
        Joueur* actif = Jeu::getJeu().getJoueurActuel();
        std::map<Couleur, int> prix = carteSelectionnee->getPrix();
        std::vector<int> difference = Obligatoire::calculDifference(actif, prix);
        bool peut_acheter = Obligatoire::achatCartePossible(actif, difference);
        if (peut_acheter) {
            int numero_pioche = carteSelectionnee->getCarte()->getNiveau();
            carte_sel_carte = pioches[numero_pioche-1]->joueurPrend(carteSelectionnee->getCarteJoaillerieId());
            actif->ajouterCarteJoaillerie(const_cast<CarteJoaillerie *>(carte_sel_carte));

            // On retire les jetons au joueur et les remet dans le sac
            Plateau* plateau = Jeu::getJeu().getVueJeu()->getVuePlateau()->getPlateau();
            for (auto elem = prix.begin(); elem != prix.end(); elem++) {
                int prix_elem = elem->second;
                switch (elem->first) {
                    case Couleur::bleu:
                        Obligatoire::remettreJetonSac(actif, plateau, Couleur::bleu, difference[0], prix_elem, 0);
                        break;
                    case Couleur::vert:
                        Obligatoire::remettreJetonSac(actif, plateau, Couleur::vert, difference[1], prix_elem, 1);
                        break;
                    case Couleur::rouge:
                        Obligatoire::remettreJetonSac(actif, plateau, Couleur::rouge, difference[2], prix_elem, 2);
                        break;
                    case Couleur::blanc:
                        Obligatoire::remettreJetonSac(actif, plateau, Couleur::blanc, difference[3], prix_elem, 3);
                        break;
                    case Couleur::noir:
                        Obligatoire::remettreJetonSac(actif, plateau, Couleur::noir, difference[4], prix_elem, 4);
                        break;
                    case Couleur::rose:
                        Obligatoire::remettreJetonSac(actif, plateau, Couleur::rose, difference[5], prix_elem, 5);
                        break;
                    default:
                        std::cout << "Il y a un probleme avec le jeton pris au joueur !\n";
                }
            }

            std::cout<<plateau->etatPlateau();

                mettreAJour(numero_pioche-1, carte_sel_carte->getID());
            Jeu::getJeu().getVueJeu()->finiAction(3);

        } else {
            Jeu::getJeu().getVueJeu()->message("Action", "Vous ne pouvez pas acheter cette carte");
        }
        //return carteSelectionnee->getCarteJoaillerieId();
    }
    else {
        std::cout << "\nCarte sel " << "nullptr" << "\n";
    }
//        return -1;
}

void VuePioche::mettreAJour(int index_to_update, int index_carte) {
    while (QLayoutItem *item = layout_pioches[index_to_update]->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    for (size_t row = 0; row < pioches[index_to_update]->getMaxCartesRevelees(); row++) {
        VueCarteJoaillerie * carte = new VueCarteJoaillerie(pioches[index_to_update]->cartes_dehors[row], tot_cartes_jo, this);
        carte->setStyleSheet("border: 1px solid black;");  // Ajouter une bordure pour la séparation
        carte->setFixedSize(100, 150);
        vuescartes_tot[index_to_update].push_back(carte);
        layout_pioches[index_to_update]->addWidget(vuescartes_tot[index_to_update][row]);
        connect(vuescartes_tot[index_to_update][row], SIGNAL(carteClickJ(VueCarteJoaillerie*)), this, SLOT(carteClique(VueCarteJoaillerie*)));
    }
    repaint();
}
