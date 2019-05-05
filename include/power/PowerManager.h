#ifndef _POWER_MANAGER_H
#define _POWER_MANAGER_H

//#include <utils/Thread.h>
#include <utils/Log.h>
#include <utils/Mutex.h>

#include <cutils/android_reboot.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//#include <standby/IStandBy.h>
#define DE2
#define DISP_DEV "/dev/disp"

enum {
    SCREEN_ON = 0,
    SCREEN_OFF
};

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

class PowerManager
{
public:    
    // get the single instance of PowerManager
    static PowerManager* singleton();
    
    void pulse();
    void powerOff();
    int screenOff();
    int screenOn();

    void screenSwitch();
    void reboot();
    bool isScreenOn();

private:
    // constructor & desctructor, for internal use only
    PowerManager();
    virtual ~PowerManager();
    
    int mDispFd;
    Mutex mLock;
    //Condition mCon;
    int mState;
    int poweroff();
    bool mRestoreScreenOn;
    
    // store the single instance of ActivityStack
    static PowerManager* s_single;
};

#define POWERMANAGER   PowerManager::singleton()

#endif
