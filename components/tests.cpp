#define CATCH_CONFIG_MAIN
#include "Include/catch.hpp"
#include "EventSystem/EventSystem.h"

unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("Event System", "[Events]") {
    Event<int> e([](int i) {std::cout << i << std::endl; }, 12);
    e.call();
    int k = 0;
    Event<int*> e1([](int* i) {*i += 13; }, &k);
    e1.call();
    std::cout << k << std::endl;
}