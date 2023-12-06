//
// Created by alexa on 24/10/2023.
//

#ifndef SPLENDOR_PLATEAU_H
#define SPLENDOR_PLATEAU_H

#include <iostream>
#include <tuple>
#include <QGridLayout>
#include <vector>

#include "privilege.h" // safe
#include "jeton.h" // safe
//#include "carteNoble.h"

class CarteNoble;
class Jeu;

class PlateauException {
    std::string info;
    friend class Jeu;
public:
    PlateauException(const std::string& s): info(s) {}
    const std::string& get_info() const {return info;}
};

struct ReponseValidationSelection {
    const Jeton** jetons;
    unsigned int nombre;
    ReponseValidationSelection(const Jeton** j, unsigned int n):
    jetons(j), nombre(n) {}
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

    int matrix[5][5] = {25, 10, 11, 12, 13,
                        24, 9, 2, 3, 14,
                        23, 8, 1, 4, 15,
                        22, 7, 6, 5, 16,
                        21, 20, 19, 18, 17};


    //bool verificationSelectionPositions();

    friend class VuePlateau;
    //const Jeton* getJeton(unsigned int i) const  {return jetons[i];}
public:
    bool verificationSelectionPositions()const;
    const Jeton* getJeton(unsigned int i) const  {return jetons[i];}
    // A mettre en privé plus tard :
    Plateau();
    friend class Jeu;

    void remplissagePlateau(bool avecAffichage = false);
    std::string etatPlateau();
    void ajouterSac(const Jeton *j);

    int selectionJeton(unsigned int position_x, unsigned int position_y);
    std::vector<const Jeton*> validerSelectionEtPrendreJetons();
    const Jeton* prendreJeton(unsigned int position_x, unsigned int position_y);

    const Privilege* prendrePrivilege();
    void donnePrivilege(const Privilege* p);
    const CarteNoble* prendreCarteNoble(unsigned int numero);

    bool hasJeton(); // Vérifiez s'il y a jeton en plateau

    ~Plateau();

    // Usefull for Optionnelle and Obligatoire
    unsigned int getNbJetonsPlateau() const { return nb_jetons_plateau; }
    unsigned int getNbJetonsPlateauMAX() const { return nb_jetons_plateau_MAX; }
    unsigned int getNbJetonsSac() const { return nb_jetons_sac; }
    unsigned int getNbPrivilegeMAX() const { return nb_privileges_MAX; }
    unsigned int getNbPrivileges() const { return nb_privileges; }
    bool hasJetonOr(); // Vérifier qu'il y a au moins un jeton or sur le plateau

    std::vector<std::vector<unsigned  int>>  donnePositionsPossiblesAPartirDe(unsigned int x, unsigned int y);
};

std::tuple<int, int> choisir_jeton();

void testes_pour_plateau();

class VuePlateau : public QWidget {
Q_OBJECT
public:
    explicit VuePlateau(QWidget *parent = nullptr);
private:
    Plateau* plateau = nullptr;
    QGridLayout* layout_bouton;
    QHBoxLayout* layout_info;
    QVBoxLayout* main_layout;
    std::vector<VueJeton*> vuesJetons;
    QPushButton* boutonValider;
    QPushButton* boutonRemplissage;

    void miseAJourJetons();
    void affichageJetons();

private slots:
    void jetonClick_Plateau(VueJeton*) ;//{ std::cout<<"Clicked!\n"; }
    void validerPlateau();
    void remplirPlateau();

};

#endif //SPLENDOR_PLATEAU_H
