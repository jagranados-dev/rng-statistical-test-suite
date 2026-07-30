Documentation
=============

This directory contains the configuration required to generate the project's
API documentation using Doxygen.

Dependencies
------------

The documentation generation process requires the following tools:

1. **Doxygen**: Used to parse the source code and generate the HTML documentation.

   Ubuntu/Debian:

       sudo apt update
       sudo apt install doxygen

2. **Graphviz**: Required to generate class, collaboration, include, and call graphs.
   The 'dot' executable must be available in the system PATH.

   Ubuntu/Debian:

       sudo apt install graphviz

Installation Verification
-------------------------

Verify that both tools are correctly installed:

    doxygen --version
    dot -V

Both commands should return a valid version number.

Documentation Output
--------------------

The generated documentation is stored in:

    build/doc/doxygen/html/

The main entry point is:

    build/doc/doxygen/html/index.html

Open this file with any modern web browser.

Automatic Generation
--------------------

When the project is configured with:

    cmake -DNIST_STS_BUILD_DOCS=ON ..

the documentation target is added to the build system.

Depending on the project configuration, the documentation may be generated
automatically as part of the standard build process:

    cmake --build build

Manual Generation
-----------------

If the documentation is not generated automatically, it can always be
generated manually.

Using the CMake Target
~~~~~~~~~~~~~~~~~~~~~~

From the build directory:

    cmake --build . --target doc_doxygen

Or:

    make doc_doxygen

when using the Makefile generator.

Direct Doxygen Execution
~~~~~~~~~~~~~~~~~~~~~~~~

As a fallback, execute Doxygen manually from the documentation build
directory:

    cd build/doc
    doxygen Doxyfile

Troubleshooting
---------------

1. Error: "dot: not found"

   Example:

       sh: 1: dot: not found

   This indicates that Graphviz is not installed or that the 'dot'
   executable is not available in the system PATH.

   Verify the installation:

       dot -V

2. Documentation Is Empty

   Verify that:

   - Source files are located in the directories specified by the INPUT
     option in Doxyfile.in.
   - Source files match the configured file patterns.
   - The project was configured with BUILD_DOCS=ON.

3. Configuration Changes Are Not Applied

   If Doxyfile.in has been modified, reconfigure the project before
   regenerating the documentation:

       cmake -S . -B build

   Then regenerate the documentation.

Notes
-----

The documentation is generated directly from the project's source code and
Doxygen comments. Keeping the documentation comments up to date ensures that
the generated documentation remains accurate, consistent, and useful.