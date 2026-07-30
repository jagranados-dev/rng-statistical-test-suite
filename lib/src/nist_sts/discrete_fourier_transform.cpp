/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <nist_sts/discrete_fourier_transform.hpp>

#include <algorithm>
#include <complex>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   namespace
   {

      /**
       * Computes the Fast Fourier Transform (FFT) of a complex vector
       * using the iterative Cooley-Tukey Radix-2 algorithm.
       *
       * @param x A vector of complex numbers, modified in-place.
       *          Its size MUST be a power of 2.
       */
      void
      fft ( std::vector < std::complex < double > >& x )
      {
         const size_t N = x.size ();
         if ( N <= 1 ) return;

         // Bit-reversal permutation
         for ( size_t i = 1, j = 0; i < N; i++ )
         {
            size_t bit = N >> 1;
            for ( ; j & bit; bit >>= 1 ) j ^= bit;
            j ^= bit;
            if ( i < j ) std::swap ( x [ i ], x [ j ] );
         }

         // Cooley-Tukey decimation-in-time
         const double PI = std::acos ( -1.0 );
         for ( size_t len = 2; len <= N; len <<= 1 )
         {
            double angle = -2.0 * PI / len;
            std::complex < double > wlen ( std::cos ( angle ), std::sin ( angle ) );
            for ( size_t i = 0; i < N; i += len )
            {
               std::complex < double > w ( 1.0, 0.0 );
               for ( size_t j = 0; j < len / 2; j++ )
               {
                  std::complex < double > u = x [ i + j ];
                  std::complex < double > v = x [ i + j + len / 2 ] * w;
                  x [ i + j ] = u + v;
                  x [ i + j + len / 2 ] = u - v;
                  w *= wlen;
               }
            }
         }
      }

   } // namespace

   //-----------------------------------------------------------------------------

   bool
   discrete_fourier_transform_test ( const uint8_t input [], size_t input_length )
   {
      // n >= 1000
      size_t total_bits = input_length * 8;
      if ( total_bits < 1000 ) return false;
      
      // Calculate the largest power of 2 less than or equal to total_bits
      size_t n = 1;
      while ( ( n << 1 ) <= total_bits ) n <<= 1;
      
      std::vector < std::complex < double > > X ( n, { 0.0, 0.0 } );
      for ( size_t i = 0; i < n; i++ )
      {
         X [ i ].real ( ( 2.0 * utilities::get_bit ( input, i ) ) - 1.0 );
      }
      
      // Compute FFT in-place
      fft ( X );
      
      size_t half_bits = n / 2;
      std::vector < double > M ( half_bits, 0.0 );
      for ( size_t i = 0; i < half_bits; i++ )
      {
         M [ i ] = std::abs ( X [ i ] );
      }

      double T = std::sqrt ( std::log ( 1.0 / 0.05 ) * n );

      double N0 = 0.95 * half_bits;

      size_t N1 = std::count_if ( M.begin (), M.end (),
         [ T ] ( double mag ) { return mag < T; } );

      double d = ( N1 - N0 ) / std::sqrt ( n * 0.95 * 0.05 / 4.0 );

      double p_value = std::erfc ( std::abs ( d ) / std::sqrt ( 2.0 ) );
      return p_value >= 0.01;
   }

} // nist_sts