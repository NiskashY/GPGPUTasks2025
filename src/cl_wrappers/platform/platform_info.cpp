#include "platform_info.hpp"

#include <cl_wrappers/safe_call.hpp>
#include "CL/cl.h"

namespace cl {

std::string GetPlatformInfo(cl_platform_id platform, PlatformInfo info_type)
{
    size_t info_size = 0;
    OCL_SAFE_CALL(
        clGetPlatformInfo(
            platform,
            static_cast<cl_platform_info>(info_type),
            0,
            nullptr,
            &info_size 
        )
    );

    std::string result(info_size, '0');

    OCL_SAFE_CALL(
        clGetPlatformInfo(
            platform,
            static_cast<cl_platform_info>(info_type),
            info_size,
            result.data(),
            nullptr
        )
    );

    return result;
}
}  // namespace cl