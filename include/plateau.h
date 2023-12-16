//
// Created by alexa on 24/10/2023.
//

#ifndef SPLENDOR_PLATEAU_H
#define SPLENDOR_PLATEAU_H

#include <iostream>
#include <tuple>
#include <QGridLayout>
#include <vector>
#include <sqlite3.h>

#include "privilege.h" // safe
#include "jeton.h" // safe
//#include "jeu.h"
//#include "carte.h"
//#include "carteNoble.h"

class CarteNoble;
class Jeu;
class Jeton;
class Privilege;
class QPushButton;
class VueJeton;
class VuePlateau;
class VueCarteNoble;

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
    Privilege** privileges;
    const Jeton** sac;
    std::vector<const CarteNoble*> cartes_nobles;
    unsigned int nb_jetons_sac;
    unsigned int nb_jetons_plateau;
    unsigned int pointeur_case_libre = 0;
    unsigned int nb_privileges;
    unsigned int nb_carte_noble;


    const Jeton** selection_courante;
    int* selection_courante_positions;
    unsigned int nombre_jetons_dans_selection = 0;

    // Constantes
    unsigned int nombre_jetons_par_cote_de_plateau = 5;
    unsigned int nombre_jetons_dans_selection_MAX = 3;
    unsigned int nb_jetons_sac_MAX = 25;
    unsigned int nb_privileges_MAX = 3;
    unsigned int nb_jetons_plateau_MAX = 25;
    unsigned int nb_cartes_nobles_MAX = 4;

    int matrix[5][5] = {25, 10, 11, 12, 13,
                        24, 9, 2, 3, 14,
                        23, 8, 1, 4, 15,
                        22, 7, 6, 5, 16,
                        21, 20, 19, 18, 17};


    // VuePlateau utilisé pour mettre à jour l'affichage du plateau
    VuePlateau* vuePlateau;

    // Utilisé en interne par donnePositionsAPartirDe().
    std::vector<unsigned int> parcoursPlateauVerificationPosition(unsigned int x, unsigned int y, int coefX, int coefY );


    friend class VuePlateau;
    //const Jeton* getJeton(unsigned int i) const  {return jetons[i];}
public:
    bool verificationSelectionPositions()const;
    const Jeton* getJeton(unsigned int i) const  {return jetons[i];}
    // A mettre en privé plus tard :


    Plateau(sqlite3** db= nullptr, VuePlateau* vp = nullptr);
    friend class Jeu;

    void remplissagePlateau(bool avecAffichage = false);
    std::string etatPlateau();
    void ajouterSac(const Jeton *j);

    int selectionJeton(unsigned int position_x, unsigned int position_y);
    std::vector<const Jeton*> validerSelectionEtPrendreJetons();
    const Jeton* prendreJeton(unsigned int position_x, unsigned int position_y);

    const Privilege* prendrePrivilege();
    void donnePrivilege(Privilege* p);
    const CarteNoble* prendreCarteNoble(unsigned int numero);

    bool hasJeton(); // Vérifiez s'il y a jeton en plateau

    ~Plateau();

    // Usefull for Optionnelle and Obligatoire
    unsigned int getNbJetonsPlateau() const { return nb_jetons_plateau; }
    unsigned int getNbJetonsPlateauMAX() const { return nb_jetons_plateau_MAX; }
    unsigned int getNbJetonsSac() const { return nb_jetons_sac; }
    unsigned int getNbPrivilegeMAX() const { return nb_privileges_MAX; }
    unsigned int getNbPrivileges() const { return nb_privileges; }
    unsigned int getPointeurCaseLibre() const { return pointeur_case_libre; }
    unsigned int getNbCarteNoble() const { return nb_carte_noble; }
    bool hasJetonOr(); // Vérifier qu'il y a au moins un jeton or sur le plateau
    void setNbJetonsSac(int nbJetons) { nb_jetons_sac = nbJetons; }
    void setNbJetonsPlateau(int nbJetons) { nb_jetons_plateau = nbJetons; }
    void setPointeurCaseLibre(int nbPointeur) { pointeur_case_libre = nbPointeur; }
    void setNbPrivileges(int nbPriv) { nb_privileges = nbPriv; }
    void setNbCarteNoble(int nbCarteNoble) { nb_carte_noble = nbCarteNoble; }
    void setSac(const std::vector<const Jeton*>& newSac) {
        delete[] sac;
        sac = new const Jeton*[newSac.size()];
        for (size_t i = 0; i < newSac.size(); ++i) { sac[i] = newSac[i]; }
        nb_jetons_sac = static_cast<unsigned int>(newSac.size());
    }

    std::vector<const Jeton*> getSac() const {
        std::vector<const Jeton*> sacCopy;
        for (unsigned int i = 0; i < nb_jetons_sac; ++i) { sacCopy.push_back(sac[i]); }
        return sacCopy;
    }

    void setJetons(const std::vector<const Jeton*>& newJetons) {
        delete[] jetons;
        jetons = new const Jeton*[newJetons.size()];
        for (size_t i = 0; i < newJetons.size(); ++i) { jetons[i] = newJetons[i]; }
        nb_jetons_plateau = static_cast<unsigned int>(newJetons.size());
    }

    std::vector<const Jeton*> getJetons() const {
        std::vector<const Jeton*> jetonsCopy;
        for (unsigned int i = 0; i < nb_jetons_plateau; ++i) { jetonsCopy.push_back(jetons[i]); }
        return jetonsCopy;
    }

    void setCartesNobles(const std::vector<const CarteNoble*>& newCartesNobles) {
        cartes_nobles.clear();
        cartes_nobles =  std::vector<const CarteNoble*>(newCartesNobles.size());
        for (size_t i = 0; i < newCartesNobles.size(); ++i) { cartes_nobles[i] = newCartesNobles[i]; }
        nb_carte_noble = static_cast<unsigned int>(newCartesNobles.size());
    }

    std::vector<const CarteNoble*> getCartesNobles() const {
        std::vector<const CarteNoble*> cartesNoblesCopy(0);
        for (unsigned int i = 0; i < nb_carte_noble; i++) {
            const CarteNoble* cn  = cartes_nobles.at(i);
            cartesNoblesCopy.push_back(cn);
        }
        return cartesNoblesCopy;
    }

    void setPrivileges(const std::vector<Privilege*>& newPrivileges) {
        delete[] privileges;
        privileges = new Privilege*[newPrivileges.size()];
        for (size_t i = 0; i < newPrivileges.size(); ++i) { privileges[i] = newPrivileges[i]; }
        nb_privileges = static_cast<unsigned int>(newPrivileges.size());
    }

    std::vector<Privilege*> getPrivileges() const {
        std::vector<Privilege*> privilegesCopy;
        for (unsigned int i = 0; i < nb_privileges; i++) {
            std::cout<<"privilege ";
            privilegesCopy.push_back(privileges[i]);
        }
        std::cout<<"\returned\n";
        return privilegesCopy;
    }

    std::vector<std::vector<unsigned  int>>  donnePositionsPossiblesAPartirDe(unsigned int x, unsigned int y);
};

std::tuple<int, int> choisir_jeton();

void testes_pour_plateau();






class VuePlateau : public QWidget {
Q_OBJECT
public:
    explicit VuePlateau(QWidget *parent = nullptr);
    Plateau* getPlateau() {return plateau;}

    void affichageJetons(); // à appeler si chargement mémoire

private:
    Plateau* plateau;
    QGridLayout* layout_bouton;
    QGridLayout* layout_carte;
    QHBoxLayout* layout_info;
    QVBoxLayout* main_layout;
    QHBoxLayout* layout_privilege;
    std::vector<VueJeton*> vuesJetons;
    std::vector<VueCarteNoble*> vuesCartes;
    QPushButton* boutonValider;
    QPushButton* boutonRemplissage;
    QPushButton* boutonDonnerPrivilege;
    std::vector<VuePrivilege*> vuesPrivileges;

    void miseAJourJetons();
    void affichageCartes();
    void affichagePrivileges();
    friend class Plateau;

private slots:
    void jetonClick_Plateau(VueJeton*) ;//{ std::cout<<"Clicked!\n"; }
    void validerPlateau();
    void remplirPlateau();
    void privilegeClick_Plateau(VuePrivilege*);
    void carteNobleClick_Plateau(VueCarteNoble*);
    //void donnerPrivilege(const Privilege* p);

};

#endif //SPLENDOR_PLATEAU_H
