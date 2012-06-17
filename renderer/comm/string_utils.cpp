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

string upper(const string &str)
{
    string res(str);
    std::for_each(res.begin(), res.end(), [&](char &c){ c = toupper(c); });

    return res;
}

string lower(const string &str)
{
    string res(str);
    std::for_each(res.begin(), res.end(), [&](char &c){ c = tolower(c); });

    return res;
}

}
