/*
 * exception.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

namespace common
{

//! Base class for all renderer exceptions.
class Exception : public std::exception
{
    //! "What"-string.
    /*! Contains error message. */
    std::string m_what;

public:
    Exception(const char *text)
        : m_what(text) { }
    Exception(const std::string &text)
        : m_what(text) { }
    virtual ~Exception() throw() { }

    //! Returns error message.
    virtual const char* what() const throw() { return m_what.c_str(); }
};

}

//! Macro-helper for creating different exceptions.
/*! Using: DECLARE_EXCEPTION(SomethingWasWrongException). */
#define DECLARE_EXCEPTION(TYPE) class TYPE : public common::Exception \
{ \
public: \
    TYPE(const char *text) \
    : Exception(text) \
{} \
};

namespace common
{

// Some standart exceptions.
DECLARE_EXCEPTION(OutOfRangeException)

}

#endif // EXCEPTION_H
