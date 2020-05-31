#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "domain/RequestBody.hpp"
#include "domain/Response.hpp"

namespace getit::domain
{
    class Request
    {
        public:
            Request(const std::string&  method, const std::string&  uri);
            virtual ~Request() = default;

            void addHeader(const std::string& header, const std::string& value);
            void setBody(std::shared_ptr<RequestBody> body);
            virtual void send(std::function<void(Response*)> callback) = 0;

        protected:
            const std::string& method;
            const std::string& uri;
            std::map<std::string, std::string> headers;
            std::shared_ptr<RequestBody> body;
    };
}
