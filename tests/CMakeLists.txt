cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
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
target_link_libraries(getit_tests trompeloeil Catch2::Catch2)
target_link_libraries(getit_tests cpprest)
target_link_libraries(getit_tests Boost::thread Boost::system Boost::chrono)

add_test(NAME getit_tests  COMMAND getit_tests)
