#include "logger.h"

namespace base
{

Logger *Logger::m_instance = 0;

Logger::Logger()
{
    cerr << "Started\n";
}

Logger *Logger::instance()
{
    if (!m_instance)
        m_instance = new Logger;

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

Logger &Logger::operator<< (const int num)
{
    m_buffer << num << " ";

    return *this;
}

Logger &Logger::operator<< (const unsigned num)
{
    m_buffer << num << " ";

    return *this;
}

Logger &Logger::operator<< (const double num)
{
    m_buffer << num << " ";

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

base::Logger *syslog = base::Logger::instance();
const base::LoggerManipulator logdebug(base::MT_DEBUG);
const base::LoggerManipulator logmess(base::MT_MESSAGE);
const base::LoggerManipulator logwarn(base::MT_WARNING);
const base::LoggerManipulator logerr(base::MT_ERROR);
