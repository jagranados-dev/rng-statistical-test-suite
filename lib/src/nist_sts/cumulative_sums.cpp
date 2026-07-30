/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <nist_sts/cumulative_sums.hpp>

#include <algorithm>
#include <cmath>

#include "utilities.hpp"

namespace nist_sts
{

   namespace
   {

      /**
       * Computes the standard normal cumulative distribution function (CDF).
       * 
       * @param x The value to evaluate.
       * @return The standard normal CDF of x.
       */
      double 
      normal_cdf ( double x )
      {
         return 0.5 * std::erfc ( -x / std::sqrt ( 2.0 ) );
      }

      /**
       * Computes the p-value for the Cumulative Sums test given a max excursion.
       * 
       * @param z The maximum absolute cumulative sum.
       * @param n The total number of bits.
       * @return The calculated p-value.
       */
      double
      compute_cusum_p_value ( size_t z, size_t n )
      {
         if ( z == 0 ) return 0.0;

         double p_value = 1.0;
         double sqrt_n = std::sqrt ( (double) n );

         // First summation term
         int k_start1 = std::floor ( ( -(double) n / z + 1.0 ) / 4.0 );
         int k_end1   = std::floor ( (  (double) n / z - 1.0 ) / 4.0 );
         for ( int k = k_start1; k <= k_end1; k++ )
         {
            double arg1 = ( 4.0 * k + 1.0 ) * z / sqrt_n;
            double arg2 = ( 4.0 * k - 1.0 ) * z / sqrt_n;
            p_value -= ( normal_cdf ( arg1 ) - normal_cdf ( arg2 ) );
         }

         // Second summation term
         int k_start2 = std::floor ( ( -(double) n / z - 3.0 ) / 4.0 );
         int k_end2   = std::floor ( (  (double) n / z - 1.0 ) / 4.0 );
         for ( int k = k_start2; k <= k_end2; k++ )
         {
            double arg1 = ( 4.0 * k + 3.0 ) * z / sqrt_n;
            double arg2 = ( 4.0 * k + 1.0 ) * z / sqrt_n;
            p_value += ( normal_cdf ( arg1 ) - normal_cdf ( arg2 ) );
         }

         return p_value;
      }

   } // namespace

   //------------------------------------------------------------------------------

   std::tuple < bool, bool >
   cumulative_sums_test ( const uint8_t input [], size_t input_length )
   {
      size_t total_bits = input_length * 8;
      
      // Minimum recommended sequence length is 100
      if ( total_bits < 100 )
      {
         return { false, false };
      }

      // Forward Random Walk
      int S_fwd = 0;
      size_t z_fwd = 0;
      for ( size_t i = 0; i < total_bits; i++ )
      {
         S_fwd += ( utilities::get_bit ( input, i ) ? 1 : -1 );
         z_fwd = std::max ( z_fwd, (size_t) std::abs ( S_fwd ) );
      }

      // Backward Random Walk
      int S_bwd = 0;
      size_t z_bwd = 0;
      for ( int i = total_bits - 1; i >= 0; i-- )
      {
         S_bwd += ( utilities::get_bit ( input, i ) ? 1 : -1 );
         z_bwd = std::max ( z_bwd, (size_t) std::abs ( S_bwd ) );
      }

      double p_value_fwd = compute_cusum_p_value ( z_fwd, total_bits );
      double p_value_bwd = compute_cusum_p_value ( z_bwd, total_bits );

      return { p_value_fwd >= 0.01, p_value_bwd >= 0.01 };
   }

} // nist_sts