/*
 * exception.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

//#include <exception>
#include <stdexcept>
#include <string>

namespace common
{

//! Base class for all renderer exceptions.
class Exception
{
    //! "What"-string.
    /*! Contains error message. */
    std::string m_what;

public:
    Exception(const std::string &text)
        : m_what(text) { }
    virtual ~Exception() throw() { }

    //! Returns error message.
    virtual const char* what() const throw() { return m_what.c_str(); }
};

}

//! Macro-helper for creating different exceptions.
/*!
  * Using: DECLARE_EXCEPTION(SomethingWasWrongException).
  */
#define DECLARE_EXCEPTION(TYPE) class TYPE : public common::Exception \
{ \
public: \
    TYPE(const char *text) \
    : Exception(text) \
{} \
};

#endif // EXCEPTION_H
