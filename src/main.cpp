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
// WARNING:
// there is a macro conflict between mgncs.h:PRIVATE and 
// android::Mutex::PRIVATE
// SO we can not include both files at the same time.
//#include <mgncs/mgncs.h>
//#include <mgncs4touch/mgncs4touch.h>


//5. Your project's .h files.
#include "debug.h"
#include "version.h"
#include "Activity.h"
#include "ActivityStack.h"
#include "ResourceManager.h"

extern "C" {
    extern BOOL ncs4TouchInitialize(void);
    extern BOOL ncsInitialize(void);
    extern void ncsUninitialize(void);
    extern void ncs4TouchUninitialize(void);
}

#undef LOG_TAG
#define LOG_TAG "Main"
#define SCREEN_IDLE_TIMER_ID	1
#define SCREEN_IDLE_TIMER	(30*100)

/* 
 * this is initialize and finalize function, please call it when desktop
 * strat and end.
 */
BOOL initializeEnvironment(void)
{
    Init32MemDC();
    ncsInitialize();
    ncs4TouchInitialize();
    return TRUE;
}

void finalizeEnvironment()
{
    ncs4TouchUninitialize();
    ncsUninitialize();
    Release32MemDC();
}

static BOOL screenIdleHandler(HWND hwnd, LINT timer_id, DWORD tick_count)
{
    db_debug("screen idle.\n");
    Activity* currApp = ACTIVITYSTACK.top();

    if (currApp) {
        HWND hwnd = currApp->hwnd();
        assert(IsMainWindow(hwnd));
        int ret = SendMessage(hwnd, Activity::MSG_SCREENSAVE, 0, 0);
        db_debug("Could do screensave?...(%s)", ret?"yes":"no");
        if ( ret != 0) {
            // 返回到Home，应用可以通过重写Activity::onHome方法来禁止返回Home
            // onHome() 返回 1表示当前界面禁止(ACTIVITYSTACK->home())返回Home
            ACTIVITYSTACK.home();
            ACTIVITYSTACK.push("BlackScreenActivity");
        }
    }
    
    return TRUE;
}

static LRESULT DesktopProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message) {
        case MSG_CREATE:
        {
            mGEffInit();
            
            ResourceManager* rm = ResourceManager::getInstance();
            rm->lazyLoad();
            
            ACTIVITYSTACK.push("HomeActivity");
        }
        break;
        /*case MSG_PAINT:
        {
            HDC hdc = BeginPaint(hWnd);
            RECT rc;
            GetClientRect(hWnd, &rc);

            ncsCommRDRFillHalfRoundRect(hdc, &rc, 0, 0, COLOR_black, 0);
            EndPaint(hWnd, hdc);
        }
        return 0;*/
        case MSG_CLOSE:
            ACTIVITYSTACK.clear();
            DestroyMainWindow(hWnd);
        break;
        default:
            break;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int MiniGUIMain(int argc, const char* argv[])
{
    initializeEnvironment();
    
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

    ResourceManager* rm = ResourceManager::getInstance();
    rm->lazyLoad();
    
    int screenW = GetGDCapability(HDC_SCREEN,GDCAP_HPIXEL);
    int screenH = GetGDCapability(HDC_SCREEN,GDCAP_VPIXEL);
    
    memset(&CreateInfo, 0, sizeof(CreateInfo));
    CreateInfo.dwStyle = WS_NONE;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "Desktop";
    CreateInfo.hMenu = 0;
    //CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = DesktopProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = screenW;
    CreateInfo.by = screenH;
    CreateInfo.iBkColor = COLOR_black;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    hMainWnd = CreateMainWindow(&CreateInfo);
    if (hMainWnd == HWND_INVALID) {
        assert(0);
        return -1;
    }

    SetTimerEx(hMainWnd, SCREEN_IDLE_TIMER_ID, SCREEN_IDLE_TIMER,(TIMERPROC)screenIdleHandler);
    
    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        
        if (Msg.message >= MSG_FIRSTMOUSEMSG && Msg.message <= MSG_LASTMOUSEMSG) {
            ResetTimerEx(hMainWnd, SCREEN_IDLE_TIMER_ID, SCREEN_IDLE_TIMER,(TIMERPROC)screenIdleHandler);
        }

        DispatchMessage(&Msg);
#if 0
        if (Msg.message != MSG_IDLE)
            db_debug("Activity[@%p] <= %s(0x%lx, 0x%lx)\n", 
                Msg.hwnd, Message2Str(Msg.message), Msg.wParam, Msg.lParam);
#endif
    }
    
    KillTimer(hMainWnd, SCREEN_IDLE_TIMER_ID);
    MainWindowThreadCleanup(hMainWnd);
    
    finalizeEnvironment();

    mGEffDeinit();
    rm->unload();
    db_info("XiaoE (Normal) Exit.");
    return 0;
}
