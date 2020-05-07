#pragma once

#include <string>

#include "domain/CppRestRequest.hpp"
#include "domain/Request.hpp"

namespace getit::domain
{
    class RequestFactory
    {
        public:
            explicit RequestFactory(std::string requestType);
            ~RequestFactory();

            Request* getRequest(std::string method, std::string uri);

        private:
            std::string requestType;
    };
}