/*!============================================================================
 * @file ResourceManager.cc 
 * @Synopsis Resource Manager source. 
 * @author WangXuBin
 * @version 1.0
 *  Company: Beijing Feynman Software Technology Co., Ltd.
 */

#include "debug.h"
#include "ResourceManager.h"

#define LOG_TAG "ResourceManager"

static HDC s_hw_memRefDC = HDC_INVALID;
static HDC s_sw_memRefDC = HDC_INVALID;

static HDC s_hw_mem32RefDC = HDC_INVALID;
//static HDC s_sw_mem32RefDC = HDC_INVALID;

void Init32MemDC (void)
{
#ifdef USE_32HW_MEMDC
    s_hw_memRefDC = CreateMemDC(1, 1, 32, MEMDC_FLAG_HWSURFACE,
            0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
#else
    s_hw_memRefDC = HDC_SCREEN;
#endif
#ifdef USE_32SW_MEMDC
    s_sw_memRefDC = CreateMemDC(1, 1, 32, MEMDC_FLAG_SWSURFACE,
            0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
#else
    s_sw_memRefDC = HDC_SCREEN;
#endif

    s_hw_mem32RefDC = CreateMemDC(1, 1, 32, MEMDC_FLAG_HWSURFACE,
            0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

void Release32MemDC (void)
{
#ifdef USE_32HW_MEMDC
    if (s_hw_memRefDC != HDC_INVALID)
        DeleteMemDC (s_hw_memRefDC);
    if (s_sw_memRefDC != HDC_INVALID)
        DeleteMemDC (s_hw_memRefDC);
#endif
    if (s_hw_mem32RefDC != HDC_INVALID)
        DeleteMemDC (s_hw_mem32RefDC);
}

#ifndef COMP_HW_MEMD
HDC CreateMyCompatibleDC(HDC hdc, int w, int h)
{
    HDC ret = HDC_INVALID;
    int depth = GetGDCapability(hdc, GDCAP_BITSPP);
    int Amask = GetGDCapability(hdc, GDCAP_AMASK);
    int Rmask = GetGDCapability(hdc, GDCAP_RMASK);
    int Gmask = GetGDCapability(hdc, GDCAP_GMASK);
    int Bmask = GetGDCapability(hdc, GDCAP_BMASK);

    ret = CreateMemDC(w, h, depth, MEMDC_FLAG_SWSURFACE,
            Rmask, Gmask, Bmask, Amask);
    return ret;
}
#endif

HDC Get32MemDC (void)
{
    return s_hw_memRefDC;
}

HDC Get32SwMemDC (void)
{
    return s_sw_memRefDC;
}

void* Load32Resource (const char* res_name, int type, DWORD usr_param)
{
    HDC hdc = s_hw_memRefDC;

    if (hdc == HDC_INVALID) {
        hdc = HDC_SCREEN;
    }

    return LoadResource (res_name, type, (DWORD) hdc);
}

int StepLoadRes (RES_NODE *node_list, int step)
{
    int cnt;

    RES_NODE *res_node = node_list;

    cnt = 0;

    db_debug ("start load resource.\n");

    for (;;) {
        if (res_node->res_name == NULL) {
            break;
        }

        if (res_node->flag == 1) {
            if ((step == 0) || (res_node->step == step)) {
                if (res_node->bits == 32) {
                    LoadResource (res_node->res_name, res_node->type, (DWORD) s_hw_mem32RefDC);
                }
                else {
                    Load32Resource (res_node->res_name, res_node->type, (DWORD) HDC_SCREEN);
                }

                cnt++;
                db_debug ("\tload %s\n", res_node->res_name);
            }
        } /* if */

        res_node++;
    } /* for */

    db_debug ("end load resource.(%d)\n", cnt);
    return cnt;
}

int UnLoadAllRes (RES_NODE *node_list)
{
    int cnt;

    RES_NODE *res_node = node_list;

    cnt = 0;

    db_debug ("start unload resource.\n");

    for (;;) {
        if (res_node->res_name == NULL) {
            break;
        }

        if (res_node->flag == 1) {
            ReleaseRes (Str2Key(res_node->res_name));
            cnt++;
            db_debug ("\tunload %s\n", res_node->res_name);
        } /* if */

        res_node++;
    } /* for */

    db_debug ("end unload resource.(%d)\n", cnt);
    return cnt;
}
