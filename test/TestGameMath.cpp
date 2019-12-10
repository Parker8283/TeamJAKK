#include <catch.hpp>
#include <GameMath.h>

TEST_CASE("Test Normalize dir", "[classic]")
{
	SECTION("Test all vectors from (1, 0) to (7, 7)") {
		REQUIRE(normalizeDir(glm::vec2(1, 0)) == glm::vec2(1, 0));
		REQUIRE(normalizeDir(glm::vec2(0, 1)) == glm::vec2(0, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 1)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(2, 2)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(3, 3)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(4, 4)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(5, 5)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(6, 6)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(7, 7)) == glm::vec2(1, 1));
	}
}

TEST_CASE("Test Quadrant", "[classic]")
{
	SECTION("Test passing in all different quadrants") {
		REQUIRE(quadrant(glm::vec2( 1,  1)) == 1);
		REQUIRE(quadrant(glm::vec2(-1,  1)) == 2);
		REQUIRE(quadrant(glm::vec2(-1, -1)) == 3);
		REQUIRE(quadrant(glm::vec2( 1, -1)) == 4);
		REQUIRE(quadrant(glm::vec2( 0,  0)) == 9);
		REQUIRE(quadrant(glm::vec2( 0,  1)) == 5);
		REQUIRE(quadrant(glm::vec2( 1,  0)) == 5);
	}
}
