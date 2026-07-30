/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <nist_sts/universal.hpp>

#include <cmath>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   namespace
   {

      /**
       * Extracts an L-bit pattern from the given bit offset.
       */
      size_t
      extract_pattern ( const uint8_t input [],
                        size_t        start_bit,
                        size_t        L )
      {
         size_t pattern = 0;
         for ( size_t i = 0; i < L; i++ )
         {
            pattern = ( pattern << 1 ) | utilities::get_bit ( input, start_bit + i );
         }
         return pattern;
      }

   } // namespace

   //------------------------------------------------------------------------------

   bool
   universal_test ( const uint8_t input [], size_t input_length )
   {
      size_t total_bits = input_length * 8;

      // Minimum sequence length recommended by NIST
      if ( total_bits < 387840 ) return false;

      // Determine block length (L) based on total sequence length
      size_t L = 6;
      if ( total_bits >= 1059061760 ) L = 16;
      else if ( total_bits >= 496435200 ) L = 15;
      else if ( total_bits >= 231669760 ) L = 14;
      else if ( total_bits >= 107560960 ) L = 13;
      else if ( total_bits >= 49643520 ) L = 12;
      else if ( total_bits >= 22753280 ) L = 11;
      else if ( total_bits >= 10342400 ) L = 10;
      else if ( total_bits >= 4654080 ) L = 9;
      else if ( total_bits >= 2068480 ) L = 8;
      else if ( total_bits >= 904960 ) L = 7;

      size_t Q = 10 * ( 1ULL << L ); // Initialization blocks
      size_t K = ( total_bits / L ) - Q; // Test blocks

      // Table for initialization
      std::vector < size_t > T ( 1ULL << L, 0 );

      // 1. Initialize table with the first Q blocks
      for ( size_t i = 1; i <= Q; i++ )
      {
         size_t pattern = extract_pattern ( input, ( i - 1 ) * L, L );
         T [ pattern ] = i;
      }

      // 2. Process the remaining K blocks
      double sum = 0.0;
      for ( size_t i = Q + 1; i <= Q + K; i++ )
      {
         size_t pattern = extract_pattern ( input, ( i - 1 ) * L, L );
         
         // Ignore blocks that haven't appeared during initialization (rare but safe)
         if ( T [ pattern ] != 0 ) 
         {
            sum += std::log2 ( (double) ( i - T [ pattern ] ) );
         }
         
         T [ pattern ] = i;
      }

      double fn = sum / (double) K;

      // NIST SP800-22 Expected values for L = 6 to 16
      const double expected_values [ 17 ] = 
      {
         0, 0, 0, 0, 0, 0,
         5.2177052, 6.1962507, 7.1836656, 8.1764248, 9.1723243,
         10.170032, 11.168765, 12.168070, 13.167693, 14.167488, 15.167379
      };
      
      const double variance_values [ 17 ] = 
      {
         0, 0, 0, 0, 0, 0,
         2.954, 3.125, 3.238, 3.311, 3.356,
         3.384, 3.401, 3.410, 3.416, 3.419, 3.421
      };

      double c = 0.7 - ( 0.8 / L ) + ( 4.0 + 32.0 / L ) * std::pow ( (double) K, -3.0 / L ) / 15.0;
      double sigma = c * std::sqrt ( variance_values [ L ] / K );
      
      double p_value = std::erfc ( std::abs ( fn - expected_values [ L ] ) / ( std::sqrt ( 2.0 ) * sigma ) );

      return p_value >= 0.01;
   }

} // nist_sts