#pragma once

#include <vector>

#include <CL/cl.h>

namespace cl {

std::vector<cl_device_id> GetDevicesIds(cl_platform_id platform);

} // 