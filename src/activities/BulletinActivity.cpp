#include "BulletinActivity.h"

AUTO_REGISTER_ACTIVITY(BulletinActivity);

#define ACTIVITY_NAME "BulletinActivity"
#undef LOG_TAG
#define LOG_TAG ACTIVITY_NAME

enum {
    ID_BUTTON_MAIN = 100,
    ID_HTEXTVIEW,
    ID_VTEXTVIEW,
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
BulletinActivity::BulletinActivity()
                 : XiaoEActivity(&BulletinActivity::window_template)
{
    m_style = STYLE_ZOOM;
    background_image = (BITMAP*)calloc(1, sizeof(BITMAP));
    assert(background_image);
    
    LoadBitmap(HDC_SCREEN, background_image, 
        "./res/images/unlocking/background.png");
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
BulletinActivity::~BulletinActivity()
{
    UnloadBitmap(background_image);
    free(background_image);
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   3. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++
// |  control properties  |
// ++++++++++++++++++++++++
static NCS_PROP_ENTRY home_button_props[] = {
    {0, 0},
};

static NCS_PROP_ENTRY htextview_props[] = {
    {NCSP_TEXTVIEW_ALIGN, (DWORD)NCS_ALIGN_CENTER},
    {NCSP_TEXTVIEW_VALIGN, (DWORD)NCS_VALIGN_CENTER},
    {0, 0},
};

static NCS_PROP_ENTRY vtextview_props[] = {
    {NCSP_TEXTVIEW_ALIGN, (DWORD)NCS_ALIGN_LEFT},
    {NCSP_TEXTVIEW_AUTOWRAP, (DWORD)1},
    {0, 0},
};

// ++++++++++++++++++++++++
// |  control render      |
// ++++++++++++++++++++++++
static NCS_RDR_INFO home_button_render[] = {
    {"skin", "skin", NULL}
};

// ++++++++++++++++++++++++
// |  control handlers    |
// ++++++++++++++++++++++++
static BOOL home_button_onCreate(mButton*, DWORD);
static void home_button_notify(mWidget *, int, int, DWORD);

static NCS_EVENT_HANDLER home_button_handlers [] = {
    {MSG_CREATE, NCS_EVENT_HANDLER_CAST(home_button_onCreate)},
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, home_button_notify),
	{0, NULL}	
};

static NCS_EVENT_HANDLER textview_handlers [] = {
    {MSG_LBUTTONDOWN, NCS_EVENT_HANDLER_CAST(SpeedMeterMessageHandler)},
    {MSG_LBUTTONUP, NCS_EVENT_HANDLER_CAST(SpeedMeterMessageHandler)},
    {MSG_MOUSEMOVE, NCS_EVENT_HANDLER_CAST(SpeedMeterMessageHandler)},
	{0, NULL}	
};

// +++++++++++++++++++++++++++
// |   3.8. member functions |
// +++++++++++++++++++++++++++
BOOL BulletinActivity::onCreate(mMainWnd* self, DWORD dwAddData )
{
    db_debug(" >> \n");

    return TRUE;
}

void BulletinActivity::onPaint(mMainWnd *self, HDC hdc, const CLIPRGN* inv)
{
}

BOOL BulletinActivity::onScreensave(mMainWnd* self, int message, WPARAM wParam, LPARAM lParam)
{
    return TRUE; // enable screensave
}

BOOL BulletinActivity::onEraseBackground(mMainWnd *self, HDC hdc, const PRECT clip)
{
    RECT rc;
    GetClientRect(self->hwnd, &rc);

    if(background_image) {
        FillBoxWithBitmap(hdc, 0, 0, RECTW(rc), RECTH(rc), background_image);
    }
    
    return TRUE;
}

static BOOL home_button_onCreate(mButton* self, DWORD dwAddData )
{
    DWORD key = (DWORD)Str2Key("images/unlocking/home_button.png");

    ncsSetElement(self, NCS_IMAGE_BUTTON, key);

    return TRUE;
}

static void home_button_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    ACTIVITYSTACK.back();
}

// +++++++++++++++++++++++++++
// |   3.9. member variables |
// +++++++++++++++++++++++++++
BITMAP* BulletinActivity::background_image = NULL;

NCS_WND_TEMPLATE BulletinActivity::control_templates[] = {
    {
        NCSCTRL_BUTTON,
        ID_BUTTON_MAIN,
        684, 369, 106, 106,
        WS_VISIBLE | NCSS_BUTTON_IMAGE,
        WS_EX_TRANSPARENT,
        NULL,
        home_button_props,
        home_button_render,
        home_button_handlers,
        CTRL_TEMPL_ZERO_AFTER_HANDLERS
    },
    {
        NCSCTRL_TEXTVIEW, 
        ID_HTEXTVIEW,
        100, 40, 600, 40,
        WS_VISIBLE,
        WS_EX_TRANSPARENT,
        "踩着自己的节奏 中国扩大金融开放",
        htextview_props, //props,
        NULL, //rdr_info
        textview_handlers, //handlers,
        NULL, 0, 0, 0,
        "*-simfang-rrT*nn-*-32-UTF-8",
        CTRL_TEMPL_ZERO_AFTER_FONTNAME
    },
    {
        NCSCTRL_TEXTVIEW, 
        ID_VTEXTVIEW,
        100, 96, 600, 270,
        WS_VISIBLE | NCSS_TEXTVIEW_VERTICAL,
        WS_EX_TRANSPARENT,
        "    中国银保监会主席郭树清日前表示，中国近期将推出12条新措施，进一步扩大银行业保险业的对外开放。这些措施包括，对来华设立外资法人银行、入股信托公司、经营保险经纪公司等外资金融机构取消对其资产总额的准入要求；放宽中外资投资设立消费金融公司准入政策；取消外资银行开办人民币业务审批等。\n"
        "    这是继去年4月中国推出15条银行业保险业开放措施基本落地之后，中国又一轮金融业对外开放举措蓄势待发。无疑，它将进一步提升中国银行业保险业的开放力度和市场化水平，完善中国金融领域的营商环境，激发外资参与中国金融业发展的活力，并从根本上推动中国金融服务业的竞争意识、市场意识、创新意识、服务意识。\n"
        "    金融业是一国经济发展的稳定器与动力。关注中国经济的人应该注意到，自中共十九大报告提出要推动形成全面开放新格局之后，中国国家主席习近平即在2018博鳌亚洲论坛年会上宣布包括金融业在内的四大对外开放重要举措，今年中国政府工作报告也提出要落实金融等行业改革开放举措，中国的金融开放正按照既定的战略部署，踩着自己的节奏，一步一个脚印地稳健推进，以不断增强服务实体经济的能力。\n"
        "    中国此次新推出的12条金融开放举措，是对中国金融业对外开放整体布局的进一步细化和落实，也是基于自身经济和金融发展规律需要的又一次主动作为。从具体内容来看，这12条措施有三个鲜明特点："
        "    一是突出强调内外资一致原则。比如，同时取消单家中资银行和单家外资银行对中资商业银行的持股比例上限，也同时放宽中资和外资金融机构投资设立消费金融公司方面的准入政策等，这为中外资金融机构提供了一视同仁、公平竞争的市场环境，从根本上符合中国新通过的《外商投资法》要求。"
        "    二是降低外资金融机构进入中国市场的门槛，也就是对准备进入中国相关金融领域的外资金融机构取消了对其资产规模的数量型限制，这不仅能吸引更多“小而美”的外资机构来华从事金融服务，实现对各国外资金融机构的完全公平，同时也将促使中国资产规模相对较小的金融机构不断创新金融服务，提升竞争力，从根本上推动中国金融市场更好地努力服务实体经济，激发市场更大活力。"
        "    三是拓宽外资在华业务范围。比如，允许外资银行开业时即可经营人民币业务、经营“代理收付款项”业务等，这是对外资实施准入前国民待遇措施的落地，势必会进一步扩大外资机构在华经营空间。"
        "    中国改革开放历经40年，金融业对外开放走到今天相当不容易。从入世前主要服务于国内经济建设，到入世后将“走出去”与“引进来”相结合，中国金融业的服务水平、竞争能力与营商环境得到大幅提升，金融体系建设取得了明显成效，银行业保险业已形成包括国有、民营和外资在内等多元股权结构，其中，外资银行和外资保险公司在华资产占比为1.64%和6.36%。"
        "",
        vtextview_props, //props,
        NULL, //rdr_info
        textview_handlers, //handlers,
        NULL, 0, 0, 0,
        //"*-simfang-drn*nn-*-23-UTF-8",
        "*-simfang-rrT*nn-*-26-UTF-8",
        CTRL_TEMPL_ZERO_AFTER_FONTNAME
    },
};

NCS_MNWND_TEMPLATE BulletinActivity::window_template = 
    XIAOE_WINDOW_TEMPLATE(ACTIVITY_NAME, BulletinActivity::control_templates);

