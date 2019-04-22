/*! ============================================================================
 * @file Activity.cpp
 * @Synopsis  
 * @author DongKai
 * @version 1.0
 *  Company: Beijing Feynman Software Technology Co., Ltd.
 */
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


ActivityFactory *ActivityFactory::s_single = NULL;

// public:

// constructor & destructor
Activity::Activity() :
    m_pushIndex(0), m_hwnd(HWND_INVALID), m_style(Activity::STYLE_ALPHA), m_needSwitchEffect(true)
{
}

Activity::~Activity()
{
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
    ShowWindow(m_hwnd, SW_SHOWNORMAL);
}

// hide the window of this activity
void Activity::hide()
{
    ShowWindow(m_hwnd, SW_HIDE);
}

// get snapshot of this activity
HDC Activity::snapshot() const
{
    return GetWindowForeground(m_hwnd, FALSE);
}

