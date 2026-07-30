/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_DISCRETE_FOURIER_TRANSFORM_HPP_
#define __NIST_STS_DISCRETE_FOURIER_TRANSFORM_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts
{

   /**
    * The focus of this test is the peak heights in the Discrete 
    * Fourier Transform of the sequence.
    * 
    * The purpose of this test is to detect periodic features (i.e.,
    * repetitive patterns that are near each other) in the tested 
    * sequence that would indicate a deviation from the assumption
    * of randomness.
    * 
    * The intention is to detect whether the number of peaks exceeding
    * the 95 % threshold is significantly different than 5 %. 
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length.
    * 
    * @return True if the the p-value is 0.01 or greater.
    */
   bool
   discrete_fourier_transform_test ( const uint8_t input [], size_t input_length );

} // nist_sts

#endif // __NIST_STS_DISCRETE_FOURIER_TRANSFORM_HPP_