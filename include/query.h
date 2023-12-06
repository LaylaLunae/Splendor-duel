//
// Created by Pacino on 03/12/2023.
//

#ifndef SPLENDOR_QUERY_H
#define SPLENDOR_QUERY_H

#include <sqlite3.h>
//#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/sqlite3.h"
#include <string>
#include <iostream>
#include <map>

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

template <typename T>
T queryJoueurField(sqlite3* db, const std::string& fieldName, int joueurId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM Joueur WHERE id = ?;";
    T result;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return T();
    }

    sqlite3_bind_int(stmt, 1, joueurId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        if constexpr (std::is_same_v<T, int>) {
            result = sqlite3_column_int(stmt, 0);
        } else if constexpr (std::is_same_v<T, std::string>) {
            result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        } else if constexpr (std::is_same_v<T, bool>) {
            result = static_cast<bool>(sqlite3_column_int(stmt, 0));
        }
    } else {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return result;
}

template <typename T>
bool updateJoueurField(sqlite3* db, const std::string& fieldName, T value, int joueurId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE Joueur SET " + fieldName + " = ? WHERE id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, bool>) {
        sqlite3_bind_int(stmt, 1, static_cast<int>(value));
    } else if constexpr (std::is_same_v<T, std::string>) {
        sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
    }

    sqlite3_bind_int(stmt, 2, joueurId);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
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

template <typename T>
T queryPrivilege(sqlite3* db, int privilegeId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT status FROM Privilege WHERE id = ?;";
    T status = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, privilegeId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            status = static_cast<T>(sqlite3_column_int(stmt, 0));
        }
        sqlite3_finalize(stmt);
    }

    return status;
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

template <typename T>
T queryPiocheField(sqlite3* db, const std::string& fieldName, int piocheId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM Pioche WHERE id = ?;";
    T result;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return T();
    }

    sqlite3_bind_int(stmt, 1, piocheId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        if constexpr (std::is_same_v<T, int>) {
            result = sqlite3_column_int(stmt, 0);
        } else if constexpr (std::is_same_v<T, std::string>) {
            result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        } else if constexpr (std::is_same_v<T, bool>) {
            result = static_cast<bool>(sqlite3_column_int(stmt, 0));
        }
    } else {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return result;
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

template <typename T>
T queryJoueurJetonField(sqlite3* db, const std::string& fieldName, int joueurId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM JoueurJetons WHERE joueur_id = ? AND jeton_id = ?;";
    T result = T();

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, joueurId);
        sqlite3_bind_int(stmt, 2, jetonId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result;
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

template <typename T>
T queryPlateauField(sqlite3* db, const std::string& fieldName, int plateauId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM Plateau WHERE id = ?;";
    T result = T();

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result;
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

template <typename T>
T queryPlateauJetonsField(sqlite3* db, const std::string& fieldName, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM PlateauJetons WHERE plateau_id = ? AND jeton_id = ?;";
    T result = T();

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, jetonId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result;
}

void updatePlateauJetonsField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE PlateauJetons SET " + fieldName + " = ? WHERE plateau_id = ? AND jeton_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, fieldValue);
        sqlite3_bind_int(stmt, 2, plateauId);
        sqlite3_bind_int(stmt, 3, jetonId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void insertIntoPlateauJetons(sqlite3* db, int plateauId, int jetonId, int quantite) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO PlateauJetons (plateau_id, jeton_id, quantite) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, jetonId);
        sqlite3_bind_int(stmt, 3, quantite);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

template <typename T>
T queryPlateauSelectionCouranteField(sqlite3* db, const std::string& fieldName, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM PlateauSelectionCourante WHERE plateau_id = ? AND jeton_id = ?;";
    T result = T();

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, jetonId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result;
}

void updatePlateauSelectionCouranteField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE PlateauSelectionCourante SET " + fieldName + " = ? WHERE plateau_id = ? AND jeton_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, fieldValue);
        sqlite3_bind_int(stmt, 2, plateauId);
        sqlite3_bind_int(stmt, 3, jetonId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void insertIntoPlateauSelectionCourante(sqlite3* db, int plateauId, int jetonId, int posX, int posY) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO PlateauSelectionCourante (plateau_id, jeton_id, position_x, position_y) VALUES (?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, jetonId);
        sqlite3_bind_int(stmt, 3, posX);
        sqlite3_bind_int(stmt, 4, posY);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

template <typename T>
T queryPlateauSacField(sqlite3* db, const std::string& fieldName, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM PlateauSac WHERE plateau_id = ? AND jeton_id = ?;";
    T result = T();

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, jetonId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result;
}

void updatePlateauSacField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "UPDATE PlateauSac SET " + fieldName + " = ? WHERE plateau_id = ? AND jeton_id = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, fieldValue);
        sqlite3_bind_int(stmt, 2, plateauId);
        sqlite3_bind_int(stmt, 3, jetonId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void insertIntoPlateauSac(sqlite3* db, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "INSERT INTO PlateauSac (plateau_id, jeton_id) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, jetonId);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

template <typename T>
T queryPlateauPrivilegesField(sqlite3* db, const std::string& fieldName, int plateauId, int privilegeId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM PlateauPrivileges WHERE plateau_id = ? AND privilege_id = ?;";
    T result = T();

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, privilegeId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result;
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

template <typename T>
T queryPlateauCartesNobleField(sqlite3* db, const std::string& fieldName, int plateauId, int carteNobleId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM PlateauCartesNoble WHERE plateau_id = ? AND carte_noble_id = ?;";
    T result = T();

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, plateauId);
        sqlite3_bind_int(stmt, 2, carteNobleId);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result;
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

// Optionelle et Obligatoire
template <typename T>
T queryTableField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int id) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM " + tableName + " WHERE id = ?;";
    T result = T();

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result;
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



// Exemples d'utilisation !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//int main() {
//    sqlite3* db;
//
//    int pointsPrestigeTotal = queryJoueurField<int>(db, "points_prestige_total", 1);
//    std::string pseudo = queryJoueurField<std::string>(db, "pseudo", 1);
//    bool isIA = queryJoueurField<bool>(db, "is_IA", 1);
//
//    bool updateSuccess = updateJoueurField<int>(db, "nombre_couronnes", 5, 1);

//    int joueur1Id = queryJeuField(db, "Joueur1_id", 1);
//
//    bool updateSuccess = updateJeuField(db, "Pioche1_id", 5, 1);
//
//}

#endif //SPLENDOR_QUERY_H
