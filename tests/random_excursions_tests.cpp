/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/random_excursions.hpp>

TEST_CASE("Random Excursions Test fails gracefully with insufficient input", "[random-excursions]")
{
   const std::vector < uint8_t > test_vector ( 100, 0xFF );

   using namespace nist_sts;
   REQUIRE ( random_excursions_test ( test_vector.data (), test_vector.size () ) == false );
   REQUIRE ( random_excursions_variant_test ( test_vector.data (), test_vector.size () ) == false );
}

TEST_CASE("Random Excursions Test executes and detects non-random cyclical sequence", "[random-excursions]")
{
   // 125,000 bytes * 8 = 1,000,000 bits (Minimum required)
   // An alternating sequence (101010...) crosses zero constantly, resulting 
   // in J = 500,000 cycles, but fails the statistical variance entirely.
   const std::vector < uint8_t > test_vector ( 125000, 0b10101010 ); 

   using namespace nist_sts;
   REQUIRE ( random_excursions_test ( test_vector.data (), test_vector.size () ) == false );
   REQUIRE ( random_excursions_variant_test ( test_vector.data (), test_vector.size () ) == false );
}