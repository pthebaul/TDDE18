#include "time.h"
#include "catch.hpp"
// sstream is already included in time.cc, so we do not need to include it here

TEST_CASE("Testing time struct", "Test de description")
{
  Time const valid_time{13, 29, 32};
  Time const invalid_time{42, 69, 420};
  REQUIRE(is_valid(valid_time));
  REQUIRE_FALSE(is_valid(invalid_time));

  // Changed the way of declaring ints, all cases
  Time const midnight{0, 0, 0};
  Time const single_digits{1, 2, 3};
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
  //Testing "!="
  CHECK(midnight != very_late);
  CHECK_FALSE(midnight != midnight);
  
  //Testing "+"
  Time const midnight_plus_12{0, 0, 12};
  REQUIRE(is_valid(midnight + 12));
  CHECK(midnight + 12 == midnight_plus_12);
  
  Time const verylate_plus_15{0, 0, 14};
  REQUIRE(is_valid(very_late + 15));
  CHECK(very_late + 15 == verylate_plus_15);
  
  Time const afternoon_plus_50{14, 54, 0};
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

  //Testing ">"
  CHECK(afternoon > midnight);
  CHECK_FALSE(afternoon > very_late);
  //Testing ">="
  CHECK(afternoon >= midnight);
  CHECK_FALSE(afternoon >= very_late);
  CHECK(afternoon >= afternoon);
  //Testing "<"
  CHECK(midnight < afternoon);
  CHECK_FALSE(very_late < afternoon);
  //Testing "<="
  CHECK(midnight <= afternoon);
  CHECK_FALSE(very_late <= afternoon);
  CHECK(afternoon <= afternoon);

  //Testing "<<"
  std::ostringstream os1{};
  os1 << afternoon;
  CHECK(os1.str() == "14:53:10");
  std::ostringstream os2{};
  os2 << midnight;
  CHECK(os2.str() == "00:00:00");

  //Testing ">>"
  std::istringstream is1{"08:47:32"};
  Time t_is1{};
  is1 >> t_is1;
  CHECK(to_string(t_is1) == "08:47:32");
  
  std::istringstream is2{"64:47:32"};
  Time t_is2{};
  is2 >> t_is2;
  CHECK(is2.fail());
}
