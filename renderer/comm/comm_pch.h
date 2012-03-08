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

#ifdef WIN32
#include <memory>
#else
#include <memory>
#include <tr1/memory>
#endif

#include <boost/foreach.hpp>
#include <boost/utility.hpp>
#include <boost/date_time.hpp>

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

#define foreach BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

#define FORCEINLINE __attribute__((always_inline))

#include "dll.h"
#include "comm_macro.h"
#include "exception.h"
#include "logger.h"

#endif // COMM_PCH_H
