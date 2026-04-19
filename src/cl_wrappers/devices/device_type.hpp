#pragma once

#include <CL/cl.h>

namespace cl { 

enum class DeviceType : cl_uint { 
    kCPU = CL_DEVICE_TYPE_CPU,
    kGPU = CL_DEVICE_TYPE_GPU,
    kAccelerator = CL_DEVICE_TYPE_ACCELERATOR,
    kCustom = CL_DEVICE_TYPE_CUSTOM,
    kDefault = CL_DEVICE_TYPE_DEFAULT,
    kAll = CL_DEVICE_TYPE_ALL,
};

} // 