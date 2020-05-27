cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

include(FetchContent)

# ------------------------------------------------------------------------------
# Trompeloeil
FetchContent_Declare(
    extern_trompeloeil

    GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
    GIT_TAG        v35)
FetchContent_MakeAvailable(extern_trompeloeil)

# ------------------------------------------------------------------------------
# Catch2
FetchContent_Declare(
    extern_catch2

    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.10.2)
FetchContent_MakeAvailable(extern_catch2)

# ------------------------------------------------------------------------------
# Cpp rest SDK
FetchContent_Declare(
        extern_restsdk

        GIT_REPOSITORY https://github.com/microsoft/cpprestsdk.git
        GIT_TAG        v2.10.16)
FetchContent_MakeAvailable(extern_restsdk)