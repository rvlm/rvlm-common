#include <catch/catch.hpp>
#include "rvlm/core/Flags.hh"
using rvlm::core::Flags;
using rvlm::core::operator |;
using rvlm::core::operator +;

enum class TestEnum {
    Item00, Item01, Item02, Item03,
    Item04, Item05, Item06, Item07,
    Item08, Item09, Item10, Item11,
    Item12, Item13, Item14, Item15,
    Item16, Item17, Item18, Item19,
    Item20, Item21, Item22, Item23,
    Item24, Item25, Item26, Item27,
    Item28, Item29, Item30, Item31,
};

// TODO: Incomprehensive test.
TEST_CASE("Flags work", "rvlm::core::Flags") {

    SECTION("Initializing as empty set") {
        Flags<TestEnum> flagsNone;
        REQUIRE(flagsNone.empty());
        REQUIRE(flagsNone == Flags<TestEnum>());
    }

    SECTION("Basic equality and inequality") {
        Flags<TestEnum> flags0 = TestEnum::Item00;
        Flags<TestEnum> flags1 = TestEnum::Item31;
        Flags<TestEnum> flags2 = TestEnum::Item00 | TestEnum::Item31;
        Flags<TestEnum> flags3 = TestEnum::Item00 + TestEnum::Item31;
        Flags<TestEnum> flags4 = flags1;
        REQUIRE(flags0 != flags1);
        REQUIRE(flags2 == flags3);
        REQUIRE(flags4 == flags1);
        REQUIRE(flags0 == TestEnum::Item00);
        REQUIRE(flags0 != TestEnum::Item01);
    }

    SECTION("Comprehensive set operations") {
        Flags<TestEnum> flagsNone;

        Flags<TestEnum> flagsOdd =
            TestEnum::Item01 |
            TestEnum::Item03 |
            TestEnum::Item05 |
            TestEnum::Item07 |
            TestEnum::Item09 |
            TestEnum::Item11 |
            TestEnum::Item13 |
            TestEnum::Item15 |
            TestEnum::Item17 |
            TestEnum::Item19 |
            TestEnum::Item21 |
            TestEnum::Item23 |
            TestEnum::Item25 |
            TestEnum::Item27 |
            TestEnum::Item29 |
            TestEnum::Item31;

        Flags<TestEnum> flagsEven =
            TestEnum::Item00 |
            TestEnum::Item02 |
            TestEnum::Item04 |
            TestEnum::Item06 |
            TestEnum::Item08 |
            TestEnum::Item10 |
            TestEnum::Item12 |
            TestEnum::Item14 |
            TestEnum::Item16 |
            TestEnum::Item18 |
            TestEnum::Item20 |
            TestEnum::Item22 |
            TestEnum::Item24 |
            TestEnum::Item26 |
            TestEnum::Item28 |
            TestEnum::Item30;

        Flags<TestEnum> flagsAll =
            TestEnum::Item00 | TestEnum::Item01 |
            TestEnum::Item02 | TestEnum::Item03 |
            TestEnum::Item04 | TestEnum::Item05 |
            TestEnum::Item06 | TestEnum::Item07 |
            TestEnum::Item08 | TestEnum::Item09 |
            TestEnum::Item10 | TestEnum::Item11 |
            TestEnum::Item12 | TestEnum::Item13 |
            TestEnum::Item14 | TestEnum::Item15 |
            TestEnum::Item16 | TestEnum::Item17 |
            TestEnum::Item18 | TestEnum::Item19 |
            TestEnum::Item20 | TestEnum::Item21 |
            TestEnum::Item22 | TestEnum::Item23 |
            TestEnum::Item24 | TestEnum::Item25 |
            TestEnum::Item26 | TestEnum::Item27 |
            TestEnum::Item28 | TestEnum::Item29 |
            TestEnum::Item30 | TestEnum::Item31;

        Flags<TestEnum> flagsFirstHalf =
            TestEnum::Item00 | TestEnum::Item01 |
            TestEnum::Item02 | TestEnum::Item03 |
            TestEnum::Item04 | TestEnum::Item05 |
            TestEnum::Item06 | TestEnum::Item07 |
            TestEnum::Item08 | TestEnum::Item09 |
            TestEnum::Item10 | TestEnum::Item11 |
            TestEnum::Item12 | TestEnum::Item13 |
            TestEnum::Item14 | TestEnum::Item15;

        Flags<TestEnum> flagsSecondHalf =
            TestEnum::Item16 | TestEnum::Item17 |
            TestEnum::Item18 | TestEnum::Item19 |
            TestEnum::Item20 | TestEnum::Item21 |
            TestEnum::Item22 | TestEnum::Item23 |
            TestEnum::Item24 | TestEnum::Item25 |
            TestEnum::Item26 | TestEnum::Item27 |
            TestEnum::Item28 | TestEnum::Item29 |
            TestEnum::Item30 | TestEnum::Item31;

        REQUIRE(flagsAll == flagsEven + flagsOdd);
        REQUIRE(flagsAll == flagsFirstHalf + flagsSecondHalf);
        REQUIRE(flagsOdd == flagsAll - flagsEven);
        REQUIRE(flagsEven == flagsAll - flagsOdd);
        REQUIRE((flagsOdd & flagsEven).empty());
    }
}
