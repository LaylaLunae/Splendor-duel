
#include <iostream>
#include "../include/jeu.h"

#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()

int IA::choisirChoix(int min, int max) {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int choix = rand() % max + 1;

    if (choix < min || choix > max) {
        choix = choisirChoix(min, max);
    }
    return choix;
}




IA::~IA() {}




std::vector<std::pair<const Jeton*, const Jeton*>> IA::genererCombinaisonsDeuxJetons(Plateau* plateau) {
    std::vector<std::pair<const Jeton*, const Jeton*>> combinaisons;

    // Parcourir le plateau de jetons
    for (unsigned int i = 0; i < plateau->getNbJetonsPlateauMAX(); ++i) {
        const Jeton* jeton1 = plateau->getJeton(i);

        // Obtenir les positions possibles pour le jeton1
        unsigned int x = i / 5;
        unsigned int y = i % 5;
        std::vector<std::vector<unsigned int>> positionsPossibles = plateau->donnePositionsPossiblesAPartirDe(x, y);

        // Insérer les positions possibles dans un vecteur global
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

            int selectionResult = plateau->selectionJeton(posX, posY);

            if (selectionResult == 0) {
                const Jeton* jeton2 = plateau->getJeton(posX * 5 + posY);

                // Ajouter la paire de jetons
                combinaisons.push_back({jeton1, jeton2});
            }
            else if (selectionResult == 2) {  // Trois jetons de la même couleur
                const Privilege* privilege = plateau->adversairePrendPrivilege();

            } else if (selectionResult == 5) {  // Deux perles

                const Privilege* privilege = plateau->adversairePrendPrivilege();

            }
        }
    }

    plateau->validerSelectionEtPrendreJetons();

    return combinaisons;
}








void IA::prendreJetons(Plateau* plateau) {
    if (!plateau->hasJeton()) {
        Optionnelle::remplissagePlateau(this, plateau);
    }

    // Calculer le nombre actuel de jetons
    int nombreJetonsActuel = std::accumulate(nb_jeton.begin(), nb_jeton.end(), 0);

    int choix;

    // L'IA peut prendre 1 jeton si elle a moins de 10 jetons
    if (nombreJetonsActuel ==9) {
        choisirJetonSurPlateau(plateau);
    }

    if(nombreJetonsActuel ==8){
        choix = choisirChoix(1, 2);
        if(choix==1)
            choisirJetonSurPlateau(plateau);
        else
            std::vector<std::pair<const Jeton*, const Jeton*>> combinaisonsDeux = genererCombinaisonsDeuxJetons(*plateau);
    }
    else {
        int choix = choisirChoix(1, 3);

        if (choix == 1)
            choisirJetonSurPlateau(plateau);

        else if (choix == 2)
            std::vector<std::pair<const Jeton*, const Jeton*>> combinaisonsDeux = genererCombinaisonsDeuxJetons(*plateau);


        else if (choix == 3)
            std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisonsTrois = genererCombinaisonsTroisJetons(*plateau);

    }
}

