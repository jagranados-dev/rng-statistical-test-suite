/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/runs.hpp>

TEST_CASE("Runs Test pass with valid input", "[runs]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   REQUIRE ( runs_test ( test_vector.data (), test_vector.size () ) == true);
}

TEST_CASE("Runs Test fails with invalid input", "[runs]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000, 0b00000000, 0b00000000, 0b11111111,
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   REQUIRE ( runs_test ( test_vector.data (), test_vector.size () ) == false);
}

//--------------------------------------------------------------------------------

TEST_CASE("Longest Run of Ones in a Block Test pass with valid input", "[runs]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001100, 0b00010101, 0b01101100, 0b01001100, 
      0b11100000, 0b00000010, 0b01001101, 0b01010001,
      0b00010011, 0b11010110, 0b10000000, 0b11010111, 
      0b11001100, 0b11100110, 0b11011000, 0b10110010 
   };

   using namespace nist_sts;
   REQUIRE ( runs_test ( test_vector.data (), test_vector.size () ) == true);
}

TEST_CASE("Longest Run of Ones in a Block Test fails with invalid input", "[runs]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000, 0b00000000, 0b00000000, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
   };

   using namespace nist_sts;
   REQUIRE ( runs_test ( test_vector.data (), test_vector.size () ) == false);
}