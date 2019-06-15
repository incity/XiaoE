#ifndef _MACROS_H_
#define _MACROS_H_

// Put this in the declarations for a class to be uncopyable.
#define DISALLOW_COPY(TypeName) \
    TypeName(const TypeName&)
    
// Put this in the declarations for a class to be unassignable.
#define DISALLOW_ASSIGN(TypeName) \
    TypeName& operator=(const TypeName&)

// Put this in the declarations for a class to be uncopyable and unassignable.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    DISALLOW_COPY(TypeName);                 \
    DISALLOW_ASSIGN(TypeName)
    
// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
// This is especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
    TypeName();                           \
    DISALLOW_COPY_AND_ASSIGN(TypeName)

#endif
