/*
 * osfile.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "osfile.h"
#include "string_utils.h"

namespace base
{

OsFile::OsFile(const string &path, FileType ft)
{
    if (ft == FT_TEXT)
        m_file.open(path);
    else if (ft == FT_BINARY)
        m_file.open(path, std::ios::binary);
    else
        throw FileException("Bad file type");

    if (!m_file)
    {
        syslog << "Can't locate file" << path << logerr;
        throw FileException("Can't locate file");
    }
}

OsFile::~OsFile()
{
    m_file.close();
}

TextFile::TextFile(const string &path)
    : OsFile(path, FT_TEXT)
{
    istreambuf_iterator<char> dataBegin(m_file);
    istreambuf_iterator<char> dataEnd;

    string fileDataStr(dataBegin, dataEnd);
    m_fileData.str(fileDataStr);
}

string TextFile::getLine(const char delim)
{
    string token;

    while(m_fileData)
    {
        std::getline(m_fileData, token, delim);

        if (token.empty())
            continue;

        string::iterator it = std::find_if(token.begin(), token.end(), common::isNotSpacePredicat);
        token.erase(token.begin(), it);

        return token;
    }

    return string("");
}

BinaryFile::BinaryFile(const string &path)
    : OsFile(path, FT_BINARY)
{
    istreambuf_iterator<char> dataBegin(m_file);
    istreambuf_iterator<char> dataEnd;

    std::copy(dataBegin, dataEnd, std::back_inserter(m_fileData));
}

void *BinaryFile::getBytes(size_t offset)
{
    size_t i = offset / sizeof(uint8_t);
    return &m_fileData[i];
}

}
