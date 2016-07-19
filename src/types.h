#pragma once

#ifdef _MSC_VER

#	include <stddef.h>

#ifndef MSC_TYPE_REDEFINITIONS
#define MSC_TYPE_REDEFINITIONS

typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;

#endif

#else
#	include <stdint.h>
#endif

#include <sys/types.h>

