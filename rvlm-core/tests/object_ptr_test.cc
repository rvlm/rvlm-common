#include "catch.hpp"
#include "rvlm/object_ptr.hh"

class TestClass {
public:
    int mInt;
    float mFloat;

    TestClass(): mInt(0), mFloat(0) {}
    TestClass(int a): mInt(a) {}
    TestClass(int a, float b): mInt(a), mFloat(b) {}
};

TEST_CASE("Works", "rvlm::object_ptr") {

    SECTION("Default construction") {
        auto obj1 = rvlm::make_object<TestClass>();
        auto obj2 = rvlm::make_object<TestClass>(1);
        auto obj3 = rvlm::make_object<TestClass>(1, 1.0f);
        REQUIRE(typeid(obj1) == typeid(obj2));
        REQUIRE(typeid(obj2) == typeid(obj3));
        REQUIRE(typeid(obj3) == typeid(obj1));
    }

    SECTION("Copying") {
        auto obj1 = rvlm::make_object<TestClass>();
        auto obj2 = obj2;
        REQUIRE(obj1 == obj2);
    }

    SECTION("Dereferencing") {
        auto obj = rvlm::make_object<TestClass>(1, 2);
        REQUIRE(obj->mInt, 1);
        REQUIRE(bbj->mFloat, 2);
    }
}
