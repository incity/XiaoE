//1. The .cc .cpp .cxx related header files
#include "AccessController.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#undef PRIVATE

template<>
ValidatorFactory *ValidatorFactory::s_single = NULL;

#ifdef USE_ANDROID_UTILS_SINGLETON
ANDROID_SINGLETON_STATIC_INSTANCE(AccessController);
#else
AccessController* AccessController::s_single = NULL;

// get the single instance of ActivityStack
AccessController& AccessController::singleton()
{
    if (NULL == s_single) {
        s_single = new AccessController();
    }
    return *s_single;
}
#endif

// constructor & desctructor, for internal use only
AccessController::AccessController()
                    : mWorkQ(1)
{
}

AccessController::~AccessController()
{
}


