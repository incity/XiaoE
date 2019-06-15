#ifndef _POWER_MANAGER_H
#define _POWER_MANAGER_H
//1. The .cc .cpp .cxx related header files
//2. C system include files.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//3. C++ system include files.
#include <utils/Thread.h>
#include <utils/Log.h>
#include <utils/Mutex.h>
#ifdef USE_ANDROID_UTILS_SINGLETON
    #include <utils/Singleton.h>
#endif
#include <cutils/android_reboot.h>
//4. Other libraries' .h files.

//5. Your project's .h files.

//#include <standby/IStandBy.h>
#define DE2
#define DISP_DEV "/dev/disp"

#define DISP_CMD_LCD_ON     0x140
#define DISP_CMD_LCD_OFF    0x141

#ifdef DE2
typedef enum
{
	DISP_OUTPUT_TYPE_NONE   = 0,
	DISP_OUTPUT_TYPE_LCD    = 1,
	DISP_OUTPUT_TYPE_TV     = 2,
	DISP_OUTPUT_TYPE_HDMI   = 4,
	DISP_OUTPUT_TYPE_VGA    = 8,
}disp_output_type;
#endif

#define DISP_DEVICE_SWITCH    0x0F
#define DISP_BLANK          0x0C

using namespace android;

#ifdef USE_ANDROID_UTILS_SINGLETON
class PowerManager : public Singleton<PowerManager> 
#else
class PowerManager
#endif
{
public:
#ifndef USE_ANDROID_UTILS_SINGLETON
    // get the single instance of PowerManager
    static PowerManager& singleton();
#endif

    void shutdown();
    int screenOff();
    int screenOn();

    void reboot();

private:
    // constructor & desctructor, for internal use only
#ifdef USE_ANDROID_UTILS_SINGLETON
    friend class Singleton<PowerManager>;
#endif
    PowerManager();
    virtual ~PowerManager();
    
    int mDispFd;

#ifndef USE_ANDROID_UTILS_SINGLETON
    // store the single instance of ActivityStack
    static PowerManager* s_single;
#endif
};

#ifdef USE_ANDROID_UTILS_SINGLETON
    #define POWERMANAGER   PowerManager::getInstance()
#else
    #define POWERMANAGER   PowerManager::singleton()
#endif

#endif
