/*
 * comm_macro.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef COMM_MACRO_H
#define COMM_MACRO_H

#include <boost/smart_ptr.hpp>

// macro-helpers to create smart pointers
// use this everywhere
#define sptr(TYPE) boost::shared_ptr<TYPE>

#define aptr(TYPE) std::auto_ptr<TYPE>

#define foreach BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

#define FORCEINLINE __attribute__((always_inline))

#endif // COMM_MACRO_H
