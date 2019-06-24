#ifndef TOAST_H
#define TOAST_H

#include "macros.h"
#include "XiaoEActivity.h"

class Toast : public XiaoEActivity
{
// 1. public members
public:
    // 1.1. typedefs
    // 1.2. nested enums
    // 1.3. nested structs
    // 1.4. nested classes
    // 1.5. consts
    // 1.6. constructors
    Toast(const char* caption = NULL);
    // 1.7. destructors
    ~Toast();
    // 1.8. member functions
    void autosize();
    static Toast* makeText(const char* caption)
    {
        Toast* toast = new Toast(caption);
        toast->create();
        SetWindowCaption(toast->hwnd(), caption);
        toast->autosize();
        return toast;
    }
    // 1.9. member variables

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
    // 3.7. destructors
    // 3.8. member functions
    BOOL onCreate(mMainWnd* self, DWORD dwAddData);
    void onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv);
    //BOOL onIntent(mMainWnd* self, int message,
      //                    WPARAM wParam, LPARAM lParam);
    
    static NCS_MNWND_TEMPLATE window_template;
    static NCS_WND_TEMPLATE control_templates[];
    DISALLOW_COPY_AND_ASSIGN(Toast);
    // 3.9. member variables
};
#endif // << end #ifndef TOAST_H >>

