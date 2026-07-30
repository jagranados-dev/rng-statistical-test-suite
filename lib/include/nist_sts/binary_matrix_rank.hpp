/*********************************************************************************
 * MIT License
 * Copyright (c) 2026 Jose Alberto Granados
 *********************************************************************************/

#ifndef __NIST_STS_BINARY_MATRIX_RANK_HPP_
#define __NIST_STS_BINARY_MATRIX_RANK_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist_sts
{

   /**
    * The focus of the test is the rank of disjoint sub-matrices 
    * of the entire sequence.
    * 
    * The purpose of this test is to check
    * for linear dependence among fixed length substrings of the
    * original sequence. Note that this test also appears in the 
    * DIEHARD battery of tests. 
    * 
    * The minimum number of bits to be tested must be such that 
    * n ≥ 38MQ (i.e., at least 38 matrices are created). For 
    * M = Q = 32, each sequence to be tested should consist
    * of a minimum of 38,912 bits. 
    * 
    * @param input        The random sequence to be tested.
    * @param input_length The random sequence length.
    * @param num_rows     The number of matrix rows (M).
    * @param num_columns  The number of matrix columns (Q).
    * 
    * @return True if the the p-value is 0.01 or greater.
    */
   bool
   binary_matrix_rank_test ( const uint8_t input [],
                             size_t input_length,
                             size_t num_rows = 32,
                             size_t num_columns = 32 );

} // nist_sts

#endif // __NIST_STS_BINARY_MATRIX_RANK_HPP_