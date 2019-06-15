#ifndef  ACCESS_RECORD_INC
#define  ACCESS_RECORD_INC

//1. The .cc .cpp .cxx related header files
//2. C system include files.
//3. C++ system include files.
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>

//4. Other libraries' .h files.
#include <utils/WorkQueue.h>
#ifdef USE_ANDROID_UTILS_SINGLETON
    #include <utils/Singleton.h>
    using namespace android;
#endif
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"

//5. Your project's .h files.
#include "debug.h"
#include "GenericValidator.h"

using namespace android;
using namespace rapidjson;

struct AccessRecord
{
    AccessRecord(){}

    AccessRecord(int id,
                        int access_mode,
                std::string access_code,
                     time_t access_time,
                      void* candid_shot = NULL) :
                        id(id),
                        access_mode(access_mode),
                        access_code(access_code),
                        access_time(access_time),
                        candid_shot(candid_shot){}

    struct JsonConverter
    {
        JsonConverter(AccessRecord& record)
        {
            Writer<StringBuffer> writer(mStringBuf);
            writer.StartObject();
            writer.Key("id");
            writer.Int(record.id);
            
            writer.Key("access_mode");
            writer.Int(record.access_mode);
            
            writer.Key("access_code");
            writer.String(record.access_code.c_str());
            
            writer.Key("access_time");
            writer.Uint(record.access_time);
            writer.EndObject();
        }

        JsonConverter(AccessRecord record[], size_t count)
        {
            Writer<StringBuffer> writer(mStringBuf);

            size_t i;
            for (i = 0; i < count; i++) {    
                writer.StartObject();
                writer.Key("id");
                writer.Int(record[i].id);
                
                writer.Key("access_mode");
                writer.Int(record[i].access_mode);
                
                writer.Key("access_code");
                writer.String(record[i].access_code.c_str());
                
                writer.Key("access_time");
                writer.Uint(record[i].access_time);
                writer.EndObject();
            }
        }

        const char* getString()
        {
            return mStringBuf.GetString();
        }
    private:
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

        int select(AccessRecord& record)
        {
            SQLite::Statement query(mDb, "SELECT * "
                                           "FROM access_records "
                                          "ORDER BY id DESC LIMIT 1");

            while (query.executeStep()) {
                record.id          = query.getColumn("id");
                record.access_mode = query.getColumn("access_mode");
                record.access_code = query.getColumn("access_code").getText();;
                record.access_time = query.getColumn("access_time");
                
                return 1;
            }

            return 0;
        }

        int select(AccessRecord record[], size_t count)
        {
            SQLite::Statement query(mDb, "SELECT * "
                                           "FROM access_records "
                                          "ORDER BY id DESC LIMIT :count");
            query.bind(":count", count);

            int i;
            for (i = 0; query.executeStep(); i++) {
                record[i].id          = query.getColumn("id");
                record[i].access_mode = query.getColumn("access_mode");
                record[i].access_code = query.getColumn("access_code").getText();;
                record[i].access_time = query.getColumn("access_time");
            }

            return i;
        }

        int insert(AccessRecord& record)
        {
            SQLite::Statement query(mDb, "INSERT INTO access_records "
                                         "VALUES (NULL, ?, ?, ?, NULL)");
            query.bind(1, record.access_mode);
            query.bind(2, record.access_code);
            query.bind(3, record.access_time);

            return query.exec();
        }

        // delete is a reserved C++ keyword, use remove instead
        int remove(AccessRecord& record)
        {
            SQLite::Statement query(mDb, "DELETE FROM access_records "
                                          "WHERE id = ?");
            query.bind(1, record.id);
            
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
    int         access_mode;
    std::string access_code;
    time_t      access_time;
    void*       candid_shot;
};

#endif
