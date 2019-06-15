#ifndef _STORAGE_MANAGER_H
#define _STORAGE_MANAGER_H

//1. The .cc .cpp .cxx related header files
//2. C system include files.
#include <sys/vfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
//3. C++ system include files.
#ifdef USE_ANDROID_UTILS_SINGLETON
    #include <utils/Singleton.h>
    using namespace android;
#endif
//4. Other libraries' .h files.
#include <utils/String8.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"

//5. Your project's .h files.
#include "macros.h"
#include "AccessRecord.h"

#define ACCESS_CONTROL_SYSTEM_DB_PATH "./access_control_system.db"

#ifdef USE_ANDROID_UTILS_SINGLETON
class StorageManager : public Singleton<StorageManager>
#else
class StorageManager
#endif
{
// 1. public members
public:
    // 1.1. typedefs
    // 1.2. nested enums
    // 1.3. nested structs
    // 1.4. nested classes
    // 1.5. consts
    // 1.6. constructors
    // 1.7. destructors
    // 1.8. member functions
    void store(AccessRecord &record);
    void remove(AccessRecord &record);
    int load(AccessRecord &record);
#ifndef USE_ANDROID_UTILS_SINGLETON
    // get the single instance of StorageManager
    static StorageManager& singleton();
#endif
    // 1.9. member variables

// 2. protected members
protected:
    // 2.1. typedefs
    // 2.2. nested enums
    // 2.3. nested structs
    // 2.4. nested classes
    // 2.5. consts
    // 2.6. constructors
    // 2.7. destructors
    // 2.8. member functions
    // 2.9. member variables

// 3. protected members
private:
    // 3.1. typedefs
    // 3.2. nested enums
    // 3.3. nested structs
    // 3.4. nested classes
    // 3.5. consts
    // 3.6. constructors
    StorageManager();
    // 3.7. destructors
    ~StorageManager();
    // 3.8. member functions
    DISALLOW_COPY_AND_ASSIGN(StorageManager);
    // 3.9. member variables
    SQLite::Database mDb;
    Mutex mDbLock;

#ifdef USE_ANDROID_UTILS_SINGLETON
    friend class Singleton<StorageManager>;
#else
    // store the single instance of StorageManager
    static StorageManager* s_single;
#endif

};

#ifdef USE_ANDROID_UTILS_SINGLETON
    #define STORAGEMANAGER   StorageManager::getInstance()
#else
    #define STORAGEMANAGER   StorageManager::singleton()
#endif

#endif
