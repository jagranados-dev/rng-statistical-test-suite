/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist_sts/runs.hpp>

#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   bool
   runs_test ( const uint8_t input [], size_t input_length )
   {
      // n >= 100
      size_t total_bits = input_length * 8;
      if ( total_bits < 100 ) return false;

      int64_t ones = utilities::count_ones ( input, input_length );
      double pi = (double) ones / total_bits;
      double threshold = 2.0 / std::sqrt ( total_bits );

      // check runs precondition
      if ( std::abs ( pi - 0.5 ) >= threshold ) return false;

      size_t Vn = 1;
      for ( size_t idx = 1; idx < total_bits; idx++ )
      {
         if ( utilities::get_bit ( input, idx ) != utilities::get_bit ( input, idx - 1 ) ) Vn++;
      }

      double numerator = std::abs ( Vn - ( 2 * total_bits * pi * ( 1.0 - pi ) ) );
      double denominator = 2.0 * ( std::sqrt ( 2.0 * total_bits ) * pi * ( 1.0 - pi ) );
      double p_value = std::erfc ( numerator / denominator );

      return p_value >= 0.01;
   }

   //------------------------------------------------------------------------------

   bool
   longest_run_of_ones_test ( const uint8_t input [], size_t input_length )
   {
      // n >= 100
      size_t total_bits = input_length * 8;
      if ( total_bits < 128 ) return false;

      struct Parameters
      {
         size_t M;
         size_t K;
         std::vector < int > V;
         std::vector < double > pi;
      };

      Parameters params;
      if ( total_bits < 6272 ) 
      {
         if ( total_bits % 8 != 0) return false;
         params.M = 8;
         params.K = 3;
         params.V = { 1, 2, 3, 4 };
         params.pi = {0.2148, 0.3672, 0.2305, 0.1875 };
      } 
      else if ( total_bits < 750000 ) 
      {
         if ( total_bits % 128 != 0) return false;
         params.M = 128;
         params.K = 5;
         params.V = { 4, 5, 6, 7, 8, 9 };
         params.pi = { 0.1174, 0.2430, 0.2493, 0.1752, 0.1027, 0.1124 };
      } 
      else 
      {
         if ( total_bits % 10000 != 0) return false;
         params.M = 10000;
         params.K = 6;
         params.V = { 10, 11, 12, 13, 14, 15, 16 };
         params.pi = { 0.0882, 0.2092, 0.2483, 0.1933, 0.1208, 0.0675, 0.0727 };
      }

      const size_t num_blocks = total_bits / params.M;
      std::vector < int > freq ( params.K + 1, 0 );

      for ( size_t i = 0; i < num_blocks; i++ )
      {
         int max_run = 0, run = 0;
         for ( size_t j = 0; j < params.M; j++ )
         {
            if ( utilities::get_bit ( input, i * params.M + j ) )
            {
               run++;
               if ( run > max_run ) max_run = run;
            }
            else
            {
               run = 0;
            }
         }

         int category = 0;
         while ( ( category < (int) params.K ) && ( max_run > params.V [ category ] ) )
         {
            category++;
         }

         ++freq [ category ];
      }

      double chi_squared = 0.0;
      for ( size_t i = 0; i <= params.K; i++ )
      {
         double expected = num_blocks * params.pi [ i ];
         double diff = freq [ i ] - expected;
         chi_squared += ( diff * diff ) / expected;
      }

      double p_value = utilities::igamc ( params.K / 2.0, chi_squared / 2.0 );
      return p_value >= 0.01;
   }

} // nist_sts