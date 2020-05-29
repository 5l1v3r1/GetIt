cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(SOURCEFILES
    main.cpp
    domain/CppRestRequest.cpp
    domain/FormdataRequestBody.cpp
    domain/Request.cpp
    domain/RequestFactory.cpp
    domain/RawRequestBody.cpp

    gui/MainWindow/MainWindow.cpp
)

set(HEADERFILES
    domain/CppRestRequest.hpp
    domain/FormdataRequestBody.hpp
    domain/RawRequestBody.hpp
    domain/Request.hpp
    domain/RequestBody.hpp
    domain/RequestFactory.hpp
    domain/Response.hpp

    gui/MainWindow/MainWindow.hpp
)

add_executable(getit
    ${HEADERFILES}
    ${SOURCEFILES}
)

# Libraries
target_link_libraries(getit cpprest)
target_link_libraries(getit Qt5::Widgets)
