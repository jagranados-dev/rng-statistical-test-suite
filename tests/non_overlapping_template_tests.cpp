/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/non_overlapping_template.hpp>

TEST_CASE("Non-overlapping Template Matching Test passes with valid input", "[non-overlapping]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000, 0b11110000, 0b01010101, 0b10101010
   };
   
   std::vector < bool > template_bits = { 1, 0, 1 };

   using namespace nist_sts;
   REQUIRE ( non_overlapping_template_test ( test_vector.data (), test_vector.size (), template_bits, 4 ) == true );
}

TEST_CASE("Non-overlapping Template Matching Test fails with targeted uniform input", "[non-overlapping]")
{
   const std::vector < uint8_t > test_vector ( 16, 0b10110110 ); 
   std::vector < bool > template_bits = { 1, 0, 1 };

   using namespace nist_sts;
   REQUIRE ( non_overlapping_template_test ( test_vector.data (), test_vector.size (), template_bits, 4 ) == false );
}