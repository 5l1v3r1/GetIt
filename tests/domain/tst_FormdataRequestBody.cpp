#include <catch2/catch.hpp>
#include <string>
#include <boost/format.hpp>

#include "domain/FormdataRequestBody.hpp"

SCENARIO("Newly constructed FormdataRequestBody", "FormdataRequestBody")
{
    std::string boundary = "--abc";

    WHEN("The contentType is requested")
    {
        auto requestBody = new getit::domain::FormdataRequestBody(boundary);

        THEN("the contentType with the given boundary is returned")
        {
            auto expectedContentType = boost::format(
                "multipart/form-data; boundary=\"%1%\""
            ) % boundary;
            
            std::string result = requestBody->getContentType();

            REQUIRE(result == expectedContentType.str());
        }
    }

    WHEN("A value is added to the body")
    {
        auto requestBody = new getit::domain::FormdataRequestBody(boundary);
        const std::string& key = "MyBodyKey";
        const std::string& value = "This&is=My+Body@";
    
        auto expectedOutput = boost::format(
            "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n\r\n--%1%--\r\n"
        ) % boundary % key % value;

        requestBody->addElement(key, value);

        THEN("the body should include the value")
        {
            const std::string& result = requestBody->getBody();

            REQUIRE(result == expectedOutput.str());
        }
    }

    WHEN("A non-existing file is added to the body")
    {
        auto requestBody = new getit::domain::FormdataRequestBody(boundary);
        const std::string& key = "MyFile";
        const std::string& filePath = "../non-existing-file.non_existing_ext";

        auto expectedOutput = boost::format(
            "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\n\r\n\r\n--%1%--\r\n"
        ) % boundary % key % filePath;

        requestBody->addFile(key, filePath);

        THEN("the body should include the file without any data")
        {
            const std::string& result = requestBody->getBody();

            REQUIRE(result == expectedOutput.str());
        }

        THEN("the size of the body should be the same as the size of the expected body")
        {
            const size_t result = requestBody->getSize();

            REQUIRE(result == expectedOutput.str().size());
        }
    }

    WHEN("An existing file is added to the body")
    {
        auto requestBody = new getit::domain::FormdataRequestBody(boundary);
        const std::string& key = "MyFile";
        const std::string& filePath = "./tst_file.txt";

        auto expectedOutput = boost::format(
            "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\ncontent\r\n\r\n--%1%--\r\n"
        ) % boundary % key % filePath;

        requestBody->addFile(key, filePath);

        THEN("the body should include the file with it's contents")
        {
            const std::string& result = requestBody->getBody();

            REQUIRE(result == expectedOutput.str());
        }

        THEN("the size of the body should be the same as the size of the expected body")
        {
            size_t result = requestBody->getSize();

            REQUIRE(result == expectedOutput.str().size());
        }
    }

    WHEN("An existing file and an element are added to the body")
    {
        auto requestBody = new getit::domain::FormdataRequestBody(boundary);

        const std::string& elementKey = "MyBodyKey";
        const std::string& elementValue = "This&is=My+Body@";
        const std::string& fileKey = "MyFile";
        const std::string& filePath = "./tst_file.txt";

        auto expectedElementOutput = boost::format(
            "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n"
        ) % boundary % elementKey % elementValue;

        auto expectedFileOutput = boost::format(
            "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\ncontent\r\n"
        ) % boundary % fileKey % filePath;

        auto expectedOutput = boost::format(
            "%1%%2%\r\n--%3%--\r\n"
        ) % expectedFileOutput % expectedElementOutput % boundary;

        requestBody->addFile(fileKey, filePath);
        requestBody->addElement(elementKey, elementValue);

        THEN("the body should include both the file and value")
        {
            const std::string& result = requestBody->getBody();

            REQUIRE(result == expectedOutput.str());
        }

        THEN("the size of the body should be the sizes of the expected outputs combined")
        {
            size_t result = requestBody->getSize();

            REQUIRE(result == expectedOutput.str().size());
        }
    }
}
