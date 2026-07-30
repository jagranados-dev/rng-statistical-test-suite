##################################################################################
# MIT License
# Copyright (c) 2026 Jose Alberto Granados
##################################################################################

find_package(Doxygen REQUIRED)

find_program(DOT_EXECUTABLE dot)
if(DOT_EXECUTABLE)
    set(DOXYGEN_HAVE_DOT YES)
else()
    set(DOXYGEN_HAVE_DOT NO)
    message(STATUS "Graphviz was not found; Doxygen diagrams are disabled")
endif()

set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
set(DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
configure_file("${DOXYFILE_IN}" "${DOXYFILE_OUT}" @ONLY)

add_custom_target(nist_sts_docs
    COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYFILE_OUT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Generating ASN.1 API documentation"
    VERBATIM
)

add_custom_target(doc_doxygen DEPENDS nist_sts_docs)
