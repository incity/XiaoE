#ifndef  PASSWORD_VALIDATOR_INC
#define  PASSWORD_VALIDATOR_INC

//1. The .cc .cpp .cxx related header files
//2. C system include files.
//3. C++ system include files.
#include <iostream>
#include <sstream>

//4. Other libraries' .h files.
//5. Your project's .h files.
#include "debug.h"
#include "GenericValidator.h"

class PasswordValidator : public GenericValidator
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
    int create(const char* );
    bool validate();
    const char* dumpcode() const;
    int modeid() const;
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

// 3. private members
private:
    // 3.1. typedefs
    // 3.2. nested enums
    // 3.3. nested structs
    // 3.4. nested classes
    // 3.5. consts
    // 3.6. constructors
    // 3.7. destructors
    // 3.8. member functions
    // 3.9. member variables
    char mPassword[64];
};

#endif
