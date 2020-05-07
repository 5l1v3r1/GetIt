#pragma once

#include <string>
#include <cpprest/http_client.h>

#include "domain/Request.hpp"

namespace getit::domain
{
    class CppRestRequest: public Request
    {
        public:
            CppRestRequest(std::string method, std::string uri);
            CppRestRequest(std::string method, std::string uri, web::http::client::http_client client);
            ~CppRestRequest() override;

            void send(std::function<void(Response* response)> callback) override;

        private:
            web::http::client::http_client client;

            web::http::http_request buildRequest();
            void addHeadersToRequest(web::http::http_request* request);
            void addBodyToRequest(web::http::http_request* request);
            Response* buildResponse(web::http::http_response restResponse);
    };
}
