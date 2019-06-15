/*!============================================================================
 * @file ActivityStack.h 
 * @Synopsis  
 * @author DongKai
 * @version 1.0
 *  Company: Beijing Feynman Software Technology Co., Ltd.
 */

// refactored @ 2010-11-22 by min
#ifndef  _ACTIVITYSTACK_H
#define  _ACTIVITYSTACK_H
//#undef USE_ANDROID_UTILS_SINGLETON
//1. The .cc .cpp .cxx related header files
//2. C system include files.
//3. C++ system include files.
#include <string>
#include <vector>
#ifdef USE_ANDROID_UTILS_SINGLETON
    #include <utils/Singleton.h>
    using namespace android;
#endif
//4. Other libraries' .h files.

//5. Your project's .h files.
#include "Activity.h"

/** 
 * @synopsis  A stack for activities manager.
 */
#ifdef USE_ANDROID_UTILS_SINGLETON
class ActivityStack : public Singleton<ActivityStack>
#else
class ActivityStack
#endif
{
public:
    typedef std::pair<std::string, Activity*> ActivityEntry;
    typedef std::vector<ActivityEntry> ActivityCollection;
    
#ifndef USE_ANDROID_UTILS_SINGLETON
    // get the single instance of ActivityStack
    static ActivityStack& singleton();
#endif

    // get the top activity in stack
    Activity* top() const;

    // return activity name of current app
    const char* currentActivityName() const;

    // Create a new activity and bring it to the top of the stack, 
    // using activityName to specify which Activity will be created,
    // using intentPtr to specify your intend (optionally).
    bool push(const char* activityName, Intent* intentPtr = NULL);

    // Remove the top activity from the stack, and send MSG_CLOSE message to 
    // the window of the activity, instead of destroying it directly.
    bool pop();
    void clear();

    // Back to previous view
    bool back();

    // Return to home
    bool home();

    // get depth of the stack
    int depth() const { return m_activities.size(); }

    // This method will find the first Activity named 'activityName' in the stack from top to bottom,
    // if the Activity is existed, then pop to that Activity by calling popTo method;
    // if the Activity is not existed, then create a new Activity named activityName, and push it into the stack.
    void navigateTo(const char* activityName, Intent* intentPtr = NULL);

    void dump();
private:
    // constructor & desctructor, for internal use only
#ifdef USE_ANDROID_UTILS_SINGLETON
    friend class Singleton<ActivityStack>;
#endif
    ActivityStack();
    virtual ~ActivityStack();

    Activity* innerPush(const char* activityName, Intent* intentPtr);
    bool innerPop();
    
    // Do the same thing as pop(), but supply a parameter "which" to specify 
    // which activity you want to show up, and all activities above it will be poped.
    // Notice that, if you call this function with parameter NULL, the stack will be cleared.
    // return how much activities has been poped up
    int popTo(Activity* which, Intent* intentPtr = NULL);
    
    // get the activity under the top
    Activity* _underTop() const;

    void _doSwitchEffect(Activity* prev, Activity* next, BOOL switchTo=TRUE);

    // search the first Activity named 'activityName' in the stack in the order from top to bottom
    Activity* searchActivityByName(std::string activityName);
    

    // store all activities
    ActivityCollection m_activities;

    int m_status;
    enum STATUS {
        READY = 0,
        PUSH,
        POP,
    };

#ifndef USE_ANDROID_UTILS_SINGLETON
    // store the single instance of ActivityStack
    static ActivityStack* s_single;
#endif
};

#ifdef USE_ANDROID_UTILS_SINGLETON
    #define ACTIVITYSTACK   ActivityStack::getInstance()
#else
    #define ACTIVITYSTACK   ActivityStack::singleton()
#endif

#endif   /* ----- #ifndef ACTIVITYSTACK_INC  ----- */

