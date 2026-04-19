#pragma once

#include <vector>

#include <CL/cl.h>

namespace cl {

std::vector<cl_platform_id> GetPlatformIds();

} // 