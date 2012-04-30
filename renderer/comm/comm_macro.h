/*
 * comm_macro.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef COMM_MACRO_H
#define COMM_MACRO_H

#ifdef _MSC_VER
    #include <memory>
#else
#ifdef __GNUC__
    #include <memory>
    #include <tr1/memory>
    #endif
#endif

// macro-helpers to create smart pointers
// use this everywhere
#ifdef _MSC_VER
#define sptr(TYPE) std::shared_ptr<TYPE>
#else
#define sptr(TYPE) std::tr1::shared_ptr<TYPE>
#endif

#define aptr(TYPE) std::auto_ptr<TYPE>

#define foreach BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

#define FORCEINLINE __attribute__((always_inline))

#endif // COMM_MACRO_H
