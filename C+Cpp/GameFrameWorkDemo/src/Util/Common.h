#ifndef COMMON_H
#define COMMON_H

/*
 * common header including:
 * - most often used c++ headers
 * - commonly used macros
 */

#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <bitset>
#include <sstream>

#include <Util\Constants.h>

#include <GL\glew.h>
#include <GL\freeglut.h>

// output debug information
#define Debug(msg) std::wcout << __FUNCTIONW__ << L": " << msg << std::endl

#endif // !COMMON_H