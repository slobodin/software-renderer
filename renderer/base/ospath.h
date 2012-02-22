#ifndef OSPATH_H
#define OSPATH_H

#include "comm_pch.h"

namespace base
{

class OsPath
{
    string m_path;
    string m_extention;

    void parse();
public:
    OsPath(const string &path);
    OsPath(const char *path);
    ~OsPath();

    string fileExtention() const;
    string filePath() const;
};

}

#endif // OSPATH_H
