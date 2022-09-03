#pragma once

#include "bbzpch.h"
#include "Bubatsu/Core/Log.h"

#ifdef BBZ_PLATFORM_WINDOWS
#	ifdef BBZ_DYNAMIC_LINK
#		ifdef BBZ_BUILD_DLL
#			define BUBATSU_API __declspec(dllexport)
#		else
#			define BUBATSU_API __declspec(dllimport)
#		endif
#	else
#		define BUBATSU_API
#	endif
#else
#	error BUBATSU PROBABLY DOESN'T SUPPORT THIS PLATFORM YET...
#endif

#ifdef BBZ_DEBUG
#	define BBZ_ENABLE_ASSERTS
#endif

#define BIT(x) (1 << x)
#define BBZ_BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Bubatsu
{
    template<typename T>
    using URef = std::unique_ptr<T>;
    template<typename T, typename... Args>
    constexpr URef<T> NewURef(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using SRef = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr SRef<T> NewSRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    
    using String = std::string;

    template<typename T>
    using Vector = std::vector<T>;
}

#ifdef BBZ_ENABLE_ASSERTS
#	define BBZ_ASSERT(x, ...) { if(x) { BBZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#	define BBZ_CORE_ASSERT(x, ...) { if(x) { BBZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#	define BBZ_ASSERT(x, ...)
#	define BBZ_CORE_ASSERT(x, ...)
#endif

