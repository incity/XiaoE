/* HttpText.cpp */
/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "HttpText.h"

#include <cstring>

#define OK 0

using std::memcpy;
using std::strncpy;
using std::strlen;

#define MIN(x,y) (((x)<(y))?(x):(y))

HttpText::HttpText(char* str) : m_str(str), m_pos(0)
{
    m_size = strlen(str) + 1;
}

HttpText::HttpText(char* str, size_t size) : m_str(str), m_size(size), m_pos(0)
{

}

//IHttpDataIn
/*virtual*/ void HttpText::readReset()
{
    m_pos = 0;
}

/*virtual*/ int HttpText::read(char* buf, size_t len, size_t* pReadLen)
{
    *pReadLen = MIN(len, m_size - 1 - m_pos);
    memcpy(buf, m_str + m_pos, *pReadLen);
    m_pos += *pReadLen;
    return OK;
}

/*virtual*/ int HttpText::getDataType(char* type, size_t maxTypeLen) //Internet media type for Content-Type header
{
    strncpy(type, "text/plain", maxTypeLen-1);
    type[maxTypeLen-1] = '\0';
    return OK;
}

/*virtual*/ bool HttpText::getIsChunked() //For Transfer-Encoding header
{
    return false;
}

/*virtual*/ size_t HttpText::getDataLen() //For Content-Length header
{
    return m_size - 1;
}

//IHttpDataOut
/*virtual*/ void HttpText::writeReset()
{
    m_pos = 0;
}

/*virtual*/ int HttpText::write(const char* buf, size_t len)
{
    size_t writeLen = MIN(len, m_size - 1 - m_pos);
    memcpy(m_str + m_pos, buf, writeLen);
    m_pos += writeLen;
    m_str[m_pos] = '\0';
    return OK;
}

/*virtual*/ void HttpText::setDataType(const char* type) //Internet media type from Content-Type header
{

}

/*virtual*/ void HttpText::setIsChunked(bool chunked) //From Transfer-Encoding header
{

}

/*virtual*/ void HttpText::setDataLen(size_t len) //From Content-Length header, or if the transfer is chunked, next chunk length
{

}



