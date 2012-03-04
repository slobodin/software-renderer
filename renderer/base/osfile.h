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
    enum FileType
    {
        FT_TEXT,
        FT_BINARY
    };

    std::ifstream m_file;

public:
    OsFile(const OsPath &path, FileType ft);
    virtual ~OsFile();
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
    vector<uint8_t> m_fileData;

public:
    BinaryFile(const OsPath &path);

    void *getBytes(size_t offset);
    template <typename T>
    void copy(size_t offset, T *dest, size_t numElemets);
};

template <typename T>
void BinaryFile::copy(size_t offset, T *dest, size_t numElemets)
{
    size_t i = offset / sizeof(uint8_t);
    memcpy(dest, &m_fileData[i], numElemets * sizeof(T));
}

}

#endif // OSFILE_H
