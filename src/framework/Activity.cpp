//1. The .cc .cpp .cxx related header files
#include "Activity.h"

//2. C system include files.


//3. C++ system include files.
#include <cassert>
#include <sstream>

//4. Other libraries' .h files.
    
//5. Your project's .h files.
#include "utility.h"
#include "ContentResolver.h"
#include "ActivityStack.h"

template<> GenericFactory<Activity> *GenericFactory<Activity>::s_single = NULL;
#define ACTIVITY_COUNTER
#ifdef ACTIVITY_COUNTER
static int total_activities = 0;
#endif

// public:

// constructor & destructor
Activity::Activity() :
    m_pushIndex(0), m_hwnd(HWND_INVALID), m_style(Activity::STYLE_ALPHA)//, m_needSwitchEffect(true)
{
#ifdef ACTIVITY_COUNTER
    total_activities++;
    db_info("total activities = %d\n", total_activities);
#endif
}

Activity::~Activity()
{
    printf("%s %d >>\n", __func__, __LINE__);
#ifdef ACTIVITY_COUNTER
    total_activities--;
    db_info("total activities = %d\n", total_activities);
#endif
}

// create this activity, including creating window, setting additional data, etc.
int Activity::create() 
{
    db_msg("create called!\n");
    
    m_hwnd = createHWND();

    db_msg("created window by createHWND: %p!\n", m_hwnd);

    if (m_hwnd == HWND_INVALID || m_hwnd == HWND_NULL) {
        db_error("Create Window failed!\n");
        return -1;
    }

    // store 'this' pointer for static function.
    SetWindowAdditionalData(m_hwnd, (DWORD)this);
    return 0;
}

// show the window of this activity
void Activity::show()
{
    db_debug("show window[@%p] >>\n", m_hwnd);
    ShowWindow(m_hwnd, SW_SHOWNORMAL);
}

// hide the window of this activity
void Activity::hide()
{
    db_debug("hide window[@%p] >>\n", m_hwnd);
    ShowWindow(m_hwnd, SW_HIDE);
}

// get snapshot of this activity
HDC Activity::snapshot() const
{
    return GetWindowForeground(m_hwnd, FALSE);
}

