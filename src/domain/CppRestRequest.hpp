#pragma once

#include <boost/format.hpp>
#include <cpprest/http_client.h>
#include <string>
#include <memory>

#include "domain/Request.hpp"

using namespace web::http;

namespace getit::domain
{
    class CppRestRequest: public Request
    {
        public:
            CppRestRequest(const std::string& method, const std::string& uri);
            CppRestRequest(const std::string& method, const std::string& uri, const client::http_client& client);
            ~CppRestRequest() override = default;

            void send(std::function<void(Response*)> callback) override;

        private:
            client::http_client client;

            http_request buildRequest();
            void addCookiesToRequest(http_request* request);
            void addHeadersToRequest(http_request* request);
            void addBodyToRequest(http_request* request);
            static Response* buildResponse(http_response restResponse);
    };
}
