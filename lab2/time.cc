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
    // setfill is now used once 
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
    
    os << ":" << std::setw(2) << t.min << ":"
       << std::setw(2) << t.sec;
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

//Comment: We prefer to use !, &&, || instead of not, and, or.
bool operator==(Time const& t1, Time const& t2)
{
    return (t1.hrs == t2.hrs) and (t1.min == t2.min) and (t1.sec == t2.sec);
}

bool operator!=(Time const& t1, Time const& t2)
{
    return not(t1 == t2);
}

bool operator>(Time const& t1, Time const& t2)
{
    return (t1.hrs > t2.hrs)
	or (t1.hrs == t2.hrs and t1.min > t2.min)
	or (t1.hrs == t2.hrs and t1.min == t2.min and t1.sec > t2.sec);
}

bool operator>=(Time const& t1, Time const& t2)
{
    return (t1 > t2) or (t1 == t2);
}

bool operator<(Time const& t1, Time const& t2)
{
    return (t2 > t1);
}

bool operator<=(Time const& t1, Time const& t2)
{
    return (t1 < t2) or (t1 == t2);
}


Time operator+(Time const& t, int const& N)
{
    Time result{t};
    
    result.sec = t.sec + N;
    
    if (result.sec >= 60)
    {
	result.min += result.sec / 60;
	result.sec %= 60;
    }
    
    if (result.min >= 60)
    {
	result.hrs += result.min / 60;
	result.min %= 60;
    }
    
    if (result.hrs >= 24)
    {
	result.hrs %= 24;
    }

    return result;
}

Time operator-(Time const& t, int const& N)
{
    Time result{t};
    
    result.sec = t.sec - N;
    
    if (result.sec < 0)
    {
	result.min -= -result.sec / 60 + 1;
	result.sec = ((result.sec % 60) + 60) % 60;
    }
    
    if (result.min < 0)
    {
	result.hrs -= -result.min / 60 + 1;
	result.min = ((result.min % 60) + 60) % 60;
    }
    
    if (result.hrs < 0)
    {
	result.hrs = ((result.hrs % 24) + 24) % 24;
    }
    
    return result;
}


Time& operator++(Time& t)
{
    t = t + 1;
    return t;
}

Time operator++(Time& t, int)
{
    Time old{t};
    ++t;
    return old;
}

Time& operator--(Time& t)
{
    t = t - 1;
    return t;
}

Time operator--(Time& t, int)
{
    Time old{t};
    --t;
    return old;
}

std::ostream& operator<<(std::ostream& os, Time const& t)
{
    os << to_string(t);
    return os;
}

std::istream& operator>>(std::istream& is, Time & t)
{
    is >> t.hrs;
    is.ignore(1, ':');
    is >> t.min;
    is.ignore(1, ':');
    is >> t.sec;
    if (not is_valid(t))
    {
	is.setstate(std::ios_base::failbit);
    }
    return is;
}
