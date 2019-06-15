/* HttpJson.h */
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
 
 
#ifndef HTTPJSON_H_
#define HTTPJSON_H_
 
#include "HttpText.h"
 
/** A data endpoint to store JSON text
*/
class HttpJson : public HttpText
{
public:
    /** Create an HttpJson instance for output
    * @param json_str JSON string to be transmitted
    */
    HttpJson(char* json_str);
    
    /** Create an HttpText instance for input
    * @param json_str Buffer to store the incoming JSON string
    * @param size Size of the buffer
    */
    HttpJson(char* json_str, size_t size);
 
protected:
    virtual int getDataType(char* type, size_t maxTypeLen); //Internet media type for Content-Type header
};
 
#endif /* HTTPJSON_H_ */
