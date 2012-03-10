/*
 * ospath.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

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
    bool empty() const;
};

}

#endif // OSPATH_H
