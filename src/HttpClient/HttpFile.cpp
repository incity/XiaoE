#include "HttpFile.h"

#include <cstdio>
#include "debug.h"

HttpFile::HttpFile(char* filename) {
    db_info("HttpFile %s", filename);
    file = fopen(filename, "w");   
    m_chunked = false; 
}

void HttpFile::close() {
    db_info("close()");
    if (file) {
        fclose(file);
        file = NULL;
    }        
}

void HttpFile::writeReset() {
    db_info("writeReset()");
    if (file) {
        rewind(file);   
    }
}

int HttpFile::write(const char* buf, size_t len) {
    size_t written;
    db_info("write(%d,%s) m_len(%d), chunk %d", len, buf, m_len, m_chunked);
    if (file) {
        written = fwrite(buf, 1, len, file);   
        db_info("  writ:%d, ftell: %d", written, ftell(file)); 
        if ((!m_chunked && ((size_t)ftell(file) >= m_len)) || (m_chunked && !written)) {
            db_info("closing");
            close();
        }
    }
    return len;    
}

void HttpFile::setDataType(const char* type) {
    db_info("setDataType(%s)", type);
}

//void HttpFile::setLocation(const char * location) {
//
//}

void HttpFile::setIsChunked(bool chunked) {
    db_info("setIsChunked(%d)", chunked);
    m_chunked = chunked;
}

void HttpFile::setDataLen(size_t len) {
    db_info("setDataLen(%d)", len);
    m_len = len;
}
