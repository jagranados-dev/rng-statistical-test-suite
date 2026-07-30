/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/frequency.hpp>

TEST_CASE("Frequency (Monobit) Test pass with valid input", "[monobit]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   REQUIRE ( frequency_test ( test_vector.data (), test_vector.size () ) == true);
}

TEST_CASE("Frequency (Monobit) Test fails with invalid input", "[monobit]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000, 0b00000000, 0b00000000, 0b11111111,
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   REQUIRE ( frequency_test ( test_vector.data (), test_vector.size () ) == false);
}

//--------------------------------------------------------------------------------

TEST_CASE("Frequency Test within a Block pass with valid input", "[frequency-within-block]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   REQUIRE ( frequency_test_within_a_block ( test_vector.data (), test_vector.size (), 20 ) == true);
}

TEST_CASE("Frequency Test within a Block fails with invalid input", "[frequency-within-block]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000, 0b00000000, 0b00000000, 0b11111111,
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   REQUIRE ( frequency_test_within_a_block ( test_vector.data (), test_vector.size (), 20 ) == false);
}

TEST_CASE("Frequency Test within a Block fails with invalid block size", "[frequency-within-block]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   REQUIRE ( frequency_test_within_a_block ( test_vector.data (), test_vector.size (), 10 ) == false);
}