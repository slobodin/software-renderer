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

#ifdef WIN32
#include <memory>
#else
#include <memory>
#include <tr1/memory>
#endif

#include <map>
#include <algorithm>
#include <exception>

using std::string;
using std::wstring;
using std::cerr;
using std::cout;
using std::endl;
using std::swap;
using std::vector;
using std::list;
using std::map;
using std::auto_ptr;
using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;
using std::stringstream;
using std::ostringstream;
using std::istringstream;
using std::auto_ptr;
using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

#define FORCEINLINE __attribute__((always_inline))

#include "dll.h"
#include "comm_macro.h"
#include "exception.h"
#include "logger.h"

#endif // COMM_PCH_H
