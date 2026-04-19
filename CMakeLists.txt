cmake_minimum_required(VERSION 3.5)

project(GPGPUTasks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs)

# Компилируем исполняемый файл нашей программы
add_executable(enumDevices 
    src/main.cpp

    # cl custom wrappers
    src/cl_wrappers/platform/platform_ids.cpp
    src/cl_wrappers/platform/platform_info.cpp

    src/cl_wrappers/devices/devices_ids.cpp
    src/cl_wrappers/devices/devices_info.cpp

    src/cl_wrappers/safe_call.cpp
)

# Мы линкуемся с библиотекой clew (см. папку libs/clew) - она содержит в себе OpenCL headers + позволяет в runtime слинковаться с OpenCL API функциями
target_link_libraries(enumDevices libclew)

target_include_directories(enumDevices PUBLIC src)
