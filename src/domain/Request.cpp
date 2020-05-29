#include "domain/Request.hpp"

#include <utility>

using namespace getit::domain;

Request::Request(const std::string&  method, const std::string&  uri):
    method(method),
    uri(uri)
{

}

void Request::addHeader(const std::string& header, const std::string& value)
{
    this->headers.insert({header, value});
}

void Request::addHeaders(std::map<std::string, std::string> headers)
{
    for (auto const& [header, value]: headers) {
        this->addHeader(header, value);
    }
}

void Request::setBody(RequestBody* body)
{
    this->body = body;
}
