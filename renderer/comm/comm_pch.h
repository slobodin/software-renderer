/*
 * comm_pch.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef COMM_PCH_H
#define COMM_PCH_H

// Common C-stuff.
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <ctime>

// Common C++ stuff.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <algorithm>
#include <exception>
#include <functional>
#ifdef _MSC_VER
    #include <memory>
#else
#ifdef __GNUC__
    #include <memory>
    #include <tr1/memory>
    #endif
#endif

// Boost stuff.
#include <boost/foreach.hpp>
#include <boost/utility.hpp>
#include <boost/date_time.hpp>
#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/pool/pool.hpp>
#include <boost/pool/pool_alloc.hpp>

// Some useful classes.
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

using boost::shared_ptr;
using boost::make_shared;
using boost::dynamic_pointer_cast;
namespace fs = boost::filesystem;
using fs::path;

#ifdef RENDERER_LIBRARY
#include "logger.h"
#endif

#include "comm_macro.h"
#include "exception.h"

#endif // COMM_PCH_H
