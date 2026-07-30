/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/linear_complexity.hpp>

TEST_CASE("Linear Complexity Test fails gracefully with insufficient input", "[linear-complexity]")
{
   const std::vector < uint8_t > test_vector ( 100, 0xFF );

   using namespace nist_sts;
   REQUIRE ( linear_complexity_test ( test_vector.data (), test_vector.size () ) == false );
}

TEST_CASE("Linear Complexity Test executes and detects predictable sequence", "[linear-complexity]")
{
   // 125,000 bytes * 8 = 1,000,000 bits (Minimum required for M=500)
   const std::vector < uint8_t > test_vector ( 125000, 0b10101010 ); 

   using namespace nist_sts;
   
   // A purely alternating sequence has an extremely low LFSR complexity length.
   // It should be immediately rejected by the Berlekamp-Massey analysis.
   REQUIRE ( linear_complexity_test ( test_vector.data (), test_vector.size () ) == false );
}