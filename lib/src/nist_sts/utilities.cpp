/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include "utilities.hpp"

#include <bitset>
#include <cmath>
#include <limits>

namespace nist_sts::utilities
{

   namespace
   {

      double 
      log_gamma ( double x )
      {
         static const double coeffs [] = 
         {
            76.18009172947146,     -86.50532032941677,
            24.01409824083091,     -1.231739572450155,
            0.1208650973866179e-2, -0.5395239384953e-5
         };

         double y = x;
         double tmp = x + 5.5;
         tmp -= ( x + 0.5 ) * std::log ( tmp );
         double ser = 1.000000000190015;

         for ( int j = 0; j < 6; j++ )
         {
            ser += coeffs[j] / ++y;
         }

         return -tmp + std::log ( 2.5066282746310005 * ser / x );
      }

   } // namespace

   //------------------------------------------------------------------------------
   
   size_t
   count_ones ( const uint8_t input [], size_t input_length )
   {
      size_t count = 0;
      for ( size_t idx = 0; idx < input_length; idx++ )
      {
         count += std::bitset < 8 > ( input [ idx ] ).count ();
      }

      return count;
   }

   uint8_t
   get_bit ( const uint8_t input [], size_t bit_index )
   {
      size_t byte_index = bit_index / 8;
      size_t bit_offset = bit_index % 8;

      return ( input [ byte_index ] >> ( 7 - bit_offset ) ) & 0x01;
   }

   double
   igamc ( double a, double x )
   {
      if ( x < 0.0 || a <= 0.0 )
      {
         return std::numeric_limits < double >::quiet_NaN ();
      }

      if ( x == 0.0 ) return 1.0;

      if ( x < a + 1.0 )
      {
         // Series expansion
         double ap = a;
         double sum = 1.0 / a;
         double del = sum;

         for ( int n = 1; n <= 100; n++)
         {
            ++ap;
            del *= x / ap;
            sum += del;
            if ( std::fabs ( del ) < std::fabs ( sum ) * 1e-14 ) break;
         }

         return 1.0 - sum * std::exp ( -x + a * std::log ( x ) - log_gamma ( a ) );
      }
      else
      {
         // Continued fraction
         double b = x + 1.0 - a;
         double c = 1.0 / 1e-30;
         double d = 1.0 / b;
         double h = d;

         for ( int i = 1; i <= 100; i++ )
         {
            double an = -i * (i - a);
            b += 2.0;
            d = an * d + b;
            if ( std::fabs ( d ) < 1e-30 ) d = 1e-30;
            c = b + an / c;
            if ( std::fabs ( c ) < 1e-30 ) c = 1e-30;
            d = 1.0 / d;
            double delta = d * c;
            h *= delta;
            if ( std::fabs ( delta - 1.0 ) < 1e-14 ) break;
         }

         return std::exp ( -x + a * std::log ( x ) - log_gamma ( a ) ) * h;
      }
   }

} // nist_sts::utilities