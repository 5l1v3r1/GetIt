#include <boost/format.hpp>
#include <catch2/catch.hpp>
#include <memory>
#include <string>

#include "domain/FormdataRequestBody.hpp"

using namespace getit::domain;

TEST_CASE("getContentType returns the Content-Type header with the boundary given through the constructor")
{
    // Arrange
    const auto& boundary = "my_boundary";
    auto expectedContentType = boost::format("multipart/form-data; boundary=\"%1%\"") % boundary;
    const auto& requestBody = std::make_unique<FormdataRequestBody>(boundary);

    // Act
    const auto& result = requestBody->getContentType();

    // Assert
    REQUIRE(expectedContentType.str() == result);
}

TEST_CASE("getBody returns empty string when no elements or files are added")
{
    // Arrange
    const auto& boundary = "my_boundary";
    const auto& expectedBody = "";
    const auto& requestBody = std::make_unique<FormdataRequestBody>(boundary);

    // Act
    const auto& result = requestBody->getBody();

    // Assert
    REQUIRE(expectedBody == result);
}

TEST_CASE("getBody returns string with unescaped characters in the form-data template")
{
    // Arrange
    const auto& boundary = "my_boundary";
    const auto& formdataKey = "myKey";
    const auto& formdataValue = "&mySpeci@lValu3s!s";
    const auto& requestBody = std::make_unique<FormdataRequestBody>(boundary);
    auto expectedBody = boost::format(
        "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n\r\n--%1%--\r\n"
    ) % boundary % formdataKey % formdataValue;

    // Act
    requestBody->addElement(formdataKey, formdataValue);
    const auto& result = requestBody->getBody();

    // Assert
    REQUIRE(expectedBody.str() == result);
}

TEST_CASE("getBody returns complete form-data template with emtpy file contents for a non-existing file")
{
    // Arrange
    const auto& boundary = "my_boundary";
    const auto& fileName = "My non existing file";
    const auto& nonExistingFilePath = "./non-exsting-file.txt";
    auto expectedBody = boost::format(
        "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\n\r\n\r\n--%1%--\r\n"
    ) % boundary % fileName % nonExistingFilePath;
    const auto& requestBody = std::make_unique<FormdataRequestBody>(boundary);

    // Act
    requestBody->addFile(fileName, nonExistingFilePath);
    const auto& result = requestBody->getBody();

    // Assert
    REQUIRE(expectedBody.str() == result);
}

TEST_CASE("getBody returns complete form-data template with contents of the file for an existing file")
{
    // Arrange
    const auto& boundary = "my_boundary";
    const auto& fileName = "My existing file";
    const auto& existingFilePath = "./tst_file.txt";
    const auto& fileContents = "content";
    auto expectedBody = boost::format(
        "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\n%4%\r\n\r\n--%1%--\r\n"
    ) % boundary % fileName % existingFilePath % fileContents;
    const auto& requestBody = std::make_unique<FormdataRequestBody>(boundary);

    // Act
    requestBody->addFile(fileName, existingFilePath);
    const auto& result = requestBody->getBody();

    // Assert
    REQUIRE(expectedBody.str() == result);
}

TEST_CASE("getBody returns complete form-data template with elements and content of a file for an existing file")
{
    // Arrange
    const auto& boundary = "my_boundary";
    const auto& fileName = "My existing file";
    const auto& existingFilePath = "./tst_file.txt";
    const auto& fileContents = "content";
    const auto& formdataElement = "MyElement";
    const auto& formdataElementValue = "MyElementsValue";
    auto expectedFormdataElementBody = boost::format(
        "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n"
    ) % boundary % formdataElement % formdataElementValue;
    auto expectedFileBody = boost::format(
        "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\n%4%\r\n"
    ) % boundary % fileName % existingFilePath % fileContents;
    auto expectedBody = boost::format(
        "%1%%2%\r\n--%3%--\r\n"
    ) % expectedFileBody % expectedFormdataElementBody % boundary;
    const auto& requestBody = std::make_unique<FormdataRequestBody>(boundary);

    // Act
    requestBody->addFile(fileName, existingFilePath);
    requestBody->addElement(formdataElement, formdataElementValue);
    const auto& result = requestBody->getBody();

    // Assert
    REQUIRE(expectedBody.str() == result);
}

