#include "doctest.h"

#include <vector>

// typedefs are required if variadic macro support is not available (otherwise the commas are a problem)
typedef doctest::Types<char, short, int> int_types;
typedef doctest::Types<float, double> float_types;

// =================================================================================================
// NORMAL TEMPLATED TEST CASES
// =================================================================================================

TEST_CASE_TEMPLATE("signed integers stuff", T, int_types) {
    T var = T();
    --var;
    CHECK(var == -1);
}

// teach the library how to stringify this type - otherwise <> will be used
TYPE_TO_STRING(std::vector<int>);

TEST_CASE_TEMPLATE("vector stuff", T, doctest::Types<std::vector<int> >) {
    T vec(10);
    CHECK(vec.size() == 20); // fill fail
}

// =================================================================================================
// NAMED TEMPLATED TEST CASES WITH DEFERRED INSTANTIATION
// =================================================================================================

TEST_CASE_TEMPLATE_DEFINE("default construction", T, test_id) {
    T var = T();
    CHECK(doctest::Approx(var) == T());
}

TEST_CASE_TEMPLATE_INSTANTIATE(test_id, int_types);
TEST_CASE_TEMPLATE_INSTANTIATE(test_id, float_types);

// =================================================================================================
// MULTIPLE TYPES AS PARAMETERS
// =================================================================================================

template <typename first, typename second>
struct TypePair
{
    typedef first  A;
    typedef second B;
};

typedef doctest::Types<
    TypePair<int, char>,
    TypePair<char, int>,
    TypePair<bool, int>
> pairs;


// if variadic macros are supported then "TypePair<bool, int>" can be passed directly to the macro (otherwise the commas are a problem)
// currently result will be "bool_int_pair" instead of "TypePair<bool, int>" because of the way the type stringification works
typedef TypePair<bool, int> bool_int_pair;
TYPE_TO_STRING(bool_int_pair);

TEST_CASE_TEMPLATE("multiple types", T, pairs) {
    typedef typename T::A T1;
    typedef typename T::B T2;
    // use T1 and T2 types
    CHECK(T1() == T1());
    CHECK(T2() != T2());
}