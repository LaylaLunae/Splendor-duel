#include <iostream>
#include "../include/jeu.h"
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <vector>
#include <algorithm>
#include <random>

class Plateau;
// cette fonction permet à l'IA de faire tous ces choix de manière aléatoire
int IA::choisirChoix(int min, int max) {
    int choix = rand() % max + 1;

    if (choix < min || choix > max) {
        choix = choisirChoix(min, max);
    }
    return choix;
}
//Cette fonction permet de mettre dans un vecteur toutes les cartes que l'IA peut acheter en fonction des ressources qu'elle possède.
//Cette fonction utilise les fonctions de la classe obligatoire afin de ne pas re-coder deux fois la même fonction.

std::vector<CarteJoaillerie*> IA::getCartesAchetable(const Pioche& pioche) const {
    std::vector<CarteJoaillerie*> cartesAchetable;
    for (int i = 0; i < pioche.getMaxCartesRevelees(); ++i) {   // parcourt toutes les cartes disponibles
        const CarteJoaillerie* carte = pioche.getCartesDehors(i);
        if (carte) {
            std::vector<int> difference = Obligatoire::calculDifference((Joueur *) this, carte->getPrix());
            if (Obligatoire::achatPiochePossible((Joueur *) this, const_cast<Pioche*>(&pioche))) {
                cartesAchetable.push_back(const_cast<CarteJoaillerie*>(carte));  // on ajout dans le vecteur si l'IA peut acheter la carte
            }
        }
    }
    return cartesAchetable;
}

//Cette fonction récupère le vecteur qui contient toutes les cartes que l'IA peut acheter, mélange le vectoeur et retroune la dernière carte
// Cette denrière carte sera ensuite acheter par l'utilisateur, les ressources correspondantes remises dans le sac, les bonus et les pouvoirs activés et ajouté au joueur.

CarteJoaillerie* IA::melangerEtObtenirDerniereCarte(Pioche& pioche, Joueur& joueur, Plateau& plateau) {
    if (pioche.getMaxCartesRevelees() == 0 || pioche.getCartesDehors(0) == nullptr) {
        return nullptr;
    }
    std::random_device rd;  // cela permet de créer le génèrateur pour mélanger ensuite le vecteur
    std::default_random_engine generator(rd());

    std::vector<CarteJoaillerie*> cartesAchetable = getCartesAchetable(pioche);
    if (cartesAchetable.empty()) {
        return nullptr;
    }
    std::shuffle(cartesAchetable.begin(), cartesAchetable.end(), generator);
    CarteJoaillerie* derniereCarte = cartesAchetable.back();    // on retir la carte du vecteur

    for (const auto& cout : derniereCarte->getPrix()) {
        if (cout.second > 0) {
            // on remet les jetons utilisés dans le sac
            Obligatoire::remettreJetonSac(&joueur, &plateau, cout.first, joueur.getNbJeton((int) cout.first) - cout.second, cout.second,(int) cout.first);
        }
    }
    joueur.ajouterCarteJoaillerie(*derniereCarte);  // on ajoute à la main du joueur les bonus

    auto* carte_non_const = const_cast<CarteJoaillerie*>(derniereCarte);
    carte_non_const->actionPouvoir(&plateau, &joueur);
    return derniereCarte;
}

//Cette fonction met dans un vecteur toutes les combinaisons de deux jetons que l'IA à le droit de prendre.
// Ce vecteur est ensuite mélanger
// la dernier combinaison est ensuite retirer du vecteur, cette combinaison correspond à celle que va prendre l'IA.
std::vector<std::pair<const Jeton*, const Jeton*>> IA::genererCombinaisonsDeuxJetons(Plateau* plateau) {
    std::vector<std::pair<const Jeton*, const Jeton*>> combinaisons;

    // Parcourir le plateau de jetons
    for (unsigned int i = 0; i < plateau->getNbJetonsPlateauMAX(); ++i) {
        const Jeton* jeton1 = plateau->getJeton(i);

        // Obtenir les positions possibles pour le jeton1
        unsigned int x = i / 5;
        unsigned int y = i % 5;
// on utilise la fonction de plateau pour avoir toutes les combinaisons possible pour un jeton donné
        std::vector<std::vector<unsigned int>> positionsPossibles = std::vector<std::vector<unsigned int>>(0);
        for (auto vec : plateau->donnePositionsPossiblesAPartirDe(x, y)) {
            positionsPossibles.push_back(vec);
        }
        // Insérer les positions possibles dans un vecteur
        std::vector<std::pair<unsigned int, unsigned int>> positions;
        for (const auto& pos : positionsPossibles) {
            for (unsigned int j = 0; j < pos.size(); j += 2) {
                positions.push_back({pos[j], pos[j + 1]});
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(positions.begin(), positions.end(), g);

        // Parcourir le vecteur de positions et sélectionner deux jetons
        for (unsigned int k = 0; k < positions.size() && combinaisons.size() < 2; ++k) {
            unsigned int posX = positions[k].first;
            unsigned int posY = positions[k].second;
            const Jeton* jeton2 = plateau->getJeton(posX * 5 + posY);
// on utilise la fonction de plateau afin de faire la selection
            int selectionResult = plateau->selectionJeton(posX, posY);
            combinaisons.push_back({jeton1, jeton2});
// Si la selection possède de l'or, on recommence.
            if(selectionResult==2){
                return genererCombinaisonsDeuxJetons(plateau);
            }
            // s'il y a deux perles l'adeversaire prend un privilège.
            if (jeton1->getCouleur()==Couleur::rose && jeton2->getCouleur()==Couleur::rose) {
                Obligatoire::donnerPrivilegeAdversaire(this, plateau);
            }
        }
    }
    // on utilise la fonciton de plateau afin de valider la selection en cours.
    plateau->validerSelectionEtPrendreJetons();
    return combinaisons;
}

// Cette fonction est la même que la fonction précédente mais cetet fois-ci avec une combinaison de 3 jetons au lieu de 2.
std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> IA::genererCombinaisonsTroisJetons(Plateau* plateau) const {
    std::vector<std::tuple<const Jeton *, const Jeton *, const Jeton *>> combinaisons;
    // Parcourir le plateau de jetons
    for (unsigned int i = 0; i < plateau->getNbJetonsPlateauMAX(); ++i) {
        const Jeton *jeton1 = plateau->getJeton(i);

        // Obtenir les positions possibles pour le jeton1
        unsigned int x = i / 5;
        unsigned int y = i % 5;

        std::vector<std::vector<unsigned int>> positionsPossibles = std::vector<std::vector<unsigned int>>(0);
        for (auto vec: plateau->donnePositionsPossiblesAPartirDe(x, y)) {
            positionsPossibles.push_back(vec);
        }
        // Insérer les positions possibles dans un vecteur
        std::vector<std::pair<unsigned int, unsigned int>> positions;
        for (const auto &pos: positionsPossibles) {
            for (unsigned int j = 0; j < pos.size(); j += 2) {
                positions.push_back({pos[j], pos[j + 1]});
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(positions.begin(), positions.end(), g);

        // Parcourir le vecteur de positions et sélectionner deux jetons
        for (unsigned int k = 0; k < positions.size() && combinaisons.size() < 2; ++k) {
            unsigned int posX = positions[k].first;
            unsigned int posY = positions[k].second;
            const Jeton *jeton2 = plateau->getJeton(posX * 5 + posY);

            for(unsigned int l = 0; l<positions.size(); l++){
                unsigned int posX2 = positions[l].first;
                unsigned int posY2 = positions[l].second;
                const Jeton *jeton3 = plateau->getJeton(posX2 * 5 + posY2);

                int selectionResult = plateau->selectionJeton(posX2, posY2);
                combinaisons.push_back({jeton1, jeton2, jeton3});

                if(selectionResult==2){
                    return genererCombinaisonsTroisJetons(plateau);
                }
                if (jeton1->getCouleur()==Couleur::rose && jeton2->getCouleur()==Couleur::rose) {
                    Obligatoire::donnerPrivilegeAdversaire((Joueur *) this, plateau);
                }
            }
        }
    }
    plateau->validerSelectionEtPrendreJetons();
    return combinaisons;
}

// Cette fonction peremt à l'IA de choisir aléatoirement si elle souahite prendre 1, 2, ou 3 jetons.
// Cela est fait en fonction du nombre de jetons qu'elle possède et à l'aide de la fonction choisirChoix.
void IA::prendreJetons(Plateau* plateau) {
    if (!plateau->hasJeton()) {
        Optionnelle::remplissagePlateau(this, plateau);
    }
    // Calculer le nombre actuel de jetons
    int nombreJetonsActuel = std::accumulate(nb_jeton.begin(), nb_jeton.end(), 0);
    int choix;
// Si l'IA a déjà 9 jetons elle ne peut pas en prendre plus
    if (nombreJetonsActuel == 9) {
        choisirJetonSurPlateau(plateau);
    }
    // Si l'IA a déjà 8 jetons elle peut prendre soit 1 jetons soit 2 jetons mais pas 3.
    if (nombreJetonsActuel == 8) {
        choix = choisirChoix(1, 2);
        if (choix == 1)
            choisirJetonSurPlateau(plateau);
        else {
            std::vector<std::pair<const Jeton*, const Jeton*>> combinaisonsDeux = genererCombinaisonsDeuxJetons(plateau);
            std::vector<int> resultatAjout = Obligatoire::ajouterJetonsJoueur(this, {combinaisonsDeux[0].first, combinaisonsDeux[0].second});
        }
    }
    // SI l'IA a 7 ou moins de jetons elle peut en prendre autant qu'elle souhaite.
    else {
        choix = choisirChoix(1, 3);

        if (choix == 1)
            choisirJetonSurPlateau(plateau);
        else if (choix == 2) {
            std::vector<std::pair<const Jeton*, const Jeton*>> combinaisonsDeux = genererCombinaisonsDeuxJetons(plateau);

            std::vector<int> resultatAjout = Obligatoire::ajouterJetonsJoueur(this, {combinaisonsDeux[0].first, combinaisonsDeux[0].second});
        }
        else if (choix == 3) {
            std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisonsTrois = genererCombinaisonsTroisJetons(plateau);

            std::vector<int> resultatAjout = Obligatoire::ajouterJetonsJoueur(this, {std::get<0>(combinaisonsTrois[0]), std::get<1>(combinaisonsTrois[0]), std::get<2>(combinaisonsTrois[0])});
        }
    }
}

// Cette fonction permet à l'IA de prendre qu'un seul jetons disponible sur le plateau.
void IA::choisirJetonSurPlateau(Plateau* plateau) {
    int positionX = rand() % 5 ;
    int positionY = rand() % 5 ;

    int retour = plateau->selectionJeton(positionX, positionY);
    if (retour== 0) {  // sélection valide
        std::vector<const Jeton*> jetonsSelectionne = plateau->validerSelectionEtPrendreJetons();

        std::vector<const Jeton*> jetonsSelectionnes = {jetonsSelectionne[0]};
        std::vector<int> resultatsAjout = Obligatoire::ajouterJetonsJoueur(this, jetonsSelectionnes);
    }
    else
        // Dans le cas ou la selection n'est pas valide, comme par exmeple si le jeton choisi en premier lieu est un or on rappelle la fonction.
        choisirJetonSurPlateau(plateau);
}