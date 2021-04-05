# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
# for details.

include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.x
)
FetchContent_MakeAvailable(Catch2)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${Catch2_SOURCE_DIR}/contrib")
include(Catch)
include(CTest)

add_executable(bj_refraction_tests "main.cpp" "SomeClass.hpp" "basic.cpp" "animals.hpp" "animals.cpp" "voider.cpp" "crc.cpp" "nomacro.cpp")
pwropt_target_compile_options(bj_refraction_tests PRIVATE pwr_werror pwr_lefticus)
pwropt_target_cxx_latest(bj_refraction_tests PRIVATE)
target_link_libraries(bj_refraction_tests PRIVATE Catch2 bj::refraction)

catch_discover_tests(bj_refraction_tests)