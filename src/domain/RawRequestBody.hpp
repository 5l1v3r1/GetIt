#pragma once

#include <string>

#include "domain/RequestBody.hpp"

namespace getit::domain
{
    class RawRequestBody: public RequestBody
    {
        public:
            explicit RawRequestBody(const std::string& contentType);
            RawRequestBody();
            ~RawRequestBody() override = default;

//            void setContentType(const std::string& contentType);
            void setBody(const std::string& body);
            
            std::string getContentType() override;
            std::string getBody() override;
            size_t getSize() override;

        private:
            const std::string& contentType;
            std::string body;

            inline static const std::string DEF_CONTENT_TYPE = "text/plain";
    };
}