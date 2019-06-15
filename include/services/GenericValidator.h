#ifndef  GENERIC_VALIDATOR_INC
#define  GENERIC_VALIDATOR_INC

//1. The .cc .cpp .cxx related header files
//2. C system include files.
//3. C++ system include files.
#include <iostream>
#include <sstream>

//4. Other libraries' .h files.
//5. Your project's .h files.
#include "debug.h"
#include "GenericFactory.h"

#define ACCESS_MODE(m1, m2, m3, m4) (m1+m2+m3+m4 - 4*'a')
#define ACCESS_MODEEx(m1, m2, m3, m4, m5) (m1+m2+m3+m4+m5 - 5*'a')
#define ACCESS_MODEEx2(m1, m2, m3, m4, m5, m6) (m1+m2+m3+m4+m5+m6 - 6*'a')

enum AccessMode {
    // WARNING:
    // This macro does not guarantee the uniqueness of the value.
    // You need to check it by yourself.
    // And make sure not to exceed one byte(<=255).
    // And it's better not to exceed ACCESS_MODE_UNKNOWN.
    /*11*/ACCESS_MODE_FACE        = ACCESS_MODE   ('f', 'a', 'c', 'e'),
    /*22*/ACCESS_MODE_CARD        = ACCESS_MODE   ('c', 'a', 'r', 'd'),
    /*38*/ACCESS_MODE_BLUETOOTH   = ACCESS_MODE   ('b', 'l', 't', 'h'),
    /*42*/ACCESS_MODE_LORA        = ACCESS_MODE   ('l', 'o', 'r', 'a'),
    /*48*/ACCESS_MODE_ZIGBEE      = ACCESS_MODEEx2('z', 'i', 'g', 'b', 'e', 'e'),
    /*50*/ACCESS_MODE_SPEECH      = ACCESS_MODEEx2('s', 'p', 'e', 'e', 'c', 'h'),
    /*55*/ACCESS_MODE_NBIOT       = ACCESS_MODEEx ('n', 'b', 'i', 'o', 't'),
    /*56*/ACCESS_MODE_FINGERPRINT = ACCESS_MODE   ('f', 'p', 'r', 't'),
    /*58*/ACCESS_MODE_PASSWORD    = ACCESS_MODE   ('p', 's', 'w', 'd'),
    /*60*/ACCESS_MODE_TOKEN       = ACCESS_MODEEx ('t', 'o', 'k', 'e', 'n'),
    /*61*/ACCESS_MODE_RETINA      = ACCESS_MODEEx2('r', 'e', 't', 'i', 'n', 'a'),
    /*69*/ACCESS_MODE_INDOOR      = ACCESS_MODEEx2('i', 'n', 'd', 'o', 'o','r'),
    /*92*/ACCESS_MODE_UNKNOWN     = ACCESS_MODEEx2('u', 'k', 'n', 'o', 'w', 'n'),
};

class GenericValidator
{
public:
    virtual ~GenericValidator() {}
    virtual inline int create(const char* )
    {
        return 0;
    }
    virtual inline int why()
    {
        return 0;
    }
    virtual bool validate() = 0;
    virtual const char* dumpcode() const = 0;
    virtual int modeid() const = 0;
};

typedef GenericFactory<GenericValidator> ValidatorFactory;

#define DO_REGISTER_VALIDATOR(_class) \
    extern void realRegister##_class (void); \
    realRegister##_class ()

#define AUTO_REGISTER_VALIDATOR(_class) \
    static struct _ValidatorFactory_##_class { \
        static GenericValidator *create() { \
            return new _class(); \
        } \
        _ValidatorFactory_##_class() { \
            GenericFactory<GenericValidator>::singleton()->doRegister(#_class, create); \
        } \
    } _autoRegister_##_class

#endif
