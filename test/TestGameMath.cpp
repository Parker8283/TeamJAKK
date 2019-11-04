
#include <catch.hpp>
#include <GameMath.h>


TEST_CASE("Test Normalize dir", "[classic]")
{
	SECTION("Test all vectors from (1, 0) to (1, 10)") {
		REQUIRE(normalizeDir(glm::vec2(1, 0)) == glm::vec2(1, 0));
		REQUIRE(normalizeDir(glm::vec2(1, 1)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 2)) == glm::vec2(.4472, .8944));
		REQUIRE(normalizeDir(glm::vec2(1, 3)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 4)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 5)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 6)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 7)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 8)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 9)) == glm::vec2(1, 1));
		REQUIRE(normalizeDir(glm::vec2(1, 10)) == glm::vec2(1, 1));
	}
}
