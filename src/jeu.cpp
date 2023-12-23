#include <iostream>
#include <string.h>
#include "../include/jeu.h"
#include <QMessageBox>

/* Jeu& Jeu::getJeu(){
    if (handler.instance == nullptr)
        handler.instance = new Jeu();
    return * handler.instance;
}

void Jeu::libereJeu() {
    delete handler.instance;
    handler.instance = nullptr;
}*/

Jeu * Jeu::instance = nullptr;

//création de Jeu ou récupération de Jeu si déjà créé
Jeu& Jeu::getJeu(){
    if (instance == nullptr)
        instance = new Jeu;
    return * instance;
}

//destruction du Jeu
void Jeu::libereJeu() {
    delete instance;
    instance = nullptr;
}

void Jeu::nouvellePartie() {
    Plateau * plateau_jeu = new Plateau();
    std::string sortie = plateau_jeu->etatPlateau();
    std::cout << sortie << "\n";

    // création des pioches
    Pioche * pioche1 = new Pioche(1,5,30);
    Pioche * pioche2 = new Pioche(2,4,24);
    Pioche * pioche3 = new Pioche(3,3,13);

    // à retirer
    //initCarteJoa(pioche1, pioche2, pioche3, plateau_jeu);

    //distribution des pioches
    pioche1->distribution();
    pioche2->distribution();
    pioche3->distribution();

    // création des instances des actions
    Optionnelle * act_opt = new Optionnelle();
    Obligatoire * act_obl = new Obligatoire();

    //Choix des joueurs
    std::cout << "Choix des joueurs :\n" << "0 - Joueur vs joueur\n";
    std::cout << "1 - Joueur vs IA\n" << "2 - IA vs IA\n";
    int choix;
    std::cout << "Choix : ";
    std::cin >> choix;

    switch (choix) {
        case 0: {
            //Joueur vs joueur
            std::cout << "Nom du joueur 1 : ";
            std::string nom1;
            std::cin >> nom1;
            Humain *joueur1 = new Humain(nom1);

            std::cout << "Nom du joueur 2 : ";
            std::string nom2;
            std::cin >> nom2;
            Humain *joueur2 = new Humain(nom2);

            //initialisation des adversaires
            joueur1->setAdversaire(joueur2);
            joueur2->setAdversaire(joueur1);

            //joueur_actuel pour le tour
            joueur_actuel = joueur1;

            //début de la partie
            manche(plateau_jeu, pioche1, pioche2, pioche3, joueur1, joueur2, act_obl, act_opt);
            /*joueur_actuel->nombre_couronnes = 3;
            std::cout << "Nb carte noble : " << joueur_actuel->cartes_noble.size() << "\n";
            verifCarteNoble(joueur_actuel,plateau_jeu);*/

            break;
        }

        case 1: {
            //IA vs Joueur
            std::cout << "Nom du joueur : ";
            std::string nom4;
            std::cin >> nom4;
            Humain *humain = new Humain(nom4);

            std::cout << "Nom de l'IA : ";
            std::string nom3;
            std::cin >> nom3;
            IA *ia = new IA(nom3, facile);

            humain->setAdversaire(ia);
            ia->setAdversaire(humain);

            joueur_actuel = humain;

            manche(plateau_jeu, pioche1, pioche2, pioche3, humain, ia, act_obl, act_opt);

            break;
        }

        case 2: {
            //IA vs IA
            std::cout << "Nom de l'IA 1 : ";
            std::string nom5;
            std::cin >> nom5;
            IA *ia1 = new IA(nom5, facile);

            std::cout << "Nom de l'IA 2 : ";
            std::string nom6;
            std::cin >> nom6;
            IA *ia2 = new IA(nom6, facile);

            ia1->setAdversaire(ia2);
            ia2->setAdversaire(ia1);

            joueur_actuel = ia1;

            manche(plateau_jeu, pioche1, pioche2, pioche3, ia1, ia2, act_obl, act_opt);

            break;
        }

        default:
            std::cout << "Il fait rien\n";
            break;
    }
}

//Partie
void Jeu::manche(Plateau * p, Pioche * p1, Pioche * p2, Pioche * p3, Joueur * j1, Joueur * j2, Obligatoire * obl, Optionnelle * opt) {
    while(joueur_gagnant == nullptr) { //tant qu'on n'a pas de gagnant
        tour(p, p1, p2, p3, joueur_actuel, obl, opt); //tour du joueur
        verifCarteNoble(joueur_actuel, p); //le joueur reçoit-il une carte noble ?
        verifGagnant(j1, j2); //le joueur a-t-il gagné ?
    }
    std::cout << "Bravo " << joueur_gagnant->getPseudo() << " ! Tu as gagne !\n";
    std::cout << "Fin de la partie\n";
}

//Actions du joueur actuel
void Jeu::tour(Plateau * p, Pioche * p1, Pioche * p2, Pioche * p3, Joueur * j, Obligatoire * obl, Optionnelle * opt){
    std::string sortie = p->etatPlateau(); //affichage plateau en console
    std::cout << sortie << "\n";
    p1->afficherCartesRevelees(); //affichage des pioches en console
    p2->afficherCartesRevelees();
    p3->afficherCartesRevelees();
    int choix_opt = -1; //initialisation du choix des actions optionnellese
    int stop = 0; //sert à arrêter l'IA si elle ne passe pas à la suite au bout de 10 appels
    IA * test_ia = dynamic_cast<IA *>(j); //pour tester si c'est une IA, si ce n'est pas le cas, alors l'attribut est à nullptr
    while (choix_opt != 1 && stop != 10){
        if (!(p->hasJeton())){ //obligation de remplir le plateau s'il n'a plus de jeton
            std::cout << "Vous devez remplir le plateau.\n";
            opt->remplissagePlateau(j,p);
        }
        else { //choix de l'action optionnelle en console
            std::cout << "Actions optionnelles :\n" << "1 - Aucune action\n";
            std::cout << "2 - Remplir le plateau\n" << "3 - Utiliser un privilege\n";

            if (test_ia) { //choix de l'action pour l'IA
                choix_opt = j->choisirChoix(1,3);
                std::cout << "l'IA choisit l'action" << choix_opt << "\n";
                stop++;
            }
            else { //choix de l'action pour l'Humain
                std::cout << "Votre choix : ";
                std::cin >> choix_opt;
            }

            switch (choix_opt) {
                case 2: {
                    std::cout << "Remplissage du plateau.\n";
                    opt->remplissagePlateau(j,p);
                    break;
                }

                case 3: {
                    std::cout << "Dépense d'un privilege.\n";
                    opt->depenserPrivilege(j,p);
                    break;
                }

                default: {
                    if (choix_opt != 1)
                            std::cout << "Tu t'es trompe de chiffre banane !\n";
                    break;
                }
            }
        }
    }

    int choix_obl; //choix obligatoire
    std::cout << "Actions obligatoires :\n" << "1 - Prendre des jetons\n";
    std::cout << "2 - Acheter une carte\n" << "3 - Reserver une carte\n";

    if (test_ia) { //si IA
        choix_obl = j->choisirChoix(1,3);
        //choix_obl = 3;
        std::cout << "l'IA choisit l'action" << choix_obl << "\n";
    }
    else { //si Humain
        std::cout << "Votre choix : ";
        std::cin >> choix_obl;
    }
    /* Les actions de IA ne sont pas les mêmes que celles d'un joueur
    On traite donc chacun des cas */
    switch(choix_obl){
        case 1:
            std::cout << "Prendre un jeton.\n";
            if (test_ia) {
                test_ia->prendreJetons(p);
            }
            else {
                obl->prendreJeton(j,p);
            }
            break;

        case 2:
            std::cout << "Acheter une carte.\n";
            if (test_ia) {
                int np = test_ia->choisirChoix(1,3); //choisit la pioche où acheter la carte
                if (np == 1)
                    test_ia->melangerEtObtenirDerniereCarte(*p1,*test_ia,*p);
                else if (np==2)
                    test_ia->melangerEtObtenirDerniereCarte(*p2,*test_ia,*p);
                else
                    test_ia->melangerEtObtenirDerniereCarte(*p3,*test_ia,*p);
            }
            else {
                obl->acheterCarte(j,p,p1,p2,p3);
            }
            break;

        case 3:
            std::cout << "Reserve une carte.\n";
            if (test_ia) {
                int np = test_ia->choisirChoix(1,3); //choisit la pioche où réserver
                int choix_bool = test_ia->choisirChoix(1,2);
                bool booleen; //sert à savoir si l'IA réserve une carte du plateau ou de la pioche
                if (choix_bool == 1)
                    booleen = true;
                else
                    booleen = false;
                int nc = 0;
                if (np == 1)
                    nc = test_ia->choisirChoix(1,p1->getMaxCartesRevelees());
                else if (np==2)
                    nc = test_ia->choisirChoix(1,p2->getMaxCartesRevelees());
                else
                    nc = test_ia->choisirChoix(1,p3->getMaxCartesRevelees());
                obl->reserverCarte(joueur_actuel,p,p1,p2,p3,np, nc, booleen);
            }
            else
                obl->demanderCarteAReserver(j,p,p1,p2,p3);
            break;

        default:
            std::cout << "Eh ben voila, t'as plus la possibilite de prendre une action banane !\n";
            break;
    }
}

//Désigne le gagnant
void Jeu::vainqueur(Joueur * j){
    joueur_gagnant = j;
}

//Passe la main au joueur suivant
void Jeu::auSuivant(Joueur * j1, Joueur * j2){
    if (joueur_actuel->getPseudo() == j1->getPseudo()) {
        std::cout << joueur_actuel->getPseudo() << " passe la main a " << j2->getPseudo() << "\n";
        joueur_actuel = j2;
    }
    else {
        std::cout << joueur_actuel->getPseudo() << " passe la main a " << j1->getPseudo() << "\n";
        joueur_actuel = j1;
    }
}

//Pour savoir si le joueur reçoit une carte noble
void Jeu::verifCarteNoble(Joueur * j, Plateau * p) {
    //conditions de réception d'une carte : >=3 couronnes et 0 carte ou >=6 couronnes et 1 carte
    if ((j->getNombreCouronnes() >= 3 && j->getNombreCartesNobles()==0) || (j->getNombreCartesNobles() == 1 && j->getNombreCouronnes() >= 6)) {
        if (p->nb_carte_noble > 0) { //s'il reste des cartes nobles
            std::cout << "Joueur : " << j->getPseudo() << ", couronnes : " << j->getNombreCouronnes() << "\n";
            std::cout << "Cartes nobles : " << j->getNombreCartesNobles() << "\n";
            int choix;
            std::cout << "Cartes noble\n";
            for (int i = 0; i < p->nb_carte_noble; i++){ //affichage des cartes nobles disponibles
                if (p->cartes_nobles[i] != nullptr)
                    std::cout << "noble " << i + 1 << "\t";
            }
            std::cout << "\n\n";
            IA * test_ia = dynamic_cast<IA *>(j); //dans le cas d'une IA, elle choisit aléatoirement
            if (test_ia) {
                int verif = 0;
                do { //elle doit choisir une carte qui n'a pas été prise
                    choix = test_ia->choisirChoix(1,4);
                    if (p->cartes_nobles[choix-1] != nullptr) {
                        verif = 1;
                    }
                } while(verif != 1);
                std::cout << "Choix de la carte noble : " << choix << "\n";
                const CarteNoble * carte = p->prendreCarteNoble(choix-1);
                j->ajouterCarteNoble(carte); //attribution de la carte
                auto* carte_non_const = const_cast<CarteNoble*>(carte);
                carte_non_const->actionPouvoir(p, j); //activation des pouvoirs si elle en a
            }
            else { //cas pour un humain
                std::cout << "Choix de la carte noble : ";
                //std::cin >> choix;
                vue_jeu->message("Action", "Vous pouvez prendre une carte noble !");
                vue_jeu->choixCarteNoble(true);
            }

        }
    }
}

//vérification du gagnant
void Jeu::verifGagnant(Joueur * j1, Joueur * j2) {
    if (joueur_actuel->getNombreCouronnes() >= 10) //si le joueur a 10 couronnes
        vainqueur(joueur_actuel);
    else if (joueur_actuel->getPointsPrestigeTotal() >= 20) //si le joueur a 20 points de prestige
        vainqueur(joueur_actuel);
    else {
        bool gagnant = false;
        for (int i = 0; i<5; i++) { //si le joueur a 10 points de prestige dans une couleur
            if (joueur_actuel->getPointsPrestigeCouleurs(i) >= 10)
                gagnant = true;
        }
        if (gagnant) //si l'une des conditions est valide -> appel de vainqueur
            vainqueur(joueur_actuel);
        else
            auSuivant(j1, j2); //sinon au suivant
    }
//    int choix = -1;
//    std::cout << "On continue ? 1 - oui, 0 - non :";
//    std::cin >> choix;
//    if (choix == 0) {
//        vainqueur(joueur_actuel);
//    }
//    else {
//        auSuivant(j1, j2);
//    }
}


void Jeu::validationAction() {
    // si bouton pressé
    // recueillir variable qui contient bouton choisi
    // si variable vide -> peut pas presser bouton ?
    // appeler action correspondante
}

/* =============================================== Fonctions avec BDD =============================================== */

void executeSQL(sqlite3* db, const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void initCarteJoaillerie(sqlite3* db, std::vector<const CarteJoaillerie*>* cartes) {
    for (int id = 1; id <= 67; ++id) {
        CarteJoaillerieData data = queryCarteJoaillerie(db, id);

        // Convertissez les données interrogées au format requis
        std::array<Couleur, 2> pierres = {static_cast<Couleur>(data.pierres[0]), static_cast<Couleur>(data.pierres[1])};
        std::map<Couleur, int> prix;
        for (const auto& p : data.prix) {
            prix[static_cast<Couleur>(p.first)] = p.second;
        }

        std::string imagePath = "../images/" + (id < 10 ? "0" + std::to_string(id) : std::to_string(id)) + ".png";

        CarteJoaillerie* carte = new CarteJoaillerie(
                nullptr, nullptr, data.niveau, data.couronnes, pierres, prix, imagePath,
                data.pointPrestige, static_cast<Pouvoir>(data.pouvoirs[0]),
                static_cast<Pouvoir>(data.pouvoirs[1]), id
        );

        cartes->push_back(carte);
    }
}


void initCarteJoaillerieNonConst(sqlite3* db, std::vector<CarteJoaillerie*>* cartes) {
    for (int id = 1; id <= 67; id++) {
        CarteJoaillerieData data = queryCarteJoaillerie(db, id);
        std::cout<<"------ création cartes id : "<< id<<"\n";
        // Convertissez les données interrogées au format requis
        std::array<Couleur, 2> pierres = {static_cast<Couleur>(data.pierres[0]), static_cast<Couleur>(data.pierres[1])};
        std::map<Couleur, int> prix;
        Couleur couleur;
        for (const auto& p : data.prix) {
            switch (p.first) {
                case 1:
                    couleur = Couleur::rouge;
                    break;
                case 2:
                    couleur= Couleur::bleu;
                    break;
                case 3:
                    couleur= Couleur::vert;
                    break;
                case 4:
                    couleur= Couleur::blanc;
                    break;
                case 5:
                    couleur= Couleur::noir;
                    break;
                case 6:
                    couleur= Couleur::rose;
                    break;
            }
            prix[couleur] = p.second;
        }

        std::string imagePath = "../images/" + (id < 10 ? "0" + std::to_string(id) : std::to_string(id)) + ".png";

        CarteJoaillerie* carte = new CarteJoaillerie(
                nullptr, nullptr, data.niveau, data.couronnes, pierres, prix, imagePath,
                data.pointPrestige, static_cast<Pouvoir>(data.pouvoirs[0]),
                static_cast<Pouvoir>(data.pouvoirs[1]), id
        );

        cartes->push_back(carte);
    }
}

void initCarteNoble(sqlite3* db, std::vector<const CarteNoble*>* cartesNoble) {
    for (int id = 1; id <=4; ++id) {
        CarteNobleData data = queryCarteNoble(db, id);

        //Construire le chemin de l'image
        std::string imagePath = "../images/" + std::to_string(id + 67) + ".png";

        const CarteNoble* carteNoble = new CarteNoble(
                nullptr, nullptr,imagePath,
                data.pointPrestige,
                data.couronnes,
                data.pointPrestige,
                static_cast<Pouvoir>(data.pouvoirs[0]),
                static_cast<Pouvoir>(data.pouvoirs[1]),
                id
        );

        cartesNoble->push_back(carteNoble);
    }
}

Jeton* queryJetonById(sqlite3* db, int jetonId) {
    const char* querySql = "SELECT id, type, couleur, position_x, position_y FROM Jeton WHERE id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, querySql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, jetonId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        JetonType type = static_cast<JetonType>(sqlite3_column_int(stmt, 1));
        Couleur couleur = static_cast<Couleur>(sqlite3_column_int(stmt, 2));
        int positionX = sqlite3_column_int(stmt, 3);
        int positionY = sqlite3_column_int(stmt, 4);

        sqlite3_finalize(stmt);
        return new Jeton(type, couleur, positionX, positionY);
    }

    sqlite3_finalize(stmt);
    return nullptr;
}

void clearAndInitializeTables(sqlite3* db) {
    // Tables to be cleared
    std::vector<std::string> tablesToClear = {
            "CartesDansPioche", "CartesDehors", "JoueurCartesMain", "JoueurCartesNoble",
            "JoueurCartesReservees", "JoueurJetons", "JoueurPrivilege", "PlateauCartesNoble",
            "PlateauJetons", "PlateauPrivileges", "PlateauSac", "PlateauJetonsColors",
            "PlateauJetonsColorsSac","Jeu", "Joueur", "Plateau"
    };

    // Clear tables
    for (const auto& table : tablesToClear) {
        std::string sql = R"(DELETE FROM )" + table + R"(;)";
        executeSQL(db, sql);
    }

    // Reset information for certain tables
    std::string resetJeu = R"(
        INSERT INTO Jeu
            (handler_id, Joueur1_id, Joueur2_id, Pioche1_id, Pioche2_id, Pioche3_id, Plateau_id
        ) VALUES
            (1, NULL, NULL, 1, 2, 3, 1);
    )";

    // Reset Joueur 1 et 2
    std::string resetJoueurs = R"(
        INSERT INTO Joueur (
            id, is_IA, pseudo, nombre_couronnes, points_prestige_total,
            points_prestige_couleur1, points_prestige_couleur2, points_prestige_couleur3,
            points_prestige_couleur4, points_prestige_couleur5, points_prestige_couleur6,
            gemmes_bonus1, gemmes_bonus2, gemmes_bonus3, gemmes_bonus4, gemmes_bonus5,
            gemmes_bonus6, nb_jeton1, nb_jeton2, nb_jeton3, nb_jeton4, nb_jeton5, nb_jeton6,
            nombre_de_privileges, adversaire_id, droit_de_rejouer, difficulte
        ) VALUES
            (1, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0),
            (2, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
    )";

    std::string resetPlateau = R"(
        INSERT INTO Plateau (
            id, nb_jetons_sac, nb_jetons_plateau, pointeur_case_libre,
            nb_privileges, nb_carte_noble, nombre_jetons_par_cote_de_plateau,
            nombre_jetons_dans_selection_MAX, nb_jetons_sac_MAX, nb_privileges_MAX,
            nb_jetons_plateau_MAX
        ) VALUES (
            1, 0, 0, 0, 0, 4, 55, 25, 25, 3, 25
        );
    )";

    std::string resetJeton = R"(
        UPDATE Jeton
        SET position_x = -1, position_y = -1;
    )";

    executeSQL(db, resetJeu);
    executeSQL(db, resetJoueurs);
    executeSQL(db, resetPlateau);
    executeSQL(db, resetJeton);

    std::cout << "Database tables cleared and initialized successfully." << std::endl;
}

std::vector<Joueur*> continuerLaPartie(sqlite3* db,
                       std::vector<CarteJoaillerie*>& cartesJoaillerie,
                       std::vector<const CarteNoble*>& cartesNoble,
                       //std::vector<CarteJoaillerie>& cartesDansPioche,
                       //std::vector<CarteJoaillerie>& cartesDehors,
                       Jeu* jeu,
//                       Joueur* joueur1,
//                       Joueur* joueur2,
                       std::vector<Pioche*>& pioches,
                       Plateau& plateau,
                       std::vector<Privilege*> privileges) {
    /*
     * Doit retourner les deux joueurs, car leur type (humain/ia) n'est pas connu
     * lors de l'appelle de cette fonction ! Nous retournons donc les deux
     * objets créés dans un variable joueur_resultat.
     */

//    Présentation de deux classes "Humain" et d'une classe "IA" car nous ne pouvons pas être sûrs si le jeu se joue avec deux Humains ou un Humain et un IA
//
//    En fonction des données lues dans la base de données, décidez si vous souhaitez utiliser deux « Humain » ou un « Humain » et un « IA » après avoir restauré les données.

    std::vector<Joueur*> joueur_resultat (0);

    for (auto& pioche : pioches) {
        // 1. Obtenir des informations sur CartesDansPioche

        // Requête cartes_dans_pioche dans Pioche i
        std::vector<int> cartesDansPiocheIds = queryCartesInPioche(db, "CartesDansPioche", pioche->getNumeroPioche());
        int cartesDansPiocheCount = 0;
        // Requête cartes_dans_pioche dans Pioche
        for (int id: cartesDansPiocheIds) {
            const CarteJoaillerie *carte = nullptr;
            for (auto c: cartesJoaillerie) {
                if (c->getID() == id) {
                    carte = c;
                    break;
                }
            }
            if (carte != nullptr) {
                pioche->setCartesDansPioche(carte, cartesDansPiocheCount);
                cartesDansPiocheCount++;
            }
        }

        // 2. Obtenir des informations CartesDehors
        std::vector<int> cartesDehorsIds = queryCartesInPioche(db, "CartesDehors", pioche->getNumeroPioche());
        int cartesDehorsCount = 0;
        // Requête cartes_dehors dans Pioche
        for (int id: cartesDehorsIds) {
            const CarteJoaillerie *carte = nullptr;
            for (const auto &c: cartesJoaillerie) {
                if (c->getID() == id) {
                    carte = c;
                    break;
                }
            }
            if (carte != nullptr) {
                pioche->setCartesDehors(carte, cartesDehorsCount);
                cartesDehorsCount++;
            }
        }
    }

    // 3. Obtenir des informations Joueurs
    std::string pseudo = queryJoueurField<std::string>(db, "pseudo", 1);
    bool isIA = queryJoueurField<bool>(db, "is_IA", 1);
    int nombre_couronnes = queryJoueurField<int>(db, "nombre_couronnes", 1);
    int points_prestige_total = queryJoueurField<int>(db, "points_prestige_total", 1);
    int points_prestige_couleur1 = queryJoueurField<int>(db, "points_prestige_couleur1", 1);
    int points_prestige_couleur2 = queryJoueurField<int>(db, "points_prestige_couleur1", 1);
    int points_prestige_couleur3 = queryJoueurField<int>(db, "points_prestige_couleur1", 1);
    int points_prestige_couleur4 = queryJoueurField<int>(db, "points_prestige_couleur1", 1);
    int points_prestige_couleur5 = queryJoueurField<int>(db, "points_prestige_couleur1", 1);
    int points_prestige_couleur6 = queryJoueurField<int>(db, "points_prestige_couleur1", 1);
    int gemmes_bonus1 = queryJoueurField<int>(db, "gemmes_bonus1", 1);
    int gemmes_bonus2 = queryJoueurField<int>(db, "gemmes_bonus2", 1);
    int gemmes_bonus3 = queryJoueurField<int>(db, "gemmes_bonus3", 1);
    int gemmes_bonus4 = queryJoueurField<int>(db, "gemmes_bonus4", 1);
    int gemmes_bonus5 = queryJoueurField<int>(db, "gemmes_bonus5", 1);
    int gemmes_bonus6 = queryJoueurField<int>(db, "gemmes_bonus6", 1);
    int nb_jeton1 = queryJoueurField<int>(db, "nb_jeton1", 1);
    int nb_jeton2 = queryJoueurField<int>(db, "nb_jeton2", 1);
    int nb_jeton3 = queryJoueurField<int>(db, "nb_jeton3", 1);
    int nb_jeton4 = queryJoueurField<int>(db, "nb_jeton4", 1);
    int nb_jeton5 = queryJoueurField<int>(db, "nb_jeton5", 1);
    int nb_jeton6 = queryJoueurField<int>(db, "nb_jeton6", 1);
    int nb_jeton7 = queryJoueurField<int>(db, "nb_jeton7", 1);
    //int nombre_de_privileges = queryJoueurField<int>(db, "nombre_de_privileges", 1);
    int adversaire_id = queryJoueurField<int>(db, "adversaire_id", 1);
    bool droit_de_rejouer = queryJoueurField<bool>(db, "droit_de_rejouer", 1);
    int difficulteValue = queryJoueurField<int>(db, "difficulte", 1);
    Difficulte difficulte = static_cast<Difficulte>(difficulteValue);

    Joueur* joueur1;
    if (isIA) {joueur1 = new IA(pseudo, difficulte);}
    else { joueur1 = new Humain(pseudo);}
    joueur1->setPseudo(pseudo);
    joueur1->setNombreCouronnes(nombre_couronnes);
    joueur1->setPointsPrestigeTotal(points_prestige_total);
    joueur1->setPointsPrestigeCouleurs(0, points_prestige_couleur1);
    joueur1->setPointsPrestigeCouleurs(1, points_prestige_couleur2);
    joueur1->setPointsPrestigeCouleurs(2, points_prestige_couleur3);
    joueur1->setPointsPrestigeCouleurs(3, points_prestige_couleur4);
    joueur1->setPointsPrestigeCouleurs(4, points_prestige_couleur5);
    joueur1->setPointsPrestigeCouleurs(5, points_prestige_couleur6);
    joueur1->setGemmesBonus(0,gemmes_bonus1);
    joueur1->setGemmesBonus(1,gemmes_bonus2);
    joueur1->setGemmesBonus(2,gemmes_bonus3);
    joueur1->setGemmesBonus(3,gemmes_bonus4);
    joueur1->setGemmesBonus(4,gemmes_bonus5);
    joueur1->setGemmesBonus(5,gemmes_bonus6);
    joueur1->setNbJeton(0, nb_jeton1);
    joueur1->setNbJeton(1, nb_jeton2);
    joueur1->setNbJeton(2, nb_jeton3);
    joueur1->setNbJeton(3, nb_jeton4);
    joueur1->setNbJeton(4, nb_jeton5);
    joueur1->setNbJeton(5, nb_jeton6);
    joueur1->setNbJeton(6, nb_jeton7);
    joueur1->resetRejouer(droit_de_rejouer);
    joueur1->setIsIA(isIA);
    joueur1->setDifficulte(difficulte);

    pseudo = queryJoueurField<std::string>(db, "pseudo", 2);
    isIA = queryJoueurField<bool>(db, "is_IA", 2);
    nombre_couronnes = queryJoueurField<int>(db, "nombre_couronnes", 2);
    points_prestige_total = queryJoueurField<int>(db, "points_prestige_total", 2);
    points_prestige_couleur1 = queryJoueurField<int>(db, "points_prestige_couleur1", 2);
    points_prestige_couleur2 = queryJoueurField<int>(db, "points_prestige_couleur1", 2);
    points_prestige_couleur3 = queryJoueurField<int>(db, "points_prestige_couleur1", 2);
    points_prestige_couleur4 = queryJoueurField<int>(db, "points_prestige_couleur1", 2);
    points_prestige_couleur5 = queryJoueurField<int>(db, "points_prestige_couleur1", 2);
    points_prestige_couleur6 = queryJoueurField<int>(db, "points_prestige_couleur1", 2);
    gemmes_bonus1 = queryJoueurField<int>(db, "gemmes_bonus1", 2);
    gemmes_bonus2 = queryJoueurField<int>(db, "gemmes_bonus2", 2);
    gemmes_bonus3 = queryJoueurField<int>(db, "gemmes_bonus3", 2);
    gemmes_bonus4 = queryJoueurField<int>(db, "gemmes_bonus4", 2);
    gemmes_bonus5 = queryJoueurField<int>(db, "gemmes_bonus5", 2);
    gemmes_bonus6 = queryJoueurField<int>(db, "gemmes_bonus6", 2);
    nb_jeton1 = queryJoueurField<int>(db, "nb_jeton1", 2);
    nb_jeton2 = queryJoueurField<int>(db, "nb_jeton2", 2);
    nb_jeton3 = queryJoueurField<int>(db, "nb_jeton3", 2);
    nb_jeton4 = queryJoueurField<int>(db, "nb_jeton4", 2);
    nb_jeton5 = queryJoueurField<int>(db, "nb_jeton5", 2);
    nb_jeton6 = queryJoueurField<int>(db, "nb_jeton6", 2);
    nb_jeton7 = queryJoueurField<int>(db, "nb_jeton7", 2);
    //nombre_de_privileges = queryJoueurField<int>(db, "nombre_de_privileges", 2);
    adversaire_id = queryJoueurField<int>(db, "adversaire_id", 2);
    droit_de_rejouer = queryJoueurField<bool>(db, "droit_de_rejouer", 2);
    difficulteValue = queryJoueurField<int>(db, "difficulte", 2);
    difficulte = static_cast<Difficulte>(difficulteValue);


    Joueur* joueur2;
    if (isIA) {joueur2 = new IA(pseudo, difficulte);}
    else { joueur2 = new Humain(pseudo);}

    joueur2->setPseudo(pseudo);
    joueur2->setNombreCouronnes(nombre_couronnes);
    joueur2->setPointsPrestigeTotal(points_prestige_total);
    joueur2->setPointsPrestigeCouleurs(0, points_prestige_couleur1);
    joueur2->setPointsPrestigeCouleurs(1, points_prestige_couleur2);
    joueur2->setPointsPrestigeCouleurs(2, points_prestige_couleur3);
    joueur2->setPointsPrestigeCouleurs(3, points_prestige_couleur4);
    joueur2->setPointsPrestigeCouleurs(4, points_prestige_couleur5);
    joueur2->setPointsPrestigeCouleurs(5, points_prestige_couleur6);
    joueur2->setGemmesBonus(0,gemmes_bonus1);
    joueur2->setGemmesBonus(1,gemmes_bonus2);
    joueur2->setGemmesBonus(2,gemmes_bonus3);
    joueur2->setGemmesBonus(3,gemmes_bonus4);
    joueur2->setGemmesBonus(4,gemmes_bonus5);
    joueur2->setGemmesBonus(5,gemmes_bonus6);
    joueur2->setNbJeton(0, nb_jeton1);
    joueur2->setNbJeton(1, nb_jeton2);
    joueur2->setNbJeton(2, nb_jeton3);
    joueur2->setNbJeton(3, nb_jeton4);
    joueur2->setNbJeton(4, nb_jeton5);
    joueur2->setNbJeton(5, nb_jeton6);
    joueur2->setNbJeton(6, nb_jeton7);
    joueur2->resetRejouer(droit_de_rejouer);
    joueur2->setIsIA(isIA);
    joueur2->setDifficulte(difficulte);

    joueur1->setAdversaire(joueur2);
    joueur2->setAdversaire(joueur1);

    joueur_resultat.push_back(joueur1);
    joueur_resultat.push_back(joueur2);

    // 4. Obtenir des informations JoueurCartesMain, JoueurCartesNoble, JoueurCartesReservees, JoueurJetons, JoueurPrivilege
    // 查询玩家的特权和卡片信息
    std::vector<int> cartesReserveesIds = queryJoueurCartes(db, "JoueurCartesReservees", 1);
    std::vector<int> cartesMainIds = queryJoueurCartes(db, "JoueurCartesMain", 1);
    std::vector<int> cartesNobleIds = queryJoueurCartes(db, "JoueurCartesNoble", 1);
    std::vector<int> privilegesIds = queryJoueurPrivileges(db, 1);

    for (int carteId : cartesReserveesIds) {
        for (CarteJoaillerie* carte : cartesJoaillerie) {
            if (carte->getID() == carteId) {
                joueur1->ajouterCarteReservee(carte);
                break;
            }
        }
    }
    for (int carteId : cartesMainIds) {
        for (CarteJoaillerie* carte : cartesJoaillerie) {
            if (carte->getID() == carteId) {
                joueur1->ajouterCarteJoaillerie(carte);
                break;
            }
        }
    }
    for (int carteId : cartesNobleIds) {
        for (const CarteNoble* carte : cartesNoble) {
            if (carte && carte->getID() == carteId) {
                joueur1->ajouterCarteNoble(carte);
                break;
            }
        }
    }
    for (int privilegeId : privilegesIds) {
        for (Privilege* priv : privileges) {
            if (priv->getID() == privilegeId) {
                joueur1->ajouterPrivilege(priv);
                break;
            }
        }
    }

    cartesReserveesIds.clear();
    cartesMainIds.clear();
    cartesNobleIds.clear();
    privilegesIds.clear();

    cartesReserveesIds = queryJoueurCartes(db, "JoueurCartesReservees", 2);
    cartesMainIds = queryJoueurCartes(db, "JoueurCartesMain", 2);
    cartesNobleIds = queryJoueurCartes(db, "JoueurCartesNoble", 2);
    privilegesIds = queryJoueurPrivileges(db, 2);

    for (int carteId : cartesReserveesIds) {
        for (CarteJoaillerie* carte : cartesJoaillerie) {
            if (carte->getID() == carteId) {
                joueur2->ajouterCarteReservee(carte);
                break;
            }
        }
    }
    for (int carteId : cartesMainIds) {
        for (CarteJoaillerie *carte : cartesJoaillerie) {
            if (carte->getID() == carteId) {
                joueur2->ajouterCarteJoaillerie(carte);
                break;
            }
        }
    }
    for (int carteId : cartesNobleIds) {
        for (const CarteNoble* carte : cartesNoble) {
            if (carte && carte->getID() == carteId) {
                joueur2->ajouterCarteNoble(carte);
                break;
            }
        }
    }
    for (int privilegeId : privilegesIds) {
        for (Privilege* priv : privileges) {
            if (priv->getID() == privilegeId) {
                joueur2->ajouterPrivilege(priv);
                break;
            }
        }
    }

    // 5. Obtenir des informations Jeu
    int jeuId = 1; // L'ID de JEU est fixé à 1

    int joueur1Id = queryJeuField(db, "Joueur1_id", jeuId); // joueur actuel
    int joueur2Id = queryJeuField(db, "Joueur2_id", jeuId); // joueur gagnant
//    int pioche1Id = queryJeuField(db, "Pioche1_id", jeuId);
//    int pioche2Id = queryJeuField(db, "Pioche2_id", jeuId);
//    int pioche3Id = queryJeuField(db, "Pioche3_id", jeuId);
//    int plateauId = queryJeuField(db, "Plateau_id", jeuId);

    if(joueur1Id == 1) {
        jeu->setJoueurActuel(joueur1);
    } else {
        jeu->setJoueurActuel(joueur2);
    }
    if(joueur1Id == 1) {
        jeu->setJoueurGagnant(joueur1);
    } else if (joueur1Id == 2){
        jeu->setJoueurGagnant(joueur2);
    } else {
        jeu->setJoueurGagnant(nullptr);
    }

    // 6. obtenir des informations Plateau
    int plateauId = 1;

    int nb_jetons_sac = queryPlateauField<int>(db, "nb_jetons_sac", plateauId);
    int nb_jetons_plateau = queryPlateauField<int>(db, "nb_jetons_plateau", plateauId);
    int nb_privileges = queryPlateauField<int>(db, "nb_privileges", plateauId);
    int pointeur_case_libre = queryPlateauField<int>(db, "pointeur_case_libre", plateauId);
    int nb_carte_noble = queryPlateauField<int>(db, "nb_carte_noble", plateauId);

    plateau.setNbJetonsSac(nb_jetons_sac);
    plateau.setNbJetonsPlateau(nb_jetons_plateau);
    plateau.setNbPrivileges(nb_privileges);
    plateau.setPointeurCaseLibre(pointeur_case_libre);
    plateau.setNbCarteNoble(nb_carte_noble);

    // 7. Obtenir des informations PlateauCartesNoble，PlateauJetons，PlateauPrivileges，PlateauSac

    std::vector<const CarteNoble*> cartesNobles(0);
    std::vector<int> carteNobleIds = queryPlateauCartesNobleFieldVector(db, "carte_noble_id", plateauId);
    for (int i = 0; i < 4; i++) {
        const CarteNoble* carteNoble = nullptr;
        for (const CarteNoble* cn : cartesNoble) { if (cn && cn->getID() == carteNobleIds[i]) { carteNoble = cn; break; } }
        if (carteNoble != nullptr) { cartesNobles.push_back(carteNoble); }
    }
    plateau.setCartesNobles(cartesNobles);

//    // Pour stocker les Jetons sur le Plateau
//    std::vector<const Jeton*> newJetons;
//    // Pour stocker les Jetons sur le sac dans Plateau
//    std::vector<const Jeton*> newSac;
//
//    std::vector<int> jetonsPlateauIds = queryAllJetonIdsForPlateau(db, "PlateauJetons", 1);
//    for (int jetonId : jetonsPlateauIds) {
//        // 根据 Jeton ID 查询 Jeton 表中的记录
//        Jeton* jeton = queryJetonById(db, jetonId);
//        if (jeton != nullptr) {
//            newJetons.push_back(jeton);
//        }
//    }

//    std::vector<int> jetonsSacIds = queryAllJetonIdsForPlateau(db, "PlateauSac", 1);
//    for (int jetonId : jetonsSacIds) {
//        // 根据 Jeton ID 查询 Jeton 表中的记录
//        Jeton* jeton = queryJetonById(db, jetonId);
//        if (jeton != nullptr) {
//            newSac.push_back(jeton);
//        }
//    }
//    plateau.setJetons(newJetons);
//    plateau.setSac(newSac);
//
//    std::vector<int> privilegeIds = queryPlateauPrivilegesField(db, plateauId);
//    std::vector<Privilege*> plateauPrivileges;
//    for (int id : privilegeIds) {
//        for (Privilege* priv : privileges) {
//            if (priv->getID() == id) { plateauPrivileges.push_back(priv); break; }
//        }
//    }
//    plateau.setPrivileges(plateauPrivileges);

    std::vector<int> privilegeIds = queryPlateauPrivilegesField(db, plateauId);
    std::vector<Privilege*> plateauPrivileges;
    for (int id : privilegeIds) {
        for (Privilege* priv : privileges) {
            if (priv->getID() == id) { plateauPrivileges.push_back(priv); break; }
        }
    }
    plateau.setPrivileges(plateauPrivileges);

    // ------------------ Jetons du plateau ------------------
    std::vector<const char*> jc = queryAllJetonColorsForPlateau(db, "PlateauJetonsColors");
    unsigned int index = 0;
    std::vector<std::vector<int>> matrix = plateau.getMatrix();
    for (auto color : jc) {
        std::cout<<"index : "<<matrix[index%5][index/5]-1<<" : "<<color<<std::endl;

        //plateau.setJetonsByColor(color, plateau.getMatrix()[index%5][index/5]-1);
        plateau.setJetonsByColor(color, index);
        index++;
    }

    // ------------------ Jetons du sac ---------------
    jc = queryAllJetonColorsForPlateau(db, "PlateauJetonsColorsSac");
    index = 0;
    for (auto color : jc) {
        std::cout<<"index sac : "<<index<<" : "<<color<<std::endl;

        //plateau.setJetonsByColor(color, plateau.getMatrix()[index%5][index/5]-1);
        plateau.setJetonsByColorSac(color, index);
        index++;
    }
    return joueur_resultat;
}

void sauvegarderPartie(sqlite3* db,
        //const std::vector<CarteJoaillerie>& cartesDansPioche,
        //const std::vector<CarteJoaillerie>& cartesDehors,
                       const Jeu& jeu,
                       const Joueur& joueur1,
                       const Joueur& joueur2,
                       std::vector<Pioche*>* pioches,
                       const Plateau& plateau) {

    // 0 先清空之前的信息
    clearAndInitializeTables(db);

    // 1 存储和Pioche有关的信息
    const CarteJoaillerie* tmp = nullptr;
    int id_tmp = 0;
    for (Pioche* pioche : *pioches) {
        // 存储 cartes_dans_pioche
        for (int i = 0; i < pioche->getMaxCartesPioche(); i++) {
            tmp = pioche->getCartesDansPioche(i);
            if (tmp != nullptr) {
                id_tmp = tmp->getID();
                insertCarteInPioche(db, "CartesDansPioche", pioche->getNumeroPioche(), id_tmp);
            }
        }
        // 存储 cartes_dehors
        for (int i = 0; i < pioche->getMaxCartesRevelees(); ++i) {
            const int numero = pioche->getNumeroPioche();
            const CarteJoaillerie* carte= pioche->getCartesDehors(i);
            if (carte != nullptr) {
                const int carteid = carte->getID();
                std::cout << carteid << std::endl;
                insertCarteInPioche(db, "CartesDehors", numero, carteid);
            }
        }
    }


    // 更新 Joueur 数据
    std::string updateSql = R"(UPDATE Joueur SET
        is_IA = ?, pseudo = ?, nombre_couronnes = ?, points_prestige_total = ?,
        points_prestige_couleur1 = ?, points_prestige_couleur2 = ?,
        points_prestige_couleur3 = ?, points_prestige_couleur4 = ?,
        points_prestige_couleur5 = ?, points_prestige_couleur6 = ?,
        gemmes_bonus1 = ?, gemmes_bonus2 = ?, gemmes_bonus3 = ?,
        gemmes_bonus4 = ?, gemmes_bonus5 = ?, gemmes_bonus6 = ?,
        nb_jeton1 = ?, nb_jeton2 = ?, nb_jeton3 = ?,
        nb_jeton4 = ?, nb_jeton5 = ?, nb_jeton6 = ?, nb_jeton7 = ?,
        adversaire_id = ?, droit_de_rejouer = ?,
        difficulte = ? WHERE id = ?;)";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, updateSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) { std::cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << std::endl; return; }

    // 绑定 Joueur 类的属性到 SQL 语句
    sqlite3_bind_int(stmt, 1, joueur1.getIsIA() ? 1 : 0); // 假设 isIA 是 bool 类型
    sqlite3_bind_text(stmt, 2, joueur1.getPseudo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, joueur1.getNombreCouronnes());
    sqlite3_bind_int(stmt, 4, joueur1.getPointsPrestigeTotal());
    for (int i = 0; i < 6; ++i) { sqlite3_bind_int(stmt, 5 + i, joueur1.getPointsPrestigeCouleurs(i)); }
    for (int i = 0; i < 6; ++i) { sqlite3_bind_int(stmt, 11 + i, joueur1.getGemmesBonus(i)); }
    for (int i = 0; i < 7; ++i) { sqlite3_bind_int(stmt, 17 + i, joueur1.getNbJeton(i)); }
    sqlite3_bind_int(stmt, 24, 2);
    sqlite3_bind_int(stmt, 25, joueur1.getDroitDeRejouer());
    Difficulte diff = joueur1.getDifficulte();
    int diffInt = static_cast<int>(diff);
    sqlite3_bind_int(stmt, 26, diffInt);
    sqlite3_bind_int(stmt, 27, 1);

    // 执行更新语句
    if (sqlite3_step(stmt) != SQLITE_DONE) { std::cerr << "Error executing update statement: " << sqlite3_errmsg(db) << std::endl; }

    if (sqlite3_prepare_v2(db, updateSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) { std::cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << std::endl; return; }

    // 绑定 Joueur 类的属性到 SQL 语句
    sqlite3_bind_int(stmt, 1, joueur2.getIsIA() ? 1 : 0); // 假设 isIA 是 bool 类型
    sqlite3_bind_text(stmt, 2, joueur2.getPseudo().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, joueur2.getNombreCouronnes());
    sqlite3_bind_int(stmt, 4, joueur2.getPointsPrestigeTotal());
    for (int i = 0; i < 6; ++i) { sqlite3_bind_int(stmt, 5 + i, joueur2.getPointsPrestigeCouleurs(i)); }
    for (int i = 0; i < 6; ++i) { sqlite3_bind_int(stmt, 11 + i, joueur2.getGemmesBonus(i)); }
    for (int i = 0; i < 7; ++i) { sqlite3_bind_int(stmt, 17 + i, joueur2.getNbJeton(i)); }
    sqlite3_bind_int(stmt, 24, 2);
    sqlite3_bind_int(stmt, 25, joueur2.getDroitDeRejouer());
    diff = joueur1.getDifficulte();
    diffInt = static_cast<int>(diff);
    sqlite3_bind_int(stmt, 26, diffInt);
    sqlite3_bind_int(stmt, 27, 2);

    if (sqlite3_step(stmt) != SQLITE_DONE) { std::cerr << "Error executing update statement: " << sqlite3_errmsg(db) << std::endl; }
    sqlite3_finalize(stmt);

    std::vector<int> ids;
    std::vector<CarteJoaillerie*> cartesMain = joueur1.getCartesMain();
    for (CarteJoaillerie* carte : cartesMain) { ids.push_back(carte->getID()); }
    for (int id : ids) { insertJoueurCarte(db, "JoueurCartesMain", 1, id); }
    ids.clear();

    std::vector<CarteJoaillerie*> cartesReservees = joueur1.getCartesReservees();
    for (CarteJoaillerie* carte : cartesReservees) { ids.push_back(carte->getID()); }
    for (int id : ids) { insertJoueurCarte(db, "JoueurCartesReservees", 1, id); }
    ids.clear();

    std::vector<const CarteNoble*> cartesNobles = joueur1.getCartesNoble();
    for (const CarteNoble* carte : cartesNobles) { ids.push_back(carte->getID()); }
    for (int id : ids) { insertJoueurCarte(db, "JoueurCartesNoble", 1, id); }
    ids.clear();

    cartesMain.clear();
    cartesReservees.clear();
    cartesNobles.clear();

    cartesMain = joueur2.getCartesMain();
    for (CarteJoaillerie* carte : cartesMain) { ids.push_back(carte->getID()); }
    for (int id : ids) { insertJoueurCarte(db, "JoueurCartesMain", 2, id); }
    ids.clear();

    cartesReservees = joueur2.getCartesReservees();
    for (CarteJoaillerie* carte : cartesReservees) { ids.push_back(carte->getID()); }
    for (int id : ids) { insertJoueurCarte(db, "JoueurCartesReservees", 2, id); }
    ids.clear();

    cartesNobles = joueur2.getCartesNoble();
    for (const CarteNoble* carte : cartesNobles) { ids.push_back(carte->getID()); }
    for (int id : ids) { insertJoueurCarte(db, "JoueurCartesNoble", 2, id); }
    ids.clear();

    cartesMain.clear();
    cartesReservees.clear();
    cartesNobles.clear();

    std::vector<Privilege*> JoueurPrivileges = joueur1.getPrivileges();
    for (Privilege* joueurPrivilege : JoueurPrivileges) { ids.push_back(joueurPrivilege->getID()); }
    for (int id : ids) { insertJoueurPrivilege(db, 1, id); }
    ids.clear();
    JoueurPrivileges.clear();

    JoueurPrivileges = joueur2.getPrivileges();
    for (Privilege* joueurPrivilege : JoueurPrivileges) { ids.push_back(joueurPrivilege->getID()); }
    for (int id : ids) { insertJoueurPrivilege(db, 2, id); }
    ids.clear();
    JoueurPrivileges.clear();


    // 更新Jeu
    std::string updateJeuSql = "UPDATE Jeu SET Joueur1_id = ?, Joueur2_id = ? WHERE handler_id = ?;";

    sqlite3_stmt* stmtJeu;
    if (sqlite3_prepare_v2(db, updateJeuSql.c_str(), -1, &stmtJeu, NULL) != SQLITE_OK) {
        std::cerr << "Error preparing update statement for Jeu: " << sqlite3_errmsg(db) << std::endl;
        return;
    }


    sqlite3_bind_int(stmtJeu, 1, joueur1.getPseudo() == jeu.getJoueurActuel()->getPseudo() ? 1 : 2);
    if (jeu.getJoueurActuel() != nullptr && jeu.getJoueurGagnant() != nullptr) sqlite3_bind_int(stmtJeu, 2, joueur1.getPseudo() == jeu.getJoueurGagnant()->getPseudo() ? 1 : 2);
    sqlite3_bind_int(stmtJeu, 3, 1); // 假设游戏 ID 为 1

    if (sqlite3_step(stmtJeu) != SQLITE_DONE) {
        std::cerr << "Error executing update statement for Jeu: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmtJeu);



    // 更新 Plateau 数据
    updatePlateauField(db, "nb_jetons_sac", plateau.getNbJetonsSac(), 1);
    updatePlateauField(db, "nb_jetons_plateau", plateau.getNbJetonsPlateau(), 1);
    updatePlateauField(db, "pointeur_case_libre", plateau.getPointeurCaseLibre(), 1);
    updatePlateauField(db, "nb_privileges", plateau.getNbPrivileges(), 1);
    updatePlateauField(db, "nb_carte_noble", plateau.getNbCarteNoble(), 1);

    // 更新PlateauCartesNoble PlateauJetons PlateauPrivileges PlateauSac
    auto plateauCartesNobles = plateau.getCartesNobles();
    for (auto carteNoble : plateauCartesNobles) {
        if (carteNoble) {
            int carteNobleId = carteNoble->getID();
            insertIntoPlateauCartesNoble(db, 1, carteNobleId);
        }
    }



    auto plateauPrivileges = plateau.getPrivileges();
    for (auto privilege : plateauPrivileges) {
        if (privilege != nullptr) {
            int privilegeId = privilege->getID();
            insertIntoPlateauPrivileges(db, 1, privilegeId);
        }
    }

//    // Stockage des données Jeton dans PlateauSac et dans Jeton
//    for (auto jeton : plateau.getSac()) {
//        if (jeton != nullptr) {
//            std::string updateJetonSql = R"(UPDATE Jeton SET position_x = ?, position_y = ? WHERE id = ?;)";
//
//            sqlite3_stmt* stmtJeton;
//            if (sqlite3_prepare_v2(db, updateJetonSql.c_str(), -1, &stmtJeton, NULL) != SQLITE_OK) {
//                std::cerr << "Error preparing update statement for Jeton: " << sqlite3_errmsg(db) << std::endl;
//                return;
//            }
//
//            sqlite3_bind_int(stmtJeton, 1, -1);
//            sqlite3_bind_int(stmtJeton, 2, -1);
//            sqlite3_bind_int(stmtJeton, 3, jeton->getID());
//
//            if (sqlite3_step(stmtJeton) != SQLITE_DONE) {
//                std::cerr << "Error executing update statement for Jeton: " << sqlite3_errmsg(db) << std::endl;
//            }
//
//            sqlite3_finalize(stmtJeton);
//        }
//    }

//    for (auto jeton : plateau.getJetons()) {
//        if (jeton != nullptr) {
//            std::string updateOrInsertSql = R"(REPLACE INTO PlateauSac (plateau_id, jeton_id) VALUES (?, ?);)";
//
//            sqlite3_stmt* stmtPlateauJeton;
//            if (sqlite3_prepare_v2(db, updateOrInsertSql.c_str(), -1, &stmtPlateauJeton, NULL) != SQLITE_OK) {
//                std::cerr << "Error preparing statement for PlateauJetons: " << sqlite3_errmsg(db) << std::endl;
//                return;
//            }
//
//            sqlite3_bind_int(stmtPlateauJeton, 1, 1); // 假设 Plateau ID 总是 1
//            sqlite3_bind_int(stmtPlateauJeton, 2, jeton->getID());
//
//            if (sqlite3_step(stmtPlateauJeton) != SQLITE_DONE) {
//                std::cerr << "Error executing statement for PlateauJetons: " << sqlite3_errmsg(db) << std::endl;
//            }
//
//            sqlite3_finalize(stmtPlateauJeton);
//        }
//    }

//    // Obtenez tous les jetons du Plateau et enregistrez leurs coordonnées
//    for (auto jeton : plateau.getJetons()) {
//        if (jeton != nullptr) {
//            std::string updateJetonSql = R"(UPDATE Jeton SET position_x = ?, position_y = ? WHERE id = ?;)";
//
//            sqlite3_stmt* stmtJeton;
//            if (sqlite3_prepare_v2(db, updateJetonSql.c_str(), -1, &stmtJeton, NULL) != SQLITE_OK) {
//                std::cerr << "Error preparing update statement for Jeton: " << sqlite3_errmsg(db) << std::endl;
//                return;
//            }
//
//            sqlite3_bind_int(stmtJeton, 1, jeton->getX());
//            sqlite3_bind_int(stmtJeton, 2, jeton->getY());
//            sqlite3_bind_int(stmtJeton, 3, jeton->getID());
//
//            if (sqlite3_step(stmtJeton) != SQLITE_DONE) {
//                std::cerr << "Error executing update statement for Jeton: " << sqlite3_errmsg(db) << std::endl;
//            }
//
//            sqlite3_finalize(stmtJeton);
//        }
//    }
    for (auto jeton : plateau.getJetons()) {
        if (jeton != nullptr) {
            std::string updateOrInsertSql = R"(REPLACE INTO PlateauSac (plateau_id, jeton_id) VALUES (?, ?);)";


            sqlite3_stmt* stmtPlateauJeton;
            if (sqlite3_prepare_v2(db, updateOrInsertSql.c_str(), -1, &stmtPlateauJeton, NULL) != SQLITE_OK) {
                std::cerr << "Error preparing statement for PlateauJetons: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            sqlite3_bind_int(stmtPlateauJeton, 1, 1); // 假设 Plateau ID 总是 1
            sqlite3_bind_int(stmtPlateauJeton, 2, jeton->getID());

            if (sqlite3_step(stmtPlateauJeton) != SQLITE_DONE) {
                std::cerr << "Error executing statement for PlateauJetons: " << sqlite3_errmsg(db) << std::endl;
            }

            sqlite3_finalize(stmtPlateauJeton);
        }
    }

    // Obtenez tous les jetons du Plateau et enregistrez leurs coordonnées
    for (auto jeton : plateau.getJetons()) {
        if (jeton != nullptr) {
            std::string updateJetonSql = R"(UPDATE Jeton SET position_x = ?, position_y = ? WHERE id = ?;)";

            sqlite3_stmt* stmtJeton;
            if (sqlite3_prepare_v2(db, updateJetonSql.c_str(), -1, &stmtJeton, NULL) != SQLITE_OK) {
                std::cerr << "Error preparing update statement for Jeton: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            sqlite3_bind_int(stmtJeton, 1, jeton->getX());
            sqlite3_bind_int(stmtJeton, 2, jeton->getY());
            sqlite3_bind_int(stmtJeton, 3, jeton->getID());

            if (sqlite3_step(stmtJeton) != SQLITE_DONE) {
                std::cerr << "Error executing update statement for Jeton: " << sqlite3_errmsg(db) << std::endl;
            }

            sqlite3_finalize(stmtJeton);
        }
    }

    for (auto jeton : plateau.getJetons()) {
        if (jeton != nullptr) {
            std::string updateOrInsertSql = R"(REPLACE INTO PlateauJetons (plateau_id, jeton_id) VALUES (?, ?);)";

            sqlite3_stmt* stmtPlateauJeton;
            if (sqlite3_prepare_v2(db, updateOrInsertSql.c_str(), -1, &stmtPlateauJeton, NULL) != SQLITE_OK) {
                std::cerr << "Error preparing statement for PlateauJetons: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            sqlite3_bind_int(stmtPlateauJeton, 1, 1);
            sqlite3_bind_int(stmtPlateauJeton, 2, jeton->getID());

            if (sqlite3_step(stmtPlateauJeton) != SQLITE_DONE) {
                std::cerr << "Error executing statement for PlateauJetons: " << sqlite3_errmsg(db) << std::endl;
            }

            sqlite3_finalize(stmtPlateauJeton);

            // ---------------- Utilisation de la table PlateauJetonsColors --------------------
            std::string updateOrInsertColor = R"(INSERT INTO PlateauJetonsColors(colors) VALUES (?);)";
            sqlite3_stmt* stmtPlateauJetonColors;
            if (sqlite3_prepare_v2(db, updateOrInsertColor.c_str(), -1, &stmtPlateauJetonColors, nullptr) != SQLITE_OK) {
                std::cerr << "Error preparing statement for PlateauJetonsColors: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            sqlite3_bind_text(stmtPlateauJetonColors, 1, jeton->getCouleurString().c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmtPlateauJetonColors) != SQLITE_DONE) {
                std::cerr << "Error executing statement for PlateauJetonsColors: " << sqlite3_errmsg(db) << std::endl;
            }

            sqlite3_finalize(stmtPlateauJetonColors);

        } else {
            // ---------------- Utilisation de la table PlateauJetonsColors --------------------
            std::string updateOrInsertColor = R"(INSERT INTO PlateauJetonsColors(colors) VALUES (?);)";
            sqlite3_stmt* stmtPlateauJetonColors;
            if (sqlite3_prepare_v2(db, updateOrInsertColor.c_str(), -1, &stmtPlateauJetonColors, nullptr) != SQLITE_OK) {
                std::cerr << "Error preparing statement for PlateauJetonsColors: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            sqlite3_bind_text(stmtPlateauJetonColors, 1, "", -1, SQLITE_STATIC);

            if (sqlite3_step(stmtPlateauJetonColors) != SQLITE_DONE) {
                std::cerr << "Error executing statement for PlateauJetonsColors: " << sqlite3_errmsg(db) << std::endl;
            }

            sqlite3_finalize(stmtPlateauJetonColors);
        }
    }

    // ---------------------------------  Sauvegarde de la couleur des jetons du sac ------------
    for (auto jeton : plateau.getJetonsSac()) {
        if (jeton != nullptr) {

            // ---------------- Utilisation de la table PlateauJetonsColorsSac non null --------------------
            std::string updateOrInsertColor = R"(INSERT INTO PlateauJetonsColorsSac(colors) VALUES (?);)";
            sqlite3_stmt *stmtPlateauJetonColors;
            if (sqlite3_prepare_v2(db, updateOrInsertColor.c_str(), -1, &stmtPlateauJetonColors, nullptr) !=
                SQLITE_OK) {
                std::cerr << "Error preparing statement for PlateauJetonsColorsSac: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            sqlite3_bind_text(stmtPlateauJetonColors, 1, jeton->getCouleurString().c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmtPlateauJetonColors) != SQLITE_DONE) {
                std::cerr << "Error executing statement for PlateauJetonsColorsSac: " << sqlite3_errmsg(db) << std::endl;
            }

            sqlite3_finalize(stmtPlateauJetonColors);

        } else {
            // ---------------- Utilisation de la table PlateauJetonsColorsSac null --------------------
            std::string updateOrInsertColor = R"(INSERT INTO PlateauJetonsColorsSac(colors) VALUES (?);)";
            sqlite3_stmt *stmtPlateauJetonColors;
            if (sqlite3_prepare_v2(db, updateOrInsertColor.c_str(), -1, &stmtPlateauJetonColors, nullptr) !=
                SQLITE_OK) {
                std::cerr << "Error preparing statement for PlateauJetonsColors: " << sqlite3_errmsg(db) << std::endl;
                return;
            }

            sqlite3_bind_text(stmtPlateauJetonColors, 1, "", -1, SQLITE_STATIC);

            if (sqlite3_step(stmtPlateauJetonColors) != SQLITE_DONE) {
                std::cerr << "Error executing statement for PlateauJetonsColors: " << sqlite3_errmsg(db) << std::endl;
            }

            sqlite3_finalize(stmtPlateauJetonColors);
        }
    }

    }

/*
 *
 /$$    /$$                                                            /$$$$$
| $$   | $$                                                              |__  $$
| $$   | $$       /$$   /$$        /$$$$$$                        | $$        /$$$$$$        /$$     /$$
|  $$ / $$/      | $$  | $$       /$$__  $$                        | $$       /$$__  $$      | $$      | $$
 \  $$ $$/       | $$  | $$      | $$$$$$$$             /$$  | $$      | $$$$$$$$      | $$     | $$
  \  $$$/        | $$  | $$      | $$_____/               | $$  | $$      | $$_____/         | $$      | $$
   \  $/         |  $$$$$$/      |  $$$$$$$            |  $$$$$$/      |  $$$$$$$      |  $$$$$$/
    \_/           \______/        \_______/                  \______/        \_______/          \______/
 */


// ----------------------- Partie Vue Jeu --------------------
VueJeu::VueJeu(Jeu* jeu, QWidget *parent): QWidget(parent),jeu(jeu){

    // ---------------- bg color ------------
    //setStyleSheet("background-color: #736f72;");


    // ---------------------- init bdd  ---------------------
    if (sqlite3_open("../base.db", &db) != SQLITE_OK) {
        std::cerr << "Can't open database, from VueJeu constructor: " ;
        std::cerr<< sqlite3_errmsg(db) << std::endl;
    }

    // --------------------- init pioches et cartes -----------------
    cartesJoaillerie = std::vector<CarteJoaillerie*>(0);
    pioche1 = new Pioche(1, 5, 31);
    pioche2 = new Pioche(2, 4, 24);
    pioche3 = new Pioche(3, 3, 13);
    pioches  = std::vector<Pioche*>(0);
    initCarteJoaillerieNonConst(db, &cartesJoaillerie);
    int niveau = 1;
    const CarteJoaillerie* tmp = nullptr;
    for (int i = 0; i < 30 ; i ++) {
        tmp = pioche1->setCartesDansPioche(cartesJoaillerie[i], i);
        if (tmp == nullptr) std::cerr<<"---- init VueJeu : CarteJo nulle\n";
    }
    niveau++;
    for (int i = 30; i < 54 ; i ++) {
        tmp = pioche2->setCartesDansPioche(cartesJoaillerie[i], i-30);
        if (tmp == nullptr) std::cerr<<"---- init VueJeu : CarteJo nulle\n";
    }
    niveau++;
    int index_dans_pioche3 = 0;
    for (int i_ = 54; i_ < 67 ; i_ ++) {
        tmp = pioche3->setCartesDansPioche(cartesJoaillerie[i_], index_dans_pioche3);
        if (tmp == nullptr) std::cerr<<"---- init VueJeu : CarteJo nulle\n";
        index_dans_pioche3++;
        tmp = nullptr;
    }

    pioche1->distribution();
    pioche2->distribution();
    pioche3->distribution();

    pioches.push_back(pioche1);
    pioches.push_back(pioche2);
    pioches.push_back(pioche3);

    // ---------------- init layout ----------------
    layout_bas = new QHBoxLayout();
    layout_centre = new QHBoxLayout();
    layout_main = new QVBoxLayout(this);
    layout_jeu = new QVBoxLayout();
    layout_menu = new QVBoxLayout();
    layout_pioche = new QHBoxLayout();



    // --------------- menu --------------------
    bouton_nouvelle_partie = new QPushButton("Nouvelle partie");
    QObject::connect(
            bouton_nouvelle_partie,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonNouvellePartie
    );
    bouton_nouvelle_partie->show();
    bouton_charger_partie = new QPushButton("Charger partie en cours");
    QObject::connect(
            bouton_charger_partie,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonChargerPartie
    );
    bouton_charger_partie->show();
    layout_menu->addWidget(bouton_nouvelle_partie);
    layout_menu->addWidget(bouton_charger_partie);

    layout_main->addLayout(layout_menu);

    setLayout(layout_main);
}

void VueJeu::dessinerPartie() {
    // ------------ init bouton sauvegarder -------------
    bouton_sauvegarde = new QPushButton("Sauvegarder la partie");
    QObject::connect(
            bouton_sauvegarde,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonSauvegardeClick
    );
    bouton_sauvegarde->show();

    // ------------------ layout centre --------------
    layout_centre->addWidget(vueJoueur1);
    layout_centre->addWidget(vueJoueur2);



    // ---------------------- update widgets ------------------
    setJoueurActuelInfo();
    vueJoueur1->displayCartes();
    vueJoueur2->displayCartes();
    vueJoueur1->show();
    vueJoueur2->show();

    // ---------------- Layout Choix Action ---------------
    layout_choix_actions = new QVBoxLayout();
    layout_top = new QHBoxLayout();

    // ------------- connecter les layouts -------------
    layout_choix_actions->addWidget(bouton_sauvegarde);

    vue_pioche = new VuePioche(pioche1, pioche2, pioche3, cartesJoaillerie, this);

    afficherChoix();

    layout_pioche->addWidget(vue_plateau);
    //layout_top->addLayout(layout_choix_actions);
    layout_pioche->addWidget(vue_pioche);
    layout_top->addLayout(layout_choix_actions);
    layout_top->addLayout(layout_pioche);
    layout_jeu->addLayout(layout_top);
    layout_jeu->addLayout(layout_centre);
    layout_jeu->addLayout(layout_bas);

}

void VueJeu::choixDesJoueurs() {
    bouton_joueur_joueur = new QPushButton("Joueur VS Joueur");
    QObject::connect(
            bouton_joueur_joueur,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonJoueurJoueur
    );
    bouton_joueur_joueur->show();

    bouton_joueur_IA = new QPushButton("Joueur VS IA");
    QObject::connect(
            bouton_joueur_IA,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonJoueurIA
    );
    bouton_joueur_IA->show();

    bouton_IA_IA = new QPushButton("IA VS IA");
    QObject::connect(
            bouton_IA_IA,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonIAIA
    );
    bouton_IA_IA->show();

    layout_choix_joueurs = new QVBoxLayout();
    layout_choix_joueurs->addWidget(bouton_joueur_joueur);
    layout_choix_joueurs->addWidget(bouton_joueur_IA);
    layout_choix_joueurs->addWidget(bouton_IA_IA);
}

void VueJeu::afficherChoix() {
    bouton_depenser_privilege = new QPushButton("Dépenser Privilege");
    bouton_prendre_jeton = new QPushButton("Prendre jeton");
    bouton_acheter_carte = new QPushButton("Acheter carte");
    bouton_reserver_carte = new QPushButton("Réserver carte");
    bouton_remplir_plateau = new QPushButton("Remplir plateau");
    bouton_valider = new QPushButton("Valider\naction");

    // connect
    QObject::connect(
            bouton_depenser_privilege,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonActionPrivilege
    );
    QObject::connect(
            bouton_prendre_jeton,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonPrendreJeton
    );

    QObject::connect(
            bouton_remplir_plateau,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonRemplirPlateau
    );
    QObject::connect(
            bouton_acheter_carte,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonAcheterCarte
    );
    QObject::connect(
            bouton_reserver_carte,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonReserverCarte
    );
    QObject::connect(
            bouton_valider,
            &QPushButton::clicked,
            this,
            &VueJeu::boutonValiderAction
    );

    bouton_depenser_privilege->show();
    bouton_prendre_jeton->show();
    bouton_acheter_carte->show();
    bouton_reserver_carte->show();
    bouton_remplir_plateau->show();
    bouton_valider->show();

    setEtatBoutonPrivilege();

    layout_choix_actions->addWidget(bouton_depenser_privilege);
    layout_choix_actions->addWidget(bouton_prendre_jeton);
    layout_choix_actions->addWidget(bouton_acheter_carte);
    layout_choix_actions->addWidget(bouton_reserver_carte);
    layout_choix_actions->addWidget(bouton_remplir_plateau);
    layout_choix_actions->addWidget(bouton_valider);
}

void VueJeu::setEtatBoutonPrivilege() {
    if (jeu->getJoueurActuel()->hasPrivilege()) {
        bouton_depenser_privilege->setEnabled(true);
    } else {
        bouton_depenser_privilege->setEnabled(false);
    }
}

void VueJeu::deleteLayout(QLayout* layout) {
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QLayout*layout= item->layout()) {
            while (QLayoutItem *itemL = layout->takeAt(0)) {
                if (QWidget *widget = itemL->widget()) {
                    widget->deleteLater();
                }
                delete itemL;
            }
            layout->deleteLater();
        }
        delete item;
    }
}

void VueJeu::boutonNouvellePartie() {
    // ------------------ init vuePlateau ------------
    vue_plateau = new VuePlateau(this);

    // ------------------- init partie --------------------
    deleteLayout(layout_main);
    this->choixDesJoueurs();
    layout_main->addLayout(layout_choix_joueurs);
    setLayout(layout_main);
    repaint();
}

void VueJeu::boutonJoueurJoueur() {
    this->initJoueurs(true, true);
    deleteLayout(layout_main);
    this->dessinerPartie();
    layout_main->addLayout(layout_jeu);
    setLayout(layout_main);
    repaint();
}

void VueJeu::boutonValiderAction() {
    if (action_en_cours == 1) {
        //if (checkPlateau()) {
            vue_plateau->getPlateau()->remplissagePlateau();
            vue_plateau->affichageJetons();
        //}
    } else if (action_en_cours == 2) {
        vue_plateau->actionValiderSelection();
    }else if (action_en_cours == 3) {
        vue_pioche->validerCarte();
    }
}

void VueJeu::boutonJoueurIA() {
    this->initJoueurs(true, false);
    deleteLayout(layout_main);
    this->dessinerPartie();
    layout_main->addLayout(layout_jeu);
    setLayout(layout_main);
    repaint();
}

void VueJeu::boutonIAIA() {
    this->initJoueurs(false, false);
    deleteLayout(layout_main);
    this->dessinerPartie();
    layout_main->addLayout(layout_jeu);
    setLayout(layout_main);
    repaint();
}

void VueJeu::initJoueurs(bool j1EstHumain, bool j2EstHumain) {
    // --------------------- init joueurs --------------
    if (j1EstHumain) j1 = new Humain("Joueur 1 Humain");
    else j1 = new IA("Joueur 1 IA", Difficulte::aleatoire);
    if (j2EstHumain) j2 = new Humain("Joueur 2 Humain");
    else j2 = new IA("Joueur 2 IA", Difficulte::aleatoire);
    jeu->setJoueurActuel(j1);
    jeu->setVueJeu(this);
    vueJoueur1 = new FenetreInformations(j1);
    vueJoueur2 = new FenetreInformations(j2);
    j1->setInfo(vueJoueur1);
    j2 ->setInfo(vueJoueur2);
}

void VueJeu::boutonChargerPartie() {
    // ------------------ init vuePlateau ------------
    vue_plateau = new VuePlateau(this);

    // ----------------- Load dernière partie ------------
    // Récupération du vecteur cartes nobles
    std::vector<const CarteNoble*> cartesNoble = vue_plateau->getPlateau()->getCartesNobles();

    deleteLayout(layout_main);

    // Load partie
    std::vector<Joueur*> joueurs =  continuerLaPartie(
            db,
            cartesJoaillerie,
            cartesNoble,
            jeu,
            pioches,
            *vue_plateau->getPlateau(),
            vue_plateau->getPlateau()->getPrivileges()
    );

    jeu->setVueJeu(this);
    j1 = joueurs[0];
    j2 = joueurs[1];
    vueJoueur1 = new FenetreInformations(j1);
    vueJoueur2 = new FenetreInformations(j2);
    j1->setInfo(vueJoueur1);
    j2 ->setInfo(vueJoueur2);

    // ---------- MIse a jour  des composants------------
    vue_plateau->affichageJetons(false);
    vue_plateau->affichageCartes();
//    vueJoueur1->miseAJourInformations();
//    vueJoueur2->miseAJourInformations();

    this->dessinerPartie();
    layout_main->addLayout(layout_jeu);
    setLayout(layout_main);
    repaint();

    std::cout<<vue_plateau->getPlateau()->etatPlateau();
}

void VueJeu::boutonSauvegardeClick() {
    /*
     * Méthode appelée pour sauvegarder la partie en cours, quand le bouton
     * est appuyé.
     */
    sauvegarderPartie(db, *jeu, *j1,*j2, &pioches, *vue_plateau->getPlateau());
}

void VueJeu::boutonActionPrivilege() {
    if (checkPlateau()) return;
    desactiverOuActiverBouton(false);
    Plateau* p = vue_plateau->getPlateau();
    vue_plateau->getPlateau()->setMaxSelectionPossible(1, false, false) ;
    vue_plateau->affichageJetons(true);
    finiAction(0);
}

void VueJeu::boutonRemplirPlateau() {
    if (checkPlateau()) return;
    Plateau* plateau = vue_plateau->getPlateau();
    bool a_rempli = plateau->remplissagePlateau();
   if (a_rempli) {
       desactiverOuActiverBouton(false);
        bouton_depenser_privilege->setEnabled(false);
        vue_plateau->affichageJetons();
    } else {
       message("Action", "Le plateau est déjà rempli !");
   }
    std::cout<<vue_plateau->getPlateau()->etatPlateau();
    finiAction(1);
}

void VueJeu::boutonAcheterCarte() {
    desactiverOuActiverBouton(false);
    if (checkPlateau()) {
        //vue_plateau->affichageJetons(false);
        vue_plateau->desactiverOuActiverLesJetons(false);
    }
    vue_pioche->setStatutActif(true);
    action_en_cours= 3;
    //finiAction(3);
}

void VueJeu::boutonReserverCarte() {
    if (checkPlateau()) return;
    desactiverOuActiverBouton(false);
    vue_plateau->getPlateau()->setMaxSelectionPossible(1, true) ;
    //vue_plateau->affichageJetons(true);
    vue_plateau->desactiverOuActiverLesJetons(false);
    //finiAction(4);
}

void VueJeu::boutonPrendreJeton() {
    desactiverOuActiverBouton(false);
    if (checkPlateau()) return;
    Plateau* p = vue_plateau->getPlateau();
    p->setMaxSelectionPossible(3, false);
    vue_plateau->affichageJetons(true);
    action_en_cours = 2;
    //finiAction(2);
}

void VueJeu::desactiverOuActiverBouton(bool etat) {
    bouton_depenser_privilege->setEnabled(etat);
    bouton_acheter_carte->setEnabled(etat);
    bouton_remplir_plateau->setEnabled(etat);
    bouton_reserver_carte->setEnabled(etat);
    bouton_prendre_jeton->setEnabled(etat);
}

void VueJeu::setJoueurActuelInfo() {
    Joueur* j = jeu->getJoueurActuel();
    vueJoueur1->setJoueurCourrant(j);
    vueJoueur2->setJoueurCourrant(j);
    // mise à jour déjà faite dans setJoueurCourrant
    vueJoueur2->miseAJourInformations();
    vueJoueur1->miseAJourInformations();
}

void VueJeu::choixCarteNoble(bool ok_pour_choix) {
    peut_passer_tour_suivant=!ok_pour_choix;
    desactiverOuActiverBouton(!ok_pour_choix);
    vue_plateau->desactiverOuActiverLesJetons(!ok_pour_choix);
}

void VueJeu::finiAction(int action) {
    /**
     * 0 = dépenser privilège
     * 1 = remplissage plateau
     * 2 = prendre jeton
     * 3 = acheter carte
     * 4 = réservation
     * 5 utilisé également pour forcer la fin du tour
     */
    if (action == 0) {
        compteur_action_optionelles--;
        if (compteur_action_optionelles==0) {
            finiAction(5);
        }
    }else   if (action == 1) {
        a_fini_optionnelles = true;
        desactiverOuActiverBouton(true);
    } else if (action >=2) {
        jeu->verifCarteNoble(jeu->getJoueurActuel(), vue_plateau->getPlateau());
        if (!peut_passer_tour_suivant) return;
        a_fini_optionnelles = true;
        a_fini_obligatoires = true;
        desactiverOuActiverBouton(true);

        // Remise à défaut des paramètres de choix plateau :
        vue_plateau->getPlateau()->setMaxSelectionPossible(3,false) ;

        jeu->verifGagnant(j1, j2); // modifie le joueur actuelle

        // MIse à jour pour le joueur actuel
        setJoueurActuelInfo();
        if (action == 3 || action == 4 || action==5) {
            vue_pioche->setStatutActif(false);
            if (jeu->getJoueurActuel() == j1) {
                // Si le joueur actuel est 1, alors au moment de l'action passé,
                // le joueur qui a modiié ses cartes est le joueur 2.
                vueJoueur2->displayCartes();
            } else {
                vueJoueur1->displayCartes();
            }
        }

        if (jeu->getJoueurGagnant() == nullptr) {
            // Tour suivant
            setEtatBoutonPrivilege();
            setJoueurActuelInfo();
        } else {
            // ----------------Popup pour gagnat ici ! ----------------
            //
        }

    }

}

void VueJeu::message(const char  title[], const char  texte[]) {
    QMessageBox::warning(nullptr, title, texte);
}

//int main() {
//    sqlite3* db;
//    if (sqlite3_open("path_to_your_database.db", &db) != SQLITE_OK) {
//        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//        return -1;
//    }
//
//    clearAndInitializeTables(db);
//
//    // Close the database connection
//    sqlite3_close(db);
//    return 0;
//}






