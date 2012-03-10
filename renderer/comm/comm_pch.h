/*
 * comm_pch.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef COMM_PCH_H
#define COMM_PCH_H

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <ctime>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <exception>
#include <functional>

#ifdef WIN32
#include <memory>
#else
#include <memory>
#include <tr1/memory>
#endif

#include <boost/foreach.hpp>
#include <boost/utility.hpp>
#include <boost/date_time.hpp>
#include <boost/function.hpp>

using std::string;
using std::wstring;
using std::cerr;
using std::cout;
using std::endl;
using std::swap;
using std::vector;
using std::list;
using std::map;
using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;
using std::stringstream;
using std::ostringstream;
using std::istringstream;
using std::tr1::dynamic_pointer_cast;
using std::tr1::shared_ptr;

#include "dll.h"
#include "comm_macro.h"
#include "exception.h"
#include "logger.h"

#endif // COMM_PCH_H
