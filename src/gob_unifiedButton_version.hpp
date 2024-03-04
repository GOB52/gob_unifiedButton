#ifndef GOBLIB_UNIFIED_BUTTON_VERSION_HPP
#define GOBLIB_UNIFIED_BUTTON_VERSION_HPP

#define GOBLIB_UNIFIED_BUTTON_VERSION_MAJOR 0
#define GOBLIB_UNIFIED_BUTTON_VERSION_MINOR 1
#define GOBLIB_UNIFIED_BUTTON_VERSION_PATCH 2

#define GOBLIB_UNIFIED_BUTTON_VERSION_STRINGIFY_AGAIN(x) #x
#define GOBLIB_UNIFIED_BUTTON_VERSION_STRINGIFY(x) GOBLIB_UNIFIED_BUTTON_VERSION_STRINGIFY_AGAIN(x)

#define GOBLIB_UNIFIED_BUTTON_VERSION_VALUE ((GOBLIB_UNIFIED_BUTTON_VERSION_MAJOR << 16) | (GOBLIB_UNIFIED_BUTTON_VERSION_MINOR << 8) | (GOBLIB_UNIFIED_BUTTON_VERSION_PATCH))
#define GOBLIB_UNIFIED_BUTTON_VERSION_STRING GOBLIB_UNIFIED_BUTTON_VERSION_STRINGIFY(GOBLIB_UNIFIED_BUTTON_VERSION_MAJOR.GOBLIB_UNIFIED_BUTTON_VERSION_MINOR.GOBLIB_UNIFIED_BUTTON_VERSION_PATCH)

#endif
