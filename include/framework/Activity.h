#ifndef  ACTIVITY_INC
#define  ACTIVITY_INC

//1. The .cc .cpp .cxx related header files
//2. C system include files.
#include <string.h>
#include <assert.h>
//3. C++ system include files.
//4. Other libraries' .h files.
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <mgeff/mgeff.h>
//5. Your project's .h files.
#include "debug.h"
#include "ContentValues.h"
#include "GenericFactory.h"

#undef LOG_TAG
#define LOG_TAG "Activity"

class ContentResolver;

class Activity
{
public:
    // constructor & destructor
    Activity();
    virtual ~Activity();

    // get activity pointer from window handle
    static Activity* getActivityFromHWND(HWND hwnd)
    {
        return (Activity*)GetWindowAdditionalData(hwnd);
    }

    // create this activity, including creating window, setting additional data, etc.
    int create();

    // show the window of this activity
    virtual void show();

    // hide the window of this activity
    virtual void hide();

    // get window handle of this activity
    HWND hwnd() const { return m_hwnd; }

    // get snapshot of this activity
    HDC snapshot() const;

    // get style of this activity
    int style() const { return m_style; }

    // determine whether I need the switch effect provide by the framework
    //bool needSwitchEffect() const { return m_needSwitchEffect; }

    enum STYLE
    {
        STYLE_NONE,
        STYLE_PUSH,
        STYLE_ZOOM,
        STYLE_ALPHA,
    };

    enum MESSAGE
    {
        MSG_INTENT = MSG_USER,
        MSG_SCREENSAVE,
        MSG_FRAMEWORK,
    };

    // index for push style
    int m_pushIndex;

protected:

    virtual int onStart() { return 0; }
    virtual int onStop() { return 0; }

    // Give you a chance to do some special things when switching to another activity.
    // You can override this behavior in your own inherited class.
    virtual int onPause() { return 0; }

    // Give you a chance to do some special things when switching back from another activity.
    // You can override this behavior in your own inherited class.
    virtual int onResume() { return 0; }

    virtual int onBack() { return 0; }
    virtual int onHome() {return 0;}

    // Create window for this activity, you must override this method to create your own 
    // window for your activity.
    virtual HWND createHWND() = 0;

protected:

    // store window handle of this activity
    HWND m_hwnd;

    // indicate style of activity, default is STYLE_NONE
    int m_style;

    // indicate if this activity need a switch effect or not, default is TRUE
    //bool m_needSwitchEffect;

    friend class ActivityStack;
};

class Intent
{
    public:
        enum ACTION {
            ACTION_MAIN,
            ACTION_VIEW,
        };
        static Intent* newIntent(int action = ACTION_MAIN, std::string uri="")
        {
            return new Intent(action, uri);
        }
        static void deleteIntent(Intent* intentPtr)
        {
            assert(intentPtr);
            delete intentPtr;
        }

    public:
        int action() const
        {
            return m_action;
        }
        const std::string& uri() const
        {
            return m_uri;
        }

        void putExtra(const std::string& key, const boost::any& value)
        {
            m_extras[key] = value;
        }

        const boost::any& getExtra(const std::string& key) const
        {
            ExtraMap::const_iterator found = m_extras.find(key);
            static boost::any empty;

            if (found == m_extras.end()) {
                return empty;
            }
            else {
                return found->second;
            }
        }

        int getInt(const std::string& key) const
        {
            ExtraMap::const_iterator found = m_extras.find(key);

            if (found == m_extras.end()) {
                return 0;
            }
            else {
                return boost::any_cast<int>(found->second);
            }
        }

        const char* getCString(const std::string& key) const
        {
            ExtraMap::const_iterator found = m_extras.find(key);

            if (found == m_extras.end()) {
                return "";
            }
            else {
                return boost::any_cast<const char*>(found->second);
            }
        }

        const std::string& getString(const std::string& key) const
        {
            ExtraMap::const_iterator found = m_extras.find(key);
            static std::string empty("");

            if (found == m_extras.end()) {
                return empty;
            }
            else {
                return boost::any_cast<const std::string&>(found->second);
            }
        }

    protected:
        Intent(int action = ACTION_MAIN, std::string uri = "")
            : m_action(action), m_uri(uri) {}
        virtual ~Intent() {}

    protected:

        int m_action;
        std::string m_uri;
        ExtraMap m_extras;
};

#define REGISTER_ACTIVITY(_class) \
static T * my_create() \
{ \
    return new _class(); \
} \
void realRegister##_class (void) \
{ \
    GenericFactory<Activity>::singleton()->register(#_class, my_create); \
}

#define DO_REGISTER_ACTIVITY(_class) \
    extern void realRegister##_class (void); \
    realRegister##_class ()

#define AUTO_REGISTER_ACTIVITY(_class) \
    static struct _ActivityFactory_##_class { \
        static Activity *create() { \
            return new _class(); \
        } \
        _ActivityFactory_##_class() { \
            GenericFactory<Activity>::singleton()->doRegister(#_class, create); \
        } \
    } _autoRegister_##_class

#endif   /* ----- #ifndef ACTIVITY_INC  ----- */
