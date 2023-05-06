#pragma once

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) ||  \
    defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32__) || defined(__NT__)
#define ENGINE_101_EXPORT __declspec(dllexport)
#else
#define ENGINE_101_EXPORT __attribute__((visibility("default")))
#endif

#if defined(ENGINE_101_SHARED_LIBRARY)
#define ENGINE_101_EXPORT ENGINE_101_EXPORT
#else
#define ENGINE_101_EXPORT
#endif
