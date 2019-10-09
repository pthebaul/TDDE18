#include "catch.hpp"
#include "sorted_list.h"

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE("Creating an empty list") {
    Sorted_List l{};

    REQUIRE(l.is_empty());
    REQUIRE(l.size == 0);
    REQUIRE(l.to_string() == "nullptr");
}

TEST_CASE("Inserting some numbers into an empty list and printing it")
{
    Sorted_List l{};
    REQUIRE(l.is_empty());
    REQUIRE(l.to_string() == "nullptr");
    REQUIRE(l.size == 0);
    
    l.add(5);
    REQUIRE(l.to_string() == "5->nullptr");
    REQUIRE(l.size == 1);
    
    l.add(3);
    REQUIRE(l.to_string() == "3->5->nullptr");
    REQUIRE(l.size == 2);

    l.add(9);
    REQUIRE(l.to_string() == "3->5->9->nullptr");
    REQUIRE(l.size == 3);
    
    l.add(7);
    REQUIRE(l.to_string() == "3->5->7->9->nullptr");
    REQUIRE(l.size == 4);
}

TEST_CASE("Sorted_List::rm")
{
    Sorted_List l{};
    REQUIRE_THROWS_AS(l.rm(420), std::out_of_range);
    
    l.add(5);
    l.add(3);
    l.add(9);
    l.add(7);
    // Just to be sure
    REQUIRE(l.to_string() == "3->5->7->9->nullptr");
    REQUIRE(l.size == 4);
    
    REQUIRE_THROWS_AS(l.rm(6), std::out_of_range);

    l.rm(5);
    REQUIRE(l.to_string() == "3->7->9->nullptr");
    REQUIRE(l.size == 3);

    REQUIRE_THROWS_AS(l.rm(5), std::out_of_range);
    
    l.rm(3);
    REQUIRE(l.to_string() == "7->9->nullptr");
    REQUIRE(l.size == 2);
    
    l.rm(9);
    REQUIRE(l.to_string() == "7->nullptr");
    REQUIRE(l.size == 1);
    
    l.rm(7);
    REQUIRE(l.is_empty());
    REQUIRE(l.to_string() == "nullptr");
    REQUIRE(l.size == 0);
}

