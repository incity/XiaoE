#ifndef  SOUND_PLAYER_INC
#define  SOUND_PLAYER_INC

//1. The .cc .cpp .cxx related header files
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
#include <media/SoundPool.h>
//5. Your project's .h files.
#include "common.h"
#include "debug.h"
#ifdef USE_ANDROID_UTILS_SINGLETON
    #include <utils/Singleton.h>
    using namespace android;
#endif

#undef LOG_TAG
#define LOG_TAG "SoundPlayer"

using namespace android;

#ifdef USE_ANDROID_UTILS_SINGLETON
class SoundPlayer : public Singleton<SoundPlayer>
#else
class SoundPlayer
#endif
{
// 1. public members
public:
    // 1.1. typedefs
    // 1.2. nested enums
    enum
    {
        SOUND_KEYTONE = 1,
    };
    // 1.3. nested structs
    // 1.4. nested classes
    // class ToneGenerator
    
    // 1.5. consts
    static const int MAX_CHANNELS = 10;
    static const float LEFT_VOLUME = 1.0;
    static const float RIGHT_VOLUME = 1.0;
    
    // 1.6. constructors
    // 1.7. destructors
    // 1.8. member functions
    void play(int sound);
    // 1.9. member variables
#ifndef USE_ANDROID_UTILS_SINGLETON
    // get the single instance of SoundPlayer
    static SoundPlayer& singleton();
#endif

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
    SoundPlayer();
    // 3.7. destructors
    virtual ~SoundPlayer();

    // 3.8. member functions
    // 3.9. member variables
#ifndef USE_ANDROID_UTILS_SINGLETON
    // store the single instance of ActivityStack
    static SoundPlayer* s_single;
#endif
#ifdef USE_ANDROID_UTILS_SINGLETON
    friend class Singleton<SoundPlayer>;
#endif
};

#ifdef USE_ANDROID_UTILS_SINGLETON
    #define SOUNDPLAYER   SoundPlayer::getInstance()
#else
    #define SOUNDPLAYER   SoundPlayer::singleton()
#endif

#endif
