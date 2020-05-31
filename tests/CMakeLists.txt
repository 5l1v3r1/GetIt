cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost COMPONENTS thread system chrono REQUIRED)

set(SRCFILES
    ../src/domain/CppRestRequest.cpp
    ../src/domain/FormdataRequestBody.cpp
    ../src/domain/RawRequestBody.cpp
    ../src/domain/Request.cpp
)

set(TST_SRCFILES
    main.cpp
    domain/tst_CppRestRequest.cpp
    domain/tst_FormdataRequestBody.cpp
    domain/tst_RawRequestBody.cpp
)

add_executable(getit_tests ${SRCFILES} ${TST_SRCFILES})

# Include directories for dependencies
include_directories(../src)

# Libraries
target_link_libraries(getit_tests Boost::system)
target_link_libraries(getit_tests cpprest)
target_link_libraries(getit_tests trompeloeil Catch2::Catch2)

add_test(NAME getit_tests  COMMAND getit_tests)