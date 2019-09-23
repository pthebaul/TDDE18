#include "time.h"
#include "catch.hpp"

TEST_CASE("Testing time struct", "Test de description")
{
  Time const valid_time{13, 29, 32};
  Time const invalid_time{42, 69, 420};
  CHECK(is_valid(valid_time));
  CHECK_FALSE(is_valid(invalid_time));

  Time const midnight{00, 00, 00};
  Time const single_digits{01, 02, 03};
  Time const afternoon{14, 53, 10};
  
  CHECK(to_string(midnight) == "00:00:00");
  CHECK(to_string(midnight, true) == "12:00:00[am]");
  CHECK(to_string(single_digits) == "01:02:03");
  CHECK(to_string(afternoon) == "14:53:10");
  CHECK(to_string(afternoon, true) == "02:53:10[pm]");

  CHECK(is_am(midnight));
  CHECK_FALSE(is_am(afternoon));

  Time const t3{23, 59, 59};

  REQUIRE(is_valid(midnight + 12);
  CHECK(to_string(
}
