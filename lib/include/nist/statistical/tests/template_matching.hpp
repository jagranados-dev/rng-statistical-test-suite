/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#ifndef __NIST_STATISTICAL_TESTS_TEMPLATE_MATCHING_HPP_
#define __NIST_STATISTICAL_TESTS_TEMPLATE_MATCHING_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist {
namespace statistical {
namespace tests {

   /**
    * The focus of this test is the number of occurrences of pre-specified target strings.
    * 
    * The purpose of this test is to detect generators that produce too many occurrences 
    * of a given non-periodic (aperiodic) pattern. For this test, an m-bit window is used 
    * to search for a specific m-bit pattern. 
    * 
    * If the pattern is not found, the window slides one bit position.
    * 
    * If the pattern is found, the window is reset to the bit after the found pattern, and
    * the search resumes.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length.
    * 
    * @return True if the the p-value is 0.01 or greater.
    */
   bool
   non_overlapping_template_maching_test ( const uint8_t input [], size_t input_length );

   /**
    * The focus of the Overlapping Template Matching test is the number of occurrences of
    * pre-specified target strings. Both this test and the Non-overlapping Template Matching 
    * test use an m-bit window to search for a specific m-bit pattern.
    * 
    * If the pattern is not found, the window slides one bit position.
    * 
    * The difference between this test and the test in Non-overlapping Template Matching 
    * test is that when the pattern is found, the window slides only one bit before resuming 
    * the search.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length.
    * 
    * @return True if the the p-value is 0.01 or greater.
    */
   bool
   overlapping_template_maching_test ( const uint8_t input [], size_t input_length );

} // tests
} // statistical
} // nist

#endif // __NIST_STATISTICAL_TESTS_TEMPLATE_MATCHING_HPP_