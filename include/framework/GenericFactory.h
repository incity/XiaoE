#ifndef  GENERIC_FACTORY_INC
#define  GENERIC_FACTORY_INC

//1. The .cc .cpp .cxx related header files
//2. C system include files.
#include <string.h>
#include <assert.h>
//3. C++ system include files.
#include <vector>

//4. Other libraries' .h files.
//5. Your project's .h files.

#undef LOG_TAG
#define LOG_TAG "GenericActivity"

template <typename T>
class GenericFactory {
public:
    static GenericFactory *singleton() {
       if (! s_single) {
           s_single = new GenericFactory();
       }
       return s_single;
    }
    int doRegister(const char *name, T *(*create)(void)) {
        GenericInfo *info = (GenericInfo *)malloc(sizeof(*info));
        typename std::vector<GenericInfo *>::iterator i;

        info->name = strdup(name);
        info->create = create;

        for (i=m_products.begin(); i!=m_products.end(); ++i) {
            if (strcmp(name, (*i)->name) <= 0) {
                break;
            }
        }
        m_products.insert(i, info);
        db_info("register [%s] activity...OK\n", name);
        return 0;
    }
    T *create(const char* name) {
        for (typename std::vector<GenericInfo *>::const_iterator i=m_products.begin(); i!=m_products.end(); ++i) {
            if (strcmp(name, (*i)->name) == 0) {
                T *ins = (*i)->create();
                if (ins) {
                    if (ins->create() == 0) {
                        return ins;
                    }else{
                        delete ins;
                    }
                }
                return NULL;
            }
        }
        return NULL;
    }
    
    template<typename AT>
    T *create(const char* name, AT* arg) {
        for (typename std::vector<GenericInfo *>::const_iterator i=m_products.begin(); i!=m_products.end(); ++i) {
            if (strcmp(name, (*i)->name) == 0) {
                T *ins = (*i)->create();
                if (ins) {
                    if (ins->create(arg) == 0) {
                        return ins;
                    }else{
                        delete ins;
                    }
                }
                return NULL;
            }
        }
        return NULL;
    }
    void queryNames(std::vector<std::string> &names) {
        for (typename std::vector<GenericInfo *>::const_iterator i=m_products.begin(); i!=m_products.end(); ++i) {
            names.push_back((*i)->name);
        }
    }
private:
    GenericFactory() { }
private:
    typedef struct {
        char *name;
        T *(*create)(void);
    } GenericInfo;
    std::vector<GenericInfo *> m_products;

    static GenericFactory *s_single;
};

#endif   /* ----- #ifndef GENERIC_FACTORY_INC  ----- */
