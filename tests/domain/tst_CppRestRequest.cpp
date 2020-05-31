#include <catch2/catch.hpp>
#include <cpprest/http_listener.h>
#include <functional>
#include <memory>

#include "domain/CppRestRequest.hpp"
#include "domain/RawRequestBody.hpp"

using namespace getit::domain;
using namespace web::http;
using namespace web::http::experimental::listener;

void sendAndDeleteRequest(Request* request)
{
    bool receivedResponse = false;

    request->send([&](Response* response) {
        receivedResponse = true;
        delete response;
    });

    // Explicitly wait 'till we've received
    // a response from the server before
    // continuing the main loop
    while (!receivedResponse) {}

    // Cleanup after ourselved
    delete request;
}

void listen(http_listener* listener, const std::string& method, const std::function<void(http_request)>& callback)
{
    listener->support(method, [=](http_request request) {
        callback(request);

        request.reply(status_codes::OK);
    });
}

TEST_CASE("CppRestRequest")
{
    // Before
    const auto& uri = "http://localhost:1874/test_resource";
    const auto& requestListener = new http_listener(uri);
    requestListener->open().wait();

    SECTION("send gives the given body straight to the server")
    {
        // Arrange
        const auto& method = "POST";
        const auto& expectedBodyValue = "This is my request body";
        const auto& requestBody = std::make_shared<RawRequestBody>();
        const auto& request = new CppRestRequest(method, uri);

        // Act
        requestBody->setBody(expectedBodyValue);
        request->setBody(requestBody);

        // Assert
        listen(requestListener, methods::POST, [=](http_request request) {
           REQUIRE(expectedBodyValue == request.extract_string().get());
        });

        // Send request
        sendAndDeleteRequest(request);
    }

    SECTION("send gives the correct http method to the server")
    {
        // Arrange
        const auto& expectedMethod = "GET";
        const auto& request = new CppRestRequest(expectedMethod, uri);

        // Assert
        listen(requestListener, expectedMethod, [=](const http_request& request) {
            REQUIRE(expectedMethod == request.method());
        });

        // Send request
        sendAndDeleteRequest(request);
    }

    SECTION("send gives the headers through setHeader to the server")
    {
        // Arrange
        const auto& method = "GET";
        const auto& headerKey = "Accept-Language";
        const auto& headerValue = "EN";
        const auto& request = new CppRestRequest(method, uri);

        // Act
        request->addHeader(headerKey, headerValue);

        // Assert
        listen(requestListener, method, [=](const http_request& request) {
            REQUIRE_FALSE(request.headers().empty());

            bool foundHeader = false;

            for (const auto& [header, value] : request.headers()) {
                if (header == headerKey) {
                    foundHeader = true;

                    REQUIRE(headerValue == value);
                }
            }

            REQUIRE(foundHeader);
        });

        // Send request
        sendAndDeleteRequest(request);
    }

    // After
    requestListener->close().wait();
}
