/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist_sts/overlapping_template.hpp>

TEST_CASE("Overlapping Template Matching Test fails gracefully with insufficient input", "[overlapping]")
{
   const std::vector < uint8_t > test_vector ( 100, 0xFF ); // 800 bits < 1032
   std::vector < bool > template_bits ( 9, 1 );

   using namespace nist_sts;
   REQUIRE ( overlapping_template_test ( test_vector.data (), test_vector.size (), template_bits ) == false );
}

TEST_CASE("Overlapping Template Matching Test executes and handles uniform sequence", "[overlapping]")
{
   const std::vector < uint8_t > test_vector ( 13000, 0b10101010 ); // 104000 bits
   std::vector < bool > template_bits ( 9, 1 );

   using namespace nist_sts;
   REQUIRE ( overlapping_template_test ( test_vector.data (), test_vector.size (), template_bits ) == false );
}