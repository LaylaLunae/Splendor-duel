#ifndef SPLENDOR_QUERY_H
#define SPLENDOR_QUERY_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <array>
#include <map>

// Déclarations des fonctions
bool connectToDatabase(sqlite3** db, const std::string& dbPath);

template <typename T>
T queryJoueurField(sqlite3* db, const std::string& fieldName, int joueurId);

template <typename T>
bool updateJoueurField(sqlite3* db, const std::string& fieldName, T value, int joueurId);

int queryJeuField(sqlite3* db, const std::string& fieldName, int jeuId);

bool updateJeuField(sqlite3* db, const std::string& fieldName, int value, int jeuId);

struct CarteJoaillerieData {
    int id;
    int pointPrestige;
    int couronnes;
    int niveau;
    std::array<int, 2> pouvoirs;
    std::array<int, 7> pierres;
    std::map<int, int> prix;
};

CarteJoaillerieData queryCarteJoaillerie(sqlite3* db, int carteId);

struct CarteNobleData {
    int pointPrestige;
    int couronnes;
    std::array<int, 2> pouvoirs;
};

CarteNobleData queryCarteNoble(sqlite3* db, int carteId);

template <typename T>
T queryPrivilege(sqlite3* db, int privilegeId);

void updatePrivilegeStatus(sqlite3* db, int privilegeId, int status);

template <typename T>
T queryPiocheField(sqlite3* db, const std::string& fieldName, int piocheId);

std::vector<int> queryJoueurCartes(sqlite3* db, const std::string& tableName, int joueurId);

void insertJoueurCarte(sqlite3* db, const std::string& tableName, int joueurId, int carteId);

std::vector<int> queryJoueurPrivileges(sqlite3* db, int joueurId);

void insertJoueurPrivilege(sqlite3* db, int joueurId, int privilegeId);

std::vector<int> queryCartesInPioche(sqlite3* db, const std::string& tableName, int piocheId);

void insertCarteInPioche(sqlite3* db, const std::string& tableName, int piocheId, int carteId);

struct JetonData {
    int type;
    int couleur;
};

JetonData queryJeton(sqlite3* db, int jetonId);

template <typename T>
T queryJoueurJetonField(sqlite3* db, const std::string& fieldName, int joueurId, int jetonId);

void insertJoueurJeton(sqlite3* db, int joueurId, int jetonId, int quantite);

void updateJoueurJeton(sqlite3* db, int joueurId, int jetonId, int quantite);

template <typename T>
T queryPlateauField(sqlite3* db, const std::string& fieldName, int plateauId);

void updatePlateauField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId);

template <typename T>
T queryPlateauJetonsField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int plateauId, int jetonId);

void updatePlateauJetonsField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int fieldValue, int plateauId, int jetonId);

void insertIntoPlateauJetons(sqlite3* db, const std::string& tableName, int plateauId, int jetonId, int quantite);

template <typename T>
T queryPlateauSacField(sqlite3* db, const std::string& fieldName, int plateauId, int jetonId);

void updatePlateauSacField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int jetonId);

void insertIntoPlateauSac(sqlite3* db, int plateauId, int jetonId);

std::vector<int> queryPlateauPrivilegesField(sqlite3* db, int plateauId);

void updatePlateauPrivilegesField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int privilegeId);

void insertIntoPlateauPrivileges(sqlite3* db, int plateauId, int privilegeId);

template <typename T>
T queryPlateauCartesNobleField(sqlite3* db, const std::string& fieldName, int plateauId);

void updatePlateauCartesNobleField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int carteNobleId);

void insertIntoPlateauCartesNoble(sqlite3* db, int plateauId, int carteNobleId);

template <typename T>
T queryTableField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int id);

void updateTableField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int fieldValue, int id);

void insertIntoTable(sqlite3* db, const std::string& tableName, int id, int plateauId);

std::vector<int> queryAllJetonIdsForPlateau(sqlite3* db, const std::string& tableName, int plateauId);

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

template <typename T>
T queryPlateauJetonsField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int plateauId, int jetonId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM " + tableName + " WHERE plateau_id = ? AND jeton_id = ?;";
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

template <typename T>
T queryPlateauCartesNobleField(sqlite3* db, const std::string& fieldName, int plateauId) {
    sqlite3_stmt* stmt;
    std::string query = "SELECT " + fieldName + " FROM PlateauCartesNoble WHERE plateau_id = ?;";
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

std::vector<const char*> queryAllJetonColorsForPlateau(sqlite3* db, const std::string& tableName);

#endif //SPLENDOR_QUERY_H
