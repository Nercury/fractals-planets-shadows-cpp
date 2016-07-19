#pragma once

// itraukiam windows.h su winsock pries boost, tokiu budu galim naudot winsock 2
#include "a_win.h"

#include <boost/thread.hpp>
#include "b_time.h"
#include <boost/version.hpp>

#if BOOST_VERSION / 100000 == 1
# if BOOST_VERSION / 100 % 1000 > 34
#  define B_THREADING_USE_NEW_SLEEP
# endif
#else
#  error "BOOST_VERSION is > 1, please update b_threading file."
#endif

#ifdef B_THREADING_USE_NEW_SLEEP
inline void ThreadSleep(int miliseconds)
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(miliseconds));
}
#else
void ThreadSleep(int miliseconds);
#endif
