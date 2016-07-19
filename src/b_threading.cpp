#include "b_threading.h"

#ifndef B_THREADING_USE_NEW_SLEEP

void ThreadSleep(int miliseconds)
{
	boost::xtime xt;
	boost::xtime_get(&xt, boost::TIME_UTC);
	xt.nsec += miliseconds * 1000;
	boost::thread::sleep(xt);
}

#endif