/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/universal.hpp>

TEST_CASE("Universal Test fails gracefully with insufficient input", "[universal]")
{
   const std::vector < uint8_t > test_vector ( 100, 0xFF );

   using namespace nist_sts;
   REQUIRE ( universal_test ( test_vector.data (), test_vector.size () ) == false );
}

TEST_CASE("Universal Test executes and detects highly compressible (non-random) sequence", "[universal]")
{
   // 48480 bytes * 8 = 387,840 bits (Minimum required for L=6)
   const std::vector < uint8_t > test_vector ( 48480, 0b10101010 ); 

   using namespace nist_sts;
   // A uniform repeating sequence is fully compressible, thus it fails the test
   REQUIRE ( universal_test ( test_vector.data (), test_vector.size () ) == false );
}