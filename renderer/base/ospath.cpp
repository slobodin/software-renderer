#include "ospath.h"

namespace base
{

OsPath::OsPath(const string &path)
    : m_path(path)
{
    parse();
}

OsPath::OsPath(const char *path)
    : m_path(path)
{
    parse();
}

OsPath::~OsPath()
{
}

string OsPath::fileExtention() const
{
    return m_extention;
}

string OsPath::filePath() const
{
    return m_path;
}

bool OsPath::empty() const
{
    return m_path.empty();
}

void OsPath::parse()
{
    string::reverse_iterator it = m_path.rbegin();
    while (it != m_path.rend())
    {
        if ((*it) == '.')
        {
            m_extention.append(it.base(), m_path.end());
            break;
        }
        if ((*it) == '\\' || (*it) == '/')
            break;

        it++;
    }
}

}
