#ifndef  ACCESS_CONTROLLER_INC
#define  ACCESS_CONTROLLER_INC

//1. The .cc .cpp .cxx related header files
//2. C system include files.
//3. C++ system include files.
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <queue>

#if 0
#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>

namespace sc = boost::statechart;
#endif

//4. Other libraries' .h files.
#include <CedarMediaPlayer.h>
#include <utils/WorkQueue.h>

#ifdef USE_ANDROID_UTILS_SINGLETON
    #include <utils/Singleton.h>
    using namespace android;
#endif

#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"

//5. Your project's .h files.
#include "common.h"
#include "debug.h"
#include "tinyplay.h"
#include "SoundPlayer.h"
#include "GenericValidator.h"
#include "AccessRecord.h"
#include "StorageManager.h"
#include "XiaoEActivity.h"

#undef LOG_TAG
#define LOG_TAG "AccessController"

using namespace android;
using namespace rapidjson;

#ifdef USE_ANDROID_UTILS_SINGLETON
class AccessController : public Singleton<AccessController>
#else
class AccessController
#endif
{
// 1. public members
public:
    // 1.1. typedefs
    // 1.2. nested enums
    // 1.3. nested structs
    // 1.4. nested classes
    class AccessWorkUnit : public WorkQueue::WorkUnit
    {
    public:
        AccessWorkUnit(GenericValidator* v, 
                               Handler _onValidated = NULL,
                               void* _arg = NULL,
                               HWND _hwnd = HWND_NULL)
                               : mValidator(v),
                                 onValidated(_onValidated),
                                 arg(_arg),
                                 hwnd(_hwnd)
        {
        }

        ~AccessWorkUnit()
        {
            delete mValidator;
        }

        bool run()
        {
            if(mValidator->validate()) {
                db_msg("<< Validate OK >>\n");
                sleep(3);
                db_msg("<< Open Door >>\n");
                tinyplay_SetPlayFileName("/system/res/others/opendoor.wav");
                tinyplay_RequestPlay(1);
                //SOUNDPLAYER.play(SoundPlayer::SOUND_KEYTONE);
                
                time_t now;
                time(&now);
                
                AccessRecord record(0,
                    mValidator->modeid(),
                    mValidator->dumpcode(), now, NULL);

                STORAGEMANAGER.store(record);
                
                AccessRecord::JsonConverter jc(record);
                printf("Record: %s\n", jc.getString());
            }

            db_error("vadilate failed(%d)\n", mValidator->why());
            if(onValidated) {
                if(hwnd != HWND_NULL)
                    XiaoEActivity::runOnUiThread(hwnd, 
                        (XiaoEActivity::Handler)onValidated, mValidator->why());
                else
                    onValidated(arg, mValidator->why());
            }
            
            return true;
        }
    private:
        GenericValidator* mValidator;
        Handler onValidated;
        void* arg;
        HWND hwnd;
    };

#if 0
    /* State Machine      */
    struct Closed;
    struct DoorStateMachine : sc::state_machine< DoorStateMachine, Closed > {};
    /* |-event classes    */
    /*   |-open  event:   */struct EvOpen : sc::event<EvOpen> {};
    /*   |-close event:   */struct EvClose : sc::event<EvClose> {};
    /*   |-timeout event: *///struct EvTimeOut : sc::event<EvTimeOut> {};

    /* |-state classes    */
    /*   |-closed state:  */struct Closed : sc::simple_state< Closed, DoorStateMachine >
    /*   |                */{
    /*   |                */  public:
    /*   |                */    typedef sc::transition< EvOpen, Open > reactions;
    /*   |                */};
    /*   |-open state:    */struct Open : sc::simple_state< Open, DoorStateMachine >
    /*   |                */{
    /*   |                */  public:
    /*   |                */    typedef sc::transition< EvClose, Closed > reactions;
    /*   |                */};
#endif
    // 1.5. consts
    // 1.6. constructors
    // 1.7. destructors
    // 1.8. member functions
    // If the value of 'hwnd' is specified, the handler
    // will be run in the UI thread, or it will be run directly
    // in the worker thread.
    // NOTE:
    // if the handler run in the UI thread, it's first parameter
    // is mgncs' main window object.(i.e. mMainWnd* )
    // so arg is no used.
    void work(const char* validatorName,
                const char* code, 
                    Handler onValidated = NULL,
                      void* arg = NULL,
                       HWND hwnd = HWND_NULL)
    {
        GenericValidator* validator = 
            ValidatorFactory::singleton()->create(validatorName, code);
        if(!validator) {    
            db_error("%s not found!\n", validatorName);
            exit(1);
        }
        
        mWorkQ.schedule(new AccessWorkUnit(validator, onValidated, arg, hwnd));
    }
    
    // 1.9. member variables
#ifndef USE_ANDROID_UTILS_SINGLETON
    // get the single instance of AccessController
    static AccessController& singleton();
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
    AccessController();
    // 3.7. destructors
    virtual ~AccessController();

    // 3.8. member functions
    // 3.9. member variables
    WorkQueue mWorkQ;    
#ifndef USE_ANDROID_UTILS_SINGLETON
    // store the single instance of ActivityStack
    static AccessController* s_single;
#endif
#ifdef USE_ANDROID_UTILS_SINGLETON
    friend class Singleton<AccessController>;
#endif
};

#ifdef USE_ANDROID_UTILS_SINGLETON
    #define ACCESSCONTROLLER   AccessController::getInstance()
#else
    #define ACCESSCONTROLLER   AccessController::singleton()
#endif

#endif
