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
  
  CHECK(to_string(midnight) == "00:00:00");
  CHECK(to_string(midnight, true) == "12:00:00[am]");
  CHECK(to_string(single_digits) == "01:02:03");
  CHECK(to_string(afternoon) == "14:53:10");
  CHECK(to_string(afternoon, true) == "02:53:10[pm]");

  CHECK(is_am(midnight));
  CHECK_FALSE(is_am(afternoon));

  REQUIRE(is_valid(midnight + 12));
  CHECK(to_string(midnight + 12) == "00:00:12");
  REQUIRE(is_valid(very_late + 15));
  CHECK(to_string(very_late + 15) == "00:00:14");
  REQUIRE(is_valid(afternoon + 50));
  CHECK(to_string(afternoon + 50) == "14:54:00");

  CHECK(midnight == midnight);
  CHECK_FALSE(midnight == afternoon);
  CHECK(midnight != very_late);
  CHECK_FALSE(midnight != midnight);
}
