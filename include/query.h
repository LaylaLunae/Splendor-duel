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
T queryPlateauJetonsField(sqlite3* db, const std::string& fieldName, int plateauId, int jetonId);

void updatePlateauJetonsField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int jetonId);

void insertIntoPlateauJetons(sqlite3* db, int plateauId, int jetonId, int quantite);

template <typename T>
T queryPlateauSelectionCouranteField(sqlite3* db, const std::string& fieldName, int plateauId, int jetonId);

void updatePlateauSelectionCouranteField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int jetonId);

void insertIntoPlateauSelectionCourante(sqlite3* db, int plateauId, int jetonId, int posX, int posY);

template <typename T>
T queryPlateauSacField(sqlite3* db, const std::string& fieldName, int plateauId, int jetonId);

void updatePlateauSacField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int jetonId);

void insertIntoPlateauSac(sqlite3* db, int plateauId, int jetonId);

template <typename T>
T queryPlateauPrivilegesField(sqlite3* db, const std::string& fieldName, int plateauId, int privilegeId);

void updatePlateauPrivilegesField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int privilegeId);

void insertIntoPlateauPrivileges(sqlite3* db, int plateauId, int privilegeId);

template <typename T>
T queryPlateauCartesNobleField(sqlite3* db, const std::string& fieldName, int plateauId, int carteNobleId);

void updatePlateauCartesNobleField(sqlite3* db, const std::string& fieldName, int fieldValue, int plateauId, int carteNobleId);

void insertIntoPlateauCartesNoble(sqlite3* db, int plateauId, int carteNobleId);

template <typename T>
T queryTableField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int id);

void updateTableField(sqlite3* db, const std::string& tableName, const std::string& fieldName, int fieldValue, int id);

void insertIntoTable(sqlite3* db, const std::string& tableName, int id, int plateauId);

#endif //SPLENDOR_QUERY_H
