/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <nist_sts/approximate_entropy.hpp>

#include <cmath>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   namespace
   {

      /**
       * Computes the phi statistic for a given block length m.
       *
       * @param input      The bit sequence as a byte array.
       * @param total_bits Total number of bits in the sequence.
       * @param m          The block length.
       * 
       * @return The computed phi value.
       */
      double
      compute_phi ( const uint8_t input [], size_t total_bits, size_t m )
      {
         if ( m == 0 ) return 0.0;

         const size_t num_patterns = 1ULL << m;
         std::vector < size_t > frequency ( num_patterns, 0 );

         for ( size_t i = 0; i < total_bits; i++ )
         {
            size_t pattern = 0;
            for ( size_t j = 0; j < m; j++ )
            {
               // Note: Sequence is treated as circular
               size_t bit_index = ( i + j ) % total_bits;
               pattern = ( pattern << 1 ) | utilities::get_bit ( input, bit_index );
            }
            frequency [ pattern ]++;
         }

         double phi = 0.0;
         for ( size_t i = 0; i < num_patterns; i++ )
         {
            if ( frequency [ i ] > 0 )
            {
               double pi = (double) frequency [ i ] / total_bits;
               phi += pi * std::log ( pi );
            }
         }

         return phi;
      }

   } // namespace

   //------------------------------------------------------------------------------

   bool
   approximate_entropy_test ( const uint8_t input [], size_t input_length, size_t block_length )
   {
      size_t total_bits = input_length * 8;
      
      if ( block_length == 0 || total_bits < block_length )
      {
         return false;
      }

      double phi_m = compute_phi ( input, total_bits, block_length );
      double phi_m_plus_1 = compute_phi ( input, total_bits, block_length + 1 );

      double ap_en = phi_m - phi_m_plus_1;
      
      // Compute Chi-Squared statistic
      double chi_squared = 2.0 * total_bits * ( std::log ( 2.0 ) - ap_en );

      // P-value using the Incomplete Gamma function
      double p_value = utilities::igamc ( std::pow ( 2.0, block_length - 1 ), chi_squared / 2.0 );

      return p_value >= 0.01;
   }

} // nist_sts