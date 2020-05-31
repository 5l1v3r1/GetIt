#pragma once

#include <memory>
#include <string>

#include "domain/CppRestRequest.hpp"
#include "domain/Request.hpp"

namespace getit::domain
{
    class RequestFactory
    {
        public:
            explicit RequestFactory(const std::string& requestType);
            ~RequestFactory() = default;

            static std::shared_ptr<Request> getRequest(const std::string& method, const std::string& uri);

        private:
            const std::string& requestType;
    };
}