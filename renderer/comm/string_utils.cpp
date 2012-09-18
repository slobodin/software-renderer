/*
 * string_utils.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "string_utils.h"
#include <algorithm>

namespace common
{

IsSpace isSpacePredicat;
IsNotSpace isNotSpacePredicat;

string makeUpper(const string &str)
{
    string res;
    std::transform(str.begin(), str.end(),
                   back_inserter(res),
                   toupper);

    return res;
}

string makeLower(const string &str)
{
    string res;
    std::transform(str.begin(), str.end(),
                   back_inserter(res),
                   tolower);

    return res;
}

void eraseSpaces(string &str)
{
    auto it = str.begin();
    while (it != str.end())
    {
        if (isSpacePredicat(*it))
            it = str.erase(it);
        else
            it++;
    }
}

}
