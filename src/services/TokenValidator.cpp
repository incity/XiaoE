#include "TokenValidator.h"
#include <stdlib.h>

AUTO_REGISTER_VALIDATOR(TokenValidator);

#define VALIDATOR_NAME "TokenValidator"
#undef LOG_TAG
#define LOG_TAG VALIDATOR_NAME

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static int verifyCode(unsigned int password,
                           const char *communityNo,
                           const char *deviceNo,
                           const char *PrivateKey);

int TokenValidator::create(const char* code)
{
    assert(code);
    memset(mToken, 0, sizeof(mToken));

    strncpy(mToken, code, sizeof(mToken)-1);

    hexdump(mToken, sizeof(mToken)-1);

    return 0;
}

bool TokenValidator::validate()
{
    int ret = verifyCode(atoi(mToken), 
                      "1111-1111",
                      "123",
                      "www.aoke.com");
    db_debug("ret = %d", ret);
    return ret == 0;
}

const char* TokenValidator::dumpcode() const
{
    return mToken;
}

int TokenValidator::modeid() const
{
    return ACCESS_MODE_TOKEN;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |     static members                        |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |     static variables    |
// +++++++++++++++++++++++++++
static uint8_t remasks[10][10]=
{
   {9,0,5,1,6,2,7,3,8,4},
   {5,0,9,1,8,2,7,3,6,4},
   {4,5,0,6,1,7,2,8,3,9},
   {4,9,0,8,1,7,2,6,3,5},
   {9,4,5,3,6,2,7,1,8,0},
   {5,4,9,3,8,2,7,1,6,0},
   {0,5,4,6,3,7,2,8,1,9},
   {0,9,4,8,3,7,2,6,1,5},
   {6,3,8,4,9,2,7,0,5,1},
   {1,8,3,9,4,7,2,5,0,6}
};

static uint16_t hashs[] =
{
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
	0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
	0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
	0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
	0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
	0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
	0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
	0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
	0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
	0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
	0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
	0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
	0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
	0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
	0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
	0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
	0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
	0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
	0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
	0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
	0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
	0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
	0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

// +++++++++++++++++++++++++++
// |     static functions    |
// +++++++++++++++++++++++++++
static int getHash(const char *s)
{
	int i = 0;
	unsigned short result = 0;

	for(i=0;i<strlen(s);i++)
	{
		result = (unsigned short)((hashs[(result >> 8) ^ s[i]] ^ ((result << 8) & 0xFFFF)) & 0xFFFF);
	}
	return result;
}

static int compress(int hash)
{
	return (hash >> 12 & 0x000F) + (hash >> 8 & 0x000F) + (hash >> 4 & 0x000F) + (hash & 0x000F);
}

static int verifyCode(unsigned int password,
                           const char *communityNo,
                           const char *deviceNo,
                           const char *PrivateKey)
{
	char buff[100];
	int b1, b2, b3, b4, b5, b6, b7, b8;
	b1 = password / 10000000;//算法位
	b2 = password / 1000000 % 10;
	b3 = password / 100000 % 10;
	b4 = password / 10000 % 10;
	b5 = password / 1000 % 10;
	b6 = password / 100 % 10;
	b7 = password / 10 % 10;
	b8 = password % 10;

	//解码
	b2 = remasks[b1][b2];
	b3 = remasks[b1][b3];
	b4 = remasks[b1][b4];
	b5 = remasks[b1][b5];
	b6 = remasks[b1][b6];
	b7 = remasks[b1][b7];
	b8 = remasks[b1][b8];

	//计算口令到访时间 分钟
	int totalMinutes = 0;
	totalMinutes += (b2 * 10000);
	totalMinutes += (b3 * 1000);
	totalMinutes += (b4 * 100);
	totalMinutes += (b5 * 10);
	totalMinutes += b6;
	memset(buff,'\0', sizeof(buff));
	strcpy(buff, communityNo);
	strcat(buff, PrivateKey);
	totalMinutes -= compress(getHash(buff));

    //检查时间是否在有效范围内
	if (totalMinutes < 0 || totalMinutes > 52704)
		return -1;

	//匹配时间校验值
	b2 = totalMinutes / 10000 % 10;
	b3 = totalMinutes / 1000 % 10;
	b4 = totalMinutes / 100 % 10;
	b5 = totalMinutes / 10 % 10;
	b6 = totalMinutes % 10;

	if (((b1 ^ b2 ^ b3 ^ b4 ^ b5 ^ b6) % 10) != b7)
		return -2;

    // TODO: 添加设备类型判断
    //围墙机不需要检查设备号（围墙机没有设备号）
	//检查设备号校验值
	memset(buff,'\0', sizeof(buff));
	strcpy(buff, deviceNo);
	strcat(buff, PrivateKey);
	int hash = getHash(buff);
	int h1, h2, h3, h4, h5;
	h1 = hash / 10000;
	h2 = hash / 1000 % 10;
	h3 = hash / 100 % 10;
	h4 = hash / 10 % 10;
	h5 = hash % 10;
	if (((h1 + h2 + h3 + h4 + h5) % 10) != b8)
		return -3;

	totalMinutes = totalMinutes * 10;

	time_t now, token_time;
	struct tm tm_token_time, *ptm_token_time, *ptm_now;
	char *datetime;

	time(&now);
	ptm_now = localtime(&now);

	memset(&tm_token_time, 0, sizeof(tm_token_time));

	tm_token_time.tm_year=ptm_now->tm_year;

	 //总分钟小于每年第一天 并且 当前时间是在一年的最后一天时，自动增加一年
	if (totalMinutes <= 1440 && tm_token_time.tm_mon+1 == 12 && tm_token_time.tm_mday == 31)
	{
	    	tm_token_time.tm_year=ptm_now->tm_year+1;
	}
	//总分钟大于一年倒数第二天 并且 当前时间是新一年的第一天 自动扣除一年
	if(totalMinutes>= 524160&& tm_token_time.tm_mon+1 == 1 && tm_token_time.tm_mday == 1)
	{
	    	tm_token_time.tm_year=ptm_now->tm_year-1;
	}
	tm_token_time.tm_mon=0;
	tm_token_time.tm_mday=1;
	token_time = mktime(&tm_token_time);
	token_time += totalMinutes*60;

	ptm_token_time = localtime(&token_time);
	datetime = asctime(ptm_token_time);
	if(abs(difftime(now, token_time)) > 1*60*60)
		return -4;
	return 0;
}

