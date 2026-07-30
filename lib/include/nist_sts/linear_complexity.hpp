/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_LINEAR_COMPLEXITY_HPP_
#define __NIST_STS_LINEAR_COMPLEXITY_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts
{

   /**
    * The focus of this test is the length of a linear feedback shift register 
    * (LFSR).
    * 
    * The purpose of this test is to determine whether or not the sequence is 
    * complex enough to be considered random. Random sequences are characterized 
    * by longer LFSRs. 
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length in bytes.
    * @param block_length The length of each block (M). NIST recommends 500 <= M <= 5000.
    * 
    * @return True if the p-value is 0.01 or greater, false otherwise.
    */
   bool
   linear_complexity_test ( const uint8_t input [], size_t input_length, size_t block_length = 500 );

} // nist_sts

#endif // __NIST_STS_LINEAR_COMPLEXITY_HPP_