#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <list>
#include <memory>
#include <sstream>
#include <vector>

/*
    Tests in this file is for the purpose of testing all the constructors.

    It relies on the overloaded cast to vector to be correct as
    there is the need to inspect the magnitudes.

    Testing the move constructor assumes that the dimensions() getter works.

    General approach:
    1. Construct a euclidean_vector
    2. Construct the expected casting to a std::vector or std::list
    3. Compare if they are equal

   Rational: Testing the magnitudes matches will be sufficient to test simple constructors
*/

TEST_CASE("Default Constructor: 1 Dimension of magnitude 0") {
    auto const ev1 = comp6771::euclidean_vector();

    auto const ev1_exp = std::vector<double>{0.0};
    CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
}

TEST_CASE("Single argument constructor: Take in the size and make magnitudes 0") {
    auto const ev1 = comp6771::euclidean_vector(0);
    auto const ev2 = comp6771::euclidean_vector(2);
    auto const ev3 = comp6771::euclidean_vector(5);

    auto const ev1_exp = std::vector<double>();
    auto const ev2_exp = std::vector<double>{0.0, 0.0};
    auto const ev3_exp = std::vector<double>{0.0, 0.0, 0.0, 0.0, 0.0};

    CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
    CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
    CHECK_THAT(static_cast<std::vector<double>>(ev3), Catch::Approx(ev3_exp));
}

TEST_CASE("Num dimensions - magnitudes constructor") {
    auto const ev1 = comp6771::euclidean_vector(0, 1.5);
    auto const ev2 = comp6771::euclidean_vector(3, 1.5);
    auto const ev3 = comp6771::euclidean_vector(5, 4.5);

    auto const ev1_exp = std::vector<double>();
    auto const ev2_exp = std::vector<double>{1.5, 1.5, 1.5};
    auto const ev3_exp = std::vector<double>{4.5, 4.5, 4.5, 4.5, 4.5};

    CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
    CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
    CHECK_THAT(static_cast<std::vector<double>>(ev3), Catch::Approx(ev3_exp));
}

TEST_CASE("Vector Iterator constructor") {
    auto const ev1_exp = std::vector<double>();
    auto const ev2_exp = std::vector<double>{0.0, 1.5, -4.5, 40.0};
    auto const ev3_exp = std::vector<double>{1.5, 3.0};

    auto const ev1 = comp6771::euclidean_vector(ev1_exp.begin(), ev1_exp.end());
    auto const ev2 = comp6771::euclidean_vector(ev2_exp.begin(), ev2_exp.end());
    auto const ev3 = comp6771::euclidean_vector(ev3_exp.begin(), ev3_exp.end());

    CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
    CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
    CHECK_THAT(static_cast<std::vector<double>>(ev3), Catch::Approx(ev3_exp));
}

TEST_CASE("Initialiser List constructor") {
    auto const ev1 = comp6771::euclidean_vector({});
    auto const ev2 = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};
    auto const ev3 = comp6771::euclidean_vector{1.5, 3.0};

    auto const ev1_exp = std::vector<double>();
    auto const ev2_exp = std::vector<double>{0.0, 1.5, -4.5, 40.0};
    auto const ev3_exp = std::vector<double>{1.5, 3.0};

    CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
    CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
    CHECK_THAT(static_cast<std::vector<double>>(ev3), Catch::Approx(ev3_exp));
}

/*
   Rational:
   - Other then checking if the constructed euclidean_vectors are equal, check
   if modifying the copy will not change the original. To ensure that the copied to object doesn't
   share the same data member with the copied to object.

   Assume the += operator is correctly overloaded.
*/
TEST_CASE("Copy constructor") {
    auto const ev1 = comp6771::euclidean_vector(0);
    auto const ev2 = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};
    auto const ev3 = comp6771::euclidean_vector{1.5, 3.0};

    // Invoke copy constructor
    auto ev1_copy = ev1;
    auto ev2_copy = ev2;
    auto ev3_copy = ev3;

    auto const ev1_exp = std::vector<double>();
    auto const ev2_exp = std::vector<double>{0.0, 1.5, -4.5, 40.0};
    auto const ev3_exp = std::vector<double>{1.5, 3.0};

    SECTION("Both the copy and the original version should match the expecting vector") {
        CHECK_THAT(static_cast<std::vector<double>>(ev1_copy), Catch::Approx(ev1_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev2_copy), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3_copy), Catch::Approx(ev3_exp));

        CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3), Catch::Approx(ev3_exp));
    }

    SECTION("Check if modifying one will not affect the other.") {
        ev2_copy += ev2_copy;
        ev3_copy += comp6771::euclidean_vector{2.0, 3.5};

        CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3), Catch::Approx(ev3_exp));
    }
}

/* Check_nothrow */

/*
   Rational: All move constructor does is to take the data member of the moved from object and leave
   it in an default state (0 dimension in this case). So we just need to see if the moved to objects
   contain the expected value and if the moved from object is left in a default state.
*/
TEST_CASE("Move constructor") {
    auto ev1 = comp6771::euclidean_vector(0);
    auto ev2 = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};
    auto ev3 = comp6771::euclidean_vector{1.5, 3.0};

    // Invoke move constructor
    auto const ev1_new = std::move(ev1);
    auto const ev2_new = std::move(ev2);
    auto const ev3_new = std::move(ev3);

    // Construct expected vectors
    auto const ev1_exp = std::vector<double>();
    auto const ev2_exp = std::vector<double>{0.0, 1.5, -4.5, 40.0};
    auto const ev3_exp = std::vector<double>{1.5, 3.0};

    // Check that
    SECTION("The moved to object should have the same magnitudes as the moved from object's "
            "original magnitudes") {
        CHECK_THAT(static_cast<std::vector<double>>(ev1_new), Catch::Approx(ev1_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev2_new), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3_new), Catch::Approx(ev3_exp));
    }

    // Check that
    SECTION("The moved-from object should be in a state with 0 dimension") {
        CHECK(ev1.dimensions() == 0);
        CHECK(ev2.dimensions() == 0);
        CHECK(ev3.dimensions() == 0);
    }
}

#include "comp6771/euclidean_vector.hpp"

#include <algorithm>
#include <catch2/catch.hpp>
#include <list>
#include <memory>
#include <sstream>
#include <vector>

/*
    Tests in the file test if the operations have the right behavior and if
    they throw the correct exception with correct message in appropriate
    situtation.

    These tests assumes that the constructors, dimensions getter and casting to std::vector are
    correct.
*/

/*
    Test case:
    - copy assign to an euclidean_vector(EV) of equal dimensions
    - copy assign to an euclidean_vector of different dimensions

   Assume the += operator is correctly implemented.

    Approach:
    1. Initialize some EVs of different dimensions that act as the copied from
    2. Initialize some EVs of different dimensions that act as the copied to
    3. Perform copy assignment
    4. Check that the copied to have contents equal to the copied from by casting them
       to std::vector
    5. Check that modifying the copied to will not affect the copied from (Ensure they are not
       connected underlyingly)

   Rational:
   - The semantics of copy assignment ensure that the copied from and to objects has the
   same magnitudes and has not underlying sharing data members. So the above test can ensure its
   behavior are correct.
   - Copy assignment can be perform between vectors of different internal states
   - Copying itself should not be a problem for robustness.
*/
TEST_CASE("Copy Assignment") {
    // Initialized copied from objects
    auto const ev1 = comp6771::euclidean_vector(0);
    auto const ev2 = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};
    auto const ev3 = comp6771::euclidean_vector{1.5, 3.0};

    auto const ev1_exp = std::vector<double>();
    auto const ev2_exp = std::vector<double>{0.0, 1.5, -4.5, 40.0};
    auto const ev3_exp = std::vector<double>{1.5, 3.0};

    // Initialized copied to objects
    auto ev1_copy = comp6771::euclidean_vector(10);
    auto ev2_copy = comp6771::euclidean_vector(9, -0.5);
    auto ev3_copy = comp6771::euclidean_vector(2, 0.5);

    // Invoke copy assignment operator
    ev1_copy = ev1;
    ev2_copy = ev2;
    ev3_copy = ev3;

    SECTION("Both the copy to object matches expected vector") {
        CHECK_THAT(static_cast<std::vector<double>>(ev1_copy), Catch::Approx(ev1_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev2_copy), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3_copy), Catch::Approx(ev3_exp));

        CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3), Catch::Approx(ev3_exp));
    }

    SECTION("Modifying the copied to will not affect the copied from") {
        ev2_copy += ev2;
        ev3_copy += ev3;

        CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3), Catch::Approx(ev3_exp));
    }

    SECTION("Copy Assignment to itself") {
        ev1_copy = ev1_copy;
        ev2_copy = ev2_copy;
        ev3_copy = ev3_copy;

        CHECK_THAT(static_cast<std::vector<double>>(ev1_copy), Catch::Approx(ev1_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev2_copy), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3_copy), Catch::Approx(ev3_exp));
    }
}

/*
    Test case:
    - move assign to an euclidean_vector(EV) of equal dimensions
    - move assign to an euclidean_vector of different dimensions

    Approach:
    1. Initialize some EVs of different dimensions that act as the moved from
    2. Initialize some EVs of different dimensions that act as the moved to
    3. Perform move assignment
    4. Check that the copied to have contents equal to the copied from by casting them
       to std::vector
    5. Check that the moved from has dimension of 0

   Rational:
   - Testing the above ensures correctness of the move assignment operator by testing all
   its behavior
*/
TEST_CASE("Move Assignment") {
    // Initialized moved from objects
    auto ev1 = comp6771::euclidean_vector(0);
    auto ev2 = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};
    auto ev3 = comp6771::euclidean_vector{1.5, 3.0};

    auto const ev1_exp = std::vector<double>();
    auto const ev2_exp = std::vector<double>{0.0, 1.5, -4.5, 40.0};
    auto const ev3_exp = std::vector<double>{1.5, 3.0};

    // Initialized moved to objects
    auto ev1_new = comp6771::euclidean_vector(10);
    auto ev2_new = comp6771::euclidean_vector(9, -0.5);
    auto ev3_new = comp6771::euclidean_vector(2, 0.5);

    // Invoke move assignment operator
    ev1_new = std::move(ev1);
    ev2_new = std::move(ev2);
    ev3_new = std::move(ev3);

    SECTION("The moved to object has the correct magnitudes") {
        CHECK_THAT(static_cast<std::vector<double>>(ev1_new), Catch::Approx(ev1_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev2_new), Catch::Approx(ev2_exp));
        CHECK_THAT(static_cast<std::vector<double>>(ev3_new), Catch::Approx(ev3_exp));
    }

    SECTION("The moved-from objects are in a state with 0 dimension (According to the spec)") {
        CHECK(ev1.dimensions() == 0);
        CHECK(ev2.dimensions() == 0);
        CHECK(ev3.dimensions() == 0);
    }
}

/*
   Test case for non-const
   - Can access the value in the given dimension
   - Can modify the value in the given dimension

   Test case for const
   - Can access the value in the given dimension

   Rational: Since the spec says these function will not throw exception and will terminate for
   invalid input, we only need to check that they perform correctly for valid inputes.
*/
TEST_CASE("Subscript") {
    SECTION("Const Version") {
        auto const ev = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};

        SECTION("Return the correct value of the given magnitude") {
            CHECK(ev[0] == Approx(0.0));
            CHECK(ev[1] == Approx(1.5));
            CHECK(ev[2] == Approx(-4.5));
            CHECK(ev[3] == Approx(40.0));
        }
    }

    SECTION("Non-const Version") {
        auto ev = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};

        SECTION("Return the correct value of the given magnitude") {
            CHECK(ev[0] == Approx(0.0));
            CHECK(ev[1] == Approx(1.5));
            CHECK(ev[2] == Approx(-4.5));
            CHECK(ev[3] == Approx(40.0));
        }

        SECTION("Modify the dimension in the given dimension") {
            ev[0] = 5.3;
            ev[1] = -3.19;
            ev[2] = 4.25;
            ev[3] = 8.18;

            // Check the change is correctly reflected
            CHECK(ev[0] == Approx(5.3));
            CHECK(ev[1] == Approx(-3.19));
            CHECK(ev[2] == Approx(4.25));
            CHECK(ev[3] == Approx(8.18));
        }
    }
}

/*
   Test if the unary operators are overloading correctly.
   Cases:
   - Whether the value is expected
   - Whether a copy is returned, modifying one will not affect the other
   - The original vector stays the same


   Assumes the *= operator is correctly overloaded.

   Rational:
   - In the case of the uanry plus, except for testing the the vector is returned with the
   correct dimension and magnitudes, we should also test if modifying one will not affect the
   other, so that we can ensure they have different underlying data members.
   - After return this copy, the original vector's content should remain the same.
*/
TEST_CASE("Unary Operations: Non-zero dimension vector") {
    auto ev1 = comp6771::euclidean_vector{5.3, -3.19, 4.25, 8.18};
    auto ev1_exp = std::vector<double>{5.3, -3.19, 4.25, 8.18};

    SECTION("Unary Plus +") {
        auto ev2 = (+ev1);
        auto ev2_exp = std::vector<double>{5.3, -3.19, 4.25, 8.18};

        SECTION("Returned vector has expected magnitudes") {
            REQUIRE_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
        }

        SECTION("The original vector should stay the same") {
            CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        }

        // Modify ev1, check if ev2 stays the same
        SECTION("Modify one, the other stay the same") {
            ev1 *= 2;
            CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
        }
    }

    SECTION("Negation -") {
        SECTION("Returned vector has expected magnitudes") {
            auto ev2 = (-ev1);
            auto ev2_exp = std::vector<double>{-5.3, 3.19, -4.25, -8.18};
            CHECK_THAT(static_cast<std::vector<double>>(ev2), Catch::Approx(ev2_exp));
        }

        SECTION("The original vector should stay the same") {
            CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        }
    }
}

/*
   Rational: The unary operator + and - make sense for a zero dimension vector, so we should test if
   they are behaving properly by producing a zero dimension vector.
*/
TEST_CASE("Unary Operations: Zero dimension vector") {
    auto const ev_zero_dim = comp6771::euclidean_vector(0);

    auto ev1 = (+ev_zero_dim);
    auto ev2 = (-ev_zero_dim);

    CHECK(ev1.dimensions() == 0);
    CHECK(ev2.dimensions() == 0);
}

/*
   Test if the compound operators are overloading correctly.
   Approach (Each respetive session):
   - Test if these operator will correctly update the value of the source euclidean vector
   - Test if performing them on themselves will produce the correct value
   - Test if the correct exception is thrown with the correct message

   Rational: Testing the above can ensure the correctness of these operators as these are all the
   behaviors they have. The behavior when adding two same vector object also should produce the
   right result.
*/
TEST_CASE("Compound Operators") {
    auto ev1 = comp6771::euclidean_vector{5.3, -3.19, 4.25, 8.18};
    auto ev2_same_dimension = comp6771::euclidean_vector{1.0, -5.19, 9.25, 0.0};
    auto ev3_diff_dimension = comp6771::euclidean_vector{5.2, 13.14};

    SECTION("+=: Match expected output") {
        SECTION("Add another instance") {
            ev1 += ev2_same_dimension;
            auto ev1_exp = std::vector<double>{6.3, -8.38, 13.5, 8.18};
            REQUIRE_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        }

        SECTION("Plus itself") {
            ev1 += ev1;
            auto ev1_exp = std::vector<double>{10.6, -6.38, 8.5, 16.36};
            CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        }
    }

    SECTION("-=: Match expected output") {
        SECTION("Minus another instance") {
            ev1 -= ev2_same_dimension;
            auto ev1_exp = std::vector<double>{4.3, 2.0, -5.0, 8.18};
            REQUIRE_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        }

        SECTION("Minus itself") {
            ev1 -= ev1;
            auto ev1_exp = std::vector<double>{0.0, 0.0, 0.0, 0.0};
            CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        }
    }

    SECTION("*=: Match expected output") {
        SECTION("Time non zero double") {
            ev1 *= 2.0;
            auto ev1_exp = std::vector<double>{10.6, -6.38, 8.5, 16.36};
            CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        }

        SECTION("Time 0") {
            ev1 *= 0;
            auto ev1_exp = std::vector<double>{0, 0, 0, 0};
            CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
        }
    }

    SECTION("/=: Match expected output") {
        ev1 /= 2.0;
        auto ev1_exp = std::vector<double>{2.65, -1.595, 2.125, 4.09};
        CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
    }

    SECTION("Exception of += and -=: Not matching dimension") {
        CHECK_THROWS_MATCHES(ev1 += ev3_diff_dimension,
                             comp6771::euclidean_vector_error,
                             Catch::Matchers::Message("Dimensions of LHS(4) and RHS(2) do not "
                                                      "match"));

        CHECK_THROWS_MATCHES(ev1 -= ev3_diff_dimension,
                             comp6771::euclidean_vector_error,
                             Catch::Matchers::Message("Dimensions of LHS(4) and RHS(2) do not "
                                                      "match"));
    }

    SECTION("Exception of /=: Division by 0") {
        CHECK_THROWS_MATCHES(ev1 /= 0,
                             comp6771::euclidean_vector_error,
                             Catch::Matchers::Message("Invalid vector division by 0"));
    }

    SECTION("0 dimension: The result between two 0 dimensions should yield a 0 dimension "
            "vector") {
        auto zero_dim_1 = comp6771::euclidean_vector(0);
        auto zero_dim_2 = comp6771::euclidean_vector(0);

        SECTION("+=") {
            CHECK_NOTHROW(zero_dim_1 += zero_dim_2);
            CHECK(zero_dim_1.dimensions() == 0);

            CHECK_NOTHROW(zero_dim_1 += zero_dim_1);
            CHECK(zero_dim_1.dimensions() == 0);
        }

        SECTION("-=") {
            CHECK_NOTHROW(zero_dim_1 -= zero_dim_2);
            CHECK(zero_dim_1.dimensions() == 0);

            CHECK_NOTHROW(zero_dim_1 -= zero_dim_1);
            CHECK(zero_dim_1.dimensions() == 0);
        }

        SECTION("*=") {
            CHECK_NOTHROW(zero_dim_1 *= 2.0);
            CHECK(zero_dim_1.dimensions() == 0);

            CHECK_NOTHROW(zero_dim_1 *= 2.0);
            CHECK(zero_dim_1.dimensions() == 0);
        }

        SECTION("/=") {
            CHECK_NOTHROW(zero_dim_1 /= 2.0);
            CHECK(zero_dim_1.dimensions() == 0);

            CHECK_NOTHROW(zero_dim_1 /= 2.0);
            CHECK(zero_dim_1.dimensions() == 0);
        }
    }
}

/*
   Cast euclidean_vectors to vector and check if the conversion is correct.
   Test cases:
   - Check if 0 dimensions euclidean_vectors work
   - Check if non-0 dimensions euclidean_vectors work
*/
TEST_CASE("Vector Type Conversion") {
    SECTION("Zero dimensions: Empty vector") {
        auto const ev1 = comp6771::euclidean_vector(0);
        auto const ev1_exp = std::vector<double>();

        CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
    }

    SECTION("Non-zero dimensions") {
        auto const ev1 = comp6771::euclidean_vector{5.3, -3.19, 4.25, 8.18};
        auto const ev1_exp = std::vector<double>{5.3, -3.19, 4.25, 8.18};

        CHECK_THAT(static_cast<std::vector<double>>(ev1), Catch::Approx(ev1_exp));
    }
}

/*
   Cast euclidean_vectors to list and check if the conversion is correct by compare to a manual
   constructed list. Test cases:
   - Check if 0 dimensions euclidean_vectors work
   - Check if non-0 dimensions euclidean_vectors work
*/
TEST_CASE("List Type Conversion") {
    SECTION("Zero dimensions: Empty List") {
        auto const ev1 = comp6771::euclidean_vector(0);
        auto const ev1_list = static_cast<std::list<double>>(ev1);
        auto const ev1_exp = std::list<double>();

        CHECK(ev1_list == ev1_exp);
    }

    SECTION("Non-zero dimensions") {
        auto const ev1 = comp6771::euclidean_vector{5.3, -3.19, 4.25, 8.18};
        auto const ev1_list = static_cast<std::list<double>>(ev1);

        auto const ev1_exp = std::list<double>{5.3, -3.19, 4.25, 8.18};

        CHECK(ev1_list == ev1_exp);
    }
}

#include "comp6771/euclidean_vector.hpp"

#include <algorithm>
#include <catch2/catch.hpp>

/*
    Tests in the file test if the members have the right behavior and if
    they throw the correct exception with correct message in appropriate
    situtation.

    These tests assumes that the constructors and casting to std::vector are
    correct.

   Rational: Test these member operators and functions's usage on const and non-const will be
   sufficient to ensure their correctness.
*/

/*
   Test case for non-const
   - Can access the value in the given dimension
   - Can modify the value in the given dimension
   - Is exception thrown for invalid index

   Test case for const
   - Can access the value in the given dimension
   - Is exception thrown for invalid index

   Rational:
   - Other than testing the non zero dimension vectors, since zero dimension vector has no
   magnitude so should always throw excpetion which should be tested.
   - Non const vector should be able to modify the magnitude given the reference returned.

*/
TEST_CASE("Subscript") {
    SECTION("Const Version") {
        SECTION("Non zero dimension") {
            auto const ev = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};

            SECTION("Return the correct value of the given magnitude") {
                CHECK(ev.at(0) == Approx(0.0));
                CHECK(ev.at(1) == Approx(1.5));
                CHECK(ev.at(2) == Approx(-4.5));
                CHECK(ev.at(3) == Approx(40.0));
            }

            SECTION("Exception: Index out of range") {
                CHECK_THROWS_MATCHES(ev.at(-1),
                                     comp6771::euclidean_vector_error,
                                     Catch::Matchers::Message("Index -1 is not valid for this "
                                                              "euclidean_vector object"));

                CHECK_THROWS_MATCHES(ev.at(4),
                                     comp6771::euclidean_vector_error,
                                     Catch::Matchers::Message("Index 4 is not valid for this "
                                                              "euclidean_vector "
                                                              "object"));
            }
        }

        SECTION("Exception: Access magnitude in zero Dimension vectors") {
            auto const ev = comp6771::euclidean_vector(0);

            CHECK_THROWS_MATCHES(ev.at(0),
                                 comp6771::euclidean_vector_error,
                                 Catch::Matchers::Message("Index 0 is not valid for this "
                                                          "euclidean_vector object"));
        }
    }

    SECTION("Non-const Version") {
        SECTION("Non zero dimension") {
            auto ev = comp6771::euclidean_vector{0.0, 1.5, -4.5, 40.0};

            SECTION("Return the correct value of the given magnitude") {
                CHECK(ev.at(0) == Approx(0.0));
                CHECK(ev.at(1) == Approx(1.5));
                CHECK(ev.at(2) == Approx(-4.5));
                CHECK(ev.at(3) == Approx(40.0));
            }

            SECTION("Exception: Index out of range") {
                CHECK_THROWS_MATCHES(ev.at(-1),
                                     comp6771::euclidean_vector_error,
                                     Catch::Matchers::Message("Index -1 is not valid for this "
                                                              "euclidean_vector object"));

                CHECK_THROWS_MATCHES(ev.at(4),
                                     comp6771::euclidean_vector_error,
                                     Catch::Matchers::Message("Index 4 is not valid for this "
                                                              "euclidean_vector "
                                                              "object"));
            }

            SECTION("Modify the dimension in the given dimension") {
                ev.at(0) = 5.3;
                ev.at(1) = -3.19;
                ev.at(2) = 4.25;
                ev.at(3) = 8.18;

                // Verify
                auto ev_exp = std::vector<double>{5.3, -3.19, 4.25, 8.18};
                CHECK_THAT(static_cast<std::vector<double>>(ev), Catch::Approx(ev_exp));
            }
        }

        SECTION("Zero Dimension") {
            auto ev = comp6771::euclidean_vector(0);

            CHECK_THROWS_MATCHES(ev.at(0),
                                 comp6771::euclidean_vector_error,
                                 Catch::Matchers::Message("Index 0 is not valid for this "
                                                          "euclidean_vector object"));
        }
    }
}

/*
    Test if the member function dimensions() return the correct dimensions for const and non-const
    objects.

   Rational: This is a non-modifying function, so should be about to be invoked by both const and
   non-const objects.
*/
TEST_CASE("Dimensions()") {
    SECTION("Non-const: Dimension matches") {
        auto ev1 = comp6771::euclidean_vector(0);
        auto ev2 = comp6771::euclidean_vector(5, 0.5);
        auto ev3 = comp6771::euclidean_vector{4.5, 3, 6.7};

        CHECK(ev1.dimensions() == 0);
        CHECK(ev2.dimensions() == 5);
        CHECK(ev3.dimensions() == 3);
    }

    SECTION("Const: Dimension matches") {
        auto const ev1 = comp6771::euclidean_vector(0);
        auto const ev2 = comp6771::euclidean_vector(5, 0.5);
        auto const ev3 = comp6771::euclidean_vector{4.5, 3, 6.7};

        CHECK(ev1.dimensions() == 0);
        CHECK(ev2.dimensions() == 5);
        CHECK(ev3.dimensions() == 3);
    }
}

#include "comp6771/euclidean_vector.hpp"

#include <algorithm>
#include <catch2/catch.hpp>
#include <sstream>
#include <vector>

/*
    Tests in this file tests if the friends overloaded operator have be implemently correctly.
    It matches the computed result with the expected output calculate by calculator and also see if
    appropriate exception is throw.

    Rational: These operator is can only do computation or throw exception.
*/

/*
   Test cases:
   - 0 dimension EVs are equal
   - A vector is equals to itself: Reflective
   - Two vectors are equal in the number of dimensions but different in the magnitude in each
   dimension are not equal vectors.
   - Two vecters differ in dimensions number are not equal vectors
*/
TEST_CASE("Equal Operator") {
    auto const ev_zero_dim = comp6771::euclidean_vector(0);

    SECTION("Zero dimension") {
        auto const ev = comp6771::euclidean_vector(0);

        CHECK(ev_zero_dim == ev);
        CHECK(ev == ev);
    }

    SECTION("Non Zero dimension") {
        auto const ev = comp6771::euclidean_vector{0.5, -3.5, 4.25, 3.09};
        auto const ev_same = comp6771::euclidean_vector{0.5, -3.5, 4.25, 3.09};

        auto const ev_diff_1 = comp6771::euclidean_vector{0.5, -3.5, -4.25, 3.09};
        auto const ev_diff_2 = comp6771::euclidean_vector{0.5, -3.5};

        SECTION("Same dimensions, different magnitudes") {
            CHECK_FALSE(ev == ev_diff_1);
        }

        SECTION("Different dimensions") {
            CHECK_FALSE(ev == ev_zero_dim);
            CHECK_FALSE(ev == ev_diff_2);
        }

        SECTION("Equal to itself") {
            CHECK(ev == ev);
        }

        SECTION("Equal in dimensions and magnitudes") {
            CHECK(ev == ev_same);
        }
    }
}

/*
   Rational: Basically negating the tests in the == cases.
*/
TEST_CASE("Not Equal") {
    auto const ev_zero_dim = comp6771::euclidean_vector(0);

    SECTION("Zero dimension") {
        auto const ev = comp6771::euclidean_vector(0);

        CHECK_FALSE(ev_zero_dim != ev);
        CHECK_FALSE(ev != ev);
    }

    SECTION("Non Zero dimension") {
        auto const ev = comp6771::euclidean_vector{0.5, -3.5, 4.25, 3.09};
        auto const ev_same = comp6771::euclidean_vector{0.5, -3.5, 4.25, 3.09};

        auto const ev_diff_1 = comp6771::euclidean_vector{0.5, -3.5, -4.25, 3.09};
        auto const ev_diff_2 = comp6771::euclidean_vector{0.5, -3.5};

        SECTION("Same dimensions, different magnitudes") {
            CHECK(ev != ev_diff_1);
        }

        SECTION("Different dimensions") {
            CHECK(ev != ev_zero_dim);
            CHECK(ev != ev_diff_2);
        }

        SECTION("Equal to itself") {
            CHECK_FALSE(ev != ev);
        }

        SECTION("Equal in dimensions and magnitudes") {
            CHECK_FALSE(ev != ev_same);
        }
    }
}

/*
   Test cases:
   - If performing these operators yield the expected result
   - If exception is thrown in appriopriate situtaion with the correct message
   - If 0 dimension is handled correctly

   Assumes casting to vector is implementing correctly.

   Rational: For arithmetic operators just check if they are invoked correctly and product the right
   result and throw the right exception.
*/
TEST_CASE("+ - * /: Test vectors with non zero Dimension") {
    auto const ev = comp6771::euclidean_vector{0.5, -3.5, 4.25, 3.09};
    auto const ev_same_dim_1 = comp6771::euclidean_vector{1.5, 10.2, 3.14, 5.2};
    auto const ev_same_dim_2 = comp6771::euclidean_vector{1, -1, 1, -1};

    SECTION("+") {
        CHECK_THAT(static_cast<std::vector<double>>(ev + ev_same_dim_1),
                   Catch::Approx(std::vector<double>{2, 6.7, 7.39, 8.29}));

        CHECK_THAT(static_cast<std::vector<double>>(ev + ev_same_dim_1 + ev_same_dim_2),
                   Catch::Approx(std::vector<double>{3, 5.7, 8.39, 7.29}));
    }

    SECTION("-") {
        CHECK_THAT(static_cast<std::vector<double>>(ev - ev_same_dim_1),
                   Catch::Approx(std::vector<double>{-1, -13.7, 1.11, -2.11}));

        CHECK_THAT(static_cast<std::vector<double>>(ev - ev_same_dim_1 - ev_same_dim_2),
                   Catch::Approx(std::vector<double>{-2, -12.7, 0.11, -1.11}));
    }

    SECTION("*") {
        CHECK_THAT(static_cast<std::vector<double>>(ev * 0),
                   Catch::Approx(std::vector<double>{0, 0, 0, 0}));

        CHECK_THAT(static_cast<std::vector<double>>(ev * 2),
                   Catch::Approx(std::vector<double>{1, -7, 8.5, 6.18}));
    }

    SECTION("/") {
        CHECK_THAT(static_cast<std::vector<double>>(ev / 2),
                   Catch::Approx(std::vector<double>{0.25, -1.75, 2.125, 1.545}));

        CHECK_THAT(static_cast<std::vector<double>>(ev / 2 / 0.2),
                   Catch::Approx(std::vector<double>{1.25, -8.75, 10.625, 7.725}));
    }

    SECTION("Exceptions") {
        auto const ev_diff_dim_1 = comp6771::euclidean_vector{0.5, -3.5};
        auto const ev_diff_dim_2 = comp6771::euclidean_vector(0);

        SECTION("Plus and minus: Mismatch dimensions") {
            CHECK_THROWS_MATCHES(ev + ev_diff_dim_1,
                                 comp6771::euclidean_vector_error,
                                 Catch::Matchers::Message("Dimensions of LHS(4) and RHS(2) do not "
                                                          "match"));

            CHECK_THROWS_MATCHES(ev + ev_diff_dim_2,
                                 comp6771::euclidean_vector_error,
                                 Catch::Matchers::Message("Dimensions of LHS(4) and RHS(0) do not "
                                                          "match"));

            CHECK_THROWS_MATCHES(ev - ev_diff_dim_1,
                                 comp6771::euclidean_vector_error,
                                 Catch::Matchers::Message("Dimensions of LHS(4) and RHS(2) do not "
                                                          "match"));

            CHECK_THROWS_MATCHES(ev - ev_diff_dim_2,
                                 comp6771::euclidean_vector_error,
                                 Catch::Matchers::Message("Dimensions of LHS(4) and RHS(0) do not "
                                                          "match"));
        }

        SECTION("/: Division by 0") {
            CHECK_THROWS_MATCHES(ev / 0,
                                 comp6771::euclidean_vector_error,
                                 Catch::Matchers::Message("Invalid vector division by 0"));
        }
    }
}

/*
   Check if performing these operations on 0 dimension vectors yield 0 dimension vector. And
   exception will be thrown when appropriate.

   Rational: Since this case is only for zero dimension vectors, we don't need to check for
   exception thrown due to dimension mismatch.
*/
TEST_CASE("+ - * /: Test vectors with zero dimension") {
    auto const ev_zero_dim_1 = comp6771::euclidean_vector(0);
    auto const ev_zero_dim_2 = comp6771::euclidean_vector({});

    SECTION("All results should vectors of zero dimension") {
        CHECK((ev_zero_dim_1 + ev_zero_dim_2).dimensions() == 0);
        CHECK((ev_zero_dim_1 - ev_zero_dim_2).dimensions() == 0);
        CHECK((ev_zero_dim_1 * 2).dimensions() == 0);
        CHECK((ev_zero_dim_1 / 2).dimensions() == 0);
    }

    SECTION("Exception: Division by zero") {
        CHECK_THROWS_MATCHES(ev_zero_dim_1 / 0,
                             comp6771::euclidean_vector_error,
                             Catch::Matchers::Message("Invalid vector division by 0"));
    }
}

/*
   Test cases:
   - Output a 0-dimension vector gives []
   - Output non-zero dimension vector and compare with expected output

   Rational: These tests covers all use case of this oeprator
*/
TEST_CASE("Output Stream") {
    SECTION("Zero Dimension: Yield []") {
        auto const ev_zero_dim_1 = comp6771::euclidean_vector(0);

        auto oss = std::ostringstream{};
        oss << ev_zero_dim_1;
        CHECK(oss.str() == "[]");
    }

    SECTION("Non-zero Dimension: Yield magnitudes of the inputted euclidean vector") {
        auto const ev = comp6771::euclidean_vector{3, 5.7, 8.39, 7.29};

        auto oss = std::ostringstream{};
        oss << ev;
        CHECK(oss.str() == "[3 5.7 8.39 7.29]");
    }
}

#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <catch2/catch.hpp>

#include <vector>

/*
    Tests in this file tests if the utility functions have be implemently correctly.
    By that, it means the result computed is expected and appropriate exception
    is throw.

    All tests assume that casting to vector is correctly implemented.

    Rational: These functions can only do computation or throw exception. So it is sufficient to see
   if exception is thrown and if the computation is correct.

   All the expected value are computed using scientific calcultor.
*/

TEST_CASE("Norm") {
    SECTION("Zero Dimension: Have norm of 0") {
        auto const ev_zero_dim = comp6771::euclidean_vector(0);

        CHECK(comp6771::euclidean_norm(ev_zero_dim) == Approx(0));
    }

    SECTION("Non-zero Dimension: Match expected norm calculated by calculator") {
        SECTION("Test 1") {
            auto const ev = comp6771::euclidean_vector{1, 2, 3};

            CHECK(comp6771::euclidean_norm(ev) == Approx(3.7416573867739));
        }

        SECTION("Test 2") {
            auto const ev = comp6771::euclidean_vector{4.5, 6.771, -2.041, 25.11, 92.43, -608};

            CHECK(comp6771::euclidean_norm(ev) == Approx(615.55509836407));
        }
    }
}

/*
   Since we maintain a cache of the norm, use different mutating opertions and see if cache has been
   invalidated and if the norm is computed.
 */
TEST_CASE("Norm Cache Invalidation") {
    auto ev = comp6771::euclidean_vector{1, 2, 3};

    // Compute the norm, cause it to be cached
    CHECK(comp6771::euclidean_norm(ev) == Approx(3.7416573867739));

    SECTION("Non const []") {
        ev[1] = 5;

        CHECK(comp6771::euclidean_norm(ev) == Approx(5.9160797830996));
    }

    SECTION("+=") {
        ev += comp6771::euclidean_vector{6, 7, 8};

        CHECK(comp6771::euclidean_norm(ev) == Approx(15.842979517755));
    }

    SECTION("-=") {
        ev -= comp6771::euclidean_vector{9, 4, 25};

        CHECK(comp6771::euclidean_norm(ev) == Approx(23.494680248941));
    }

    SECTION("*=") {
        ev *= 2;

        CHECK(comp6771::euclidean_norm(ev) == Approx(7.4833147735479));
    }

    SECTION("/=") {
        ev /= 0.5;

        CHECK(comp6771::euclidean_norm(ev) == Approx(7.4833147735479));
    }

    SECTION("Non const at") {
        ev.at(1) = 5;

        CHECK(comp6771::euclidean_norm(ev) == Approx(5.9160797830996));
    }
}

TEST_CASE("Unit Vector") {
    SECTION("Test if the correct unit vector is return") {
        SECTION("Test 1") {
            auto const ev = comp6771::euclidean_vector{0, 8, 6, 0};
            auto const ev_unit_exp = std::vector<double>{0, 0.8, 0.6, 0};

            CHECK_THAT(static_cast<std::vector<double>>(comp6771::unit(ev)), Catch::Approx(ev_unit_exp));
        }

        SECTION("Test 2") {
            auto const ev = comp6771::euclidean_vector{7, 4, 6, -1, -5, 9};
            auto const ev_unit_exp = std::vector<double>{0.485362671,
                                                         0.277350098,
                                                         0.416025147,
                                                         -0.069337524,
                                                         -0.346687622,
                                                         0.624037720};

            CHECK_THAT(static_cast<std::vector<double>>(comp6771::unit(ev)), Catch::Approx(ev_unit_exp));
        }
    }

    SECTION("Exception: No dimension") {
        auto const ev_zero_dim = comp6771::euclidean_vector(0);

        CHECK_THROWS_MATCHES(comp6771::unit(ev_zero_dim),
                             comp6771::euclidean_vector_error,
                             Catch::Matchers::Message("euclidean_vector with no dimensions does not "
                                                      "have a unit vector"));
    }

    SECTION("Exception: Norm == 0") {
        auto const ev_zero_norm = comp6771::euclidean_vector{0, 0, 0, 0};

        CHECK_THROWS_MATCHES(comp6771::unit(ev_zero_norm),
                             comp6771::euclidean_vector_error,
                             Catch::Matchers::Message("euclidean_vector with zero euclidean normal "
                                                      "does not have a unit vector"));
    }
}

TEST_CASE("Dot Product") {
    SECTION("Zero Dimension: Return 0 as the dot product") {
        /* Two 0 dimension should gives dot product 0 */
        auto const ev1 = comp6771::euclidean_vector(0);
        auto const ev2 = comp6771::euclidean_vector(0);

        CHECK(comp6771::dot(ev1, ev2) == 0);
    }

    SECTION("Non zero Dimension: Return the sum of squares in magnitude") {
        SECTION("Test 1") {
            auto const ev = comp6771::euclidean_vector{1, 2};
            auto const ev_same_dim = comp6771::euclidean_vector{3, 4};

            CHECK(comp6771::dot(ev, ev_same_dim) == Approx(11));
        }

        SECTION("Test 2") {
            auto const ev = comp6771::euclidean_vector{-1.2, 2.5, 3.7, 4.5};
            auto const ev_same_dim = comp6771::euclidean_vector{-4.5, 3, 2.7, 1.5};

            CHECK(comp6771::dot(ev, ev_same_dim) == Approx(29.64));
        }
    }

    SECTION("Exception: Dimension not match") {
        auto const ev = comp6771::euclidean_vector{1, 2, 3, 4};
        auto const ev_diff_dim_1 = comp6771::euclidean_vector{2, 3, 4, 5, 6, 9, 0};
        auto const ev_diff_dim_2 = comp6771::euclidean_vector(0);

        CHECK_THROWS_MATCHES(comp6771::dot(ev, ev_diff_dim_1),
                             comp6771::euclidean_vector_error,
                             Catch::Matchers::Message("Dimensions of LHS(4) and RHS(7) do not "
                                                      "match"));

        CHECK_THROWS_MATCHES(comp6771::dot(ev, ev_diff_dim_2),
                             comp6771::euclidean_vector_error,
                             Catch::Matchers::Message("Dimensions of LHS(4) and RHS(0) do not "
                                                      "match"));
    }
}

#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <catch2/catch.hpp>
#include <sstream>
#include <vector>

/*
    Tests in this file test the class by mixing the uses of different operators and operation.

    These test assume the correctness of the contructors.

    All expected output is calculated by wolframAlpha.

    Rational: Sometimes unit testing is not sufficient to ensure the correctness of using all
    operations together. So it is worth testing. There's no need to test exception throwing as the
    unit test will be sufficient.
*/

TEST_CASE("Integration Test") {
    auto ev_four_dim_1 = comp6771::euclidean_vector{2.54, 7.98, -3.76, 4.25};
    auto ev_four_dim_2 = comp6771::euclidean_vector{-8.964, 5.2, 13.19, -5.2};

    /* Test: Casting to std::vector */
    CHECK_THAT(static_cast<std::vector<double>>(ev_four_dim_1),
               Catch::Approx(std::vector<double>{2.54, 7.98, -3.76, 4.25}));

    CHECK_THAT(static_cast<std::vector<double>>(ev_four_dim_2),
               Catch::Approx(std::vector<double>{-8.964, 5.2, 13.19, -5.2}));

    /* Test Friend functions */

    // Arithmetic Operators
    CHECK_THAT(static_cast<std::vector<double>>(ev_four_dim_1 * 0.3 + ev_four_dim_2 / (-2.5)),
               Catch::Approx(std::vector<double>{4.3476, 0.314, -6.404, 3.355}));

    CHECK_THAT(static_cast<std::vector<double>>(ev_four_dim_1 / 3.598 - ev_four_dim_2 * (3.14)),
               Catch::Approx(std::vector<double>{28.85290, -14.11010, -42.46162, 17.50921}));

    // Output Stream
    auto oss = std::ostringstream{};
    oss << (ev_four_dim_1 / 3.598 - ev_four_dim_2 * (3.14));
    CHECK(oss.str() == "[28.8529 -14.1101 -42.4616 17.5092]");

    // == !=
    CHECK(ev_four_dim_1 != ev_four_dim_2);
    CHECK(ev_four_dim_1 * 0.5 != ev_four_dim_2 * 3.14);

    CHECK(ev_four_dim_1 * 0.3 / 0.3 == ev_four_dim_1);

    /* Test member functions */
    ev_four_dim_1 += ev_four_dim_2;
    ev_four_dim_1 *= 3.14;

    CHECK_THAT(static_cast<std::vector<double>>(ev_four_dim_1),
               Catch::Approx(std::vector<double>{-20.1714, 41.3852, 29.6102, -2.983}));

    /* Test Utility functions */

    // Norm & Unit Vector
    CHECK(comp6771::euclidean_norm(ev_four_dim_1) == Approx(54.8204));
    CHECK_THAT(static_cast<std::vector<double>>(comp6771::unit(ev_four_dim_1)),
               Catch::Approx(std::vector<double>{-0.367953, 0.754923, 0.540131, -0.054414}));

    ev_four_dim_1[3] = 3.1415926;
    CHECK(comp6771::euclidean_norm(ev_four_dim_1) == Approx(54.8293));
    CHECK_THAT(static_cast<std::vector<double>>(comp6771::unit(ev_four_dim_1)),
               Catch::Approx(std::vector<double>{-0.367894, 0.754801, 0.540043, 0.0572977}));

    // Dot product
    CHECK(comp6771::dot(ev_four_dim_1, ev_four_dim_2) == Approx(770.24172608));

    ev_four_dim_2 /= 0.45;
    CHECK_THAT(static_cast<std::vector<double>>(ev_four_dim_2),
               Catch::Approx(std::vector<double>{-19.92, 11.5556, 29.3111, -11.5556}));

    CHECK(comp6771::dot(ev_four_dim_1, ev_four_dim_2) == Approx(1711.64965089144));
}