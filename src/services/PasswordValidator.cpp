#include "PasswordValidator.h"

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
int PasswordValidator::create(const char* code)
{
    assert(code && code[0]);
    memset(mPassword, 0, sizeof(mPassword));

    strncpy(mPassword, code, sizeof(mPassword)-1);
    
    hexdump(mPassword, sizeof(mPassword)-1);
    
    return 0;
}

bool PasswordValidator::validate()
{    
    return true;
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

