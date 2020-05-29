#pragma once

#include <cpprest/http_client.h>
#include <string>
#include <memory>

#include "domain/Request.hpp"

namespace getit::domain
{
    class CppRestRequest: public Request
    {
        public:
            CppRestRequest(const std::string& method, const std::string& uri);
            CppRestRequest(const std::string& method, const std::string& uri, const web::http::client::http_client& client);
            ~CppRestRequest() override = default;

            void send(std::function<void(Response*)> callback) override;

        private:
            web::http::client::http_client client;

            web::http::http_request buildRequest();
            void addHeadersToRequest(web::http::http_request* request);
            void addBodyToRequest(web::http::http_request* request);
            static Response* buildResponse(web::http::http_response restResponse);
    };
}
