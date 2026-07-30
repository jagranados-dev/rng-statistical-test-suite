/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_UNIVERSAL_HPP_
#define __NIST_STS_UNIVERSAL_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts
{

   /**
    * The focus of this test is the number of bits between matching patterns 
    * (a measure that is related to the length of a compressed sequence).
    * 
    * The purpose of the test is to detect whether or not the sequence can be 
    * significantly compressed without loss of information. A significantly 
    * compressible sequence is considered to be non-random.
    * 
    * Note: The sequence length MUST be at least 387,840 bits to conform 
    * to NIST standards for valid initialization and block size derivation.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length in bytes.
    * 
    * @return True if the p-value is 0.01 or greater, false otherwise.
    */
   bool
   universal_test ( const uint8_t input [], size_t input_length );

} // nist_sts

#endif // __NIST_STS_UNIVERSAL_HPP_