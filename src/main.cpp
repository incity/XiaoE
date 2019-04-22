//1. The .cc .cpp .cxx related header files

//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//3. C++ system include files.

//4. Other libraries' .h files.
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <mgeff/mgeff.h>
#include <mgncs/mgncs.h>
#include <mgncs4touch/mgncs4touch.h>

//5. Your project's .h files.
#include "debug.h"
#include "version.h"
#include "Activity.h"
#include "ActivityStack.h"
#include "ResourceManager.h"

#define LOG_TAG "Main"
#define SCREEN_IDLE_TIMER_ID	1
#define SCREEN_IDLE_TIMER	(30*100)

static BOOL delayLoadRes ();

/* 
 * this is initialize and finalize function, please call it when desktop
 * strat and end.
 */
BOOL initializeEnvironment (void)
{
    Init32MemDC();
    ncsInitialize ();
    ncs4TouchInitialize();
    delayLoadRes();

    return TRUE;
}

void finalizeEnvironment ()
{
    ncs4TouchUninitialize();
    ncsUninitialize ();
    Release32MemDC();
}

static BOOL idleHandler(HWND hwnd, LINT timer_id, DWORD tick_count)
{
    Activity* currApp = ACTIVITYSTACK->top();

    if (currApp) {
        assert (IsMainWindow (currApp->hwnd ()));
        if (SendMessage(currApp->hwnd (), Activity::MSG_SCREENSAVE, 0, 0) != 0) {
            ACTIVITYSTACK->home();
        }

    }
    
    return TRUE;
}

static BOOL delayLoadRes ()
{
    static int step = 0;
    static RES_NODE res_list[] =
    {
        #include "./res/resource"
        { NULL, 0, 0, 0, 0}
    };

    if (step > 10) {
        return TRUE;
    }

    DWORD tick = GetTickCount();
    int count = StepLoadRes(res_list, step);
    db_info("StepLoadRes>> step: %d count: %d used time: %ld\n", step, count, GetTickCount() - tick);

    step++;
    return TRUE;
}

static LRESULT ActivityLoaderProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case MSG_CREATE:
        {
            // load resource
#ifdef STEPLOADRES
            SetTimerEx (hWnd, LOAD_RESOURCE_TIMER_ID, LOAD_RESOURCE_TIMER, (TIMERPROC)delayLoadRes);
#else

#endif
            ACTIVITYSTACK->push("ScreenLockActivity");
        }
        break;
        case MSG_PAINT:
        {
        }
        return 0; 
        case MSG_CLOSE:
        {
            for (;;) {
                if (ACTIVITYSTACK->depth() == 0) {
                    break;
                }

                ACTIVITYSTACK->pop();
            }
        }
        
        DestroyMainWindow(hWnd);
        break;
        default:
            break;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int MiniGUIMain(int argc, const char* argv[])
{
    initializeEnvironment ();
    
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

    int screenW = GetGDCapability(HDC_SCREEN,GDCAP_HPIXEL);
    int screenH =GetGDCapability(HDC_SCREEN,GDCAP_VPIXEL);
    
    memset(&CreateInfo, 0, sizeof(CreateInfo));
    CreateInfo.dwStyle = WS_NONE;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "ActivityLoader";
    CreateInfo.hMenu = 0;
    //CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = ActivityLoaderProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = screenW;
    CreateInfo.by = screenH;
    CreateInfo.iBkColor = COLOR_black;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    finalizeEnvironment (); 
    return 0;
}
