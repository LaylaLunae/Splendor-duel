//
// Created by alexa on 24/10/2023......
//
#include <random>
#include <string>
#include <iostream>
#include <cmath>

#include "../include/jeu.h"
//#include "./../include/plateau.h"
//#include "./../include/jeton.h"
//#include "./../include/carte.h"
//#include "./../include/carteNoble.h"


std::tuple<int, int> choisir_jeton() {
    std::cout<<"\n\nVous pouvez choisir un jeton. Les positions vont de (1,1) a (5,5) : ";
    std::string sx, sy;
    std::cout<<"\n    Position X : ";
    std::cin >> sx;
    std::cout<<"\n    Position Y : ";
    std::cin >> sy;
    int x = std::stoi(sx);
    int y = std::stoi(sy);
    return std::make_tuple(x, y);
}


void testes_pour_plateau() {
    /**
     * Fonction pour tester le plateau.
     * On peut choisir des jetons sur le plateau.
     * Et ensuite la première carte noble est prise automatiquement.
     * Puis on remet ces jetons dans le sac, et on reremplit le plateau.
     * On verra que les jetons pris apparaissent sur le tableau avec un
     *      autre ordre! (distribution aléatoire)
     */
    Plateau* p = new Plateau();
    std::cout<<p->etatPlateau();

    int x, y;
    int valider_selection = 0;
    try {
        while (valider_selection != 1) {
            std::tie(x, y) = choisir_jeton();
            p->selectionJeton(x, y);

            std::cout<<"\n\nVoulez vous valider la selection ? 1:oui ; 0:non";
            std::string reponse;
            std::cin >> reponse;
            valider_selection = std::stoi(reponse);
        }

        std::vector<const Jeton*> reponse = p->validerSelectionEtPrendreJetons();

        std::cout<<"\nVous avez en main les jetons de valeurs : ";
        for (const Jeton* j : reponse) {
            std::cout<<j->getCouleurString()<<",";
        }

        const CarteNoble* c = p->prendreCarteNoble(0);
        std::cout<<"\nLa carte noble 0 a ete prise. Son nombre de couronnes : "<<c->getCouronne();

        std::cout<<p->etatPlateau();

        std::cout<<"\nRemise dans le sac des jetons...";
        for (const Jeton* j : reponse) {
            p->ajouterSac(j);
        }
        std::cout<<" ...fini.";

        std::cout<<p->etatPlateau();

        std::cout<<"\nRemplissage du plateau...";
        p->remplissagePlateau();
        std::cout<<" ...fini.";

        std::cout<<p->etatPlateau();

    }
    catch (PlateauException exc) {std::cout<<exc.get_info();}
}


Plateau::Plateau():jetons(nullptr),sac(nullptr),privileges(nullptr),
cartes_nobles(nullptr),nb_jetons_plateau(0),
nb_jetons_sac(0), selection_courante(nullptr),
selection_courante_positions(nullptr),
nombre_jetons_dans_selection(0){

    jetons = new const Jeton*[nb_jetons_plateau_MAX];
    sac = new const Jeton*[nb_jetons_sac_MAX];


    for (unsigned int i = 0; i < 25 ; i++) {
        jetons[i] = nullptr;
        sac[i] = nullptr;
        JetonType jt;
        Couleur couleur;
        if (i < 3) {
            jt = JetonType::Or; couleur=Couleur::rien;
        } else if (i < 5) {
            jt = JetonType::Gemme; couleur=Couleur::rose;
        } else if (i < 9) {
            jt = JetonType::Gemme; couleur=Couleur::bleu;
        } else if (i < 13) {
            jt = JetonType::Gemme; couleur=Couleur::vert;
        } else if (i < 17) {
            jt = JetonType::Gemme; couleur=Couleur::rouge;
        } else if (i < 21) {
            jt = JetonType::Gemme; couleur=Couleur::blanc;
        } else if (i < 25) {
            jt = JetonType::Gemme; couleur=Couleur::noir;
        }

        ajouterSac(new const Jeton(jt, couleur, i%5+1, i/5+1));
    }
    nb_jetons_sac = nb_jetons_sac_MAX;

    privileges = new const Privilege*[nb_privileges_MAX];
    for (unsigned int j = 0; j<3; j++)
        privileges = new const Privilege*;
    nb_privileges = nb_privileges_MAX;

    cartes_nobles = new const CarteNoble*[4];
    std::map<Couleur, int> c;
    c.insert(std::make_pair(Couleur::rouge, 3));
     cartes_nobles[0] = new CarteNoble(
             this, nullptr, "",
             0, 3, 0,
             Pouvoir::pierre_en_plus, Pouvoir::nouveau_tour,0);
    cartes_nobles[1] = new CarteNoble(
            this, nullptr, "",
            0, 3, 0,
            Pouvoir::pierre_en_plus, Pouvoir::nouveau_tour,0);
    cartes_nobles[2] = new CarteNoble(
            this, nullptr, "",
            0, 3, 0,
            Pouvoir::pierre_en_plus, Pouvoir::nouveau_tour,0);
    cartes_nobles[3] = new CarteNoble(
            this, nullptr, "",
            0, 3, 0,
            Pouvoir::pierre_en_plus, Pouvoir::nouveau_tour,0);


    // Le plateau est vide => la première case où mettre le prochain jeton est la 0
    pointeur_case_libre = 0;

    nombre_jetons_dans_selection = 0;
    selection_courante_positions = new int[nombre_jetons_dans_selection_MAX*2];
    selection_courante = new const Jeton*[nombre_jetons_dans_selection_MAX];

    remplissagePlateau();
}


std::string Plateau::etatPlateau() {
    /**
     * Méthode pour afficher l'état du plateau :
     * stats
     * jetons dans sac
     * jetons dans plateau
     * cartes nobles
     */
    std::string sortie = "\nEtat du plateau :";
    sortie.append("\n     Nombre de jeton sur la plateau :");
    sortie.append(std::to_string(nb_jetons_plateau));
    sortie.append("\n     Nombre de jeton dans le sac :");
    sortie.append(std::to_string(nb_jetons_sac));
    sortie.append("\n     Nombre de privilege sur le plateau :");
    sortie.append(std::to_string(nb_privileges));
    sortie.append("\n     Nombre de cartes nobles sur le plateau :");
    sortie.append(std::to_string(nb_carte_noble));
    sortie.append("\n");

    sortie.append("\n\n     Sac :");
    for (unsigned  int j = 0; j <nb_jetons_sac_MAX;j++) {
        if (j%5==0) sortie.append("\n          ");
        if (sac[j] == nullptr) {
            sortie.append("null");
        } else {
            sortie.append(sac[j]->getCouleurString());
        }
        sortie.append("  ");
    }

    sortie.append("\n\n     Plateau dans memoire:");
    for (unsigned int j = 0; j <nb_jetons_plateau_MAX;j++) {
        if (j%5==0) sortie.append("\n          ");
        if (jetons[j] == nullptr) {
            sortie.append("null");
        } else {
            sortie.append(jetons[j]->getCouleurString());
        }
        sortie.append("  ");
    }
    sortie.append("\n\n     Plateau affichage respecte:");
    unsigned int index;
    for (unsigned int j = 0; j <nb_jetons_plateau_MAX;j++) {
        index = matrix[j/5][j%5]-1;
        if (j%5==0) sortie.append("\n          ");
        if (jetons[index] == nullptr) {
            sortie.append("null");
        } else {
            sortie.append(jetons[index]->getCouleurString());
        }
        sortie.append("  ");
    }

    sortie.append("\n\n     Cartes nobles : ");
    for (unsigned int i = 0; i < 4; i++) {
        if (cartes_nobles[i] == nullptr) {
            sortie.append("null,");
        } else {
            sortie.append(std::to_string(cartes_nobles[i]->getCouronne()));
            sortie.append(", ");
        }
    }

    sortie.append("\n\nFin affichage plateau.\n ");

    return sortie;
}


void Plateau::remplissagePlateau(bool avecAffichage) {

    // Initialisation de la première case libre du plateau = là où le premier jeton sera distribué.
    // Cette case n'est pas forcément la première : un joueur peut décider de remplir le plateau même s'il
    // reste des jetons sur le plateau.
    pointeur_case_libre = 0;
    while (pointeur_case_libre < nb_jetons_plateau_MAX && jetons[pointeur_case_libre] != nullptr) {
        pointeur_case_libre++;
    }
    if (pointeur_case_libre == nb_jetons_plateau_MAX)
        // throwPlateauException("Tous les jetons sont déjà sur le plateau ! ¯\\_(^^')_/¯");
        std::cout<<"Tous les jetons sont deja sur le plateau !  \"\\_(^^')_/\"\n";


    // Tant qu'il reste des jetons dans le sac : on pioche et on dépose sur le plateau
    unsigned int i = 0;
    while (nb_jetons_sac > 0) {
        if (avecAffichage) std::cout<<"\n\n"<<i<<" : "<<nb_jetons_sac<<": ";

        unsigned int r = rand() % ( nb_jetons_sac );
        if (avecAffichage) std::cout<<"\nNombre aleatoire : "<<r<<"\n";

        // On prend un jeton dans le sac
        const Jeton* jeton_aleatoire = sac[r];

        // On le retire du sac = on décale la partie droite du tableau d'un cran vers la gauche
        for (unsigned  int j = r; j <nb_jetons_sac_MAX;j++) {
            sac[j] = sac[j+1];
        }
        sac[nb_jetons_sac_MAX-1] = nullptr;
        nb_jetons_sac--;

        // Pour debug console
        if (avecAffichage) {
            for (unsigned int j = 0; j < nb_jetons_sac_MAX; j++) {
                std::cout << "\n" << j << ": ";
                if (sac[j] == nullptr) {
                    std::cout << "NULL";
                } else {
                    std::cout << sac[j]->getCouleurString();
                }
            }
        }

        // On l'ajoute au plateau.
        jetons[pointeur_case_libre++] = jeton_aleatoire;
        nb_jetons_plateau++;
        if (avecAffichage) std::cout<<"\nProchaine case d'ecriture : "<<pointeur_case_libre;
        //Attention, peut-être qu'il reste des jetons sur le plateau au moment du remplissage, et donc que la case
        // d'après contenait déjà un jeton. On augmente le pointeur jusqu'à une case vide.
        while (pointeur_case_libre < nb_jetons_plateau_MAX && jetons[pointeur_case_libre] != nullptr) {
            pointeur_case_libre++;
        }

        i++;
    }

    //for (unsigned int index = 0; index < 5; i++) {
     //   for (unsigned int index_j = 0; index_j < 5; index_j++) {
            //jetons[index][index_j]
     //   }
    //}
}


void Plateau::ajouterSac(const Jeton *j) {
    sac[nb_jetons_sac++] = j;
}


bool Plateau::verificationSelectionPositions() const{
    /**
     * Retourne vraie si la sélection est valide, faux sinon.
     *
     * Vérification que les jetons soit en ligne V/H ou diagonale G/D :
     * 1.Prendre le plus en haut à gauche
     * 2.Partir de ce jeton et ajouter 1 aux coordonnées pour tester tous les cas possibles
     */

    // Récupération du jeton le plus en haut à gauche
    // Ou de celui le plus en bas à gauche (pour diagonale de bas gauche à haut droit)
    if (nombre_jetons_dans_selection == 0) return true;

    bool affichage = false;

    if (affichage) std::cout<<"\nVERIFICATION position...";

    unsigned int n = (nombre_jetons_dans_selection+1)*2;

    int _x = selection_courante_positions[0];
    int _y = selection_courante_positions[1];
    for (unsigned int i = 2 ; i < n; i+=2) {
        int x = selection_courante_positions[i];
        int y = selection_courante_positions[i+1];

        if ((y <= _y && x <= _x) || (y == _y+1 && x == _x-1)) {
            _y = y; _x = x;
            if (affichage) std::cout<<"\n    Nouveau min en position : "<<_x<<" "<<_y;
        }
    }

    // Tous les tests possible
    bool au_moins_un_jeton_a_cette_position = false;

    bool ligneH = true;
    // ligne droite horizontale
    int index_x = _x;
    for (unsigned int i = 0 ; i < n; i+=2) {
        au_moins_un_jeton_a_cette_position = false;
        for (unsigned int j = 0; j < n; j+=2) {
            if (affichage) std::cout<<"\n     "<<i<<","<<j<<"   on veut les points :"<<index_x<<","<<_y;
            int x = selection_courante_positions[j];
            int y = selection_courante_positions[j+1];
            if (x == index_x && y == _y) {
                if (affichage) std::cout<<"\n               "<<i<<","<<j<<" on a trouve:"<<x<<","<<y;
                au_moins_un_jeton_a_cette_position = true;
                break;
            }
        }

        if (!au_moins_un_jeton_a_cette_position) { ligneH = false; break;}
        index_x++;
    }


    // ligne droite verticale
    bool ligneV = true;
    int index_y = _y;
    for (unsigned int i = 0 ; i < n; i+=2) {
        au_moins_un_jeton_a_cette_position = false;
        for (unsigned int j = 0; j < n; j+=2) {
            if (affichage) std::cout<<"\n     "<<i<<","<<j<<"   on veut les points :"<<_x<<","<<index_y;
            int x = selection_courante_positions[j];
            int y = selection_courante_positions[j+1];
            if (x == _x && y == index_y) {
                if (affichage) std::cout<<"\n               "<<i<<","<<j<<" on a trouve:"<<x<<","<<y;
                au_moins_un_jeton_a_cette_position = true;
                break;
            }
        }

        if (!au_moins_un_jeton_a_cette_position) { ligneV = false; break;}
        index_y++;
    }

    // diagonale haut gauche - bas droite
    bool diagHg = true;
    index_y = _y;
    index_x = _x;
    for (unsigned int i = 0 ; i < n; i+=2) {
        au_moins_un_jeton_a_cette_position = false;
        for (unsigned int j = 0; j < n; j+=2) {
            if (affichage) std::cout<<"\n     "<<i<<","<<j<<"   on veut les points :"<<index_x<<","<<index_y;
            int x = selection_courante_positions[j];
            int y = selection_courante_positions[j+1];
            if (x == index_x && y == index_y) {
                if (affichage) std::cout<<"\n               "<<i<<","<<j<<" on a trouve:"<<x<<","<<y;
                au_moins_un_jeton_a_cette_position = true;
                break;
            }
        }

        if (!au_moins_un_jeton_a_cette_position) { diagHg = false; break;}
        index_y++;
        index_x++;
    }

    // diagonale bas gauche - haut droite
    bool diagBg = true;
    index_y = _y;
    index_x = _x;
    for (unsigned int i = 0 ; i < n; i+=2) {
        au_moins_un_jeton_a_cette_position = false;
        for (unsigned int j = 0; j < n; j+=2) {
            if (affichage) std::cout<<"\n     "<<i<<","<<j<<"   on veut les points :"<<index_x<<","<<index_y;
            int x = selection_courante_positions[j];
            int y = selection_courante_positions[j+1];
            if (x == index_x && y == index_y) {
                if (affichage) std::cout<<"\n               "<<i<<","<<j<<" on a trouve:"<<x<<","<<y;
                au_moins_un_jeton_a_cette_position = true;
                break;
            }
        }

        if (!au_moins_un_jeton_a_cette_position) { diagBg = false; break;}
        index_y--;
        index_x++;
    }

    if (affichage) std::cout<<"\n    Validite des positions : "<<ligneH<<" "<<ligneV<<" "<<diagHg<<" "<<diagBg;
    return ligneH || ligneV || diagBg || diagHg;
}


int Plateau::selectionJeton(unsigned int position_x, unsigned int position_y) {

    // L'attribut "jetons" est une liste simple et non un tableau.
    // Il faut donc convertir les coordonnees en index de liste.
    // avant matrix:
    // unsigned int position_dans_plateau = nombre_jetons_par_cote_de_plateau  *  (position_y-1) + position_x-1;
    unsigned  int position_dans_plateau = matrix[position_y][position_x]-1;
    std::cout<<"La position dans le plateau memoire  : "<<position_dans_plateau<<"\n";
    bool a_selectionne_un_jeton_or;

    // Erreur si la case est vide.
    if (jetons[position_dans_plateau] == nullptr) {
        //throw PlateauException("Aucun jeton à cet emplacement");
        std::cout << "Aucun jeton a cet emplacement"<<"\n";
        return 1;
    }

    std::cout<<"\nLe joueur a indique le jeton de valeur : "<<jetons[position_dans_plateau]->getCouleurString()<<"\n";

    // Déselectionner le jeton s'il existe déjà
    bool deselection = false;
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection; i++) {
        if (selection_courante[i] == jetons[position_dans_plateau]) {
            deselection = true;

            // Décalage des JETONS à gauche pour écraser la valeur déselectionnée
            for (unsigned int j = i ; j < nombre_jetons_dans_selection-1; j++) {
                selection_courante[j] = selection_courante[j + 1];
            }
            selection_courante[nombre_jetons_dans_selection-1] = nullptr;

            // Décalage des POSITIONS à gauche pour écraser la valeur déselectionnée
            for (unsigned int j = i*2 ; j < nombre_jetons_dans_selection*2-2; j+=2) {
                selection_courante_positions[j] = selection_courante_positions[j + 2];
                selection_courante_positions[j+1] = selection_courante_positions[j + 3];
            }
            // Pas obligatoire de mettre les positions à zéro car ce n'est pas des pointeurs.
            // Mise à zéro pour respecter l'idée que tout est décalé à gauche.
            selection_courante_positions[nombre_jetons_dans_selection*2-2] = 0;
            selection_courante_positions[nombre_jetons_dans_selection*2-1] = 0;

            nombre_jetons_dans_selection--;
            std::cout<<"\nCe jeton a ete enleve de la selection."<<"\n";
            break;
        }
    }

    // Sinon, on vérifie la légalité de l'opération et si c'est ok on l'ajoute
    if (!deselection) {

        if (nombre_jetons_dans_selection >=3) {
            //throw PlateauException("\nImpossible de choisir plus de jetons!  <('o'<)");
            std::cout << "\nImpossible de choisir plus de jetons!  <('o'<)"<<"\n";
            return 5;
        }

        // Vérification sur l'or: ne peut être un jeton or que si un seul jeton est prix.
        if (nombre_jetons_dans_selection >= 1 &&
            (selection_courante[0]->getCouleurString() == "Or" ||
            jetons[position_dans_plateau]->getCouleurString() == "Or")) {
            //throw PlateauException("\nQue un seul jeton or possible!  <('o'<)");
            std::cout<<"\nQue un seul jeton or possible!  <('o'<)"<<"\n";
            return 3;
        }


        // On ajoute avant la vérification pour la méthode de verification des positions appelée tout de suite après
        selection_courante_positions[nombre_jetons_dans_selection*2] = position_x;
        selection_courante_positions[nombre_jetons_dans_selection*2+1] = position_y;

        if (verificationSelectionPositions()) {
            selection_courante[nombre_jetons_dans_selection++] = jetons[position_dans_plateau];
            a_selectionne_un_jeton_or = jetons[position_dans_plateau]->getCouleurString() == "Or";
            std::cout<<"\nCe jeton a ete ajoute a la selection.";
        } else {
            selection_courante_positions[nombre_jetons_dans_selection*2] = 0;
            selection_courante_positions[nombre_jetons_dans_selection*2+1] = 0;
            //throw PlateauException("\n\nVous ne pouvez pas prendre ce jeton, tricheur! \\('O')/ ");
            std::cout<<"\n\nVous ne pouvez pas prendre ce jeton, tricheur! Mauvaise position ! \\('O')/ "<<"\n";
            return 4;
        }
    }

    std::cout<<"\n\nSelection courante : ";
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection; i++) {
        if (selection_courante[i] == nullptr) {
            std::cout<<"null - ";
        } else {
            std::cout<<selection_courante[i]->getCouleurString()<<" - ";
        }
    }
    std::cout<<"\n";

    /* DEBUG : affichage des positions.
    std::cout<<"\nPositions courantes associees : ";
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection*2; i+=2) {
        std::cout<<selection_courante_positions[i]<<",";
        std::cout<<selection_courante_positions[i+1]<<" - ";
    }
    */

    if (a_selectionne_un_jeton_or)
        return 2;

    if (deselection)
        return 6;

    return 0;
}


std::vector<const Jeton*> Plateau::validerSelectionEtPrendreJetons() {
    if (nombre_jetons_dans_selection == 0) {
        //throw PlateauException("Aucun jeton dans la selection <('o'<)");
        std::cout<<"Aucun jeton dans la selection <('o'<)"<<"\n";
    }

    // Création du vecteur à retourner:
    std::vector<const Jeton*> reponse = std::vector<const Jeton*>(
            0, nullptr
            );

    // Ajoute les jetons à la liste à retourner :
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection; i++) {
        reponse.push_back(selection_courante[i]);
    }


    // Supprime les jetons du plateau :
    unsigned int position_dans_plateau;
    unsigned int position_x;
    unsigned int position_y;
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection*2; i+=2) {

        position_x = selection_courante_positions[i];
        position_y = selection_courante_positions[i+1];

        position_dans_plateau = matrix[position_y][position_x]-1;//nombre_jetons_par_cote_de_plateau  *  (position_y) + position_x;
        jetons[position_dans_plateau] = nullptr;
        nb_jetons_plateau--;
    }

    // Remise à zéro des attributs
    for (size_t i = 0; i < nombre_jetons_dans_selection_MAX; i++){
        selection_courante[i] = nullptr;
        selection_courante_positions[2*i] = 0;
        selection_courante_positions[2*i+1] = 0;

    }
    //delete[] selection_courante_positions;
    //delete[] selection_courante;
    nombre_jetons_dans_selection = 0;
    //selection_courante_positions = new int[nombre_jetons_dans_selection_MAX*2];
    //selection_courante = new const Jeton*[nombre_jetons_dans_selection_MAX];

    // Envoi du résultat
    return reponse;
}


const Privilege* Plateau::prendrePrivilege() {
    /*
     * Enlève un privilège de la liste et le retourne.
     * S'il n'y a plus de privilège, lève une exception.
     */

    if (nb_privileges == 0)
        //throw PlateauException("Il n'y a plus de Privilege sur le plateau... ¯\\_(^^')_/¯");
        std::cout<<"Il n'y a plus de Privilege sur le plateau... ¯\\_(^^')_/¯"<<"\n";
    const Privilege* resultat = privileges[nb_privileges-1];

    privileges[nb_privileges-1] = nullptr;
    nb_privileges--;

    return resultat;
}


void Plateau::donnePrivilege(const Privilege* p) {
    /*
     * Redonner un privilège au plateau
     */

    if (nb_privileges == nb_privileges_MAX)
        //throw PlateauException("Il y a déjà assez de privilège sur le plateau... ¯\\_(^^')_/¯");
        std::cout<<"Il y a déjà assez de privilège sur le plateau... ¯\\_(^^')_/¯"<<"\n";

    privileges[nb_privileges++] = p;
}


const CarteNoble* Plateau::prendreCarteNoble(unsigned int numero) {
    if (cartes_nobles[numero] == nullptr)
        //throw PlateauException("Cette carte n'est plus sur le plateau... ¯\\_(^^')_/¯");
        std::cout<<"Cette carte n'est plus sur le plateau... ¯\\_(^^')_/¯"<<"\n";

    const CarteNoble* resultat = cartes_nobles[numero];
    cartes_nobles[numero] = nullptr;
    nb_carte_noble--;
    return  resultat;
}

bool Plateau::hasJeton() {
    if (this->nb_jetons_plateau > 0)
        return true;
    return false;
}

Plateau::~Plateau() {
    for (size_t i = 0; i < nb_jetons_plateau; i++) {
        delete jetons[i];
    }
    delete[] jetons;

    for(size_t i = 0; i < nb_privileges; i ++) {
        delete privileges[i];
    }
    delete[] privileges;

    delete[] cartes_nobles;

    for (size_t i = 0; i < nb_jetons_sac; i ++) {
        delete sac[i];
    }
    delete[] sac;

    for (size_t i = 0; i < nombre_jetons_dans_selection; i ++) {
        delete selection_courante[i];
    }
    delete[] selection_courante_positions;
    delete[] selection_courante;
}

const Jeton* Plateau::prendreJeton(unsigned int position_x, unsigned int position_y) {
    if (nb_jetons_plateau == 0) {
       //throw PlateauException("Aucun jeton dans la selection <('o'<)");
       std::cout<<"Aucun jeton dans la selection <('o'<)"<<"\n";
    }
    unsigned int position_dans_plateau = nombre_jetons_par_cote_de_plateau  *  (position_y-1) + position_x-1;


    if (jetons[position_dans_plateau] == nullptr) {
            //throw PlateauException("Aucun jeton ici... <(-_-)>");
            std::cout<<"Aucun jeton ici... <(-_-)>"<<"\n";
    }

    // Tester ici que ce ne soit pas un or
    //if (position_dans_plateau == -1) {
    //    throw PlateauException("Impossible de prendre un or <('o'<)")
    //}

    const Jeton* resultat = jetons[position_dans_plateau];

    jetons[position_dans_plateau] = nullptr;
    nb_jetons_plateau--;

    return resultat;
}

bool Plateau::hasJetonOr() {
    for (int i=0; i<nb_jetons_plateau_MAX; i++) {
        if (jetons[i]->getType() == JetonType::Or) return true;
    }
    return false;
}

std::vector<unsigned int> Plateau::parcoursPlateauVerificationPosition(unsigned int x, unsigned int y, signed int coefX, signed int coefY ) {
    signed int posX = x;
    signed int posY = y;
    std::vector<unsigned int> resultat = std::vector<unsigned int> (0 );
    for (unsigned int nb_j = 0 ; nb_j < 3; nb_j ++) {
        if (posX >= 5 || posY >= 5 || posX<0 || posY<0) break;

        if (jetons[5*posX+posY] != nullptr  &&
            jetons[5*posX+posY]->getType() != JetonType::Or)
        {
            resultat.push_back(posX);
            resultat.push_back(posY);
        } else {
            break;
        }
        posX = posX + 1*coefX;
        posY = posY + 1*coefY;
    }
    return resultat;
}

std::vector<std::vector<unsigned int>>  Plateau::donnePositionsPossiblesAPartirDe(unsigned int x, unsigned int y) {

    /*
     * Donne les positions de :
     * 1. Ligne
     * 2. Colonne
     * 3. Diagonale
     * 4. Diagonale en partant du bas
     *
     Dans ces positions, il n'y a aucun jeton or.

      Les entiers sont à la suite et doivent être lus deux par deux (x,y):
      0, 0, 1, 1, 1, 2
      Correspond à (0, 0) puis (1,1) puis (1, 2) .

     * ------------ Exemple de code  et explications ---------------- *
     En lançant ce code depuis le main, on obtiens un affichage console.
     L'affichage décompose les vecteurs :
     - une ligne représente un vector<unsigned int>
     - chaque élément d'une ligne représente un int du même vector<u i>

     Le vector principal ( vect<vect<u i>> ) contiendra 4 éléments :
     1. vector<u i> de la ligne
     2. v<ui> de la colonne
     3. v<ui> de la diagonale départ hautgauche -> basdroite
     4. v<ui> de la diagonale départ basgauche -> hautdroite

     Puisqu'il contient 4 éléments, il y aura 4 lignes dans la console.

     Attention, si le jeton de départ est un Or, le vecteur retourné sera vide.

     Code à mettre dans le main :

     Plateau* p= new Plateau;
     std::cout<<p->etatPlateau(); // il faut regarder l'affichage "Plateau affichage respecte" dans la console
     std::vector<std::vector<unsigned int>> v = p->donnePositionsPossiblesAPartirDe(0, 1);
     for (auto v_ :v) {
         for (auto i : v_) {
             std::cout<<i<<" ";
         }
         std::cout<<"\n";
    }

     * ----------------- Fin explications et code ----------------- *
     */

    std::vector<std::vector<unsigned int>> resultat =std::vector<std::vector<unsigned int>>(0) ;
    resultat.push_back(parcoursPlateauVerificationPosition(x, y, 1, 0));
    resultat.push_back(parcoursPlateauVerificationPosition(x, y, 0, 1));
    resultat.push_back(parcoursPlateauVerificationPosition(x, y, 1, 1));
    resultat.push_back(parcoursPlateauVerificationPosition(x, y, 1, -1));


    return resultat;

}


// ----------------- Vue Plateau : --------------

void VuePlateau::jetonClick_Plateau(VueJeton* vj) {
    std::cout<<"Le jeton clicke a la position : "<<vj->getX()<<","<< vj->getY()<<"\n";
    int res = plateau->selectionJeton(
            vj->getX(),
            vj->getY()
            );
    if (res == 0 || res == 2) {
        vj->setSelected(true);
    } else {
        vj->setSelected(false);
    }
}

VuePlateau::VuePlateau(QWidget *parent) : QWidget(parent), vuesJetons(25, nullptr)
{
    plateau = new Plateau();
    //std::cout<<plateau->etatPlateau();

    main_layout = new QVBoxLayout(this);
    layout_info = new QHBoxLayout();
    layout_bouton = new QGridLayout();

    affichageJetons();

    boutonValider = new QPushButton("Valider", this);
    // Set the background color to light green
    QString styleSheet = "background-color: lightgreen; color: black;";
    boutonValider->setStyleSheet(styleSheet);
    QObject::connect(
            boutonValider,
            &QPushButton::clicked,
            this,
            &VuePlateau::validerPlateau
    );

    boutonValider->show();
    layout_info->addWidget(boutonValider);

    boutonRemplissage = new QPushButton("Remplir", this);
    // Set the background color to light green
    QString styleSheetRemplissage = "background-color: lightblue; color: black;";
    boutonRemplissage->setStyleSheet(styleSheetRemplissage);
    QObject::connect(
            boutonRemplissage,
            &QPushButton::clicked,
            this,
            &VuePlateau::remplirPlateau
    );

    boutonRemplissage->show();
    layout_info->addWidget(boutonRemplissage);

    main_layout->addLayout(layout_bouton);
    main_layout->addLayout(layout_info);
    setLayout(main_layout);
}

void VuePlateau::validerPlateau() {
    std::vector<const Jeton*> main = plateau->validerSelectionEtPrendreJetons();
    for (auto j : main) {
        plateau->ajouterSac(j);
    }
    affichageJetons();
}

void VuePlateau::remplirPlateau() {
    plateau->remplissagePlateau();
    affichageJetons();
}

void VuePlateau::affichageJetons() {
    while (QLayoutItem *item = layout_bouton->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    vuesJetons.clear();

    unsigned int index;
    for(unsigned int i=0; i < 5;i++) {
        for (unsigned int j = 0;j < 5;j++) {
            index = plateau->matrix[i][j]-1;
            if (plateau->jetons[index] != nullptr) {
                vuesJetons[5 * i + j] = new VueJeton(
                        plateau->jetons[index],
                        j, i,
                        this
                );

                layout_bouton->addWidget(vuesJetons[5 * i + j], i, j);
                connect(
                        vuesJetons[5 * i + j],
                        SIGNAL(jetonClick(VueJeton * )),
                        this,
                        SLOT(jetonClick_Plateau(VueJeton * ))
                );
            } // Fin if
        }
    } // Fin boucle for

    repaint();
}

void VuePlateau::miseAJourJetons() {
    for (unsigned int i = 0; i < 5; i ++) {
        for (unsigned int j = 0; j < 5; j++) {
            vuesJetons[5*i+j] ->setJeton(plateau->jetons[plateau->matrix[i][j]-1]);
        }
    }
}