#pragma once

#include <string>
#include <list>
#include <fstream>

#include "domain/RequestBody.hpp"

namespace domain
{
    class FormdataRequestBody: public RequestBody
    {
        public:
            FormdataRequestBody(std::string boundary);
            ~FormdataRequestBody();

            void addElement(std::string key, std::string value);
            void addFile(std::string key, std::string filePath);

            std::string getContentType() override;
            std::string getBody() override;
            size_t getSize() override;

        private:
            std::string buildContentData(std::string key, std::string value);
            std::string buildContentDataFile(std::string key, std::string fileName, std::string contents);

            std::string boundary;
            std::list<std::string> body;
    };
}