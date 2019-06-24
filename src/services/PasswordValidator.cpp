#include "PasswordValidator.h"
#include <string.h>
#include "StorageManager.h"
#include "Resident.h"

AUTO_REGISTER_VALIDATOR(PasswordValidator);

#define VALIDATOR_NAME "PasswordValidator"
#undef LOG_TAG
#define LOG_TAG VALIDATOR_NAME

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
int PasswordValidator::create(const char* password)
{
    assert(password && password[0]);
    memset(mPassword, 0, sizeof(mPassword));

    strncpy(mPassword, password, sizeof(mPassword)-1);
    
    hexdump(mPassword, sizeof(mPassword)-1);
    
    return 0;
}

bool PasswordValidator::validate()
{
    char delim[] = "-";
    char* telpwd = strdup(mPassword);
    assert(telpwd);

    char* tel = strsep(&telpwd, delim);
    char* pwd = strsep(&telpwd, delim);

    if(tel && pwd) {
        db_msg("tel:%s pwd:%s\n", tel, pwd);

        Resident resident;
        STORAGEMANAGER.load(resident, tel);

        if(strcmp(pwd, resident.password.c_str()) == 0) {
            free(telpwd);
            return true;
        }
    }

    result = -1;
    printf("%s %d: >> result = %d\n", __func__, __LINE__, result);
    free(telpwd);
    return false;
}

const char* PasswordValidator::dumpcode() const
{
    return mPassword;
}

int PasswordValidator::modeid() const
{
    return ACCESS_MODE_PASSWORD;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   2. protected members                    |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   2.8. member functions |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++

