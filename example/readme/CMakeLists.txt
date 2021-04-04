# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
# for details.

add_executable(bj_refraction_readme_example "readme.cpp")
pwropt_target_compile_options(bj_refraction_readme_example PRIVATE pwr_werror pwr_lefticus)
pwropt_target_cxx_latest(bj_refraction_readme_example PRIVATE)
target_link_libraries(bj_refraction_readme_example PRIVATE bj::refraction)