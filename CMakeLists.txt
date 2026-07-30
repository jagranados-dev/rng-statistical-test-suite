##################################################################################
# MIT License
# Copyright (c) 2026 Jose Alberto Granados
##################################################################################

cmake_minimum_required(VERSION 3.20)

project(nist_sts
    VERSION 1.0.0
    DESCRIPTION "A Statistical Test Suite for Random Number Generators"
    HOMEPAGE_URL "https://github.com/jagranados-dev/nist-sts"
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if(PROJECT_IS_TOP_LEVEL)
    set(NIST_STS_DEFAULT_DEVELOPER_OPTIONS ON)
else()
    set(NIST_STS_DEFAULT_DEVELOPER_OPTIONS OFF)
endif()

option(NIST_STS_BUILD_DOCS            "Build Doxygen API documentation"                           OFF)
option(NIST_STS_BUILD_TESTS           "Build Catch2 unit and functional tests"                    ${NIST_STS_DEFAULT_DEVELOPER_OPTIONS})
option(NIST_STS_BUILD_EXAMPLES        "Build example executables"                                 ${NIST_STS_DEFAULT_DEVELOPER_OPTIONS})
option(NIST_STS_BUILD_SHARED          "Build the shared library target"                           OFF)
option(NIST_STS_ENABLE_WARNINGS       "Enable strict compiler warnings for project targets"       ${NIST_STS_DEFAULT_DEVELOPER_OPTIONS})
option(NIST_STS_WARNINGS_AS_ERRORS    "Treat project warnings as errors"                          OFF)
option(NIST_STS_ENABLE_SANITIZERS     "Enable AddressSanitizer and UndefinedBehaviorSanitizer"    OFF)
option(NIST_STS_INSTALL               "Generate install and CMake package rules"                  ON)

add_subdirectory(lib)

if(NIST_STS_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

if(NIST_STS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(NIST_STS_BUILD_DOCS)
    add_subdirectory(doc)
endif()

if(NIST_STS_INSTALL)
    set(NIST_STS_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/nist_sts")

    configure_package_config_file(
        cmake/nistStsConfig.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/nistStsConfig.cmake"
        INSTALL_DESTINATION "${NIST_STS_INSTALL_CMAKEDIR}"
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/nistStsConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY SameMajorVersion
    )

    install(
        EXPORT nistStsTargets
        FILE nistStsTargets.cmake
        NAMESPACE nist_sts::
        DESTINATION "${NIST_STS_INSTALL_CMAKEDIR}"
    )

    install(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/nistStsConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/nistStsConfigVersion.cmake"
        DESTINATION "${NIST_STS_INSTALL_CMAKEDIR}"
    )

    install(
        FILES
            README.md
            LICENSE
        DESTINATION "${CMAKE_INSTALL_DOCDIR}"
    )
endif()
