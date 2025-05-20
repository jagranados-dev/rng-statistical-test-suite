/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests.hpp>

#include <cmath>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string_view>
#include <vector>

std::vector < uint8_t >
read_binary_file ( std::string file_path )
{
   auto length = std::filesystem::file_size ( file_path );

   std::vector < uint8_t > buffer ( length );
   std::ifstream file ( file_path, std::ios_base::binary );
   file.read ( reinterpret_cast < char* >( buffer.data () ), length );

   return buffer;
}

void
print_help ( std::string_view program_name )
{
   std::cerr << "Usage: " << program_name << " <binary_file>" << std::endl;
}

void
print_result ( std::string test_name, bool test_result )
{
   std::string test_result_str = ( test_result ) ? "\033[1;32mPASS\033[0m" : "\033[1;31mFAIL\033[0m";
   std::cout << "(" << test_result_str << ") " << test_name << "\n";
}

int
main ( int argc, char** argv )
{
   if ( argc != 2 )
   {
      print_help ( argv [ 0 ] );

      return EXIT_FAILURE;
   }

   std::cout << "NIST SP 800-22 Rev. 1\n"
                "---------------------\n"
                "file: " << argv [ 1 ] <<
                "\n---------------------\n";
   
   using namespace nist::statistical::tests;

   // Input test vector
   auto test_vector = read_binary_file ( argv [ 1 ] );
   auto test_vector_bit_size = test_vector.size () * 8;

   // 01. Frequency (Monobit)
   print_result ( "Frequency (Monobit) Test", 
      frequency_test ( test_vector.data (), test_vector.size () ) );

   // 02. Frequency Test within a Block
   size_t block_size = std::ceil ( test_vector.size () * 8 * 0.01 ) + 1;
   if ( block_size < 20 ) block_size = 20;
   print_result ( "Frequency Test within a Block", 
      frequency_test_within_a_block ( test_vector.data (), test_vector.size (), block_size ) );

   // 03. Runs Test
   print_result ( "Runs Test", 
      runs_test ( test_vector.data (), test_vector.size () ) );

   // 04. Longest Run of Ones in a Block Test
   print_result ( "Longest Run of Ones in a Block Test",
      longest_run_of_ones_test ( test_vector.data (), test_vector.size () ) );

   // 05. Binary Matrix Rank Test
   print_result ( "Binary Matrix Rank Test",
      binary_matrix_rank_test ( test_vector.data (), test_vector.size () ) );

   // 06. Discrete Fourier Transform (Spectral) Test
   print_result ( "Discrete Fourier Transform (Spectral) Test",
      discrete_fourier_transform_test ( test_vector.data (), test_vector.size () ) );

   // 07. Non-Overlapping Template Matching Test
   print_result ( "Non-Overlapping Template Matching Test",
      non_overlapping_template_maching_test ( test_vector.data (), test_vector.size () ) );

   // 08. Overlapping Template Matching Test
   print_result ( "Overlapping Template Matching Test",
      overlapping_template_maching_test ( test_vector.data (), test_vector.size () ) );

   return EXIT_SUCCESS;
}