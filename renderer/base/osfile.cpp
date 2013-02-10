/*
 * osfile.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "osfile.h"

namespace base
{

OsFile::OsFile(const std::string &path, FileType ft)
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

TextFile::TextFile(const std::string &path)
    : OsFile(path, FT_TEXT)
{
    std::istreambuf_iterator<char> dataBegin(m_file);
    std::istreambuf_iterator<char> dataEnd;

    std::string fileDataStr(dataBegin, dataEnd);
    m_fileData.str(fileDataStr);
}

std::string TextFile::getLine(const char delim)
{
    std::string token;

    while(m_fileData)
    {
        std::getline(m_fileData, token, delim);

        if (token.empty())
            continue;

        auto notSpace = [](char ch)->int { return !isspace(ch); };

        std::string::iterator it = std::find_if(token.begin(), token.end(), notSpace);
        token.erase(token.begin(), it);

        auto rit = std::find_if(token.rbegin(), token.rend(), notSpace);
        token.erase(rit.base(), token.end());

        return token;
    }

    return std::string("END_OF_FILE");
}

void TextFile::resetPtr()
{
//    m_file.seekg(0);
//    m_fileData.str("");

//    m_fileData.~stringstream();
//    new ( (void *) &m_fileData ) std:stringstream;

//    istreambuf_iterator<char> dataBegin(m_file);
//    istreambuf_iterator<char> dataEnd;

//    string fileDataStr(dataBegin, dataEnd);
//    m_fileData.str(fileDataStr);
}

BinaryFile::BinaryFile(const std::string &path)
    : OsFile(path, FT_BINARY)
{
    std::istreambuf_iterator<char> dataBegin(m_file);
    std::istreambuf_iterator<char> dataEnd;

    std::copy(dataBegin, dataEnd, std::back_inserter(m_fileData));
}

void *BinaryFile::getBytes(size_t offset)
{
    size_t i = offset / sizeof(uint8_t);
    return &m_fileData[i];
}

}
