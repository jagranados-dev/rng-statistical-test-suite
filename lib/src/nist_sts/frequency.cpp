/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <nist_sts/frequency.hpp>

#include <cmath>
#include <limits>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   bool
   frequency_test ( const uint8_t input [], size_t input_length )
   {
      // n >= 100
      size_t total_bits = input_length * 8;
      if ( total_bits < 100 ) return false;

      int64_t ones = utilities::count_ones ( input, input_length );
      int64_t zeros = total_bits - ones;

      size_t s_n = std::abs ( ones - zeros );
      double s_obs = s_n / std::sqrt ( (double) total_bits );
      double p_value = std::erfc ( s_obs / std::sqrt ( 2.0 ) );

      return p_value >= 0.01;
   }

   bool
   frequency_test_within_a_block ( const uint8_t input [], 
                                   size_t        input_length, 
                                   size_t        block_length )
   {
      // n >= 100
      size_t total_bits = input_length * 8;
      if ( total_bits < 100 ) return false;

      // M >= 20 & M > (0.01 * n)
      if ( block_length < 20 || block_length <= ( total_bits * 0.01 ) ) return false;

      // N < 100
      size_t num_blocks = std::floor ( (double) total_bits / block_length );
      if ( num_blocks >= 100 ) return false;

      double chi_squared = 0.0;
      for ( size_t block = 0; block < num_blocks; block++ )
      {
         size_t ones = 0;
         size_t start_bit = block * block_length;

         for ( size_t i = 0; i < block_length; i++ )
         {
            size_t bit_index = start_bit + i;
            size_t byte_index = bit_index / 8;
            size_t bit_pos = 7 - (bit_index % 8);
            bool bit = ( input [ byte_index ] >> bit_pos ) & 0x01;
            ones += bit;
         }

         double pi = (double) ones / block_length;
         chi_squared += ( pi - 0.5 ) * ( pi - 0.5 );
      }

      chi_squared *= 4.0 * block_length;

      double p_value = utilities::igamc ( (double) num_blocks / 2.0, chi_squared / 2.0 );
      return p_value >= 0.01;
   }

} // nist_sts