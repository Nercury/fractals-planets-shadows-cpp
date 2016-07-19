#include "L.h"

#include "b_threading.h"

#ifdef L_LOG_ENABLED

boost::mutex log_mutex;

void l(std::string message,int level)
{
	if (can_log(level))
	{
		boost::mutex::scoped_lock lock(log_mutex);

		std::cout << message << std::endl;
	}
}

void l(std::string message, int value, int level)
{
	if (can_log(level))
	{
		boost::mutex::scoped_lock lock(log_mutex);

		std::cout << message << value << std::endl;
	}
}

void l(std::string message, uint32_t value, int level)
{
	if (can_log(level))
	{
		boost::mutex::scoped_lock lock(log_mutex);

		std::cout << message << value << std::endl;
	}
}

void l(std::string message, std::string value, int level)
{
	if (can_log(level))
	{
		boost::mutex::scoped_lock lock(log_mutex);

		std::cout << message << value << std::endl;
	}
}

#endif
