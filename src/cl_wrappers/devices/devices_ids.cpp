#include "devices_ids.hpp"

#include <iostream>
#include <type_traits>

#include <CL/cl.h>

#include <cl_wrappers/safe_call.hpp>
#include <cl_wrappers/devices/device_type.hpp>

namespace cl {

std::vector<cl_device_id> GetDevicesIds(cl_platform_id platform) {
    cl_uint count = 0;
	OCL_SAFE_CALL(
        clGetDeviceIDs(
            platform, 
            static_cast<std::underlying_type_t<DeviceType>>(DeviceType::kAll), 
            0,
            nullptr, 
            &count
        )
    );
	std::cout << "\tNumber of OpenCL devices: " << count << std::endl;

	if (count  == 0) { 
		throw std::logic_error("No devices available");
	}

	std::vector<cl_device_id> devices(count);
	OCL_SAFE_CALL(
        clGetDeviceIDs(
            platform, 
            static_cast<std::underlying_type_t<DeviceType>>(DeviceType::kAll), 
            count,
            devices.data(), 
            nullptr
        )
    );
    return devices;
}

}  // namespace cl