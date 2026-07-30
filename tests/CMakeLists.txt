##################################################################################
# MIT License
#
# Copyright (c) 2025 Jose Alberto Granados
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
##################################################################################

include(FetchContent)

find_package(Catch2 3.15.2 QUIET)

if(NOT Catch2_FOUND)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.15.2
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(catch2)
endif()

set(NIST_STS_TEST_SOURCES
    approximate_entropy_tests.cpp
    binary_matrix_rank_tests.cpp
    cumulative_sums_tests.cpp
    discrete_fourier_transform.cpp
    frequency_tests.cpp
    linear_complexity_tests.cpp
    non_overlapping_template_tests.cpp
    overlapping_template_tests.cpp
    random_excursions_tests.cpp
    runs_tests.cpp
    serial_tests.cpp
    universal_tests.cpp
)

add_executable(nist_sts_tests ${NIST_STS_TEST_SOURCES})
target_link_libraries(nist_sts_tests PRIVATE Catch2::Catch2WithMain nist_sts::static)
target_compile_features(nist_sts_tests PRIVATE cxx_std_20)

include(Catch)
catch_discover_tests(nist_sts_tests)
