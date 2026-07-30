/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_RANDOM_EXCURSIONS_HPP_
#define __NIST_STS_RANDOM_EXCURSIONS_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts
{

   /**
    * The focus of this test is the number of cycles having exactly K visits 
    * in a cumulative sum random walk. 
    * 
    * The purpose of this test is to determine if the number of visits to a 
    * particular state within a cycle deviates from what one would expect for 
    * a random sequence.
    * 
    * Note: The sequence length MUST be at least 1,000,000 bits. If the number 
    * of cycles J < 500, the test cannot be executed reliably and will return false.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length in bytes.
    * 
    * @return True if all computed p-values (for states -4 to 4) are >= 0.01.
    */
   bool
   random_excursions_test ( const uint8_t input [], size_t input_length );

   /**
    * The focus of this test is the total number of times that a particular 
    * state is visited (i.e., occurs) in a cumulative sum random walk.
    * 
    * The purpose of this test is to detect deviations from the expected number 
    * of visits to various states in the random walk.
    * 
    * Note: The sequence length MUST be at least 1,000,000 bits. If the number 
    * of cycles J < 500, the test cannot be executed reliably and will return false.
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length in bytes.
    * 
    * @return True if all computed p-values (for states -9 to 9) are >= 0.01.
    */
   bool
   random_excursions_variant_test ( const uint8_t input [], size_t input_length );

} // nist_sts

#endif // __NIST_STS_RANDOM_EXCURSIONS_HPP_