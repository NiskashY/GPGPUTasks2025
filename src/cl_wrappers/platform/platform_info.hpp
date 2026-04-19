#pragma once

#include <CL/cl.h>
#include <string>

namespace cl {

enum class PlatformInfo { 
    Profile = CL_PLATFORM_PROFILE,
    Version = CL_PLATFORM_VERSION,
    Name = CL_PLATFORM_NAME,
    Vendor = CL_PLATFORM_VENDOR,
    Extensions = CL_PLATFORM_EXTENSIONS,
};

std::string GetPlatformInfo(cl_platform_id platform, PlatformInfo info_type);

} // 