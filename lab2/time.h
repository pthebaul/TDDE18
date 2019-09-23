#include <string>

struct Time
{
    int hrs{0};
    int min{0};
    int sec{0};
};

bool is_valid(Time const& t);

bool is_am(Time const& t);

Time operator==(Time const t1, Time const t2);
Time operator!=(Time const& t1, Time const& t2);
Time operator+(Time t, int const& N);

std::string to_string(Time const& t, bool const& in_12_format = false);
