#include "osfile.h"
#include "string_utils.h"

namespace base
{

TextFile::TextFile(const OsPath &path)
{
    m_file.open(path.filePath().c_str());
    if (!m_file)
        throw FileException("Can't locate file");

    istreambuf_iterator<char> dataBegin(m_file);
    istreambuf_iterator<char> dataEnd;

    string fileDataStr(dataBegin, dataEnd);
    m_fileData.str(fileDataStr);
}

string TextFile::getLine()
{
    string token;

    while(m_fileData)
    {
        std::getline(m_fileData, token);

        if (token.empty())
            continue;

        string::iterator it = std::find_if(token.begin(), token.end(), common::isNotSpacePredicat);
        token.erase(token.begin(), it);

        return token;
    }

    return string("");
}

}
