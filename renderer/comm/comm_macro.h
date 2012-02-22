#ifndef COMM_MACRO_H
#define COMM_MACRO_H

#ifdef WIN32
#include <memory>
#else
#include <tr1/memory>
#endif

#define NONCOPYABLE(CLASS) \
    private: \
    CLASS(const CLASS &); \
    CLASS &operator= (const CLASS &);

#ifdef WIN32
#define SPTR(TYPE) std::shared_ptr<TYPE>
#else
#define SPTR(TYPE) std::tr1::shared_ptr<TYPE>
#endif

#define APTR(TYPE) std::auto_ptr<TYPE>

#endif // COMM_MACRO_H
