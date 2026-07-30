/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#include <nist_sts/binary_matrix_rank.hpp>

#include <cmath>
#include <vector>

#include "utilities.hpp"

namespace nist_sts
{

   namespace
   {

      /**
       * Computes the binary rank of a matrix using Gaussian elimination over GF(2).
       *
       * The matrix is assumed to be stored in a 1D vector in row-major order.
       *
       * @param matrix Flattened binary matrix (row-major), modified in-place during computation.
       * @param num_rows Number of rows (M) of the matrix.
       * @param num_columns Number of columns (Q) of the matrix.
       * @return Binary rank of the matrix.
       */
      size_t
      compute_rank ( std::vector < uint8_t >& matrix,
                     size_t                   num_rows, 
                     size_t                   num_columns )
      {
         size_t rank = 0;

         for ( size_t row = 0, col = 0; row < num_rows && col < num_columns; col++ )
         {
            size_t pivot = row;
            while ( pivot < num_rows && matrix [ pivot * num_columns + col ] == 0 ) pivot++;

            if ( pivot < num_rows )
            {
               if ( pivot != row )
               {
                  for ( size_t i = 0; i < num_columns; i++ )
                  {
                     std::swap ( matrix [ row * num_columns + i ], matrix [ pivot * num_columns + i ] );
                  }
               }

               for ( size_t i = row + 1; i < num_rows; i++ )
               {
                  if ( matrix [ i * num_columns + col ] )
                  {
                     for ( size_t j = col; j < num_columns; j++ )
                     {
                        matrix [ i * num_columns + j ] ^= matrix [ row * num_columns + j ];
                     }
                  }
               }

               rank++;
               row++;
            }
         }

         return rank;
      }

      /**
       * Fills a binary matrix from a given bit offset in the input bitstream.
       *
       * The matrix is stored in row-major order, and each bit is extracted 
       * from the input byte array.
       *
       * @param input Input bitstream as a byte array.
       * @param offset_bits Offset (in bits) from the beginning of the stream.
       * @param matrix Output vector that will be filled with matrix_size bits.
       * @param matrix_size Total number of bits (M * Q) to fill in the matrix.
       */
      void
      fill_matrix ( const uint8_t            input [],
                    size_t                   offset_bits,
                    std::vector < uint8_t >& matrix,
                    size_t                   matrix_size )
      {
         matrix = std::vector < uint8_t > ( matrix_size, 0x00 );

         for ( size_t bit = 0; bit < matrix_size; bit++ )
         {
            size_t global_bit_index = offset_bits + bit;
            size_t byte_index = global_bit_index / 8;
            size_t bit_offset = 7 - ( global_bit_index % 8 );
            matrix [ bit ] = ( input [ byte_index ] >> bit_offset ) & 0x01;
         }
      }

      /**
       * Calculates the theoretical probabilities for the three possible matrix 
       * rank cases.
       *
       * Probabilities are computed according to Appendix A of 
       * the NIST SP800-22rev1a specification:
       * - pi1: probability that the rank equals M
       * - pi2: probability that the rank equals M - 1
       * - pi3: probability that the rank is less than M - 1
       *
       * @param M Number of rows in the matrix.
       * @param Q Number of columns in the matrix.
       * @param pi1 Output probability for rank = M.
       * @param pi2 Output probability for rank = M - 1.
       * @param pi3 Output probability for rank < M - 1.
       */
      void
      calculate_probabilities ( size_t  M,
                                size_t  Q,
                                double& pi1,
                                double& pi2,
                                double& pi3 )
      {
         if ( M > Q )
         {
            pi1 = pi2 = 0.0;
            pi3 = 1.0;
            return;
         }

         pi1 = 1.0;
         for ( size_t i = 0; i < M; i++ )
         {
            pi1 *= ( 1.0 - ( 1.0 / std::pow ( 2.0, Q - i ) ) );
         }

         pi2 = 2.0 * pi1 * ( 1.0 - std::pow ( 2.0, M - Q ) );
         pi3 = 1.0 - pi1 - pi2;
      }

      /**
       * Computes the chi-squared statistic based on observed and expected 
       * rank frequencies.
       *
       * @param Fm Observed frequency of matrices with full rank (M).
       * @param Fm1 Observed frequency of matrices with rank = M - 1.
       * @param Fr Observed frequency of matrices with rank < M - 1.
       * @param pi1 Expected probability of rank = M.
       * @param pi2 Expected probability of rank = M - 1.
       * @param pi3 Expected probability of rank < M - 1.
       * @param num_matrixes Total number of matrices processed.
       * 
       * @return Computed chi-squared value.
       */
      double
      calculate_chi_squared ( double Fm,
                              double Fm1,
                              double Fr,
                              double pi1,
                              double pi2,
                              double pi3,
                              size_t num_matrixes )
      {
         double chi_squared = 0.0;
         
         const double expected_Fm  = num_matrixes * pi1;
         if ( expected_Fm > 1e-10 )
         {
            chi_squared += std::pow ( Fm - expected_Fm, 2 ) / expected_Fm;
         }
         
         const double expected_Fm1 = num_matrixes * pi2;
         if ( expected_Fm1 > 1e-10 )
         {
            chi_squared += std::pow ( Fm1 - expected_Fm1, 2 ) / expected_Fm1;
         }
         
         const double expected_Fr  = num_matrixes * pi3;
         if ( expected_Fr > 1e-10 )
         {
            chi_squared += std::pow ( Fr - expected_Fr, 2 ) / expected_Fr;
         }

         return chi_squared;
      }

   } // namespace

   //--------------------------------------------------------------

   bool
   binary_matrix_rank_test ( const uint8_t input [],
                             size_t input_length,
                             size_t num_rows,
                             size_t num_columns )
   {
      if ( num_rows < 32 || num_columns < 32 ) return false;

      const size_t total_bits = input_length * 8;
      const size_t matrix_size = num_rows * num_columns;

      if ( total_bits < 38 * matrix_size ) return false;

      const size_t num_matrixes = total_bits / matrix_size;
      int Fm = 0, Fm1 = 0, Fr = 0;

      std::vector < uint8_t > matrix;
      for ( size_t i = 0; i < num_matrixes; i++ )
      {
         fill_matrix ( input, i * matrix_size, matrix, matrix_size );
         size_t rank = compute_rank ( matrix, num_rows, num_columns );

         if ( rank == num_rows ) Fm++;
         else if ( rank == num_rows - 1 ) Fm1++;
         else Fr++;
      }

      double pi1, pi2, pi3;
      calculate_probabilities ( num_rows, num_columns, pi1, pi2, pi3 );
      
      double chi_squared = calculate_chi_squared ( Fm, Fm1, Fr, pi1, pi2, pi3, num_matrixes );
      double p_value = utilities::igamc ( 1.0, chi_squared / 2.0 );

      return p_value >= 0.01;
   }

} // nist_sts