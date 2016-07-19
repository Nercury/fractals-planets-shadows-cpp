#pragma once

#include <string>

#include "a_conf.h"
#include "types.h"

#if L_LOG_LEVEL >= L_FATAL
#  define L_LOG_ENABLED
#endif

inline bool can_log(int level)
{
#ifdef L_LOG_ENABLED
	return level <= L_LOG_LEVEL;
#else
	return false;
#endif
}

#ifdef L_LOG_ENABLED
void l(std::string message,int level);
void l(std::string message, int value, int level);
void l(std::string message, uint32_t value, int level);
void l(std::string message, std::string value, int level);
#else
inline void l(std::string message,int level) {}
inline void l(std::string message, int value, int level) {}
inline void l(std::string message, uint32_t value, int level) {}
inline void l(std::string message, std::string value, int level) {}
#endif
