/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist_sts/overlapping_template.hpp>

#include <cmath>

#include "utilities.hpp"

namespace nist_sts
{

   bool
   overlapping_template_test ( const uint8_t               input [], 
                               size_t                      input_length, 
                               const std::vector < bool >& template_bits )
   {
      size_t total_bits = input_length * 8;
      size_t m = template_bits.size ();
      size_t M = 1032; 

      if ( m != 9 || total_bits < M ) return false;

      size_t num_blocks = total_bits / M;
      
      if ( num_blocks == 0 ) return false;

      const std::vector < double > pi = 
      { 
         0.364091, 0.185659, 0.139381, 0.100571, 0.070432, 0.139865 
      };
      
      const size_t K = 5;
      std::vector < size_t > freq ( K + 1, 0 );

      for ( size_t i = 0; i < num_blocks; i++ )
      {
         size_t start_bit = i * M;
         size_t W_j = 0;

         for ( size_t j = 0; j < M - m + 1; j++ )
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

            if ( match ) W_j++;
         }

         if ( W_j <= 4 )
         {
            freq [ W_j ]++;
         }
         else
         {
            freq [ K ]++;
         }
      }

      double chi_squared = 0.0;

      for ( size_t i = 0; i <= K; i++ )
      {
         double expected = (double) num_blocks * pi [ i ];
         double diff = (double) freq [ i ] - expected;
         chi_squared += ( diff * diff ) / expected;
      }

      double p_value = utilities::igamc ( K / 2.0, chi_squared / 2.0 );

      return p_value >= 0.01;
   }

} // nist_sts