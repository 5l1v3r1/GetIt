cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(cpprestsdk REQUIRED)
find_package(Boost COMPONENTS thread system chrono REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(SOURCEFILES
    main.cpp
    domain/CppRestRequest.cpp
    domain/FormdataRequestBody.cpp
    domain/Request.cpp
    domain/RequestFactory.cpp
    domain/RawRequestBody.cpp

    gui/widget/BodyWidget/BodyWidget.cpp
    gui/widget/FormdataBodyWidget/FormdataBodyWidget.cpp
    gui/widget/FormdataWidget/FormdataWidget.cpp
    gui/widget/HeadersWidget/HeadersWidget.cpp
    gui/widget/HeaderWidget/HeaderWidget.cpp
    gui/widget/RawBodyWidget/RawBodyWidget.cpp
    gui/widget/ResponseWidget/ResponseWidget.cpp

    gui/window/MainWindow/MainWindow.cpp
)

set(HEADERFILES
    domain/CppRestRequest.hpp
    domain/FormdataRequestBody.hpp
    domain/RawRequestBody.hpp
    domain/Request.hpp
    domain/RequestBody.hpp
    domain/RequestFactory.hpp
    domain/Response.hpp

    gui/widget/BodyWidget/Body.hpp
    gui/widget/BodyWidget/BodyWidget.hpp
    gui/widget/FormdataBodyWidget/FormdataBodyWidget.hpp
    gui/widget/FormdataWidget/FormdataWidget.hpp
    gui/widget/HeadersWidget/HeadersWidget.hpp
    gui/widget/HeadersWidget/HeadersWidget.cpp
    gui/widget/RawBodyWidget/RawBodyWidget.hpp
    gui/widget/ResponseWidget/ResponseWidget.hpp

    gui/window/MainWindow/MainWindow.hpp
)

add_executable(getit
    ${HEADERFILES}
    ${SOURCEFILES}  
)

# Libraries
target_link_libraries(getit Qt5::Widgets)
target_link_libraries(getit cpprestsdk::cpprest)
target_link_libraries(getit Boost::thread Boost::system Boost::chrono)
