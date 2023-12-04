#ifndef JEU_JEU_H
#define JEU_JEU_H
#include <string>

#include "carteJoaillerie.h"
#include "carte.h"
#include "carteNoble.h"
#include "privilege.h"
#include "jeton.h"
#include "plateau.h"
#include "optionnelle.h"
#include "pioche.h"
#include "obligatoire.h"
#include "joueur.h"

#include <sqlite3.h>
#include "query.h"


class Jeu {
private:
    /*struct Handler {
        Jeu * instance = nullptr;
        ~Handler() { delete instance; instance = nullptr;}
    };
    static Handler handler;*/

    static Jeu* instance;

    Joueur* joueur_actuel;
    Joueur* joueur_gagnant;

    Jeu():joueur_actuel(nullptr),joueur_gagnant(nullptr){};
    ~Jeu(){};
    Jeu(const Jeu& j) = delete;
    Jeu& operator=(const Jeu& j) = delete;

public:
    static Jeu& getJeu();
    static void libereJeu();

    Joueur* getJoueurActuel() const {return joueur_actuel;}
    Joueur* getJoueurGagnant() const {return joueur_gagnant;}

    void validationAction();

    //pour l'instant dans public
    void nouvellePartie();
    void reprendrePartie(); //faut bdd
    void verifAnciennePartie(); //faut bdd
    void verifGagnant(Joueur * j1, Joueur * j2);
    void sauvegarderPartie(); //faut bdd
    void vainqueur(Joueur * j);
    void auSuivant(Joueur * j1, Joueur * j2);

    void manche(Plateau * p, Pioche * p1, Pioche * p2, Pioche * p3, Joueur * j1, Joueur * j2, Obligatoire * obl, Optionnelle * opt);
    void tour(Plateau * p, Pioche * p1, Pioche * p2, Pioche * p3, Joueur * j, Obligatoire * obl, Optionnelle * opt);
};

void initCarteJoaillerie(sqlite3* db, std::vector<CarteJoaillerie>& cartes) {
    for (int id = 1; id <= 67; ++id) {
        CarteJoaillerieData data = queryCarteJoaillerie(db, id);

        // 将查询到的数据转换为所需的格式
        std::array<Couleur, 2> pierres = {static_cast<Couleur>(data.pierres[0]), static_cast<Couleur>(data.pierres[1])};
        std::map<Couleur, int> prix;
        for (const auto& p : data.prix) {
            prix[static_cast<Couleur>(p.first)] = p.second;
        }

        CarteJoaillerie carte(nullptr, nullptr, data.niveau, data.couronnes, pierres, prix, "", data.pointPrestige, static_cast<Pouvoir>(data.pouvoirs[0]), static_cast<Pouvoir>(data.pouvoirs[1]), id);

        cartes.push_back(carte);
    }
}

void initCarteNoble(sqlite3* db, std::vector<CarteNoble>& cartesNoble) {
    for (int id = 67; id <= 71; ++id) {
        CarteNobleData data = queryCarteNoble(db, id);

        CarteNoble carteNoble(data.couronnes, data.pointPrestige, {});

        cartesNoble.push_back(carteNoble);
    }
}




#endif //JEU_JEU_H
