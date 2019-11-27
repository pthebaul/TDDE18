#include "catch.hpp"
#include "sorted_list.h"

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE("Creating an empty list") {
    Sorted_List l{};

    REQUIRE(l.is_empty());
    REQUIRE(l.size() == 0);
    REQUIRE(l.to_string() == "nullptr");
}

TEST_CASE("Inserting some numbers into an empty list and printing it")
{
    Sorted_List l{};
    REQUIRE(l.is_empty());
    REQUIRE(l.to_string() == "nullptr");
    REQUIRE(l.size() == 0);
    
    l.add(5);
    REQUIRE(l.to_string() == "5->nullptr");
    REQUIRE(l.size() == 1);
    
    l.add(3);
    REQUIRE(l.to_string() == "3->5->nullptr");
    REQUIRE(l.size() == 2);

    l.add(9);
    REQUIRE(l.to_string() == "3->5->9->nullptr");
    REQUIRE(l.size() == 3);
    
    l.add(7);
    REQUIRE(l.to_string() == "3->5->7->9->nullptr");
    REQUIRE(l.size() == 4);
}

TEST_CASE("Sorted_List::rm and Sorted_List::at")
{
    Sorted_List l{};
    REQUIRE_THROWS_AS(l.at(4), std::out_of_range);
    REQUIRE_THROWS_AS(l.rm(420), std::out_of_range);
    
    l.add(5);
    l.add(3);
    l.add(9);
    l.add(7);

    REQUIRE(l.at(0) == 3);
    REQUIRE(l.at(2) == 7);
    REQUIRE_THROWS_AS(l.at(4), std::out_of_range);
    REQUIRE_THROWS_AS(l.at(-1), std::out_of_range);
    
    REQUIRE_THROWS_AS(l.rm(6), std::out_of_range);

    l.rm(5);
    REQUIRE(l.to_string() == "3->7->9->nullptr");
    REQUIRE(l.size() == 3);
    
    REQUIRE(l.at(2) == 9);

    REQUIRE_THROWS_AS(l.rm(5), std::out_of_range);
    
    l.rm(3);
    REQUIRE(l.to_string() == "7->9->nullptr");
    REQUIRE(l.size() == 2);
    
    l.rm(9);
    REQUIRE(l.to_string() == "7->nullptr");
    REQUIRE(l.size() == 1);
    
    l.rm(7);
    REQUIRE(l.is_empty());
    REQUIRE(l.to_string() == "nullptr");
    REQUIRE(l.size() == 0);
}

Sorted_List gen_list(bool even)
{
    Sorted_List l1{};
    if (even)
    {
	l1.add(420);
	l1.add(42);
    }
    else
    {
	l1.add(69);
	l1.add(21);
    }
    return l1;
}

TEST_CASE("Copy constructor")
{
    Sorted_List l1{};
    l1.add(1);
    l1.add(2);

    Sorted_List l2{l1};
    l1.rm(1);
    
    REQUIRE(l2.to_string() == "1->2->nullptr");
}

TEST_CASE("Move constructor")
{
    Sorted_List l = gen_list(true);
    REQUIRE(l.to_string() == "42->420->nullptr");
}

TEST_CASE("Copy assignment")
{
    Sorted_List l1{};
    l1.add(3);
    l1.add(4);

    Sorted_List l2{};
    l2.add(5);
    l2.add(6);

    l2 = l1;
    l1.rm(3);
    REQUIRE(l2.to_string() == "3->4->nullptr");
}

TEST_CASE("Move assignment")
{
    Sorted_List l{};
    l.add(7);
    l.add(8);
    
    l = gen_list(false);
    REQUIRE(l.to_string() == "21->69->nullptr");
}
