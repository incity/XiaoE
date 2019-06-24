//1. The .cc .cpp .cxx related header files
#include "SoundPlayer.h"
//2. C system include files.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

#ifdef USE_ANDROID_UTILS_SINGLETON
ANDROID_SINGLETON_STATIC_INSTANCE(SoundPlayer);
#else
SoundPlayer* SoundPlayer::s_single = NULL;

// get the single instance of ActivityStack
SoundPlayer& SoundPlayer::singleton()
{
    if (NULL == s_single) {
        s_single = new SoundPlayer();
    }
    return *s_single;
}
#endif

// constructor & desctructor, for internal use only
SoundPlayer::SoundPlayer()
{
}


SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::play(int sound)
{
}

