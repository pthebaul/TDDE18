#include "catch.hpp"
#include "sorted_list.h"

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE("Create an empty list") {
    Sorted_List l{};

    REQUIRE(l.is_empty() == true);
    REQUIRE(l.size == 0);
    REQUIRE(l.to_string() == "nullptr");
}

TEST_CASE("Insert some numbers into an empty list and printing")
{
    Sorted_List l{};
    REQUIRE(l.to_string() == "nullptr");
    
    l.add(5);
    REQUIRE(l.to_string() == "5->nullptr");
    
    l.add(3);
    REQUIRE(l.to_string() == "3->5->nullptr");

    l.add(9);
    REQUIRE(l.to_string() == "3->5->9->nullptr");
    
    l.add(7);
    REQUIRE(l.to_string() == "3->5->7->9->nullptr");
}

// TEST_CASE("Remove some numbers from a list")
