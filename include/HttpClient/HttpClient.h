/* HttpClient.h */
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

/** \file
Http Client header file
*/

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#define HTTP_CLIENT_DEFAULT_TIMEOUT 15000

class HttpData;

#include "TcpSocketConnection.h"
#include "IHttpData.h"

///Http client results
enum HttpResult {
    HTTP_OK = 0,        ///<Success
    HTTP_PROCESSING,    ///<Processing
    HTTP_PARSE,         ///<url Parse error
    HTTP_DNS,           ///<Could not resolve name
    HTTP_PRTCL,         ///<Protocol error
    HTTP_NOTFOUND,      ///<Http 404 Error
    HTTP_REFUSED,       ///<Http 403 Error
    HTTP_ERROR,         ///<Http xxx error
    HTTP_TIMEOUT,       ///<Connection timeout
    HTTP_CONN,          ///<Connection error
    HTTP_CLOSED,        ///<Connection was closed by remote host
};

/**A simple Http Client
The HttpClient is composed of:
- The actual client (HttpClient)
- Classes that act as a data repository, each of which deriving from the HttpData class (HttpText for short text content, HttpFile for file I/O, HttpMap for key/value pairs, and HttpStream for streaming purposes)
*/
class HttpClient
{
public:
    ///Instantiate the Http client
    HttpClient();
    ~HttpClient();

    /// Get the text form of the error number
    /// 
    /// Gets a pointer to a text message that described the result code.
    ///
    /// @param[in] res is the HttpResult code to translate to text.
    /// @returns a pointer to a text message.
    ///
    static const char * GetErrorMessage(HttpResult res);

    /**
    Provides a basic authentification feature (Base64 encoded username and password)
    Pass two NULL pointers to switch back to no authentication
    @param[in] user username to use for authentication, must remain valid durlng the whole Http session
    @param[in] user password to use for authentication, must remain valid durlng the whole Http session
    */
    void basicAuth(const char* user, const char* password); //Basic Authentification

    /**
    Set custom headers for request.
    
    Pass NULL, 0 to turn off custom headers.
    
    @code
     const char * hdrs[] = 
            {
            "Connection", "keep-alive",
            "Accept", "text/html",
            "User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)",
            "Accept-Encoding", "gzip,deflate,sdch",
            "Accept-Language", "en-US,en;q=0.8",
            };

        http.basicAuth("username", "password");
        http.customHeaders(hdrs, 5);
    @endcode
    
    @param[in] headers an array (size multiple of two) key-value pairs, must remain valid during the whole Http session
    @param[in] pairs number of key-value pairs
    */
    void customHeaders(const char** headers, size_t pairs);

    //High Level setup functions
    /** Execute a GET request on the URL
    Blocks until completion
    @param[in] url : url on which to execute the request
    @param[in,out] pDataIn : pointer to an IHttpDataIn instance that will collect the data returned by the request, can be NULL
    @param[in] timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
    @return 0 on success, Http error (<0) on failure
    */
    HttpResult get(const char* url, IHttpDataIn* pDataIn, int timeout = HTTP_CLIENT_DEFAULT_TIMEOUT); //Blocking

    /** Execute a GET request on the URL
    Blocks until completion
    This is a helper to directly get a piece of text from a Http result
    @param[in] url : url on which to execute the request
    @param[out] result : pointer to a char array in which the result will be stored
    @param[in] maxResultLen : length of the char array (including space for the NULL-terminating char)
    @param[in] timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
    @return 0 on success, Http error (<0) on failure
    */
    HttpResult get(const char* url, char* result, size_t maxResultLen, int timeout = HTTP_CLIENT_DEFAULT_TIMEOUT); //Blocking

    /** Execute a POST request on the URL
    Blocks until completion
    @param[in] url : url on which to execute the request
    @param[out] dataOut : a IHttpDataOut instance that contains the data that will be posted
    @param[in,out] pDataIn : pointer to an IHttpDataIn instance that will collect the data returned by the request, can be NULL
    @param[in] timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
    @return 0 on success, Http error (<0) on failure
    */
    HttpResult post(const char* url, const IHttpDataOut& dataOut, IHttpDataIn* pDataIn, int timeout = HTTP_CLIENT_DEFAULT_TIMEOUT); //Blocking

    /** Execute a PUT request on the URL
    Blocks until completion
    @param[in] url : url on which to execute the request
    @param[in] dataOut : a IHttpDataOut instance that contains the data that will be put
    @param[in,out] pDataIn : pointer to an IHttpDataIn instance that will collect the data returned by the request, can be NULL
    @param[in] timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
    @return 0 on success, Http error (<0) on failure
    */
    HttpResult put(const char* url, const IHttpDataOut& dataOut, IHttpDataIn* pDataIn, int timeout = HTTP_CLIENT_DEFAULT_TIMEOUT); //Blocking

    /** Execute a DELETE request on the URL
    Blocks until completion
    @param[in] url : url on which to execute the request
    @param[in,out] pDataIn : pointer to an IHttpDataIn instance that will collect the data returned by the request, can be NULL
    @param[in] timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
    @return 0 on success, Http error (<0) on failure
    */
    HttpResult del(const char* url, IHttpDataIn* pDataIn, int timeout = HTTP_CLIENT_DEFAULT_TIMEOUT); //Blocking

    /** Get last request's Http response code
    @return The Http response code of the last request
    */
    int getHttpResponseCode();

    /** Set the maximum number of automated redirections
    @param[in] i is the number of redirections. Values < 1 are
        set to 1.
    */
    void setMaxRedirections(int i = 1);

    /** get the redirect location url
    @returns const char pointer to the url.
    */
    const char * getLocation() {
        return m_location;
    }

private:
    enum Http_METH {
        Http_GET,
        Http_POST,
        Http_PUT,
        Http_DELETE,
        Http_HEAD
    };

    HttpResult connect(const char* url, Http_METH method, IHttpDataOut* pDataOut, IHttpDataIn* pDataIn, int timeout); //Execute request
    HttpResult recv(char* buf, size_t minLen, size_t maxLen, size_t* pReadLen); //0 on success, err code on failure
    HttpResult send(const char* buf, size_t len = 0); //0 on success, err code on failure
    HttpResult parseURL(const char* url, char* scheme, size_t maxSchemeLen, char* host, size_t maxHostLen, uint16_t* port, char* path, size_t maxPathLen); //Parse URL
    void createauth (const char *user, const char *pwd, char *buf, int len);
    int base64enc(const char *input, unsigned int length, char *output, int len);

    //Parameters
    TcpSocketConnection m_sock;

    int m_timeout;

    char* m_basicAuthUser;
    char* m_basicAuthPassword;
    const char** m_customHeaders;
    size_t m_nCustomHeaders;
    int m_httpResponseCode;
    int m_maxredirections;
    char * m_location;

};

//Including data containers here for more convenience
#include "HttpText.h"
#include "HttpMap.h"
#include "HttpFile.h"
#include "HttpJson.h"

#endif
