##################################################################################
# MIT License
# Copyright (c) 2026 Jose Alberto Granados
##################################################################################

set(NIST_STS_SOURCES
   src/nist_sts/approximate_entropy.cpp
   src/nist_sts/binary_matrix_rank.cpp
   src/nist_sts/cumulative_sums.cpp
   src/nist_sts/discrete_fourier_transform.cpp
   src/nist_sts/frequency.cpp
   src/nist_sts/linear_complexity.cpp
   src/nist_sts/non_overlapping_template.cpp
   src/nist_sts/overlapping_template.cpp
   src/nist_sts/random_excursions.cpp
   src/nist_sts/runs.cpp
   src/nist_sts/serial.cpp
   src/nist_sts/universal.cpp
   src/nist_sts/utilities.cpp
)

add_library(nist_sts_static STATIC ${NIST_STS_SOURCES})
add_library(nist_sts::static ALIAS nist_sts_static)
add_library(nist_sts::nist_sts ALIAS nist_sts_static)

set_target_properties(nist_sts_static PROPERTIES
    OUTPUT_NAME nist_sts
    EXPORT_NAME static
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(nist_sts_static PUBLIC cxx_std_20)
target_include_directories(nist_sts_static
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/nist_sts
)

function(nist_sts_configure_target target)
    if(NIST_STS_ENABLE_WARNINGS)
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4 $<$<BOOL:${NIST_STS_WARNINGS_AS_ERRORS}>:/WX>)
        else()
            target_compile_options(${target} PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                $<$<BOOL:${NIST_STS_WARNINGS_AS_ERRORS}>:-Werror>
            )
        endif()
    endif()

    if(NIST_STS_ENABLE_SANITIZERS)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
            target_link_options(${target} PRIVATE -fsanitize=address,undefined)
        else()
            message(WARNING "NIST_STS_ENABLE_SANITIZERS is supported only by GCC and Clang")
        endif()
    endif()
endfunction()

nist_sts_configure_target(nist_sts_static)

if(NIST_STS_BUILD_SHARED)
    add_library(nist_sts_shared SHARED ${NIST_STS_SOURCES})
    add_library(nist_sts::shared ALIAS nist_sts_shared)

    set_target_properties(nist_sts_shared PROPERTIES
        OUTPUT_NAME nist_sts
        EXPORT_NAME shared
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        CXX_EXTENSIONS OFF
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )

    target_compile_features(nist_sts_shared PUBLIC cxx_std_20)
    target_include_directories(nist_sts_shared
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/nist_sts
    )

    nist_sts_configure_target(nist_sts_shared)
endif()

if(NIST_STS_INSTALL)
    install(
        TARGETS nist_sts_static
        EXPORT nistStsTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    if(TARGET nist_sts_shared)
        install(
            TARGETS nist_sts_shared
            EXPORT nistStsTargets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
    endif()

    install(
        DIRECTORY include/nist_sts
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp"
    )
endif()
