//
// Created by Pacino on 03/12/2023.
//

#include <sqlite3.h>
#include <string>

class Jeu;

class database_manager {
private:
    sqlite3 *db;
    Jeu *jeu;

    void openDatabase(const std::string &dbPath) {
        if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
            // 处理打开数据库时的错误
        }
    }

    void closeDatabase() {
        if (db) {
            sqlite3_close(db);
        }
    }

    void executeSQL(const std::string &sql) {
        char *errMsg = nullptr;
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            // 处理SQL执行错误
            sqlite3_free(errMsg);
        }
    }

public:
    database_manager(Jeu *jeu, const std::string &dbPath) : jeu(jeu) {
        openDatabase(dbPath);
    }

    ~database_manager() {
        closeDatabase();
    }

    // 加载游戏状态
    void loadGameState() {
        std::string sql = "SELECT * FROM Jeu WHERE id = ..."; // 适当的SQL查询
        // 执行查询并处理结果
    }

    // 保存游戏状态
    void saveGameState() {
        std::string sql = "UPDATE Jeu SET ... WHERE id = ..."; // 适当的SQL更新
        executeSQL(sql);
    }

    // 加载玩家数据
    void loadPlayerData() {
        std::string sql = "SELECT * FROM Joueur WHERE id = ..."; // 适当的SQL查询
        // 执行查询并处理结果
    }

    // 保存玩家数据
    void savePlayerData() {
        std::string sql = "UPDATE Joueur SET ... WHERE id = ..."; // 适当的SQL更新
        executeSQL(sql);
    }

    // 其他必要的数据库操作方法
};
