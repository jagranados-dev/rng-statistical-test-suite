/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_RUNS_HPP_
#define __NIST_STS_RUNS_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts
{

   /**
    * The focus of this test is the total number of runs in
    * the sequence, where a run is an uninterrupted sequence
    * of identical bits. A run of length k consists of exactly
    * k identical bits and is bounded before and after with
    * a bit of the opposite value.
    * 
    * The purpose of the runs test is to determine whether the 
    * number of runs of ones and zeros of various lengths is as 
    * expected for a random sequence.
    * 
    * In particular, this test determines whether the oscillation
    * between such zeros and ones is too fast or too slow.
    *
    * @param input         The random sequence to be tested.
    * @param input_length  The random sequence length.
    *
    * @return True if the the p-value is 0.01 or greater.
    */
   bool
   runs_test ( const uint8_t input [], size_t input_length );

   /**
    * The focus of the test is the longest run of ones within 
    * M-bit blocks.
    * 
    * The purpose of this test is to determine whether the length
    * of the longest run of ones within the tested sequence is 
    * consistent with the length of the longest run of ones that 
    * would be expected in a random sequence.
    * 
    * Note that an irregularity in the expected length of the 
    * longest run of ones implies that there is also an irregularity 
    * in the expected length of the longest run of zeroes. Therefore,
    * only a test for ones is necessary
    *
    * @param input         The random sequence to be tested.
    * @param input_length  The random sequence length.
    *
    * @return True if the the p-value is 0.01 or greater.
    */
   bool
   longest_run_of_ones_test ( const uint8_t input [], size_t input_length );

} // nist_sts

#endif // __NIST_STS_RUNS_HPP_