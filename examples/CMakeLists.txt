##################################################################################
# MIT License
# Copyright (c) 2026 Jose Alberto Granados
##################################################################################

set(NIST_STS_LIB_EXAMPLES
    entropy_validator
)

foreach(example IN LISTS NIST_STS_LIB_EXAMPLES)
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} PRIVATE nist_sts::static)
    target_compile_features(${example} PRIVATE cxx_std_20)
endforeach()
