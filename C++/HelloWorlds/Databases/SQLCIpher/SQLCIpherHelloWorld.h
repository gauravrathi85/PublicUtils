#ifndef SQLCIPHERHELLOWORLD_H
#define SQLCIPHERHELLOWORLD_H

#include <string>

struct sqlite3;

namespace SQLCipher
{
int initDB(const std::string& src_database_file, const std::string& license_key, sqlite3 *&db);
int encryptPlainTextDatabase(sqlite3* db_plaintext, const std::string& out_db_name, const std::string &db_key);

}

#endif // SQLCIPHERHELLOWORLD_H
