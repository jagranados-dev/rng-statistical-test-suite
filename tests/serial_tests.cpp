/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/serial.hpp>

TEST_CASE("Serial Test passes with visually random input", "[serial]")
{
   // A sufficiently long semi-random block for m=3 testing
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   auto [ p1, p2 ] = serial_test ( test_vector.data (), test_vector.size (), 3 );
   REQUIRE ( p1 == true );
   REQUIRE ( p2 == true );
}

TEST_CASE("Serial Test fails with non-random input", "[serial]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000, 0b00000000, 0b00000000, 0b11111111,
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist_sts;
   auto [ p1, p2 ] = serial_test ( test_vector.data (), test_vector.size (), 3 );
   REQUIRE ( ( p1 == false || p2 == false ) );
}

TEST_CASE("Serial Test handles edge cases smoothly", "[serial]")
{
   const std::vector < uint8_t > test_vector = { 0b11001001 };

   using namespace nist_sts;
   
   // Test should fail gracefully if m is 0
   auto [ p1, p2 ] = serial_test ( test_vector.data (), test_vector.size (), 0 );
   REQUIRE ( p1 == false );
   REQUIRE ( p2 == false );
   
   // Test should fail gracefully if m is greater than total bits
   auto [ p3, p4 ] = serial_test ( test_vector.data (), test_vector.size (), 10 );
   REQUIRE ( p3 == false );
   REQUIRE ( p4 == false );
}