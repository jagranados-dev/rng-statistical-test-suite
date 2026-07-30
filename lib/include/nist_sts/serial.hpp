/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_SERIAL_HPP_
#define __NIST_STS_SERIAL_HPP_

#include <cinttypes>
#include <cstddef>
#include <tuple>

namespace nist_sts
{

   /**
    * The focus of this test is the frequency of all possible overlapping 
    * m-bit patterns across the entire sequence.
    * 
    * The purpose of this test is to determine whether the number of occurrences 
    * of the 2^m m-bit overlapping patterns is approximately the same as would 
    * be expected for a random sequence. Random sequences have uniformity; that 
    * is, every m-bit pattern has the same chance of appearing as every other 
    * m-bit pattern.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length in bytes.
    * @param block_length The length in bits of each block (m).
    * 
    * @return A tuple containing two booleans representing if p_value1 and 
    *         p_value2 are 0.01 or greater, respectively.
    */
   std::tuple < bool, bool >
   serial_test ( const uint8_t input [], size_t input_length, size_t block_length );

} // nist_sts

#endif // __NIST_STS_SERIAL_HPP_