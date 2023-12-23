//
// Created by Pacino on 03/12/2023.
//

#ifndef SPLENDOR_QUERY_H
#define SPLENDOR_QUERY_H

#include <sqlite3.h>
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include "../include/query.h"

// Déclaration de la fonction de connexion à la base de données
bool connectToDatabase(sqlite3** db, const std::string& dbPath) {
    // Tentative d'ouverture de la base de données
    if (sqlite3_open(dbPath.c_str(), db) == SQLITE_OK) {
        std::cout << "Connexion réussie à la base de données." << std::endl;
        return true;
    } else {
        std::cerr << "Erreur de connexion à la base de données: " << sqlite3_errmsg(*db) << std::endl;
        return false;
    }
}

int queryJeuField(sqlite3* db, const std::string& fieldName, int jeuId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM Jeu WHERE handler_id = ?;";
    int result = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    }

    sqlite3_bind_int(stmt, 1, jeuId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return result;
}

bool updateJeuField(sqlite3* db, const std::string& fieldName, int value, int jeuId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE Jeu SET " + fieldName + " = ? WHERE handler_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, value);
    sqlite3_bind_int(stmt, 2, jeuId);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

struct CarteJoaillerieData {
    int id;
    int pointPrestige;
    int couronnes;
    int niveau;
    std::array<int, 2> pouvoirs;
    std::array<int, 7> pierres;
    std::map<int, int> prix;
};

CarteJoaillerieData queryCarteJoaillerie(sqlite3* db, int carteId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM CarteJoaillerie WHERE id = ?;";
    CarteJoaillerieData data = {};

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, carteId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            data.id = sqlite3_column_int(stmt, 0);
            data.pointPrestige = sqlite3_column_int(stmt, 1);
            data.couronnes = sqlite3_column_int(stmt, 2);
            data.pouvoirs[0] = sqlite3_column_int(stmt, 3);
            data.pouvoirs[1] = sqlite3_column_int(stmt, 4);
            data.niveau = sqlite3_column_int(stmt, 5);

            // Lire les propriétés des couleurs
            data.pierres[0] = sqlite3_column_int(stmt, 6);  // rouge
            data.pierres[1] = sqlite3_column_int(stmt, 7);  // bleu
            data.pierres[2] = sqlite3_column_int(stmt, 8);  // vert
            data.pierres[3] = sqlite3_column_int(stmt, 9);  // blanc
            data.pierres[4] = sqlite3_column_int(stmt, 10); // noir
            data.pierres[5] = sqlite3_column_int(stmt, 11); // rose
            data.pierres[6] = sqlite3_column_int(stmt, 18); // choix_utilisateur

            // Lire l'attribut de prix
            data.prix[1] = sqlite3_column_int(stmt, 12); // Prixrouge
            data.prix[2] = sqlite3_column_int(stmt, 13); // Prixbleu
            data.prix[3] = sqlite3_column_int(stmt, 14); // Prixvert
            data.prix[4] = sqlite3_column_int(stmt, 15); // Prixblanc
            data.prix[5] = sqlite3_column_int(stmt, 16); // Prixnoir
            data.prix[6] = sqlite3_column_int(stmt, 17); // Prixrose
        }
        sqlite3_finalize(stmt);
    }

    return data;
}



struct CarteNobleData {
    int pointPrestige;
    int couronnes;
    std::array<int, 2> pouvoirs;
};

CarteNobleData queryCarteNoble(sqlite3* db, int carteId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM CarteNoble WHERE id = ?;";
    CarteNobleData data = {};

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, carteId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            data.pointPrestige = sqlite3_column_int(stmt, 1);
            data.couronnes = sqlite3_column_int(stmt, 2);
            data.pouvoirs[0] = sqlite3_column_int(stmt, 3);
            data.pouvoirs[1] = sqlite3_column_int(stmt, 4);
        }
        sqlite3_finalize(stmt);
    }

    return data;
}

void updatePrivilegeStatus(sqlite3* db, int privilegeId, int status) {
    sqlite3_stmt* stmt;
    std::string update = "UPDATE Privilege SET status = ? WHERE id = ?;";

    if (sqlite3_prepare_v2(db, update.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, status);
        sqlite3_bind_int(stmt, 2, privilegeId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

// JoueurCartesReservees JoueurCartesMain JoueurCartesNoble
std::vector<int> queryJoueurCartes(sqlite3* db, const std::string& tableName, int joueurId) {
    std::vector<int> cartes;
    sqlite3_stmt* stmt;
    std::string query = "SELECT carte_id FROM " + tableName + " WHERE joueur_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, joueurId);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            cartes.push_back(sqlite3_column_int(stmt, 0));
        }

        sqlite3_finalize(stmt);
    }

    return cartes;
}

void insertJoueurCarte(sqlite3* db, const std::string& tableName, int joueurId, int carteId) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO " + tableName + " (joueur_id, carte_id) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, joueurId);
        sqlite3_bind_int(stmt, 2, carteId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

std::vector<int> queryJoueurPrivileges(sqlite3* db, int joueurId) {
    std::vector<int> privileges;
    sqlite3_stmt* stmt;
    std::string query = "SELECT privilege_id FROM JoueurPrivilege WHERE joueur_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, joueurId);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            privileges.push_back(sqlite3_column_int(stmt, 0));
        }

        sqlite3_finalize(stmt);
    }

    return privileges;
}

void insertJoueurPrivilege(sqlite3* db, int joueurId, int privilegeId) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO JoueurPrivilege (joueur_id, privilege_id) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, joueurId);
        sqlite3_bind_int(stmt, 2, privilegeId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

std::vector<int> queryCartesInPioche(sqlite3* db, const std::string& tableName, int piocheId) {
    std::vector<int> cartes;
    sqlite3_stmt* stmt;
    std::string query = "SELECT carte_id FROM " + tableName + " WHERE pioche_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, piocheId);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            cartes.push_back(sqlite3_column_int(stmt, 0));
        }

        sqlite3_finalize(stmt);
    }

    return cartes;
}

void insertCarteInPioche(sqlite3* db, const std::string& tableName, int piocheId, int carteId) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO " + tableName + " (pioche_id, carte_id) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, piocheId);
        sqlite3_bind_int(stmt, 2, carteId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

struct JetonData {
    int type;
    int couleur;
};

JetonData queryJeton(sqlite3* db, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT type, couleur FROM Jeton WHERE id = ?;";
    JetonData data = {};

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, jetonId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            data.type = sqlite3_column_int(stmt, 0);
            data.couleur = sqlite3_column_int(stmt, 1);
        }

        sqlite3_finalize(stmt);
    }

    return data;
}

void insertJoueurJeton(sqlite3* db, int joueurId, int jetonId, int quantite) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO JoueurJetons (joueur_id, jeton_id, quantite) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, joueurId);
        sqlite3_bind_int(stmt, 2, jetonId);
        sqlite3_bind_int(stmt, 3, quantite);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void updateJoueurJeton(sqlite3* db, int joueurId, int jetonId, int quantite) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE JoueurJetons SET quantite = ? WHERE joueur_id = ? AND jeton_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, quantite);
        sqlite3_bind_int(stmt, 2, joueurId);
        sqlite3_bind_int(stmt, 3, jetonId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void updatePlateauField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE Plateau SET " + fieldName + " = ? WHERE id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, fieldValue);
        sqlite3_bind_int(stmt, 2, plateauId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void updatePlateauJetonsField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int fieldValue, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE " + tableName + " SET " + fieldName + " = ? WHERE plateau_id = ? AND jeton_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, fieldValue);
        sqlite3_bind_int(stmt, 2, plateauId);
        sqlite3_bind_int(stmt, 3, jetonId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void insertIntoPlateauJetons(sqlite3* db, const std::string& tableName, int plateauId, int jetonId, int quantite) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO " + tableName + " (plateau_id, jeton_id, quantite) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, jetonId);
        sqlite3_bind_int(stmt, 3, quantite);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

std::vector<int> queryPlateauPrivilegesField(sqlite3* db, int plateauId) {
    sqlite3_stmt* stmt;
    std::vector<int> privilegeIds;
    std::string query = "SELECT privilege_id FROM PlateauPrivileges WHERE plateau_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int privilegeId = sqlite3_column_int(stmt, 0);
            privilegeIds.push_back(privilegeId);
        }
        sqlite3_finalize(stmt);
    }

    return privilegeIds;
}

void updatePlateauPrivilegesField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int privilegeId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE PlateauPrivileges SET " + fieldName + " = ? WHERE plateau_id = ? AND privilege_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, fieldValue);
        sqlite3_bind_int(stmt, 2, plateauId);
        sqlite3_bind_int(stmt, 3, privilegeId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void insertIntoPlateauPrivileges(sqlite3* db, int plateauId, int privilegeId) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO PlateauPrivileges (plateau_id, privilege_id) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, privilegeId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void updatePlateauCartesNobleField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int carteNobleId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE PlateauCartesNoble SET " + fieldName + " = ? WHERE plateau_id = ? AND carte_noble_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, fieldValue);
        sqlite3_bind_int(stmt, 2, plateauId);
        sqlite3_bind_int(stmt, 3, carteNobleId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void insertIntoPlateauCartesNoble(sqlite3* db, int plateauId, int carteNobleId) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO PlateauCartesNoble (plateau_id, carte_noble_id) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, carteNobleId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void updateTableField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int fieldValue, int id) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE " + tableName + " SET " + fieldName + " = ? WHERE id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, fieldValue);
        sqlite3_bind_int(stmt, 2, id);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void insertIntoTable(sqlite3* db, const std::string& tableName, int id, int plateauId) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO " + tableName + " (id, plateau_id) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_bind_int(stmt, 2, plateauId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

std::vector<int> queryAllJetonIdsForPlateau(sqlite3* db, const std::string& tableName, int plateauId) {
    std::vector<int> jetonIds;
    sqlite3_stmt* stmt;
    std::string query = "SELECT jeton_id FROM " + tableName + " WHERE plateau_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int jetonId = sqlite3_column_int(stmt, 0);
            jetonIds.push_back(jetonId);
        }
        sqlite3_finalize(stmt);
    }
    return jetonIds;
}

std::vector<int> queryPlateauCartesNobleFieldVector(sqlite3* db, const std::string& fieldName, int plateauId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM PlateauCartesNoble WHERE plateau_id = ?;";
    std::vector<int> result (0);

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);

        while(sqlite3_step(stmt) == SQLITE_ROW) {
            result.push_back(sqlite3_column_int(stmt, 0));
        }
        sqlite3_finalize(stmt);
    }

    return result;
}

std::vector<const char*>
        queryAllJetonColorsForPlateau(sqlite3* db, const std::string& tableName) {
    std::vector<const char*> jetonColors;
    sqlite3_stmt* stmt;
    std::string query = "SELECT colors FROM " + tableName + ";";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        //sqlite3_bind_int(stmt, 1, plateauId);

        std::cout<<"\nCouleurs Jeton bdd : \n";
        int step = sqlite3_step(stmt);
        while (step == SQLITE_ROW) {
            const  char* res = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            // Duplicate res to a fully functional const char*
            // Begin
            char* duplicate = new char[std::strlen(res) + 1];
            // Copy the content to the duplicate
            std::strcpy(duplicate, res);
            // End
            std::cout<<res<<",  ";
            //int jetonId = sqlite3_column_int(stmt, 0);i
            jetonColors.push_back(duplicate);
            std::cout<<" Duplicate is "<<jetonColors[jetonColors.size()-1];
            step = sqlite3_step(stmt);
            std::cout<<std::endl;
        }
        std::cout<<"\n";
        sqlite3_finalize(stmt);
    }
    return jetonColors;
}


#endif //SPLENDOR_QUERY_H
