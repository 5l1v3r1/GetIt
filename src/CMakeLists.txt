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
    gui/widget/AuthenticationWidget/AuthenticationWidget.cpp
    gui/widget/BodyWidget/BodyWidget.cpp
    gui/widget/CookiesWidget/CookiesWidget.cpp
    gui/widget/HeadersWidget/HeadersWidget.cpp
    gui/widget/RequestInfoWidget/RequestInfoWidget.cpp
    gui/widget/RequestSettingsWidget/RequestSettingsWidget.cpp
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
    gui/widget/AuthenticationWidget/AuthenticationWidget.hpp
    gui/widget/BodyWidget/BodyWidget.hpp
    gui/widget/CookiesWidget/CookiesWidget.hpp
    gui/widget/HeadersWidget/HeadersWidget.hpp
    gui/widget/RequestInfoWidget/RequestInfoWidget.hpp
    gui/widget/RequestSettingsWidget/RequestSettingsWidget.hpp
    gui/widget/RequestWidget.hpp
    gui/widget/ResponseWidget.hpp
)

add_executable(getit
    ${HEADERFILES}
    ${SOURCEFILES}
    ../resources/resources.qrc
)

# Libraries
target_link_libraries(getit Boost::system)
target_link_libraries(getit cpprest)
target_link_libraries(getit Qt5::Widgets)
