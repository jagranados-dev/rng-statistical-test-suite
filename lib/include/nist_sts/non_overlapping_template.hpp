/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_NON_OVERLAPPING_TEMPLATE_HPP_
#define __NIST_STS_NON_OVERLAPPING_TEMPLATE_HPP_

#include <cinttypes>
#include <cstddef>
#include <vector>

namespace nist_sts
{

   /**
    * The focus of this test is the number of occurrences of pre-specified target strings.
    * 
    * The purpose of this test is to detect whether too many occurrences of a given 
    * non-periodic (aperiodic) pattern occur. For this test, an m-bit window is used 
    * to search for a specific m-bit pattern. If the pattern is not found, the window 
    * slides one bit position. If the pattern is found, the window is reset to the bit 
    * after the found pattern, and the search resumes.
    * 
    * @param input         The random sequence to be tested.
    * @param input_length  The random sequence length in bytes.
    * @param template_bits The m-bit template to match, represented as a vector of booleans.
    * @param num_blocks    The number of independent blocks (N). NIST recommends N=8.
    * 
    * @return True if the p-value is 0.01 or greater, false otherwise.
    */
   bool
   non_overlapping_template_test ( const uint8_t               input [], 
                                   size_t                      input_length, 
                                   const std::vector < bool >& template_bits,
                                   size_t                      num_blocks = 8 );

} // nist_sts

#endif // __NIST_STS_NON_OVERLAPPING_TEMPLATE_HPP_