/*
 * comm_macro.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef COMM_MACRO_H
#define COMM_MACRO_H

#include <memory>

// macro-helpers to create smart pointers
// use wherever its possible
#define sptr(TYPE) std::tr1::shared_ptr<TYPE>
#define aptr(TYPE) std::auto_ptr<TYPE>

#ifdef _MSC_VER
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __attribute__((always_inline))
#endif

#define NONCOPYABLE(TYPE) private: TYPE(const TYPE &); TYPE &operator= (const TYPE &);

#endif // COMM_MACRO_H
