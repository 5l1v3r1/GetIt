cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(GetIt
  VERSION 0.0.1
  DESCRIPTION "REST Client Application"
  HOMEPAGE_URL "https://getit.bartkessels.net"
)

# Variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)

if(APPLE)
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/)
    set(OPENSSL_LIBRARIES /usr/local/opt/openssl/lib)

    include_directories(/usr/local/include)
    include_directories(/usr/local/opt/openssl/include)
endif(APPLE)

# Subdirectories
add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(tests)
