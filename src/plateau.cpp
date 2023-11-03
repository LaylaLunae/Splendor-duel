//
// Created by alexa on 24/10/2023.
//
#include <random>
#include <string>
#include <iostream>
#include <cmath>

#include "./../include/plateau.h"


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
     * On peut choisir deux jetons sur le plateau.
     * Et ensuite la première carte noble est prise automatiquement.
     */
    Plateau* p = new Plateau();
    std::cout<<p->etatPlateau();

    int x, y;
    std::tie (x, y) = choisir_jeton();
    try {
        p->selectionJeton(x, y);

        std::tie (x, y) = choisir_jeton();
        p->selectionJeton(x, y);

        const CarteNoble* c = p->prendreCarteNoble(0);
        std::cout<<"La carte noble 0 a ete prise. Son nombre de couronnes : "<<c->getCouronne();
    }
    catch (PlateauException exc) {std::cout<<exc.get_info();}
}


Plateau::Plateau():jetons(nullptr),sac(nullptr),privileges(nullptr),cartes_nobles(nullptr),nb_jetons_plateau(0),
                   selection_courante(nullptr), selection_courante_positions(nullptr) {
    jetons = new const Jeton*[nb_jetons_plateau_MAX];
    sac = new const Jeton*[nb_jetons_sac_MAX];
    for (unsigned int i = 0; i < 25 ; i++) {
        jetons[i] = nullptr;
        sac[i] = nullptr;
        ajouterSac(new const Jeton(i));
    }
    nb_jetons_sac = nb_jetons_sac_MAX;

    privileges = new const Privilege*[nb_privileges_MAX];
    for (unsigned int j = 0; j<3; j++)
        privileges = new const Privilege*;
    nb_privileges = nb_privileges_MAX;

    cartes_nobles = new const CarteNoble*[4];
    std::map<Couleur, int> c;
    c.insert(std::make_pair(Couleur::rouge, 3));
    cartes_nobles[0] = new CarteNoble(1, c);
    cartes_nobles[1] = new CarteNoble(1, c);
    cartes_nobles[2] = new CarteNoble(1, c);
    cartes_nobles[3] = new CarteNoble(1, c);
    //for (unsigned int i = 0; i < 4; i++)
    //    cartes_nobles = new const CarteNoble*;

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
            sortie.append(std::to_string(sac[j]->geta()));
        }
        sortie.append("  ");
    }

    sortie.append("\n\n     Plateau :");
    for (unsigned int j = 0; j <nb_jetons_plateau_MAX;j++) {
        if (j%5==0) sortie.append("\n          ");
        if (jetons[j] == nullptr) {
            sortie.append("null");
        } else {
            sortie.append(std::to_string(jetons[j]->geta()));
        }
        sortie.append("  ");
    }

    sortie.append("\n     Cartes nobles : ");
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

        if (avecAffichage) {
            for (unsigned int j = 0; j < nb_jetons_sac_MAX; j++) {
                std::cout << "\n" << j << ": ";
                if (sac[j] == nullptr) {
                    std::cout << "NULL";
                } else {
                    std::cout << sac[j]->geta();
                }

            }
        }

        nb_jetons_sac--;

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
}


void Plateau::ajouterSac(const Jeton *j) {
    sac[nb_jetons_sac++] = j;
}


bool Plateau::verificationSelectionPositions() {
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

        if ((y < _y && x < _x) || (y == _y+1 && x == _x-1)) {
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


void Plateau::selectionJeton(unsigned int position_x, unsigned int position_y) {

    // L'attribut "jetons" est une liste simple et non un tableau.
    // Il faut donc convertir les coordonnees en index de liste.
    unsigned int position_dans_plateau = nombre_jetons_par_cote_de_plateau  *  (position_y-1) + position_x-1;

    // Erreur si la case est vide.
    if (jetons[position_dans_plateau] == nullptr)
        throw PlateauException("Aucun jeton à cet emplacement");

    std::cout<<"\nLe joueur a indique le jeton de valeur : "<<jetons[position_dans_plateau]->geta();

    // Déselectionner le jeton s'il existe déjà
    bool deselection = false;
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection; i++) {
        if (selection_courante[i] == jetons[position_dans_plateau]) {
            deselection = true;

            // Décalage des JETONS à gauche pour écraser la valeur déselectionnée
            for (int j = i ; j < nombre_jetons_dans_selection-1; j++) {
                selection_courante[j] = selection_courante[j + 1];
            }
            selection_courante[nombre_jetons_dans_selection-1] = nullptr;

            // Décalage des POSITIONS à gauche pour écraser la valeur déselectionnée
            for (int j = i*2 ; j < nombre_jetons_dans_selection*2-2; j+=2) {
                selection_courante_positions[j] = selection_courante_positions[j + 2];
                selection_courante_positions[j+1] = selection_courante_positions[j + 3];
            }
            // Pas obligatoire de mettre les positions à zéro car ce n'est pas des pointeurs.
            // Mise à zéro pour respecter l'idée que tout est décalé à gauche.
            selection_courante_positions[nombre_jetons_dans_selection*2-2] = 0;
            selection_courante_positions[nombre_jetons_dans_selection*2-1] = 0;

            nombre_jetons_dans_selection--;
            std::cout<<"\nCe jeton a ete enleve de la selection.";
            break;
        }
    }

    // Sinon, on vérifie la légalité de l'opération et si c'est ok on l'ajoute
    if (!deselection) {

        if (nombre_jetons_dans_selection >=3)
            throw PlateauException("\nImpossible de choisir plus de jetons!  <('o'<)");

        // Vérification sur l'or (valeur 0 ici) : ne peut être un jeton or que si un seul jeton est prix.
        if (nombre_jetons_dans_selection >= 1 && (selection_courante[0]->geta() == 0 || jetons[position_dans_plateau]->geta() == 0))
            throw PlateauException("\nQue un seul jeton or possible!  <('o'<)");



        // On ajoute avant la vérification pour la méthode de verification des positions appelée tout de suite après
        selection_courante_positions[nombre_jetons_dans_selection*2] = position_x;
        selection_courante_positions[nombre_jetons_dans_selection*2+1] = position_y;

        if (verificationSelectionPositions()) {
            selection_courante[nombre_jetons_dans_selection++] = jetons[position_dans_plateau];
            std::cout<<"\nCe jeton a ete ajoute a la selection.";
        } else {
            selection_courante_positions[nombre_jetons_dans_selection*2] = 0;
            selection_courante_positions[nombre_jetons_dans_selection*2+1] = 0;
            throw PlateauException("\n\nVous ne pouvez pas prendre ce jeton, tricheur! \\('O')/ ");
        }
    }

    std::cout<<"\n\nSelection courante : ";
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection; i++) {
        if (selection_courante[i] == nullptr) {
            std::cout<<"null - ";
        } else {
            std::cout<<selection_courante[i]->geta()<<" - ";
        }
    }

    /* DEBUG : affichage des positions.
    std::cout<<"\nPositions courantes associees : ";
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection*2; i+=2) {
        std::cout<<selection_courante_positions[i]<<",";
        std::cout<<selection_courante_positions[i+1]<<" - ";
    }
    */
}


const Jeton** Plateau::validerSelectionEtPrendreJetons() {
    if (nombre_jetons_dans_selection == 0) throw PlateauException("Aucun jeton dans la selection <('o'<)");
    const Jeton** liste = new const Jeton * [nombre_jetons_dans_selection];
    for (unsigned int i = 0 ; i < nombre_jetons_dans_selection; i++) {
        liste[i] = selection_courante[i];
    }
    delete[] selection_courante_positions;
    delete[] selection_courante;
    nombre_jetons_dans_selection = 0;
    selection_courante_positions = new int[nombre_jetons_dans_selection_MAX*2];
    selection_courante = new const Jeton*[nombre_jetons_dans_selection_MAX];
    return liste;
}


const Privilege* Plateau::prendrePrivilege() {
    /*
     * Enlève un privilège de la liste et le retourne.
     * S'il n'y a plus de privilège, lève une exception.
     */

    if (nb_privileges == 0) throw PlateauException("Il n'y a plus de Privilege sur le plateau... ¯\\_(^^')_/¯");

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
        throw PlateauException("Il y a déjà assez de privilège sur le plateau... ¯\\_(^^')_/¯");

    privileges[nb_privileges++] = p;
}


const CarteNoble* Plateau::prendreCarteNoble(unsigned int numero) {
    if (cartes_nobles[numero] == nullptr)
        throw PlateauException("Cette carte n'est plus sur le plateau... ¯\\_(^^')_/¯");

    const CarteNoble* resultat = cartes_nobles[numero];
    cartes_nobles[numero] = nullptr;
    nb_carte_noble--;
    return  resultat;
}


Plateau::~Plateau() {
    delete[] jetons;
    delete[] privileges;
    delete[] cartes_nobles;
    delete[] sac;
    delete[] selection_courante_positions;
    delete[] selection_courante;
}

