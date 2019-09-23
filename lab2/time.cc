#include "time.h"
#include <sstream>
#include <iomanip>

bool is_valid(Time const& t)
{
    bool valid_hrs{0 <= t.hrs and t.hrs < 24};
    bool valid_min{0 <= t.min and t.min < 60};
    bool valid_sec{0 <= t.sec and t.sec < 60};

    return valid_hrs and valid_min and valid_sec;
}

bool is_am(Time const& t)
{
    return t.hrs < 12;
}

std::string to_string(Time const& t, bool const& in_12_format)
{
    std::ostringstream os{};
    os << std::setw(2) << std::setfill('0');
    if (in_12_format)
    {
	if (t.hrs == 0)
	{
	    os << 12;
	}
	else if (is_am(t) or t.hrs == 12)
	{
	    os << t.hrs;
	}
	else
	{
	    os << t.hrs - 12;
	}
    }
    else
    {
	os << t.hrs;
    }
    
    os << ":" << std::setw(2) << std::setfill('0') << t.min << ":"
       << std::setw(2) << std::setfill('0') << t.sec;
    if (in_12_format)
    {
	os << "[";
	if (is_am(t))
	{
	    os << "am";
	}
	else
	{
	    os << "pm";
	}
	os << "]";
    }
					   
    return os.str();
}

Time operator+(Time t, int N)
{
    Time result{};
    
    result.sec = t.sec + N;
    if (result.sec >= 60)
    {
	result.min += result.sec / 60;
	result.sec %= 60;
    }
    
    result.min += t.min;
    if (result.sec >= 60)
    {
	result.min += result.sec / 60;
	result.sec %= 60;
    }
    
    result.sec = t.sec + N;
    if (result.sec >= 60)
    {
	result.min += result.sec / 60;
	result.sec %= 60;
    }
}
