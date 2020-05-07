#pragma once

#include <string>

#include "domain/RequestBody.hpp"

namespace getit::domain
{
    class RawRequestBody: public RequestBody
    {
        public:
            explicit RawRequestBody(std::string contentType);
            RawRequestBody();
            ~RawRequestBody() override;

            void setContentType(std::string contentType);
            void setBody(std::string body);
            
            std::string getContentType() override;
            std::string getBody() override;
            size_t getSize() override;

        private:
            std::string contentType;
            std::string body;

            inline static const std::string DEF_CONTENT_TYPE = "text/plain";
    };
}