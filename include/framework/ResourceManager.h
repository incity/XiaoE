/*!============================================================================
 * \file ResourceManager.hh 
 * \brief Resource Manager headfile. 
 * \author WangXuBin
 * \version 1.0
 *
 *  Company: Beijing Feynman Software Technology Co., Ltd.
 */
#ifndef __RESOURCE_MANANGER__H_
#define __RESOURCE_MANANGER__H_
#ifdef __cplusplus
extern "C" {
#endif

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

//#define USE_32HW_MEMDC
#define USE_32SW_MEMDC
//#define COMP_HW_MEMDC

/**
 * \brief struct of resource node
 */
typedef struct _RES_NODE {
    const char *res_name;
    int         type;
    int         bits;
    int         flag;
    int         step;
} RES_NODE;

/**
 * \fn Init32MemDC (void)
 */
void Init32MemDC (void);

/**
 * \fn Release32MemDC (void)
 */
void Release32MemDC (void);

/**
 * \fn Init32Resource (const char *res_name, int type, DWORD usr_param)
 */
void* Load32Resource (const char* res_name, int type, DWORD usr_param);

/**
 * \fn Get32MemDC (void)
 */
HDC Get32MemDC (void);

/**
 * \fn Get32SwMemDC (void)
 */
HDC Get32SwMemDC (void);

/**
 * \fn CreateSoftCompatibleDC(void)
 */
#ifdef COMP_HW_MEMDC
#define CreateMyCompatibleDC(hdc, w, h) CreateCompatibleDCEx(hdc, w, h)
#else
HDC CreateMyCompatibleDC(HDC hdc, int w, int h);
#endif

/**
 * \fn StepLoadRes (RES_NODE *node_list, int step);
 *
 * step  0   load all resource
 */
int StepLoadRes (RES_NODE *node_list, int step);

/**
 * \fn LoadAllRes (RES_NODE *node_list);
 */
#define LoadAllRes(node_list) StepLoadRes(node_list,0)

class ResourceManager;

class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager();
	ResourceManager& operator=(const ResourceManager& o);

public:
    static ResourceManager* getInstance();
    BOOL lazyLoad();
    void unload();
private:
    int m_step;
    RES_NODE *m_resources;
    static ResourceManager *sInstance;
};


#ifdef __cplusplus
}
#endif
#endif
