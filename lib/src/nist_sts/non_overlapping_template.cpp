/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist_sts/non_overlapping_template.hpp>

#include <cmath>

#include "utilities.hpp"

namespace nist_sts
{

   bool
   non_overlapping_template_test ( const uint8_t               input [], 
                                   size_t                      input_length, 
                                   const std::vector < bool >& template_bits,
                                   size_t                      num_blocks )
   {
      size_t total_bits = input_length * 8;
      size_t m = template_bits.size ();

      if ( num_blocks == 0 || m == 0 || total_bits < num_blocks * m ) return false;

      size_t M = total_bits / num_blocks; 

      double mu = (double) ( M - m + 1 ) / std::pow ( 2.0, m );
      double variance = M * ( ( 1.0 / std::pow ( 2.0, m ) ) - ( ( 2.0 * m - 1.0 ) / std::pow ( 2.0, 2.0 * m ) ) );

      if ( variance <= 0.0 ) return false;

      double chi_squared = 0.0;

      for ( size_t i = 0; i < num_blocks; i++ )
      {
         size_t start_bit = i * M;
         size_t W_j = 0;
         size_t j = 0;

         while ( j < M - m + 1 )
         {
            bool match = true;
            for ( size_t k = 0; k < m; k++ )
            {
               if ( utilities::get_bit ( input, start_bit + j + k ) != template_bits [ k ] )
               {
                  match = false;
                  break;
               }
            }

            if ( match )
            {
               W_j++;
               j += m; // Skip the length of the template (non-overlapping)
            }
            else
            {
               j++;
            }
         }

         chi_squared += std::pow ( (double) W_j - mu, 2.0 ) / variance;
      }

      double p_value = utilities::igamc ( (double) num_blocks / 2.0, chi_squared / 2.0 );

      return p_value >= 0.01;
   }

} // nist_sts