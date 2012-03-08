#ifndef LOGGER_H
#define LOGGER_H

#include "comm_pch.h"

#include "dll.h"

namespace base
{

enum MessageType
{
    MT_DEBUG,
    MT_MESSAGE,
    MT_WARNING,
    MT_ERROR
};

class DLL_PUBLIC LoggerManipulator
{
    friend class Logger;

    MessageType m_type;

public:
    LoggerManipulator(const MessageType type)
        : m_type(type)
    {
    }
};

class DLL_PUBLIC Logger : boost::noncopyable
{
    stringstream m_buffer;

    static Logger *m_instance;
    Logger();

public:
    static Logger *instance();

    Logger &operator<< (const char *text);
    Logger &operator<< (const string &text);
    Logger &operator<< (const int num);
    Logger &operator<< (const unsigned num);
    Logger &operator<< (const double num);

    Logger &operator<< (const LoggerManipulator &man);
};

}

extern base::Logger *syslog;
extern const base::LoggerManipulator logdebug;
extern const base::LoggerManipulator logmess;
extern const base::LoggerManipulator logwarn;
extern const base::LoggerManipulator logerr;

#endif // LOGGER_H
