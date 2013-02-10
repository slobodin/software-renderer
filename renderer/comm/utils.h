/*
 * utils.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef UTILS_H
#define UTILS_H

namespace common
{

void eraseSpaces(std::string &str);
void tokenize(std::vector<std::string> &theStringVector, const std::string &theString, const std::string &theDelimiter);

template<typename T>
T fromString(const std::string &str)
{
    std::istringstream is(str);
    T res; is >> res;

    return res;
}

template<typename T>
std::string toString(const T &item)
{
    std::ostringstream os; os << item;

    return os.str();
}

}

#endif // UTILS_H