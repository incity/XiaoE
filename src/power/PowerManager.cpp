#include "PowerManager.h"
#undef LOG_TAG
#define LOG_TAG "PowerManager"

#include "debug.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/watchdog.h>

using namespace android;

#ifdef USE_ANDROID_UTILS_SINGLETON
ANDROID_SINGLETON_STATIC_INSTANCE(PowerManager) ;
#endif

#ifndef USE_ANDROID_UTILS_SINGLETON
PowerManager* PowerManager::s_single = NULL;

// get the single instance of ActivityStack
PowerManager& PowerManager::singleton()
{
    if (NULL == s_single) {
        s_single = new PowerManager();
    }
    return *s_single;
}
#endif

PowerManager::PowerManager()
    : mDispFd(0)
{
    mDispFd = open(DISP_DEV, O_RDWR);
    if (mDispFd < 0) {
        db_error("fail to open %s", DISP_DEV);
    }
}

PowerManager::~PowerManager()
{
    close(mDispFd);
}

void PowerManager::shutdown()
{
    android_reboot(ANDROID_RB_POWEROFF, 0, 0);
}

void PowerManager::reboot()
{
    android_reboot(ANDROID_RB_RESTART, 0, 0);
}

int PowerManager::screenOff()
{
    db_msg("screenOff");
    int retval = 0;
    unsigned long args[4]={0};
    #ifdef DE2
        #ifdef NORMAL_STANDBY
            standbySuspend();
            db_msg("standbySuspend```");
        #else
            args[1] = DISP_OUTPUT_TYPE_NONE;
            retval = ioctl(mDispFd, DISP_DEVICE_SWITCH, args);
        #endif
    #else
        retval = ioctl(mDispFd, DISP_CMD_LCD_OFF, args);
    #endif
    if (retval < 0) {
        db_error("fail to set screen on\n");
        return -1;
    }
    
    return 0;
}

int PowerManager::screenOn()
{
    db_msg("screenOn");
    int retval = 0;
    unsigned long args[4]={0};
    #ifdef DE2
        #ifdef NORMAL_STANDBY
            standbyResume();
            db_msg("standbyResume```");
        #else
            args[1] = DISP_OUTPUT_TYPE_LCD;
            retval = ioctl(mDispFd, DISP_DEVICE_SWITCH, args);
        #endif
    #else
        retval = ioctl(mDispFd, DISP_CMD_LCD_ON, args);
    #endif
    if (retval < 0) {
        db_error("fail to set screen on\n");
        return -1;
    }

    return 0;
}

