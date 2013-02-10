/*
 * stdafx.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
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
#include <climits>

// SSE
#include <smmintrin.h>

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
    #include <filesystem>
#else
#ifdef __GNUC__
    #include <memory>
    #include <tr1/memory>
    #endif
#endif

#include <Windows.h>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#include "comm/exception.h"
#include "comm/comm_macro.h"
#include "comm/utils.h"

#ifdef RENDERER_LIBRARY
#include "logger.h"
namespace fs = std::tr2::sys;
#endif

#endif // COMM_PCH_H