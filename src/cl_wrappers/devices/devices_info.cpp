#include "devices_info.hpp"

#include <type_traits>
#include <ostream>

#include <CL/cl.h>

#include <cl_wrappers/safe_call.hpp>
#include <cl_wrappers/devices/device_type.hpp>

namespace cl {

namespace { 

enum class DeviceParamType  : cl_device_info { 
    // general
    kAvailable = CL_DEVICE_AVAILABLE,
    kName = CL_DEVICE_NAME,
    kType = CL_DEVICE_TYPE,
    /// memory 
    kGlobalMemSize = CL_DEVICE_GLOBAL_MEM_SIZE,
    // version
    kDeviceVersion = CL_DEVICE_VERSION,
    kDriverVersion = CL_DRIVER_VERSION,
};

template <DeviceParamType param_type>
constexpr bool IsBooleanReturnType() {
    return false ||
        param_type == DeviceParamType::kAvailable
    ;
}

template <DeviceParamType param_type>
constexpr bool IsStrReturnType() {
    return 
        false
        || param_type == DeviceParamType::kName
        || param_type == DeviceParamType::kDeviceVersion
        || param_type == DeviceParamType::kDriverVersion
    ;
}

template <DeviceParamType param_type>
constexpr bool IsUlongReturnType() { 
    return false 
        || param_type == DeviceParamType::kGlobalMemSize
    ;
}

template <DeviceParamType param_type>
auto GetDeviceParamInfo(cl_device_id device_id) {
    size_t info_size = 0;
    OCL_SAFE_CALL(
        clGetDeviceInfo(
            device_id,
            static_cast<std::underlying_type_t<DeviceParamType>>(param_type),
            0,
            nullptr,
            &info_size 
        )
    );

    auto place_into_result = [&device_id, &info_size](auto* result) { 
        OCL_SAFE_CALL(
            clGetDeviceInfo(
                device_id,
                static_cast<std::underlying_type_t<DeviceParamType>>(param_type),
                info_size,
                result,
                nullptr
            )
        );
    };

    if constexpr (IsBooleanReturnType<param_type>()) {
        cl_bool result = false;
        place_into_result(&result);
        return result == CL_TRUE;
    } else if constexpr (IsStrReturnType<param_type>()) { 
        std::string result(info_size, '0');
        place_into_result(result.data());
        return result;
    } else if constexpr (param_type == DeviceParamType::kType) { 
        cl_device_type result;
        place_into_result(&result);
        return static_cast<DeviceType>(result);
    } else if constexpr (IsUlongReturnType<param_type>()) { 
        cl_ulong result;
        place_into_result(&result);
        return result;
    } else {
        throw std::runtime_error("not handled param_type"); 
    }
}

} // 

std::ostream& Dump(std::ostream& os, const DeviceMemory& mem, size_t tab_shift) { 
    std::string tab(tab_shift, '\t');
    os << tab << "DeviceMemory{\n";
    os << tab << "\t.global_mem_size = " << mem.global_mem_size << ",\n";
    os << tab << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const DeviceType& type) { 
    const auto view = [](const DeviceType& type) -> std::string_view {
        switch(type) {
        case DeviceType::kCPU:
            return "cpu";
        case DeviceType::kGPU:
            return "gpu";
        case DeviceType::kAccelerator:
            return "accelerator";
        case DeviceType::kCustom:
            return "custom";
        case DeviceType::kDefault:
            return "default";
        case DeviceType::kAll:
            return "all";
        }
    };
    os << view(type);
    return os;
}

std::ostream& Dump(std::ostream& os, const DeviceInfo& info, size_t tab_shift) { 
    std::string tab(tab_shift, '\t');

    os << tab << "DeviceInfo{\n";
    os << tab << "\t.available = " << info.available << ",\n";
    os << tab << "\t.name = '" << info.name << "' ,\n";
    os << tab << "\t.type = " << info.type << ",\n";
    os << tab << "\t.memory =\n";
    Dump(os, info.memory, tab_shift + 2) << ",\n";

    os << tab << "\t.device_version = '" << info.device_version << "',\n";
    os << tab << "\t.driver_version = '" << info.driver_version << "',\n";
    os << tab << "}";
    return os;
}

DeviceInfo GetDeviceInfo(cl_device_id device) { 
    return {
        .available = GetDeviceParamInfo<DeviceParamType::kAvailable>(device),
        .name = GetDeviceParamInfo<DeviceParamType::kName>(device),
        .type = GetDeviceParamInfo<DeviceParamType::kType>(device),
        .memory = {
            .global_mem_size = GetDeviceParamInfo<DeviceParamType::kGlobalMemSize>(device),
        },
        .device_version = GetDeviceParamInfo<DeviceParamType::kDeviceVersion>(device),
        .driver_version = GetDeviceParamInfo<DeviceParamType::kDriverVersion>(device),
    };
}

} // 