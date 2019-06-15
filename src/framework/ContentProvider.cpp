//1. The .cc .cpp .cxx related header files
#include "ContentProvider.h"

//2. C system include files.
#include <cassert>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

//3. C++ system include files.

//4. Other libraries' .h files.
#include "debug.h"

#undef LOG_TAG
#define LOG_TAG "ContentProvider"


std::string ContentProvider::getLastSectionOfURI(const std::string& uri)
{
    static std::string def;

    if (0 == uri.find(CONTENT_URI_SCHEME)) {
        size_t pos = uri.find_last_of('/');

        if (std::string::npos != pos) {
            return uri.substr(pos + 1);
        }
    }

    return def;
}

int ContentProvider::getRowNumFromURI(const std::string& uri)
{
    int row = -1;

    std::string last = getLastSectionOfURI(uri);

    if (!last.empty()) {
        std::istringstream ss(last);
        ss >> row;
    }

    return row;
}

std::string ContentProvider::getDomainFromURI(const std::string& uri)
{
    if (getRowNumFromURI(uri) > 0) {
        std::string last = getLastSectionOfURI(uri);
        std::string domain = getLastSectionOfURI(uri.substr(0, uri.length() - last.length()));
        assert(domain.find_first_of('/') == std::string::npos);
        return domain;
    }
    else {
        return getLastSectionOfURI(uri);
    }
}

ContentProvider::ContentProvider()
{
    db_debug ("ContentProvider.....................\n");
}

ContentProvider::~ContentProvider()
{
    db_debug ("~ContentProvider.....................\n");
}

