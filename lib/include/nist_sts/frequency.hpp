/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#ifndef __NIST_STS_FREQUENCY_HPP_
#define __NIST_STS_FREQUENCY_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts
{

   /**
    * The purpose of this test is to determine whether the 
    * number of ones and zeros in a sequence are approximately 
    * the same as would be expected for a truly random sequence.
    * 
    * The test assesses the closeness of the fraction of ones
    * to ½, that is, the number of ones and zeroes in a sequence
    * should be about the same.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length.
    * 
    * @return True if the the p-value is 0.01 or greater.
    */
   bool
   frequency_test ( const uint8_t input [], size_t input_length );

   /**
    * The purpose of this test is to determine whether the 
    * frequency of ones in an M-bit block is approximately M/2, 
    * as would be expected under an assumption of randomness.
    *
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length.
    * @param block_length The block lenght (M).
    * 
    * The block size, if selected, should be selected such that 
    * M ≥ 20, M > (0.01 * the number of bits (n)) and number of 
    * blocks (N) < 100.
    *
    * @return True if the the p-value is 0.01 or greater.
    */
   bool
   frequency_test_within_a_block ( const uint8_t input [], 
                                   size_t        input_length, 
                                   size_t        block_length );

} // nist_sts

#endif // __NIST_STS_FREQUENCY_HPP_