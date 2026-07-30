/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist_sts/linear_complexity.hpp>

#include <cmath>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   namespace
   {

      /**
       * Berlekamp-Massey algorithm to compute the linear complexity of a binary sequence.
       * 
       * @param s The sequence of bits.
       * @return The length of the shortest linear feedback shift register (LFSR).
       */
      size_t
      berlekamp_massey ( const std::vector < uint8_t >& s )
      {
         size_t n = s.size ();
         std::vector < uint8_t > b ( n, 0 );
         std::vector < uint8_t > c ( n, 0 );
         std::vector < uint8_t > t ( n, 0 );

         b [ 0 ] = 1;
         c [ 0 ] = 1;

         size_t l = 0;
         int m = -1;

         for ( int i = 0; i < (int) n; i++ )
         {
            uint8_t d = 0;
            for ( size_t j = 0; j <= l; j++ )
            {
               d ^= ( c [ j ] & s [ i - j ] );
            }

            if ( d == 1 )
            {
               t = c;
               int shift = i - m;
               for ( size_t j = 0; j < n - shift; j++ )
               {
                  c [ j + shift ] ^= b [ j ];
               }
               if ( l <= (size_t) i / 2 )
               {
                  l = i + 1 - l;
                  m = i;
                  b = t;
               }
            }
         }
         return l;
      }

   } // namespace

   //------------------------------------------------------------------------------

   bool
   linear_complexity_test ( const uint8_t input [], size_t input_length, size_t block_length )
   {
      size_t total_bits = input_length * 8;
      size_t M = block_length;

      // NIST requires n >= 1,000,000 and 500 <= M <= 5000
      if ( total_bits < 1000000 || M < 500 || M > 5000 ) return false;

      size_t N = total_bits / M;
      if ( N == 0 ) return false;

      const std::vector < double > pi = 
      { 
         0.010417, 0.03125, 0.125, 0.5, 0.25, 0.0625, 0.020833 
      };
      
      std::vector < size_t > v ( 7, 0 );

      // Theoretical mean
      double mu = M / 2.0 + ( 9.0 + ( M % 2 == 0 ? -1.0 : 1.0 ) ) / 36.0 - ( M / 3.0 + 2.0 / 9.0 ) / std::pow ( 2.0, M );

      std::vector < uint8_t > block ( M, 0 );
      
      for ( size_t i = 0; i < N; i++ )
      {
         for ( size_t j = 0; j < M; j++ )
         {
            block [ j ] = utilities::get_bit ( input, ( i * M ) + j );
         }

         size_t L_i = berlekamp_massey ( block );
         
         double T = std::pow ( -1.0, M ) * ( (double) L_i - mu ) + 2.0 / 9.0;

         // Bucket assignment based on T value (Degrees of freedom K = 6)
         if ( T <= -2.5 ) v [ 0 ]++;
         else if ( T <= -1.5 ) v [ 1 ]++;
         else if ( T <= -0.5 ) v [ 2 ]++;
         else if ( T <= 0.5 ) v [ 3 ]++;
         else if ( T <= 1.5 ) v [ 4 ]++;
         else if ( T <= 2.5 ) v [ 5 ]++;
         else v [ 6 ]++;
      }

      double chi_squared = 0.0;
      for ( size_t i = 0; i < 7; i++ )
      {
         double expected = (double) N * pi [ i ];
         double diff = (double) v [ i ] - expected;
         chi_squared += ( diff * diff ) / expected;
      }

      // K = 6, so degrees of freedom divided by 2 is 3.0
      double p_value = utilities::igamc ( 3.0, chi_squared / 2.0 );
      
      return p_value >= 0.01;
   }

} // nist_sts