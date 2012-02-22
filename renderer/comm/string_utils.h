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

}

#endif // STRING_UTILS_H
