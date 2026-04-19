#pragma once

#include <string>

#include <CL/cl.h>

#include <cl_wrappers/devices/device_type.hpp>

namespace cl {

struct DeviceMemory { 
    cl_ulong global_mem_size;
};

struct DeviceInfo { 
    bool available;
    std::string name;
    DeviceType type;
    DeviceMemory memory;

    std::string device_version;
    std::string driver_version;   
};

std::ostream& operator<<(std::ostream& os, const DeviceType& type);
std::ostream& Dump(std::ostream& os, const DeviceMemory& mem, size_t tab_shift = 0);
std::ostream& Dump(std::ostream& os, const DeviceInfo& info, size_t tab_shift = 0);

DeviceInfo GetDeviceInfo(cl_device_id device);

} // 