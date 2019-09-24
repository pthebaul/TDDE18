#include "time.h"
#include "catch.hpp"

TEST_CASE("Testing time struct", "Test de description")
{
  Time const valid_time{13, 29, 32};
  Time const invalid_time{42, 69, 420};
  REQUIRE(is_valid(valid_time));
  REQUIRE_FALSE(is_valid(invalid_time));

  Time const midnight{00, 00, 00};
  Time const single_digits{01, 02, 03};
  Time const afternoon{14, 53, 10};
  Time const very_late{23, 59, 59};

  //Testing to_string
  CHECK(to_string(midnight) == "00:00:00");
  CHECK(to_string(midnight, true) == "12:00:00[am]");
  CHECK(to_string(single_digits) == "01:02:03");
  CHECK(to_string(afternoon) == "14:53:10");
  CHECK(to_string(afternoon, true) == "02:53:10[pm]");

  CHECK(is_am(midnight));
  CHECK_FALSE(is_am(afternoon));

  //Testing "=="
  CHECK(midnight == midnight);
  CHECK_FALSE(midnight == afternoon);
  CHECK(midnight != very_late);
  CHECK_FALSE(midnight != midnight);
  
  //Testing "+"
  Time const midnight_plus_12{00, 00, 12};
  REQUIRE(is_valid(midnight + 12));
  CHECK(midnight + 12 == midnight_plus_12);
  
  Time const verylate_plus_15{00, 00, 14};
  REQUIRE(is_valid(very_late + 15));
  CHECK(very_late + 15 == verylate_plus_15);
  
  Time const afternoon_plus_50{14, 54, 00};
  REQUIRE(is_valid(afternoon + 50));
  CHECK(afternoon + 50 == afternoon_plus_50);
  
  //Testing "-"
  Time const midnight_minus_12{23, 59, 48};
  CHECK(midnight - 12 == midnight_minus_12);
  
  Time const verylate_minus_15{23, 59, 44};
  CHECK(very_late - 15 == verylate_minus_15);
  
  Time const afternoon_minus_50{14, 52, 20};
  CHECK(afternoon - 50 == afternoon_minus_50);

  //Testing "++"
  Time t{midnight};
  CHECK(to_string(t++) == "00:00:00");
  CHECK(to_string(t) == "00:00:01");
  
  t = midnight;
  CHECK(to_string(++t) == "00:00:01");
  CHECK(to_string(t) == "00:00:01");
  
  t = very_late;
  CHECK(to_string(t++) == "23:59:59");
  CHECK(to_string(t) == "00:00:00");
  
  t = very_late;
  CHECK(to_string(++t) == "00:00:00");
  CHECK(to_string(t) == "00:00:00");

  //Testing "--"
  t = midnight;
  CHECK(to_string(t--) == "00:00:00");
  CHECK(to_string(t) == "23:59:59");
  
  t = midnight;
  CHECK(to_string(--t) == "23:59:59");
  CHECK(to_string(t) == "23:59:59");
  
  t = very_late;
  CHECK(to_string(t--) == "23:59:59");
  CHECK(to_string(t) == "23:59:58");
  
  t = very_late;
  CHECK(to_string(--t) == "23:59:58");
  CHECK(to_string(t) == "23:59:58");
}
