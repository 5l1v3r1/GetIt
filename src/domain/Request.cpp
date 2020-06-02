#include "domain/Request.hpp"

using namespace getit::domain;

Request::Request(const std::string&  method, const std::string&  uri):
    method(method),
    uri(uri)
{

}

void Request::addCookie(const std::string &cookie, const std::string &value)
{
    this->cookies.insert({cookie, value});
}

void Request::addHeader(const std::string& header, const std::string& value)
{
    this->headers.insert({header, value});
}

void Request::setBody(std::shared_ptr<RequestBody> body)
{
    this->body = body;
}
