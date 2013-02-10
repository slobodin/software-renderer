/*
 * utils.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "utils.h"

namespace common
{

void eraseSpaces(std::string &str)
{
    auto it = str.begin();
    while (it != str.end())
    {
        if (isspace(*it))
            it = str.erase(it);
        else
            it++;
    }
}

void tokenize(std::vector<std::string> &theStringVector, const std::string &theString, const std::string &theDelimiter)
{
    size_t start = 0, end = 0;

    while (end != std::string::npos)
    {
        end = theString.find(theDelimiter, start);

        // If at end, use length=maxLength.  Else use length=end-start.
        theStringVector.push_back(theString.substr(start, (end == std::string::npos) ? std::string::npos : end - start));

        // If at end, use start=maxSize.  Else use start=end+delimiter.
        start = (( end > (std::string::npos - theDelimiter.size())) ? std::string::npos : end + theDelimiter.size());
    }
}

}