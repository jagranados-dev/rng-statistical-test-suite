/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_APPROXIMATE_ENTROPY_HPP_
#define __NIST_STS_APPROXIMATE_ENTROPY_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts 
{

   /**
    * The focus of this test is the frequency of all possible overlapping 
    * m-bit patterns across the entire sequence.
    * 
    * The purpose of the test is to compare the frequency of overlapping 
    * blocks of two consecutive/adjacent lengths (m and m+1) against the 
    * expected result for a random sequence.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length in bytes.
    * @param block_length The length in bits of each block (m).
    * 
    * @return True if the p-value is 0.01 or greater, false otherwise.
    */
   bool
   approximate_entropy_test ( const uint8_t input [], size_t input_length, size_t block_length );

} // nist_sts

#endif // __NIST_STS_APPROXIMATE_ENTROPY_HPP_