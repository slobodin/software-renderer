/*
 * logger.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "logger.h"

#include "vec2.h"
#include "vec3.h"

namespace base
{

Logger::Logger()
{
    std::ostringstream msg;
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    boost::posix_time::time_facet *f = new boost::posix_time::time_facet("Started on %H:%M:%S");

    msg.imbue(std::locale(msg.getloc(), f));
    msg << now;

    cerr << msg.str() << endl;
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

Logger &Logger::operator<< (const string &text)
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

Logger &Logger::operator<< (size_t num)
{
    m_buffer << num << " ";

    return *this;
}

Logger &Logger::operator<< (double num)
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
        cerr << "[debug]: ";
        break;

    case MT_MESSAGE:
        cerr << "[message]: ";
        break;

    case MT_WARNING:
        cerr << "[warning]: ";
        break;

    case MT_ERROR:
        cerr << "[error]: ";
        break;
    }

    cerr << m_buffer.str() << "\n";
    m_buffer.str("");

    return *this;
}

}

base::Logger &syslog = base::Logger::instance();
const base::LoggerManipulator logdebug(base::MT_DEBUG);
const base::LoggerManipulator logmess(base::MT_MESSAGE);
const base::LoggerManipulator logwarn(base::MT_WARNING);
const base::LoggerManipulator logerr(base::MT_ERROR);
