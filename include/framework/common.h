#ifndef  COMMON_INC
#define  COMMON_INC

#include <string>

std::string stringReplace(const std::string& str, const std::string& oldVal, const std::string& newVal);

struct DeleteObject
{
    template <typename T>
        void operator()(const T* ptr) const
        {
            delete ptr;
        }
};

typedef unsigned long HandlerParam;
typedef void (*Handler)(void* obj, HandlerParam);

#endif   /* ----- #ifndef COMMON_INC  ----- */

