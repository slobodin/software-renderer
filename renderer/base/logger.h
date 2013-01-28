/*
 * logger.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "comm_pch.h"

namespace math
{
struct vec2;
struct vec3;
}

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

    Logger();

public:
    static Logger &instance();

    // TODO:
    // Template function for POD types
    // And specialization for vectors etc
    Logger &operator<< (const char *text);
    Logger &operator<< (const string &text);
    Logger &operator<< (int num);
    Logger &operator<< (unsigned num);
    Logger &operator<< (size_t num);
    Logger &operator<< (double num);
    Logger &operator<< (const math::vec2 &vect);
    Logger &operator<< (const math::vec3 &vect);

    Logger &operator<< (const LoggerManipulator &man);
};

}

extern base::Logger &syslog;
extern const base::LoggerManipulator logdebug;
extern const base::LoggerManipulator logmess;
extern const base::LoggerManipulator logwarn;
extern const base::LoggerManipulator logerr;

#endif // LOGGER_H
