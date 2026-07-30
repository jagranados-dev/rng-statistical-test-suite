/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <nist_sts/serial.hpp>

#include <cmath>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   namespace
   {

      /**
       * Computes the Psi Square statistic for a given block length m.
       *
       * @param input      The bit sequence as a byte array.
       * @param total_bits Total number of bits in the sequence.
       * @param m          The block length.
       * 
       * @return The computed Psi Square value.
       */
      double
      compute_psi_square ( const uint8_t input [], size_t total_bits, size_t m )
      {
         if ( m == 0 ) return 0.0;

         const size_t num_patterns = 1ULL << m;
         std::vector < size_t > frequency ( num_patterns, 0 );

         for ( size_t i = 0; i < total_bits; i++ )
         {
            size_t pattern = 0;
            for ( size_t j = 0; j < m; j++ )
            {
               // Note: The NIST specification requires the sequence to be 
               // logically circular (wrapped around) for this test.
               size_t bit_index = ( i + j ) % total_bits;
               pattern = ( pattern << 1 ) | utilities::get_bit ( input, bit_index );
            }
            frequency [ pattern ]++;
         }

         double sum = 0.0;
         for ( size_t i = 0; i < num_patterns; i++ )
         {
            sum += (double) frequency [ i ] * frequency [ i ];
         }

         return ( (double) num_patterns / total_bits ) * sum - total_bits;
      }

   } // namespace

   //------------------------------------------------------------------------------

   std::tuple < bool, bool >
   serial_test ( const uint8_t input [], size_t input_length, size_t block_length )
   {
      size_t total_bits = input_length * 8;
      
      // Ensure the sequence is long enough to support the block length
      if ( block_length == 0 || total_bits < block_length )
      {
         return { false, false };
      }

      double psi_m = compute_psi_square ( input, total_bits, block_length );
      double psi_m_minus_1 = compute_psi_square ( input, total_bits, block_length - 1 );
      double psi_m_minus_2 = compute_psi_square ( input, total_bits, block_length - 2 );

      double delta1 = psi_m - psi_m_minus_1;
      double delta2 = psi_m - ( 2.0 * psi_m_minus_1 ) + psi_m_minus_2;

      double p_value1 = utilities::igamc ( std::pow ( 2.0, block_length - 2 ), delta1 / 2.0 );
      double p_value2 = utilities::igamc ( std::pow ( 2.0, block_length - 3 ), delta2 / 2.0 );

      return { p_value1 >= 0.01, p_value2 >= 0.01 };
   }

} // nist_sts