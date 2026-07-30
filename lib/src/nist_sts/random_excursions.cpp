/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <nist_sts/random_excursions.hpp>

#include <cmath>
#include <map>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   namespace
   {

      /**
       * Generates the cycle counts from a cumulative sum random walk.
       * 
       * @param input      The bit sequence as a byte array.
       * @param total_bits Total number of bits in the sequence.
       * @return A vector of maps, where each map contains the state occurrences for a single cycle.
       */
      std::vector < std::map < int, int > >
      build_cycles ( const uint8_t input [], size_t total_bits )
      {
         std::vector < std::map < int, int > > cycles;
         std::map < int, int > current_cycle;
         
         int S = 0;
         for ( size_t i = 0; i < total_bits; i++ )
         {
            S += ( utilities::get_bit ( input, i ) ? 1 : -1 );
            
            if ( S == 0 )
            {
               cycles.push_back ( current_cycle );
               current_cycle.clear ();
            }
            else
            {
               current_cycle [ S ]++;
            }
         }

         // As per NIST, append a final zero crossing if the walk didn't end at 0
         if ( S != 0 )
         {
            cycles.push_back ( current_cycle );
         }

         return cycles;
      }

   } // namespace

   //------------------------------------------------------------------------------

   bool
   random_excursions_test ( const uint8_t input [], size_t input_length )
   {
      size_t total_bits = input_length * 8;
      if ( total_bits < 1000000 ) return false;

      auto cycles = build_cycles ( input, total_bits );
      size_t J = cycles.size ();

      if ( J < 500 ) return false;

      const int states [] = { -4, -3, -2, -1, 1, 2, 3, 4 };
      
      const double pi [ 4 ][ 6 ] = 
      {
         { 0.5000, 0.2500, 0.1250, 0.0625, 0.0312, 0.0312 }, // |x| = 1
         { 0.7500, 0.0625, 0.0469, 0.0352, 0.0264, 0.0791 }, // |x| = 2
         { 0.8333, 0.0278, 0.0231, 0.0193, 0.0161, 0.0804 }, // |x| = 3
         { 0.8750, 0.0156, 0.0137, 0.0120, 0.0105, 0.0732 }  // |x| = 4
      };

      for ( int x : states )
      {
         int abs_x = std::abs ( x );
         int pi_idx = abs_x - 1;
         
         std::vector < int > v ( 6, 0 );

         for ( const auto& cycle : cycles )
         {
            int count = 0;
            auto it = cycle.find ( x );
            if ( it != cycle.end () ) count = it->second;
            
            if ( count > 5 ) count = 5;
            v [ count ]++;
         }

         double chi_squared = 0.0;
         for ( int k = 0; k < 6; k++ )
         {
            double expected = (double) J * pi [ pi_idx ][ k ];
            double diff = (double) v [ k ] - expected;
            chi_squared += ( diff * diff ) / expected;
         }

         double p_value = utilities::igamc ( 5.0 / 2.0, chi_squared / 2.0 );
         
         if ( p_value < 0.01 ) return false;
      }

      return true;
   }

   //------------------------------------------------------------------------------

   bool
   random_excursions_variant_test ( const uint8_t input [], size_t input_length )
   {
      size_t total_bits = input_length * 8;
      if ( total_bits < 1000000 ) return false;

      auto cycles = build_cycles ( input, total_bits );
      size_t J = cycles.size ();

      if ( J < 500 ) return false;

      const int states [] = 
      { 
         -9, -8, -7, -6, -5, -4, -3, -2, -1, 
          1,  2,  3,  4,  5,  6,  7,  8,  9 
      };

      for ( int x : states )
      {
         int total_visits = 0;
         for ( const auto& cycle : cycles )
         {
            auto it = cycle.find ( x );
            if ( it != cycle.end () ) total_visits += it->second;
         }

         double numerator = std::abs ( (double) total_visits - J );
         double denominator = std::sqrt ( 2.0 * J * ( 4.0 * std::abs ( x ) - 2.0 ) );
         double p_value = std::erfc ( numerator / denominator );

         if ( p_value < 0.01 ) return false;
      }

      return true;
   }

} // nist_sts