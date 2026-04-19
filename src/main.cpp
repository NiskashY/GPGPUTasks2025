#include "cl_wrappers/devices/devices_ids.hpp"
#include "cl_wrappers/devices/devices_info.hpp"
#include <CL/cl.h>
#include <libclew/ocl_init.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include <utils/enumerate.hpp>
#include <cl_wrappers/platform/platform_ids.hpp>
#include <cl_wrappers/platform/platform_info.hpp>
#include <cl_wrappers/safe_call.hpp>

int main()
{
	// Пытаемся слинковаться с символами OpenCL API в runtime (через библиотеку libs/clew)
	if(!ocl_init())
		throw std::runtime_error("Can't init OpenCL driver!");

	// Откройте
	// https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/
	// Нажмите слева: "OpenCL Runtime" -> "Query Platform Info" -> "clGetPlatformIDs"
	// Прочитайте документацию clGetPlatformIDs и убедитесь, что этот способ узнать, сколько есть платформ, соответствует документации:

	const auto platforms = cl::GetPlatformIds();
	for(const auto [platformIndex, platform] : ::utils::Enumerate(platforms)) { 
		std::cout << "Platform #" << (platformIndex + 1) << "/" << platforms.size() << ": " << platform << std::endl;

		// Откройте документацию по "OpenCL Runtime" -> "Query Platform Info" -> "clGetPlatformInfo"
		// Не забывайте проверять коды ошибок с помощью макроса OCL_SAFE_CALL

		// TODO 1.1
		// Попробуйте вместо CL_PLATFORM_NAME передать какое-нибудь случайное число - например 239
		// Т.к. это некорректный идентификатор параметра платформы - то метод вернет код ошибки
		// Макрос OCL_SAFE_CALL заметит это, и кинет ошибку с кодом
		// Откройте таблицу с кодами ошибок:
		// libs/clew/CL/cl.h:103
		// P.S. Быстрый переход к файлу в CLion: Ctrl+Shift+N -> cl.h (или даже с номером строки: cl.h:103) -> Enter
		// Найдите там нужный код ошибки и ее название
		// Затем откройте документацию по clGetPlatformInfo и в секции Errors найдите ошибку, с которой столкнулись
		// в документации подробно объясняется, какой ситуации соответствует данная ошибка, и это позволит, проверив код, понять, чем же вызвана данная ошибка (некорректным аргументом param_name)
		// Обратите внимание, что в этом же libs/clew/CL/cl.h файле указаны всевоможные defines, такие как CL_DEVICE_TYPE_GPU и т.п.

		try {
			OCL_SAFE_CALL(clGetPlatformInfo(platform, 777, 0, nullptr, nullptr));
		} catch (const std::runtime_error& e) { 
			std::cerr << "Error: " << e.what() << std::endl;
		}

		// TODO 1.2
		// Аналогично тому, как был запрошен список идентификаторов всех платформ - так и с названием платформы, теперь, когда известна длина названия - его можно запросить:
		// clGetPlatformInfo(...);
		std::cout << "\tPlatform name: " << cl::GetPlatformInfo(platform, cl::PlatformInfo::Name) << std::endl;

		// TODO 1.3
		// Запросите и напечатайте так же в консоль вендора данной платформы
		std::cout << "\tPlatform vendor: " << cl::GetPlatformInfo(platform, cl::PlatformInfo::Vendor) << std::endl;

		std::cout << "\t--------------\n";
		// TODO 2.1
		// Запросите число доступных устройств данной платформы (аналогично тому, как это было сделано для запроса числа доступных платформ - см. секцию "OpenCL Runtime" -> "Query Devices")
		const auto device_ids = cl::GetDevicesIds(platform);
		for(const auto [device_idx, device_id] : ::utils::Enumerate(device_ids))
		{
			std::cout << "\tDevice #" << (device_idx + 1) << "/" << device_ids.size() << std::endl;
			// TODO 2.2
			// Запросите и напечатайте в консоль:
			// - Название устройства
			// - Тип устройства (видеокарта/процессор/что-то странное)
			// - Размер памяти устройства в мегабайтах
			// - Еще пару или более свойств устройства, которые вам покажутся наиболее интересными
			const auto device_info = cl::GetDeviceInfo(device_id);
			Dump(std::cout, device_info, /*tab_shift=*/1);
		}
	}

	return 0;
}
