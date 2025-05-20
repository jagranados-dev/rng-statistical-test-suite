/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests/template_matching.hpp>

#include <cmath>
#include <stdexcept>
#include <vector>

#include <nist/statistical/tests/utilities.hpp>

namespace nist {
namespace statistical {
namespace tests {

   bool
   non_overlapping_template_maching_test ( const uint8_t input [],
                                           size_t input_length,
                                           const std::string& template_pattern,
                                           size_t block_length )
   {
      // n
      const size_t total_bits = input_length * 8;
      // m
      const size_t template_pattern_length = template_pattern.size ();

      // m >= 9
      if ( template_pattern_length < 9 ) return false;
      // M >= m
      if ( block_length < template_pattern_length ) return false;
      // M > 0.01 * n
      if ( block_length <= ( 0.01 * total_bits ) ) return false;
      // N = n / M
      if ( total_bits % block_length ) return false;

      // N <= 100
      const size_t num_blocks = total_bits / block_length;
      if ( num_blocks > 100 ) return false;

      // B
      uint64_t template_bits = 0;
      for ( auto& bit : template_pattern )
      {
         template_bits = ( template_bits << 1 ) | ( bit == '1' ? 0x01 : 0x00 );
      }

      // W
      std::vector < uint64_t > matches ( num_blocks, 0 );
      for ( size_t block = 0; block < num_blocks; block++ )
      {
         size_t count = 0;
         size_t block_start = block * block_length;
         for ( size_t i = 0; i < block_length - template_pattern_length; ) // fix this
         {
            uint64_t window = 0;
            for ( int j = 0; j < template_pattern_length; j++ )
            {
                window = ( window << 1 ) | utilities::get_bit ( input, block_start + i + j );
            }

            if ( window == template_bits )
            {
               count++;
               i += template_pattern_length;
            }
            else
            {
               i++;
            }
         }

         matches [ block ] = count;
      }

      double lambda = ( block_length - template_pattern_length + 1) / std::pow ( 2.0, template_pattern_length );
      double variance_p1 =  1.0 / std::pow ( 2.0, template_pattern_length );
      double variance_p2 = ( 2.0 * template_pattern_length - 1.0 ) / std::pow ( 2.0, 2 * template_pattern_length );
      double variance = block_length * ( variance_p1 - variance_p2 );

      double chi_squared = 0.0;
      for ( size_t j = 0; j < num_blocks; j++ )
      {
         chi_squared += std::pow ( matches [ j ] - lambda, 2 ) / variance;
      }

      double p_value = utilities::igamc ( num_blocks / 2.0, chi_squared / 2.0 );
      return p_value >= 0.01;
   }

   bool
   overlapping_template_maching_test ( const uint8_t input [], size_t input_length )
   {
      throw std::runtime_error ( "Not implemented" );
   }

} // tests
} // statistical
} // nist