#include "platform_ids.hpp"

#include <iostream>

#include <cl_wrappers/safe_call.hpp>

namespace cl {

std::vector<cl_platform_id> GetPlatformIds() {
    	cl_uint platformsCount = 0;
	OCL_SAFE_CALL(clGetPlatformIDs(0, nullptr, &platformsCount));
	std::cout << "Number of OpenCL platforms: " << platformsCount << std::endl;

	if (platformsCount == 0) { 
		throw std::logic_error("No platforms available");
	}

	// Тот же метод используется для того, чтобы получить идентификаторы всех платформ - сверьтесь с документацией, что это сделано верно:
	std::vector<cl_platform_id> platforms(platformsCount);
	OCL_SAFE_CALL(clGetPlatformIDs(platforms.size(), platforms.data(), nullptr));
    return platforms;
}

}  // namespace cl