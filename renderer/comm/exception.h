#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class Exception : public std::exception
{
    std::string m_what;
public:
    Exception(const char *text)
        : m_what(text)
    {
    }

    Exception(const std::string &text)
        : m_what(text)
    {
    }

    virtual ~Exception() throw()
    {
    }

    virtual const char* what() const throw()
    {
        return m_what.c_str();
    }
};

#define DECLARE_EXCEPTION(TYPE) class TYPE : public Exception \
{ \
public: \
    TYPE(const char *text) \
    : Exception(text) \
{} \
};

#endif // EXCEPTION_H
