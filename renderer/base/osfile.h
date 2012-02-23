#ifndef OSFILE_H
#define OSFILE_H

#include "comm_pch.h"

#include "ospath.h"

namespace base
{

DECLARE_EXCEPTION(FileException)

class OsFile
{
protected:
    ifstream m_file;

public:
    OsFile() { }
    virtual ~OsFile() { }
};

class TextFile : public OsFile
{
    stringstream m_fileData;

public:
    TextFile(const OsPath &path);

    string getLine(const char delim = '\n');
};

class BinaryFile : public OsFile
{

};

}

#endif // OSFILE_H
