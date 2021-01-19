#include "SQLCIpherHelloWorld.h"

#include "sqlite3.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace SQLCipher
{

int initDB(const std::string& src_database_file, const std::string& license_key, sqlite3 * & db)
{

    int rc = sqlite3_open(src_database_file.c_str(), &db);
    if (rc != SQLITE_OK) {
        cout<<"Failed to open database"<<endl;
        return rc;//
    }
    string lic_st("PRAGMA cipher_license = '"+ license_key+"' ;");
    rc = sqlite3_exec(db, lic_st.c_str() , NULL, NULL, NULL);//specificc to sqlcipher commercial version
    if(rc != SQLITE_OK){
        cout<<"Failed in license step"<<endl;
    }
    return rc;
}

//
int encryptPlainTextDatabase(sqlite3* db_plaintext, const std::string& out_db_name, const std::string& db_key)
{
    //ensure that the outdb file does not exist else this step will fail
    string q_st{"ATTACH DATABASE '"+ out_db_name+ "' AS encrypted KEY '"+db_key.c_str()+"'"};
    int rc = sqlite3_exec(db_plaintext, q_st.c_str(), 0, 0, 0);
    if(rc != SQLITE_OK){
        cout<<"failed to attach to plaintext database with res"<<rc<<endl;
        return rc;
    }

    rc = sqlite3_exec(db_plaintext,  "SELECT sqlcipher_export('encrypted')",0,0,0);
    if(rc != SQLITE_OK){
        cout<<"failed in doing sqlcipher_export() with: res:"<<rc;
        return rc;
    }

    rc = sqlite3_exec(db_plaintext, "DETACH DATABASE encrypted;", 0, 0, 0);
    if(rc != SQLITE_OK){
        cout<<"failed to detach database with: res:"<<rc;
        return rc;
    }

    sqlite3_close(db_plaintext);
    cout<<"created encrypted database"<<endl;
    return rc;
}

}

