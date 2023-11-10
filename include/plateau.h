//
// Created by alexa on 24/10/2023.
//

#ifndef SPLENDOR_PLATEAU_H
#define SPLENDOR_PLATEAU_H

#include <iostream>
#include <tuple>

#include "privilege.h" // safe
#include "jeton.h" // safe
#include "carteNoble.h"

class CarteNoble;

class Jeu{
public:
    Jeu();
};

class PlateauException {
    std::string info;
public:
    PlateauException(const std::string& s): info(s) {}
    const std::string& get_info() const {return info;}
};

struct ReponseValidationSelection {
    const Jeton** jetons;
    unsigned int nombre;
};

class Plateau {
    const Jeton** jetons;
    const Privilege** privileges;
    const Jeton** sac;
    const CarteNoble** cartes_nobles;
    unsigned int nb_jetons_sac;
    unsigned int nb_jetons_plateau;
    unsigned int pointeur_case_libre = 0;
    unsigned int nb_privileges;
    unsigned int nb_carte_noble = 4;


    const Jeton** selection_courante;
    int* selection_courante_positions;
    unsigned int nombre_jetons_dans_selection = 0;

    // Constantes
    unsigned int nombre_jetons_par_cote_de_plateau = 5;
    unsigned int nombre_jetons_dans_selection_MAX = 3;
    unsigned int nb_jetons_sac_MAX = 25;
    unsigned int nb_privileges_MAX = 3;
    unsigned int nb_jetons_plateau_MAX = 25;

    bool verificationSelectionPositions();


public:

    // A mettre en privé plus tard :
    Plateau();
    friend class Jeu;

    void remplissagePlateau(bool avecAffichage = false);
    std::string etatPlateau();
    void ajouterSac(const Jeton *j);

    void selectionJeton(unsigned int position_x, unsigned int position_y);
    ReponseValidationSelection validerSelectionEtPrendreJetons();
    const Jeton prendreJeton(unsigned int position_x, unsigned int position_y);

    const Privilege* prendrePrivilege();
    void donnePrivilege(const Privilege* p);
    const CarteNoble* prendreCarteNoble(unsigned int numero);

    bool hasJeton(); // Vérifiez s'il y a jeton en plateau

    ~Plateau();


};

std::tuple<int, int> choisir_jeton();

void testes_pour_plateau();


#endif //SPLENDOR_PLATEAU_H
