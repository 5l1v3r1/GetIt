#pragma once

#include <boost/format.hpp>
#include <string>
#include <list>
#include <fstream>

#include "domain/RequestBody.hpp"

namespace getit::domain
{
    class FormdataRequestBody: public RequestBody
    {
        public:
            explicit FormdataRequestBody(const std::string& boundary);
            ~FormdataRequestBody() override = default;

            void addElement(const std::string& key, const std::string& value);
            void addFile(const std::string& key, const std::string& filePath);

            std::string getContentType() override;
            std::string getBody() override;
            size_t getSize() override;

        private:
            std::string buildContentData(const std::string& key, const std::string& value);
            std::string buildContentDataFile(const std::string&, const std::string& fileName, const std::string& contents);

            const std::string& boundary;
            std::list<std::string> body;
    };
}