/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/binary_matrix_rank.hpp>

TEST_CASE("Binary Matrix Rank Test fails with invalid input size", "[binary-matrix-rank]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b11011010, 0b10100010, 0b11000010, 0b00110100
   };

   using namespace nist_sts;
   REQUIRE ( binary_matrix_rank_test ( test_vector.data (), test_vector.size () ) == false);
}