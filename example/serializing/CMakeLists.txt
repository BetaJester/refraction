# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
# for details.

include(FetchContent)
FetchContent_Declare(fmt		GIT_REPOSITORY https://github.com/fmtlib/fmt.git			GIT_TAG master)
FetchContent_Declare(binaryizer GIT_REPOSITORY https://github.com/BetaJester/binaryizer.git GIT_TAG main)
FetchContent_MakeAvailable(fmt binaryizer)

add_executable(bj_refraction_serializing_example "serializing.cpp")
pwropt_target_compile_options(bj_refraction_serializing_example PRIVATE pwr_werror pwr_lefticus)
pwropt_target_cxx_latest(bj_refraction_serializing_example PRIVATE)
target_link_libraries(bj_refraction_serializing_example PRIVATE fmt::fmt bj::refraction bj::binaryizer)