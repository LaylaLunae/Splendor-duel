#include <iostream>
#include <tuple>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDir>
#include <vector>

#include "./include/jeu.h"
#include "./include/plateau.h"
#include "affichage/affichage_carte.h"
#include "./include/affichage_joueur.h"

class Plateau;
class Pioche;
class Joueur;


int main(int argc, char *argv[]) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

/*
    Plateau * plateau_jeu = new Plateau();
    std::string sortie = plateau_jeu->etatPlateau();
    std::cout << sortie << "\n";

    Pioche * pioche1 = new Pioche(1,5,30);
    Pioche * pioche2 = new Pioche(2,4,24);
    Pioche * pioche3 = new Pioche(3,3,13);

    IA ia("IA1", Difficulte::aleatoire);
    ia.initialiserJoueur();

    Optionnelle * act_opt = new Optionnelle();
    Obligatoire * act_obl = new Obligatoire();

    act_opt->remplissagePlateau(&ia, plateau_jeu);


    int choixIA = ia.choisirChoix(1, 3);
    std::cout << "Choix de l'IA : " << choixIA << std::endl;
*/
/*

    Plateau* p = new Plateau();
    std::cout << p->etatPlateau();
    IA* ia = new IA("Jean",aleatoire);
    IA* j2 = new IA("Adversaire",aleatoire);
    ia->setAdversaire(j2);
    Pioche* p1 = new Pioche(1,5,30);
    Pioche* p2 = new Pioche(2,4,24);
    Pioche* p3 = new Pioche(3,3,13);

    std::array<Couleur, 2> pierres = {Couleur::rouge, Couleur::bleu};
    std::map<Couleur, int> prix = {{Couleur::rouge, 3}, {Couleur::bleu, 2}};
    int id = 1;
    CarteJoaillerie* c = new CarteJoaillerie(p, ia, 3, 2, pierres, prix, "chemin_image.jpg", 5, Pouvoir(), Pouvoir(), id);

    for (int i=0; i<5;i++) {
        p1->cartes_dehors[i] = c;
        id++;
        c = new CarteJoaillerie(p, ia, 3, 2, pierres, prix, "chemin_image.jpg", 5, Pouvoir(), Pouvoir(), id);
    }
    for (int i=0; i<30; i++) {
        p1->cartes_dans_pioche[i] = c;
        id++;
        c = new CarteJoaillerie(p, ia, 3, 2, pierres, prix, "chemin_image.jpg", 5, Pouvoir(), Pouvoir(), id);
    }
    for (int i=0; i<4;i++) {
        p2->cartes_dehors[i] = c;
        id++;
        c = new CarteJoaillerie(p, ia, 3, 2, pierres, prix, "chemin_image.jpg", 5, Pouvoir(), Pouvoir(), id);
    }
    for (int i=0; i<24; i++) {
        p2->cartes_dans_pioche[i] = c;
        id++;
        c = new CarteJoaillerie(p, ia, 3, 2, pierres, prix, "chemin_image.jpg", 5, Pouvoir(), Pouvoir(), id);
    }
    for (int i=0; i<3;i++) {
        p3->cartes_dehors[i] = c;
        id++;
        c = new CarteJoaillerie(p, ia, 3, 2, pierres, prix, "chemin_image.jpg", 5, Pouvoir(), Pouvoir(), id);
    }
    for (int i=0; i<13; i++) {
        p3->cartes_dans_pioche[i] = c;
        id++;
        c = new CarteJoaillerie(p, ia, 3, 2, pierres, prix, "chemin_image.jpg", 5, Pouvoir(), Pouvoir(), id);
    }

    p1->afficherCartesRevelees();
    p2->afficherCartesRevelees();
    p3->afficherCartesRevelees();
*/
/*
    //tester pour prendre des cartes avec l'IA
    const Pioche& piocheRef = *p1; // Créer une référence constante à p1
    std::vector<CarteJoaillerie*> cartesAchetable = ia->getCartesAchetable(piocheRef);

    std::cout<<"jfjzflj";

    for (const auto& carte : cartesAchetable) {
        //std::cout << "Prix de la carte : " << carte->getPrix() << std::endl;
        std::cout << "prix : \n  " ;
    }
*/
/*
    //Carte carte;
    CarteJoaillerie* derniereCarte = ia->melangerEtObtenirDerniereCarte(*p1, *ia, *p, *c);
    std::cout << "prix :" << std::endl;

*/

// test pour prendre des jetons à l'IA :
/*
// pour 2 jetons

    std::vector<std::pair<const Jeton*, const Jeton*>> combinaisons = ia.genererCombinaisonsDeuxJetons(plateau_jeu);

    std::cout << "Combinaisons générées :\n";
    for (const auto& combinaison : combinaisons) {
        std::cout << "Jeton 1 : " << combinaison.first->getCouleurString() << ", Jeton 2 : " << combinaison.second->getCouleurString() << std::endl;
    }
*/
/*
// pour 3 jetons
    std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisons3 = ia.genererCombinaisonsTroisJetons(plateau_jeu);

    // Affichez les combinaisons générées
    std::cout << "Combinaisons générées :\n";
    for (const auto& combinaison3 : combinaisons3) {
        const Jeton* jeton1 = std::get<0>(combinaison3);
        const Jeton* jeton2 = std::get<1>(combinaison3);
        const Jeton* jeton3 = std::get<2>(combinaison3);

        std::cout << "Jeton 1 : " << jeton1->getCouleurString() << ", Jeton 2 : " << jeton2->getCouleurString() << ", Jeton 3 : " << jeton3->getCouleurString() << std::endl;
        std::cout<<"jslkdfj\n";
    }
*/
    // prendre 1 jeton

    //ia.choisirJetonSurPlateau(plateau_jeu);


    // tous choix jetons confondus :
     //ia.prendreJetons(plateau_jeu);


    /* Création Jeton : */


    /* Affichage plateau v0.1*/
    //QApplication app (argc, argv);
    //VuePlateau plateau;
    //plateau.show();
    //return app.exec();


    /* Affichage cartes v0.1 */
//     QApplication app(argc, argv);
//     QLabel label;
//     QPixmap pixmap("../images/01.png");
//    if (pixmap.isNull()) {
//        qDebug() << "Failed to load the image. Check the path:";
//        qDebug() << QDir::current().absoluteFilePath("images/01.png");
//    } else {
//        label.setPixmap(pixmap);
//        label.setScaledContents(true); // This ensures the image scales with the label size.
//        label.show();
//    }
//    return app.exec();

    /* Affichage piles de carte */
    /*
    QApplication app(argc, argv);
    AffichageCarte affichageCarte;
    affichageCarte.show();
    return app.exec();
     */


    // ZhenyangZhenyangZhenyangZhenyangZhenyangZhenyangZhenyang: test 3 fonctions de BDD

    sqlite3* db;
    if (sqlite3_open("../base.db", &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    clearAndInitializeTables(db); // succès

    auto* cartesJoaillerie = new std::vector<const CarteJoaillerie*>();
    auto* cartesNoble = new std::vector<const CarteNoble*>();
    //std::vector<Privilege> privileges;

    initCarteJoaillerie(db, cartesJoaillerie); // succès
    initCarteNoble(db, cartesNoble); // succès
//    for (int id = 1; id <= 3; ++id) {
//        Privilege privilege;
//        privilege.setID(id);
//        privileges.push_back(privilege);
//    }

    std::cout<<"          1\n";

    std::cout << "init carteJoaillerie" << std::endl;
    for (auto carteJoaillerie : *cartesJoaillerie) {
        std::cout << carteJoaillerie->getID() << std::endl;
    }

    std::cout << "init carteNoble" << std::endl;
    for (auto carteNoble : *cartesNoble) {
        std::cout << carteNoble->getID() << std::endl;
    }

    Humain joueur1("Joueur Alex");
    Humain joueur2("Joueur 2");
    std::vector<CarteJoaillerie*> cartesDansPioche;
    std::vector<CarteJoaillerie*> cartesDehors;
    Pioche* pioche1 = new Pioche(1, 5, 30);
    Pioche* pioche2 = new Pioche(2, 4, 24);
    Pioche* pioche3 = new Pioche(3, 3, 13);

    std::cout<<"            2\n";
    std::vector<Pioche*> pioches (0);
    pioches.push_back(pioche1);
    pioches.push_back(pioche2);
    pioches.push_back(pioche3);


    std::cout<<"            3\n";

    joueur1.setIsIA(false);
    joueur1.setNombreCouronnes(100);
    joueur1.setPointsPrestigeTotal(200);
    joueur1.setPointsPrestigeCouleurs(0,10);
    joueur1.setPointsPrestigeCouleurs(1,10);
    joueur1.setPointsPrestigeCouleurs(2,10);
    joueur1.setPointsPrestigeCouleurs(3,10);
    joueur1.setPointsPrestigeCouleurs(4,10);
    joueur1.setPointsPrestigeCouleurs(5,10);
    joueur1.setGemmesBonus(0,20);
    joueur1.setGemmesBonus(1,20);
    joueur1.setGemmesBonus(2,20);
    joueur1.setGemmesBonus(3,20);
    joueur1.setGemmesBonus(4,20);
    joueur1.setGemmesBonus(5,20);
    joueur1.setNbJeton(0, 100);
    joueur1.setNbJeton(1, 100);
    joueur1.setNbJeton(2, 100);
    joueur1.setNbJeton(3, 100);
    joueur1.setNbJeton(4, 100);
    joueur1.setNbJeton(5, 100);
    joueur1.setNbJeton(6, 100);
    joueur1.setAdversaire(&joueur2);
    joueur1.resetRejouer();
    joueur1.setDifficulte(aleatoire);


    joueur2.setIsIA(false);
    joueur2.setNombreCouronnes(100);
    joueur2.setPointsPrestigeTotal(200);
    joueur2.setPointsPrestigeCouleurs(0,10);
    joueur2.setPointsPrestigeCouleurs(1,10);
    joueur2.setPointsPrestigeCouleurs(2,10);
    joueur2.setPointsPrestigeCouleurs(3,10);
    joueur2.setPointsPrestigeCouleurs(4,10);
    joueur2.setPointsPrestigeCouleurs(5,10);
    joueur2.setGemmesBonus(0,20);
    joueur2.setGemmesBonus(1,20);
    joueur2.setGemmesBonus(2,20);
    joueur2.setGemmesBonus(3,20);
    joueur2.setGemmesBonus(4,20);
    joueur2.setGemmesBonus(5,20);
    joueur2.setNbJeton(0, 100);
    joueur2.setNbJeton(1, 100);
    joueur2.setNbJeton(2, 100);
    joueur2.setNbJeton(3, 100);
    joueur2.setNbJeton(4, 100);
    joueur2.setNbJeton(5, 100);
    joueur2.setNbJeton(6, 100);
    joueur2.setAdversaire(&joueur2);
    joueur2.resetRejouer();
    joueur2.setDifficulte(aleatoire);

    std::cout<<"            4\n";

    for (const auto& carte :* cartesJoaillerie) {
        if (carte != nullptr) {
            cartesDansPioche.push_back(const_cast<CarteJoaillerie *&&>(carte));
        }
    }
    for (int i = 0; i < pioche1->getMaxCartesPioche(); ++i) {
        if (i < cartesJoaillerie->size()) {
            pioche1->setCartesDansPioche((*cartesJoaillerie)[i], i);
        }
    }
    for (int i = 0; i < pioche2->getMaxCartesPioche(); ++i) {
        if (i < cartesJoaillerie->size()) {
            pioche2->setCartesDansPioche((*cartesJoaillerie)[i], i);
        }
    }
    for (int i = 0; i < pioche3->getMaxCartesPioche(); ++i) {
        if (i < cartesJoaillerie->size()) {
            pioche3->setCartesDansPioche((*cartesJoaillerie)[i], i);
        }
    }

    std::cout<<"            5\n";
    //plateau_jeu.setNbCarteNoble(10);
    //plateau_jeu.setPointeurCaseLibre(10000);

    Jeu& jeu = Jeu::getJeu();
    jeu.setJoueurActuel(&joueur1);

    //QApplication app(argc, argv);
    //VuePlateau vueplateau;

    Plateau* plateau_jeu =new Plateau();//= vueplateau.getPlateau();


    //vueplateau.show();


//    jeu.setJoueurGagnant(&joueur2);

    sauvegarderPartie(db, jeu, joueur1, joueur2, pioches, *plateau_jeu); // succès

    // ----------------------------- Gestion BDD ---------------------------
    /*
    // Si on clique sur le bouton continuer, il faut appeler :
    continuerLaPartie(db, reinterpret_cast<std::vector<CarteJoaillerie> &>(cartesJoaillerie),
                      reinterpret_cast<std::vector<CarteNoble *> &>(cartesNoble),
                      //cartesDansPioche, cartesDehors,
                      jeu, joueur1, joueur2, pioches,
                      plateau_jeu, privileges);

    std::cout << joueur1.getNombreCouronnes() << std::endl;

    // Si on clique sur le bouton Nouvelle partie, il faut appeler :
    clearAndInitializeTables(db); // succès

    // Close the database connection
    sqlite3_close(db);
    */

    //return app.exec();
}

/*
void menu(Jeu& j) {
    int choix;
    std::cout << "##### MENU #####\n";
    do {
        std::cout << "Nouvelle partie (1)\nReprendre partie (2)\nChoix = ";
        std::cin >> choix;
        std::cout << "\n";
        if (choix != 1 and choix != 2) std::cout << "Choix incorrect !\n";
    } while (choix != 1 and choix != 2);
    system("cls");
    switch (choix) {
        case 1: j.nouvellePartie();
        case 2: j.reprendrePartie();
        default: std::cout << "Probleme au niveau du menu !\n";
    }
}
 */