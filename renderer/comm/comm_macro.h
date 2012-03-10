/*
 * comm_macro.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

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
#define sptr(TYPE) std::shared_ptr<TYPE>
#else
#define sptr(TYPE) std::tr1::shared_ptr<TYPE>
#endif

#define aptr(TYPE) std::auto_ptr<TYPE>

#define foreach BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

#define FORCEINLINE __attribute__((always_inline))

#endif // COMM_MACRO_H
