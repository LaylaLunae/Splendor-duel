#include <iostream>
#include "../include/jeu.h"
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <vector>
#include <algorithm>
#include <random>

class Plateau;

int IA::choisirChoix(int min, int max) {

    //std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int choix = rand() % max + 1;

    if (choix < min || choix > max) {
        choix = choisirChoix(min, max);
    }
    return choix;
}


std::vector<CarteJoaillerie*> IA::getCartesAchetable(const Pioche& pioche) const {
    std::vector<CarteJoaillerie*> cartesAchetable;

    for (int i = 0; i < pioche.getMaxCartesRevelees(); ++i) {
        const CarteJoaillerie* carte = pioche.getCartesDehors(i);

        if (carte) {
            std::vector<int> difference = Obligatoire::calculDifference((Joueur *) this, carte->getPrix());

            if (Obligatoire::achatPiochePossible((Joueur *) this, const_cast<Pioche*>(&pioche))) {
                cartesAchetable.push_back(const_cast<CarteJoaillerie*>(carte));
            }
        }
    }
    return cartesAchetable;
}


CarteJoaillerie* IA::melangerEtObtenirDerniereCarte(Pioche& pioche, Joueur& joueur, Plateau& plateau) {
    if (pioche.getMaxCartesRevelees() == 0) {
        return nullptr;
    }
    std::vector<CarteJoaillerie*> cartesAchetable = getCartesAchetable(pioche);

    std::default_random_engine generator;
    std::shuffle(cartesAchetable.begin(), cartesAchetable.end(), generator);

    CarteJoaillerie* derniereCarte = cartesAchetable.back();

    // Remettre les jetons dans le sac
    for (const auto& cout : derniereCarte->getPrix()) {
        if (cout.second > 0) {
            Obligatoire::remettreJetonSac(&joueur, &plateau, cout.first, joueur.getNbJeton((int) cout.first) - cout.second, cout.second,(int) cout.first);
        }
    }
    joueur.ajouterCarteJoaillerie(*derniereCarte);
    activerPouvoir(reinterpret_cast<CarteJoaillerie &>(derniereCarte));
    return derniereCarte;
}

// Implémentation de la fonction activerPouvoir dans la classe IA
void IA::activerPouvoir(CarteJoaillerie& carte) {
    for (const auto& pouvoir : carte.existancePouvoir()) {
        switch (pouvoir) {
            case Pouvoir::nouveau_tour:
                //rejouer
                break;

            case Pouvoir::bonus_pierre:
                //
                break;

            case Pouvoir::pierre_en_plus:
                //
                break;

            case Pouvoir::privilege_en_plus:
                //
                break;

            case Pouvoir::vol_pierre:
                //
                break;
            default:
                //pas de pouvoir.
                break;
        }
    }
}



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
            const Jeton* jeton2 = plateau->getJeton(posX * 5 + posY);

            int selectionResult = plateau->selectionJeton(posX, posY);
            combinaisons.push_back({jeton1, jeton2});

            if (selectionResult == 2 || selectionResult == 5) {
                // Appel de la fonction donnerPrivilegeAdversaire de l'objet Obligatoire
                Obligatoire::donnerPrivilegeAdversaire(this, plateau);
            }
        }
    }
    plateau->validerSelectionEtPrendreJetons();

    return combinaisons;
}


std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> IA::genererCombinaisonsTroisJetons(Plateau *plateau) const {
    std::vector<std::tuple<const Jeton*, const Jeton*, const Jeton*>> combinaisons;

    // Parcourir le plateau de jetons
    for (unsigned int i = 0; i < plateau->getNbJetonsPlateauMAX(); ++i) {
        const Jeton* jeton1 = plateau->getJeton(i);

        // Obtenir les positions possibles pour le jeton1
        unsigned int x = i / 5;
        unsigned int y = i % 5;
        std::vector<std::vector<unsigned int>> positionsPossibles = plateau->donnePositionsPossiblesAPartirDe(x, y);

        // Insérer les positions possibles dans un vecteur
        std::vector<std::tuple<unsigned int, unsigned int, const Jeton*>> positions;
        for (const auto& pos : positionsPossibles) {
            for (unsigned int j = 0; j < pos.size(); j += 2) {
                unsigned int posX = pos[j];
                unsigned int posY = pos[j + 1];
                const Jeton* jeton2 = plateau->getJeton(posX * 5 + posY);
                positions.emplace_back(posX, posY, jeton2);
            }
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(positions.begin(), positions.end(), g);

        // Parcourir le vecteur de positions et sélectionner trois jetons
        for (unsigned int k = 0; k < positions.size() && combinaisons.size() < 3; ++k) {
            unsigned int posX2, posY2;
            const Jeton* jeton2;
            std::tie(posX2, posY2, jeton2) = positions[k];

            int selectionResult= plateau->selectionJeton(posX2, posY2);

            combinaisons.emplace_back(jeton1, jeton2, plateau->getJeton(posX2 * 5 + posY2));

            if (selectionResult == 2 || selectionResult == 5) {
                Obligatoire::donnerPrivilegeAdversaire((Joueur *) this, plateau);
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

    if (nombreJetonsActuel == 9) {
        choisirJetonSurPlateau(plateau);
    }
    if (nombreJetonsActuel == 8) {
        choix = choisirChoix(1, 2);
        if (choix == 1)
            choisirJetonSurPlateau(plateau);
        else {
            std::vector<std::pair<const Jeton*, const Jeton*>> combinaisonsDeux = genererCombinaisonsDeuxJetons(plateau);

            std::vector<int> resultatAjout = Obligatoire::ajouterJetonsJoueur(this, {combinaisonsDeux[0].first, combinaisonsDeux[0].second});
        }
    }
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


void IA::choisirJetonSurPlateau(Plateau* plateau) {

    int positionX = rand() % 5 + 1;
    int positionY = rand() % 5 + 1;

    if (plateau->selectionJeton(positionX, positionY) == 0) {  // sélection valide
        const Jeton* jetonSelectionne = plateau->getJeton(positionX * 5 + positionY);

        std::vector<const Jeton*> jetonsSelectionnes = {jetonSelectionne};
        std::vector<int> resultatsAjout = Obligatoire::ajouterJetonsJoueur(this, jetonsSelectionnes);
    }
    std::vector<const Jeton*> jetonsSelectionnes = plateau->validerSelectionEtPrendreJetons();
}
