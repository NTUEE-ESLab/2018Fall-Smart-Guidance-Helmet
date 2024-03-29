// Petter Strandmark 2012.

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <spii/spii.h>

using namespace spii;
using namespace std;

TEST_CASE("spii_assert", "")
{

	CHECK_THROWS_AS(spii_assert(1 == 2, "message"), logic_error);
	CHECK_NOTHROW(spii_assert(1 == 1, "message"));
}

TEST_CASE("check", "")
{
	CHECK_THROWS_AS(check(1 == 2, "1 is not 2"), runtime_error);
	CHECK_NOTHROW(check(1 == 1, "Something is very wrong."));
}

TEST_CASE("check-message", "")
{
	try {
		check(1 == 2, "1 ", "is ", "not ",  2);
	}
	catch (std::runtime_error& err) {
		CHECK(err.what() == std::string{"1 is not 2"});
	}
}
