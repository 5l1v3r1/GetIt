#include <catch2/catch.hpp>
#include <memory>
#include <string>

#include "domain/RawRequestBody.hpp"

using namespace getit::domain;

TEST_CASE("getContentType returns the Content-Type that is set through the constructor")
{
    // Arrange
    const auto& expectedContentType = "application/json";
    const auto& requestBody = std::make_unique<RawRequestBody>(expectedContentType);

    // Act
    const auto& result = requestBody->getContentType();

    // Assert
    REQUIRE(expectedContentType == result);
}

TEST_CASE("getContentType returns default Content-Type when one isn't set through the constructor")
{
    // Arrange
    const auto& expectedDefaultContentType = "text/plain";
    const auto& requestBody = std::make_unique<RawRequestBody>();

    // Act
    const auto& result = requestBody->getContentType();

    // Assert
    REQUIRE(expectedDefaultContentType == result);
}

TEST_CASE("getBody returns string value including linebreaks and tabs")
{
    // Arrange
    const auto& expectedString = "This\nis a\r\nnewline";
    const auto& requestBody = std::make_unique<RawRequestBody>();

    // Act
    requestBody->setBody(expectedString);
    const auto& result = requestBody->getBody();

    // Assert
    REQUIRE(expectedString == result);
}

TEST_CASE("getBody returns empty string when no body is set")
{
    // Arrange
    const auto& expectedEmptyString = "";
    const auto& requestBody = std::make_unique<RawRequestBody>();

    // Act
    const auto& result = requestBody->getBody();

    // Assert
    REQUIRE(expectedEmptyString == result);
}
