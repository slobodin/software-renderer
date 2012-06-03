/*
 * logger.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

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

class LoggerManipulator
{
    friend class Logger;

    MessageType m_type;

public:
    LoggerManipulator(const MessageType type)
        : m_type(type)
    { }
};

class Logger : boost::noncopyable
{
    stringstream m_buffer;

    static Logger *m_instance;
    Logger();

public:
    static Logger *instance();

    Logger &operator<< (const char *text);
    Logger &operator<< (const string &text);
    Logger &operator<< (int num);
    Logger &operator<< (unsigned num);
    Logger &operator<< (double num);

    Logger &operator<< (const LoggerManipulator &man);
};

}

extern base::Logger *syslog;
extern const base::LoggerManipulator logdebug;
extern const base::LoggerManipulator logmess;
extern const base::LoggerManipulator logwarn;
extern const base::LoggerManipulator logerr;

#endif // LOGGER_H
