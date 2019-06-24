#ifndef  RESIDENT_INC
#define  RESIDENT_INC

//1. The .cc .cpp .cxx related header files
//2. C system include files.
//3. C++ system include files.
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>

//4. Other libraries' .h files.
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"

//5. Your project's .h files.
#include "debug.h"

using namespace rapidjson;

struct Resident
{
    Resident(){}

    Resident(int id,
                std::string tel,
                std::string pwd) :
                id(id), tel(tel), password(pwd){}

    struct JsonConverter
    {
        JsonConverter(Resident& resident)
        {
            Writer<StringBuffer> writer(mStringBuf);
            doConvert(writer, resident);
        }

        JsonConverter(Resident residents[], size_t count)
        {
            Writer<StringBuffer> writer(mStringBuf);

            size_t i;
            for (i = 0; i < count; i++) {    
                doConvert(writer, residents[i]);
            }
        }

        const char* getString()
        {
            return mStringBuf.GetString();
        }
    private:
        void doConvert(Writer<StringBuffer>& writer, Resident& resident)
        {
            writer.StartObject();
            writer.Key("id");
            writer.Int(resident.id);
            
            writer.Key("tel");
            writer.String(resident.tel.c_str());
            
            writer.Key("password");
            writer.String(resident.password.c_str());
            writer.EndObject();
        }
        StringBuffer mStringBuf;
    };

    // TODO: maybe we need a DAO factory??
    // There's a programming technique called ORM(Object-Relational Mappings)
    // MAYBE we can use it instead.
    //
    // Core J2EE Patterns - Data Access Object
    // https://www.oracle.com/technetwork/java/dataaccessobject-138824.html
    struct SqlDao
    {
        SqlDao(SQLite::Database& db)     :mDb(db){}

        int select(Resident& resident)
        {
            SQLite::Statement query(mDb, "SELECT * "
                                           "FROM residents ");

            while (query.executeStep()) {
                resident.id       = query.getColumn("id");
                resident.tel      = query.getColumn("tel").getText();
                resident.password = query.getColumn("password").getText();
                
                return 1;
            }

            return 0;
        }

        int select(Resident& resident, const char* tel)
        {
            SQLite::Statement query(mDb, "SELECT * "
                                           "FROM residents "
                                          "WHERE tel = :tel");
            query.bind(":tel", tel);

            while (query.executeStep()) {
                resident.id       = query.getColumn("id");
                resident.tel      = query.getColumn("tel").getText();
                resident.password = query.getColumn("password").getText();

                return 1;
            }

            return 0;
        }

        int insert(Resident& resident)
        {
            SQLite::Statement query(mDb, "INSERT INTO residents "
                                         "VALUES (NULL, ?, ?)");
            query.bind(1, resident.tel);
            query.bind(2, resident.password);

            return query.exec();
        }

        // delete is a reserved C++ keyword, use remove instead
        int remove(const char* tel)
        {
            SQLite::Statement query(mDb, "DELETE FROM residents "
                                          "WHERE tel = ?");
            query.bind(1, tel);
            
            return query.exec();
        }

    private:
        SQLite::Database& mDb;
    };

    void dump()
    {
        JsonConverter jc(*this);
        db_info("%s", jc.getString());
    }

    int         id;
    std::string tel;
    std::string password;
};

#endif
