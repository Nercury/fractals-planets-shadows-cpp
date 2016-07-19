#pragma once

/*

Configuration file

*/

/* log levels */
#define L_SYSTEM_INFO 10
#define L_DETAILED_INFO 9
#define L_INFO 8
#define L_WARNING 6
#define L_FAILURE 4
#define L_ERROR 2
#define L_FATAL 0

#ifndef L_LOG_LEVEL
/* this is current log level */
#  define L_LOG_LEVEL L_SYSTEM_INFO
#endif

#include <string>

void SetAppPath(char p[]);
std::string FullPathTo(const std::string& file);
std::string GetAppPath();
std::string JoinPath(const std::string& root, const std::string& file);