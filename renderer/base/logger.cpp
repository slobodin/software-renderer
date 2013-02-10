/*
 * logger.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "logger.h"

#include "vec2.h"
#include "vec3.h"

namespace base
{

Logger::Logger()
{
    std::time_t result = std::time(0);

    std::cerr << std::asctime(std::localtime(&result)) << std::endl;
}

Logger &Logger::instance()
{
    static Logger m_instance;

    return m_instance;
}

Logger &Logger::operator<< (const char *text)
{
    m_buffer << text << " ";

    return *this;
}

Logger &Logger::operator<< (const std::string &text)
{
    m_buffer << text << " ";

    return *this;
}

Logger &Logger::operator<< (int num)
{
    m_buffer << num << " ";

    return *this;
}

Logger &Logger::operator<< (unsigned num)
{
    m_buffer << num << " ";

    return *this;
}

#if 0
Logger &Logger::operator<< (size_t num)
{
    m_buffer << num << " ";

    return *this;
}
#endif

Logger &Logger::operator<< (float num)
{
    m_buffer << num << " ";

    return *this;
}

Logger &Logger::operator<< (const math::vec2 &vect)
{
    m_buffer << vect << " ";

    return *this;
}

Logger &Logger::operator<< (const math::vec3 &vect)
{
    m_buffer << vect << " ";

    return *this;
}

Logger &Logger::operator<< (const LoggerManipulator &man)
{
    switch (man.m_type)
    {
    case MT_DEBUG:
        std::cerr << "[debug]: ";
        break;

    case MT_MESSAGE:
        std::cerr << "[message]: ";
        break;

    case MT_WARNING:
        std::cerr << "[warning]: ";
        break;

    case MT_ERROR:
        std::cerr << "[error]: ";
        break;
    }

    std::cerr << m_buffer.str() << "\n";
    m_buffer.str("");

    return *this;
}

}

base::Logger &syslog = base::Logger::instance();
const base::LoggerManipulator logdebug(base::MT_DEBUG);
const base::LoggerManipulator logmess(base::MT_MESSAGE);
const base::LoggerManipulator logwarn(base::MT_WARNING);
const base::LoggerManipulator logerr(base::MT_ERROR);
