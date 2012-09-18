/*
 * string_utils.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "comm_pch.h"

namespace common
{

class IsSpace
{
public:
    bool operator()(char ch)
    {
        return (bool)isspace(ch);
    }
};

class IsNotSpace
{
public:
    bool operator()(char ch)
    {
        return !(bool)isspace(ch);
    }
};

extern IsSpace isSpacePredicat;
extern IsNotSpace isNotSpacePredicat;

string makeUpper(const string &str);
string makeLower(const string &str);

template<typename T>
T fromString(const string &str)
{
    istringstream is(str);
    T res;
    is >> res;

    return res;
}

template<typename T>
string toString(const T &item)
{
    ostringstream os;
    os << item;
    return os.str();
}

void eraseSpaces(string &str);

}

#endif // STRING_UTILS_H
