#include <catch2/catch.hpp>
#include <string>

#include "domain/RawRequestBody.hpp"

SCENARIO("Newly constructed RawRequestBody")
{

    WHEN("The contentType is given through the constructor")
    {
        std::string contentType = "application/json";
        auto requestBody = new getit::domain::RawRequestBody(contentType);

        THEN("the given contentType is returned")
        {
            std::string result = requestBody->getContentType();

            REQUIRE(result == contentType);
        }
    }

    WHEN("No contentType is given through the constructor")
    {
        auto requestBody = new getit::domain::RawRequestBody();
        std::string defaultContentType = "text/plain";

        THEN("the default contentType is returned")
        {
            std::string result = requestBody->getContentType();

            REQUIRE(result == defaultContentType);
        }
    }

    WHEN("The data is requested")
    {
        auto requestBody = new getit::domain::RawRequestBody();

        THEN("the output is an empty string")
        {
            std::string result = requestBody->getBody();

            REQUIRE(result == "");
        }

        THEN("the output is zero")
        {
            size_t result = requestBody->getSize();

            REQUIRE(result == 0);
        }
    }
}
