# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
# for details.

cmake_minimum_required(VERSION 3.19)

project(bj_refraction)

option(BJ_REFRACTION_BUILD_TESTS	"Build tests for bj::refraction"	OFF)
option(BJ_REFRACTION_BUILD_EXAMPLES "Build examples for bj::refraction" OFF)

include(FetchContent)
FetchContent_Declare(pwropt GIT_REPOSITORY https://github.com/BetaJester/pwropt.git GIT_TAG main)
FetchContent_MakeAvailable(pwropt)

add_library(bj_refraction INTERFACE "include/bj/refraction/refractor.hpp" "include/bj/refraction/nameof.hpp")
add_library(bj::refraction ALIAS bj_refraction)
target_include_directories(bj_refraction INTERFACE "include")
pwropt_target_compile_options(bj_refraction INTERFACE pwr_werror pwr_lefticus)
pwropt_target_cxx_latest(bj_refraction INTERFACE)

if (${BJ_REFRACTION_BUILD_TESTS})
	enable_testing()
	add_subdirectory("tests")
endif()

if (${BJ_REFRACTION_BUILD_EXAMPLES})
	add_subdirectory("example")
endif()