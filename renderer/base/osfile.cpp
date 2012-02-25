#include "osfile.h"
#include "string_utils.h"

namespace base
{

OsFile::OsFile(const OsPath &path)
{
    m_file.open(path.filePath());
    if (!m_file)
    {
        *syslog << "Can't locate file" << path.filePath() << logerr;
        throw FileException("Can't locate file");
    }
}

OsFile::~OsFile()
{
    m_file.close();
}

TextFile::TextFile(const OsPath &path)
    : OsFile(path)
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

}
