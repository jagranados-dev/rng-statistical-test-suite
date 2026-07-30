/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_CUMULATIVE_SUMS_HPP_
#define __NIST_STS_CUMULATIVE_SUMS_HPP_

#include <cinttypes>
#include <cstddef>
#include <tuple>

namespace nist_sts
{

   /**
    * The focus of this test is the maximal excursion (from zero) of the random 
    * walk defined by the cumulative sum of adjusted (-1, +1) digits in the sequence.
    * 
    * The purpose of the test is to determine whether the cumulative sum of the 
    * partial sequences occurring in the tested sequence is too large or too small 
    * relative to the expected behavior of that cumulative sum for random sequences.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length in bytes.
    * 
    * @return A tuple containing two booleans representing if the forward 
    *         and backward p-values are 0.01 or greater, respectively.
    */
   std::tuple < bool, bool >
   cumulative_sums_test ( const uint8_t input [], size_t input_length );

} // nist_sts

#endif // __NIST_STS_CUMULATIVE_SUMS_HPP_