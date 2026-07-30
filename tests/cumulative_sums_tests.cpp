/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/cumulative_sums.hpp>

TEST_CASE("Cumulative Sums Test passes with valid input", "[cusum]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   auto [ p_fwd, p_bwd ] = cumulative_sums_test ( test_vector.data (), test_vector.size () );
   REQUIRE ( p_fwd == true );
   REQUIRE ( p_bwd == true );
}

TEST_CASE("Cumulative Sums Test fails with non-random sequence", "[cusum]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000
   };

   using namespace nist_sts;
   auto [ p_fwd, p_bwd ] = cumulative_sums_test ( test_vector.data (), test_vector.size () );
   
   // A sequence of all zeros will maximize the excursion, failing the test.
   REQUIRE ( p_fwd == false );
   REQUIRE ( p_bwd == false );
}