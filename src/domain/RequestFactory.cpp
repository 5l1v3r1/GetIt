#include "domain/RequestFactory.hpp"

using namespace getit::domain;

RequestFactory::RequestFactory(const std::string& requestType):
    requestType(requestType)
{

}

std::shared_ptr<Request> RequestFactory::getRequest(const std::string& method, const std::string& uri)
{
    return std::make_shared<CppRestRequest>(method, uri);
}