/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_UTILITIES_HPP_
#define __NIST_STS_UTILITIES_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts::utilities
{

   /**
    * This function counts the number of bits set in a byte 
    * sequence.
    * 
    * @param input The byte sequence.
    * @param input_length The byte sequence length.
    * 
    * @return The number of bits set.
    */
   size_t
   count_ones ( const uint8_t input [], size_t input_length );

   /**
    * This function returns a bit from a sequence of bytes.
    * 
    * @param input The byte sequence
    * @param bit_index The index of the bit to return.
    * 
    * @return The representation of the bit (0, 1) as a byte.
    */
   uint8_t
   get_bit ( const uint8_t input [], size_t bit_index );

   /**
    * @brief Computes the complemented incomplete gamma function Q(a, x).
    *
    * This function evaluates the normalized upper incomplete gamma function:
    *     Q(a, x) = (1 / Γ(a)) * ∫_x^∞ t^(a-1) * e^(-t) dt
    *
    * It is used in statistics, probability theory, and numerical analysis, 
    * particularly in cumulative distribution functions (CDFs) of gamma 
    * and chi-squared distributions.
    *
    * @param a Shape parameter (a > 0).
    * @param x Upper limit of the integral (x >= 0).
    * @return The value of the complemented incomplete gamma function Q(a, x),
    *         which is equal to 1 - P(a, x), where P is the regularized lower 
    *         incomplete gamma function.
    */
   double
   igamc ( double a, double x );

} // nist_sts::utilities

#endif // __NIST_STS_UTILITIES_HPP_