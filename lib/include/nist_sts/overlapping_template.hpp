/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_OVERLAPPING_TEMPLATE_HPP_
#define __NIST_STS_OVERLAPPING_TEMPLATE_HPP_

#include <cinttypes>
#include <cstddef>
#include <vector>

namespace nist_sts
{

   /**
    * The focus of the Overlapping Template Matching test is the number of 
    * occurrences of pre-specified target strings.
    * 
    * The purpose of this test is to detect whether there are too many 
    * occurrences of a given pattern. When a match is found, the window 
    * slides only one bit before resuming the search.
    * 
    * Note: As per NIST SP 800-22 specifications, this implementation uses 
    * the tabular degrees of freedom (K=5) and probabilities mapped for 
    * block size m = 9 and M = 1032.
    * 
    * @param input         The random sequence to be tested.
    * @param input_length  The random sequence length in bytes.
    * @param template_bits The m-bit template to match (must be size 9).
    * 
    * @return True if the p-value is 0.01 or greater, false otherwise.
    */
   bool
   overlapping_template_test ( const uint8_t               input [], 
                               size_t                      input_length, 
                               const std::vector < bool >& template_bits );

} // nist_sts

#endif // __NIST_STS_OVERLAPPING_TEMPLATE_HPP_