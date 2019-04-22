/*! ============================================================================
 * @file ContentResolver.cpp
 * @Synopsis  
 * @author DongKai
 * @version 1.0
 *  Company: Beijing Feynman Software Technology Co., Ltd.
 */
//1. The .cc .cpp .cxx related header files
#include "ContentResolver.h"

//2. C system include files.
#include <algorithm>
#include <stdio.h>

//3. C++ system include files.

//4. Other libraries' .h files.

//5. Your project's .h files.
#include "debug.h"
#include "common.h"

#define LOG_TAG "ContentResolver"

ContentResolver* ContentResolver::s_resolver = NULL;
const char* ContentResolver::CONTENT_URI = "content://";

ContentResolver* ContentResolver::singleton()
{
    // TODO: Change to double check when use mutil-thread.
    if (NULL == s_resolver) {
        s_resolver = new ContentResolver;
    }
    return s_resolver;
}

ContentResolver::ContentResolver ()
{
    db_debug ("ContentResolver......................\n");
}

ContentResolver::~ContentResolver ()
{
    db_debug ("~ContentResolver......................\n");
}

std::string ContentResolver::insert(const std::string& uri, const ContentValues& values)
{
    ContentProvider* provider = matchProviderByURI(uri);
    if (NULL != provider) {
        return provider->insert(uri, values);
    }
    return "";
}

ContentCursor* ContentResolver::query(const std::string& uri, const ContentValues::Strings* projection, const std::string* 
                selection, const ContentValues::Strings* selectionArgs, const std::string* sortOrder)
{
    ContentProvider* provider = matchProviderByURI(uri);
    if (NULL != provider) {
        return provider->query(uri, projection, selection, selectionArgs, sortOrder);
    }
    return NULL;
}

void ContentResolver::notifyChange(const std::string& uri)
{
    ContentProvider* provider = matchProviderByURI(uri);
    if (NULL != provider) {
        provider->notifyChange();
    }
}

int ContentResolver::remove(const std::string& uri, const std::string* where, const ContentValues::Strings* selectionArgs)
{
    ContentProvider* provider = matchProviderByURI(uri);
    if (NULL != provider) {
        return provider->remove(uri, where, selectionArgs);
    }
    return -1;
}

void ContentResolver::registerContentObserver(const std::string& uri, ContentObserver* observer)
{
    ContentProvider* provider = matchProviderByURI(uri);
    if (NULL != provider) {
        return provider->registerContentObserver(observer);
    }
}

void ContentResolver::unregisterContentObserver(ContentObserver* observer)
{
    ContentProviderCollection::iterator iter = m_providers.begin();
    for (; m_providers.end() != iter; ++iter) {
        (*iter)->unregisterContentObserver(observer);
    }
}

void ContentResolver::unregisterContentObserver(const std::string& uri, ContentObserver* observer)
{
    ContentProvider* provider = matchProviderByURI(uri);
    if (NULL != provider) {
        return provider->unregisterContentObserver(observer);
    }
}

int ContentResolver::update(const std::string& uri, const ContentValues& values, 
        const std::string* selection, const ContentValues::Strings* selectionArgs)
{
    ContentProvider* provider = matchProviderByURI(uri);
    if (NULL != provider) {
        return provider->update(uri, values, selection, selectionArgs);
    }
    return -1;
}

void ContentResolver::registerContentProvider(ContentProvider* provider)
{
    if (NULL != provider && m_providers.end() == m_providers.find(provider)) {
        m_providers.insert(provider);
    }
}

void ContentResolver::unregisterContentProvider(ContentProvider* provider)
{
    if (m_providers.end() == m_providers.find(provider)) {
        m_providers.erase(provider);
        delete provider;
    }
}

ContentProvider* ContentResolver::matchProviderByURI(const std::string& uri)
{
    ContentProviderCollection::iterator iter = m_providers.begin();
    ContentProvider* ret = NULL;
    for (; m_providers.end() != iter; ++iter) {
        if (0 == uri.find((*iter)->contentURI())) {
            ret = *iter;
            break;
        }
    }
    if (NULL == ret) {
        db_error("[ContentResolver] Can't match provider by URI, "
                "Please check if the suitable content provider was registered.");
    }
    return ret;
}

void ContentResolver::clearContentProvider()
{
    for_each(m_providers.begin(), m_providers.end(), DeleteObject());
    m_providers.clear();
}

