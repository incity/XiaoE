//1. The .cc .cpp .cxx related header files
#include "StorageManager.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#undef LOG_TAG
#define LOG_TAG "StorageManager"

using namespace std;
using namespace rapidjson;

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++++++++
// |   2. protected members                    |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   2.8. member functions |
// +++++++++++++++++++++++++++
#ifdef USE_ANDROID_UTILS_SINGLETON
ANDROID_SINGLETON_STATIC_INSTANCE(StorageManager);
#else
StorageManager* StorageManager::s_single = NULL;

// get the single instance of StorageManager
StorageManager& StorageManager::singleton()
{
    if (NULL == s_single) {
        s_single = new StorageManager();
    }
    return *s_single;
}
#endif

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++    

// +++++++++++++++++++++++++++
// |   3.6. constructors     |
// +++++++++++++++++++++++++++
StorageManager::StorageManager() :
    mDb(ACCESS_CONTROL_SYSTEM_DB_PATH, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    try {
        bool bExists = mDb.tableExists("access_records");
        if(!bExists) {
            mDb.exec("CREATE TABLE access_records ("
                        "PRIMARY KEY (id),"
                                 "id INTEGER,"
                        "access_mode INTEGER,"
                        "access_code TEXT,"
                        "access_time INTEGER,"
                        "candid_shot BLOB"
                    ")");
        }

        bExists = mDb.tableExists("access_cards");
        if(!bExists) {
            mDb.exec("CREATE TABLE access_cards ("
                        "PRIMARY KEY (id),"
                                 "id INTEGER,"
                        "card_number TEXT,"
                          "card_type INTEGER,"
                  "registration_time INTEGER,"
                  "cancellation_time INTEGER,"
                        "card_status INTEGER"
                    ")");
        }

        bExists = mDb.tableExists("bulletins");
        if(!bExists) {
            mDb.exec("CREATE TABLE bulletins ("
                         "PRIMARY KEY (id),"
                                  "id INTEGER,"
                            "page_num INTEGER,"
                               "title TEXT,"
                             "content TEXT,"
                            "pub_time INTEGER,"
                              "expiry INTEGER,"
                              "status INTEGER"
                    ")");
        }

        bExists = mDb.tableExists("residents");
        if(!bExists) {
            mDb.exec("CREATE TABLE residents ("
                         "PRIMARY KEY (id),"
                                  "id INTEGER,"
                                 "tel TEXT,"
                            "password TEXT,"
                    ")");
        }

    } catch (std::exception& e) {
        db_error("table create failed!(%s)", e.what());
    }
}

// +++++++++++++++++++++++++++
// |   3.7. destructors      |
// +++++++++++++++++++++++++++
StorageManager::~StorageManager()
{
}

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++
void StorageManager::store(AccessRecord &record)
{
    try {
        AccessRecord::SqlDao dao(mDb);
        Mutex::Autolock _l(mDbLock);
        dao.insert(record);
    } catch (std::exception& e) {
        record.dump();
        db_error("store access record failed!(%s)", e.what());
    }
}

void StorageManager::remove(AccessRecord &record)
{
    try {
        AccessRecord::SqlDao dao(mDb);
        Mutex::Autolock _l(mDbLock);
        dao.remove(record);
    } catch (std::exception& e) {
        record.dump();
        db_error("delete access record failed!(%s)", e.what());
    }
}

int StorageManager::load(AccessRecord &record)
{
    try {
        AccessRecord::SqlDao dao(mDb);
        Mutex::Autolock _l(mDbLock);
        return dao.select(record);
    } catch (std::exception& e) {
        db_error("load access record failed!(%s)", e.what());
    }

    return 0;
}

int StorageManager::load(Resident &resident, const char* tel)
{
    try {
        Resident::SqlDao dao(mDb);
        Mutex::Autolock _l(mDbLock);
        return dao.select(resident, tel);
    } catch (std::exception& e) {
        db_error("load resident failed!(%s)", e.what());
    }

    return 0;
}

