/*
 * logger.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef LOGGER_H
#define LOGGER_H

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

class Logger
{
    std::stringstream m_buffer;

    Logger();

public:
    static Logger &instance();

    // TODO:
    // Template function for POD types
    // And specialization for vectors etc
    Logger &operator<< (const char *text);
    Logger &operator<< (const std::string &text);
    Logger &operator<< (int num);
    Logger &operator<< (unsigned num);
#if 0
    Logger &operator<< (size_t num);
#endif
    Logger &operator<< (float num);
    Logger &operator<< (const math::vec2 &vect);
    Logger &operator<< (const math::vec3 &vect);

    Logger &operator<< (const LoggerManipulator &man);

    NONCOPYABLE(Logger)
};

}

extern base::Logger &syslog;
extern const base::LoggerManipulator logdebug;
extern const base::LoggerManipulator logmess;
extern const base::LoggerManipulator logwarn;
extern const base::LoggerManipulator logerr;

#endif // LOGGER_H
