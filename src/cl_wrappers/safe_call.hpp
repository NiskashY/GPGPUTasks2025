#pragma once

#include <string_view>

#include "CL/cl_platform.h"

void reportError(cl_int err, std::string_view filename, int line);

#define OCL_SAFE_CALL(expr) reportError(expr, __FILE__, __LINE__)